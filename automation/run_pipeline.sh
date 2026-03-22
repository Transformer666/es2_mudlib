#!/bin/bash
# ES2 天朝帝國 — Agent Pipeline (v2: modular small-context tasks)
# 使用方式：bash automation/run_pipeline.sh [phase]
# phase: analyze | build | validate | all (default: all)
# 例如：bash automation/run_pipeline.sh analyze
#        bash automation/run_pipeline.sh build
#        bash automation/run_pipeline.sh validate

# No set -e: pipeline must continue even if individual steps fail
# No set -o pipefail: grep in pipes may return 1 when no matches

LOG_FILE="docs/pipeline_run.log"
START_TIME=$(date +"%Y-%m-%d %H:%M:%S")
PHASE=${1:-"all"}
COMPLETED=0
WARNED=0

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

log()     { echo -e "${BLUE}[$(date +"%H:%M:%S")]${NC} $1" | tee -a $LOG_FILE; }
success() { echo -e "${GREEN}[OK]${NC} $1" | tee -a $LOG_FILE; ((COMPLETED++)); }
warn()    { echo -e "${YELLOW}[WARN]${NC} $1" | tee -a $LOG_FILE; ((WARNED++)); }
error()   { echo -e "${RED}[FAIL]${NC} $1" | tee -a $LOG_FILE; }

mkdir -p docs

# Detect git remote
GIT_REMOTE=$(git remote -v | grep -m1 'Transformer666' | awk '{print $1}')
GIT_REMOTE=${GIT_REMOTE:-"origin"}
log "Using git remote: $GIT_REMOTE"

# Pull latest
log "Pulling latest changes..."
git pull "$GIT_REMOTE" main 2>&1 | tee -a $LOG_FILE || warn "Pull failed, continuing with local state."

echo "" >> $LOG_FILE
echo "Pipeline start: $START_TIME (phase: $PHASE)" >> $LOG_FILE
echo "==============================" >> $LOG_FILE

# --- Helper: run a focused claude task ---
# Usage: run_step "description" "prompt" [max_turns]
STYLE_GUIDE="automation/style_guide.md"

run_step() {
    local desc="$1"
    local prompt="$2"
    local max_turns="${3:-25}"

    log "Step: $desc"
    echo "--- Step: $desc ---" >> $LOG_FILE

    # Inject style guide as system prompt so every step follows conventions
    set +e
    claude -p "$prompt" \
        --append-system-prompt "$(cat $STYLE_GUIDE)" \
        --allowedTools "Read" "Write" "Edit" "Glob" "Grep" "Bash" \
        --max-turns "$max_turns" \
        2>&1 | tee -a $LOG_FILE
    local exit_code=${PIPESTATUS[0]}
    set -e

    if [ "$exit_code" -eq 0 ]; then
        success "$desc"
    else
        warn "$desc (exit: $exit_code)"
    fi
}

# ============================================================
# PHASE 1: ANALYZE — scan what's missing
# ============================================================
phase_analyze() {
    log "=== Phase: Analyze (bash-native, no agent) ==="

    local races=$(ls mudlib/daemon/race/*.c 2>/dev/null | wc -l | tr -d ' ')
    local classes=$(ls mudlib/daemon/class/*.c 2>/dev/null | wc -l | tr -d ' ')
    local sects=$(ls mudlib/daemon/sect/*.c 2>/dev/null | wc -l | tr -d ' ')
    local skills=$(ls mudlib/daemon/skill/*.c 2>/dev/null | wc -l | tr -d ' ')
    local rooms=$(find mudlib/d/ -maxdepth 2 -name '*.c' ! -path '*/npc/*' 2>/dev/null | wc -l | tr -d ' ')
    local npcs=$(find mudlib/d/ -path '*/npc/*.c' ! -path '*/npc/obj/*' 2>/dev/null | wc -l | tr -d ' ')
    local quests=$(grep -rl 'query("quest/' mudlib/d/*/npc/*.c 2>/dev/null | grep -v master | wc -l | tr -d ' ')
    local equip=$(find mudlib/d/ -path '*/npc/obj/*.c' 2>/dev/null | wc -l | tr -d ' ')
    local equip2=$(find mudlib/obj/weapon/ mudlib/obj/armor/ -name '*.c' 2>/dev/null | wc -l | tr -d ' ')
    equip=$((equip + equip2))

    # Find stub areas (< 5 rooms)
    local stub_towns=""
    for area_dir in mudlib/d/*/; do
        [ -d "$area_dir" ] || continue
        local area=$(basename "$area_dir")
        case "$area" in road|npc|obj) continue ;; esac
        local rc=$(find "$area_dir" -maxdepth 1 -name "*.c" 2>/dev/null | wc -l | tr -d ' ')
        if [ "$rc" -lt 5 ]; then
            stub_towns="$stub_towns\"$area\","
        fi
    done
    stub_towns="[${stub_towns%,}]"

    # Find missing skills referenced by sects
    # Extract only skill names from set("skills", ({ "xxx", "yyy" })) arrays
    > /tmp/es2_missing_skills.txt
    for sect_file in mudlib/daemon/sect/*.c; do
        [ -f "$sect_file" ] || continue
        # Get lines between "skills" and "})" to only capture the skill array
        sed -n '/"skills"/,/})/p' "$sect_file" 2>/dev/null | \
            grep -o '"[a-z][a-z ]*"' | tr -d '"' | while read sk; do
            [ -z "$sk" ] && continue
            # Skip known non-skill keywords
            case "$sk" in
                skills|class|name|location|paths|english*|sect*) continue ;;
            esac
            local sk_file="mudlib/daemon/skill/$(echo "$sk" | tr ' ' '_').c"
            if [ ! -f "$sk_file" ]; then
                echo "$sk"
            fi
        done
    done | sort -u > /tmp/es2_missing_skills.txt
    local missing_skill_count=$(wc -l < /tmp/es2_missing_skills.txt | tr -d ' ')
    local missing_skills=$(sed 's/.*/"&"/' /tmp/es2_missing_skills.txt | paste -sd',' -)
    missing_skills="[${missing_skills:-}]"

    # Calculate total missing
    local races_missing=$((11 - races))
    [ "$races_missing" -lt 0 ] && races_missing=0
    local classes_missing=$((7 - classes))
    [ "$classes_missing" -lt 0 ] && classes_missing=0
    local sects_missing=$((18 - sects))
    [ "$sects_missing" -lt 0 ] && sects_missing=0
    local total_missing=$((races_missing + classes_missing + sects_missing + missing_skill_count))

    # Write JSON
    cat > docs/missing_content.json << JSONEOF
{
  "summary": {
    "total_missing": $total_missing,
    "races": $races,
    "classes": $classes,
    "sects": $sects,
    "skills": $skills,
    "rooms": $rooms,
    "npcs": $npcs,
    "quests": $quests,
    "equipment": $equip
  },
  "races": { "required": 11, "implemented": $races, "missing": $races_missing },
  "classes": { "required": 7, "implemented": $classes, "missing": $classes_missing },
  "sects": { "required": 18, "implemented": $sects, "missing": $sects_missing },
  "skills": { "implemented": $skills, "missing": $missing_skill_count, "missing_list": $missing_skills },
  "areas": { "implemented": $(ls -d mudlib/d/*/ 2>/dev/null | wc -l | tr -d ' '), "stub_towns": $stub_towns },
  "quests": { "implemented": $quests }
}
JSONEOF

    log "Analyze complete:"
    log "  Races: $races/11 | Classes: $classes/7 | Sects: $sects/18"
    log "  Skills: $skills (missing: $missing_skill_count) | Rooms: $rooms | NPCs: $npcs"
    log "  Quests: $quests | Equipment: $equip"
    log "  Total missing: $total_missing"
    success "Analyze phase"
}

# ============================================================
# PHASE 2: BUILD — implement missing content in small steps
# ============================================================
phase_build() {
    log "=== Phase: Build ==="

    if [ ! -f docs/missing_content.json ]; then
        warn "docs/missing_content.json not found, running analyze first."
        phase_analyze
    fi

    # ================================================================
    # Priority 1: Original ES2 skills (from mudchina/es2)
    # ================================================================
    # List of skills from original ES2 that we're missing (normalized names)
    local missing_original=""
    for sk in hammer lotusforce magic magic_array meihua_shou move music mysterrier mystforce mystsword necromancy nine_moon; do
        if [ ! -f "mudlib/daemon/skill/${sk}.c" ]; then
            missing_original="$missing_original $sk"
        fi
    done

    if [ -n "$missing_original" ]; then
        # Pick first 2 missing skills per round
        local skill_count=0
        for sk in $missing_original; do
            [ "$skill_count" -ge 2 ] && break
            skill_count=$((skill_count + 1))

            # Fetch original source from GitHub as reference
            local sk_hyp=$(echo "$sk" | tr '_' '-')
            local orig_content=""
            orig_content=$(gh api "repos/mudchina/es2/contents/daemon/skill/${sk}.c" --jq '.content' 2>/dev/null | base64 -d 2>/dev/null)
            if [ -z "$orig_content" ]; then
                orig_content=$(gh api "repos/mudchina/es2/contents/daemon/skill/${sk_hyp}.c" --jq '.content' 2>/dev/null | base64 -d 2>/dev/null)
            fi

            run_step "Port original skill: $sk" \
"移植原版 ES2 技能 daemon: $sk

原版程式碼（GBK 簡體，需轉為 UTF-8 繁體）：
\`\`\`
$orig_content
\`\`\`

步驟：
1. 將上面的原版程式碼轉為 UTF-8 繁體中文
2. 建立 mudlib/daemon/skill/${sk}.c
3. 保持原版的 actions/招式/valid_enable/valid_learn 邏輯
4. 確保有 DAEMON_D->register_skill_daemon(\"$(echo $sk | tr '_' ' ')\")
5. 如果原版沒有 skill_improved/skill_advanced，補上：
   - 戰鬥技能：learn >= 500 門檻
   - 內功/法術：learn >= 1500 門檻
6. 注意：原版用連字號（如 chaos-steps），我們用底線（chaos_steps）
   register 時用空格：register_skill_daemon(\"$(echo $sk | tr '_' ' ')\")
7. 輸出建立的檔案" 20

            if git status --porcelain mudlib/daemon/skill/ 2>/dev/null | grep -q .; then
                git add mudlib/daemon/skill/ 2>/dev/null
                git commit -m "feat: port original skill $sk from mudchina/es2" 2>/dev/null || true
            fi
        done
    else
        log "All original skills ported."
    fi

    # ================================================================
    # Priority 1.5: Verify sect martial arts system (拜師/學技能/門派任務)
    # ================================================================
    run_step "Audit sect systems" \
"逐一檢查所有 18 個門派的完整性：拜師系統、技能教學、門派任務。

檢查方式（用 Bash 和 Grep 工具）：

A. 拜師系統驗證 — 對每個 mudlib/daemon/sect/*.c：
1. 讀取 sect daemon 的 set(\"location\") 確認掌門房間路徑
2. 確認該房間檔案存在
3. 確認該房間的 set(\"objects\") 有載入掌門 NPC
4. 確認掌門 NPC 有以下函數（grep 檢查）：
   - accept_apprentice — 接受拜師
   - init_apprentice — 設定 class + title
   - acquire_skill — 傳授技能
   - set_flag — 設定 pending flag
5. 確認 init_apprentice 中 set_class 的值與 sect daemon 的 set(\"class\") 一致

B. 技能教學驗證 — 對每個掌門 NPC：
1. 找出 acquire_skill 中的 switch/case，列出可教的技能名稱
2. 確認每個技能名稱有對應的 mudlib/daemon/skill/<name>.c
3. 確認技能名稱與 sect daemon 的 set(\"skills\", ({...})) 一致
4. 確認技能 daemon 有 actions（戰鬥技能）或 do_exercise（內功）

C. 門派相關任務檢查：
1. 讀取 automation/wiki_reference.md 中各門派的描述
2. 檢查是否有進階路線相關的 NPC 或機制（如虎刀門護衛進階、茅山劍士、軍師轉職）
3. 列出各門派應有但尚未實作的進階/任務系統

D. 修正發現的問題（每輪最多修 3 個）：
- 掌門 acquire_skill 的技能名不匹配 → 修正名稱
- 掌門 init_apprentice 的 class 不匹配 → 修正 class
- 房間沒載入掌門 NPC → 加 set(\"objects\")
- 技能 daemon 不存在 → 報告（由 Priority 1 處理）

輸出格式：
  門派名 | 掌門 | 拜師 | 技能教學 | 進階任務 | 狀態
  -------|------|------|---------|---------|------
  封山派 | OK   | OK   | OK      | 未實作   | PASS
  天月庵 | 缺daemon| -  | -       | -       | FAIL" 25

    if git status --porcelain mudlib/ 2>/dev/null | grep -q .; then
        git add mudlib/ 2>/dev/null
        git commit -m "fix: verify and fix sect apprentice/skill systems" 2>/dev/null || true
    fi

    # ================================================================
    # Priority 2: Quests per area
    # ================================================================
    run_step "Build quests" \
"為各區域建立任務。

1. 讀取 automation/wiki_reference.md 的「城鎮謎題」段落
2. 掃描已有的任務 NPC：
   grep -rl 'query(\"quest/' mudlib/d/ | grep -v master
3. 本輪最多實作 2 個新任務，優先：
   - 雪亭鎮謎題（7個中尚未完成的）
   - 五堂鎮謎題（6個中尚未完成的）

任務實作規範：
- NPC 中加 init() 或 add_action 觸發
- pending/<quest_id> 追蹤進度
- quest/<quest_id>_done 標記完成
- gain_score(\"quest\", N) 給獎勵
- 確認任務 NPC 載入到房間

重要：有些 NPC 不應該常駐在房間裡，而是任務觸發後才出現。
例如：上古妖獸（ritual_monkey 等）應該透過任務或特殊條件召喚，
不應該用 set(\"objects\") 常駐載入。
如果發現這類 NPC，將其從房間的 objects 移除，改為任務觸發機制。" 25

    if git status --porcelain mudlib/d/ 2>/dev/null | grep -q .; then
        git add mudlib/d/ 2>/dev/null
        git commit -m "feat: add quests and fix NPC spawn logic" 2>/dev/null || true
    fi

    # ================================================================
    # Priority 3: NPC spawn audit
    # ================================================================
    run_step "Audit NPC spawns" \
"檢查 NPC 出現的時機和地點是否正確。

1. 找出所有 Boss 級 NPC（set_level >= 40）和上古妖獸：
   grep -rn 'set_level' mudlib/d/*/npc/*.c | 找出 level >= 40 的
2. 檢查這些 Boss NPC 是否被常駐載入（set(\"objects\")）
3. 以下 NPC 不應該常駐在房間，應該改為條件觸發：
   - 上古妖獸：ritual_monkey, inferno_dog, charming_bird, godly_dog,
     frost_frog, evil_hydra, celestial_bull, devilish_tiger
   - Boss：wind_god（風神）
4. 對於不應常駐的 NPC：
   - 從房間的 set(\"objects\") 中移除
   - 在房間加上 detail 描述暗示此處可能有特殊生物
   - 記錄哪些 NPC 被移除，等任務系統實作後再加入觸發機制
5. 檢查所有野外怪物是否有 set(\"attitude\", \"aggressive\")（不是 set(\"aggressive\", 1)）
6. 輸出修改清單" 20

    if git status --porcelain mudlib/d/ 2>/dev/null | grep -q .; then
        git add mudlib/d/ 2>/dev/null
        git commit -m "fix: audit NPC spawns and remove always-loaded bosses" 2>/dev/null || true
    fi

    # ================================================================
    # Priority 4: Stub area expansion (if any left)
    # ================================================================
    local stub_list=""
    if [ -f docs/missing_content.json ]; then
        stub_list=$(cat docs/missing_content.json | tr -d ' \n' | grep -o '"stub_towns":\[[^]]*\]' | grep -o '"[a-z_]*"' | tr -d '"')
    fi
    if [ -n "$stub_list" ]; then
        local area_count=0
        for area in $stub_list; do
            [ "$area_count" -ge 2 ] && break
            area_count=$((area_count + 1))

            run_step "Expand area: $area" \
"擴展 mudlib/d/$area/ 區域。

1. 讀取 automation/CLAUDE.md 的「世界地圖」確認位置
2. 掃描現有房間和 NPC
3. 城鎮需要：廣場、街道、客棧(INN)、商店、城門、廟(TEMPLE)
4. 建立缺少的內容，所有出口雙向連結
5. 城隍廟用 inherit TEMPLE，客棧用 inherit INN" 20

            if git status --porcelain "mudlib/d/$area/" 2>/dev/null | grep -q .; then
                git add "mudlib/d/$area/" 2>/dev/null
                git commit -m "feat: expand area $area" 2>/dev/null || true
            fi
        done
    fi
}

# ============================================================
# PHASE 3: VALIDATE — check everything
# ============================================================
phase_validate() {
    log "=== Phase: Validate ==="

    run_step "Static validation" \
"對 mudlib 執行靜態驗證。

用 Bash 工具執行 automation/run_tests.sh all，然後報告結果。
額外檢查：
1. grep -r 'set(\"aggressive\", 1)' mudlib/d/ — 應該為 0（要用 attitude）
2. 所有 daemon/skill/*.c 有 skill_improved — 用 grep -c 檢查
3. 所有 lv50+ 掌門有 vision_of_ghost
報告 PASS/FAIL 數量。" 10
}

# ============================================================
# MAIN
# ============================================================
echo ""
echo "========================================="
echo "  ES2 Agent Pipeline v2"
echo "  Phase: $PHASE"
echo "  Start: $START_TIME"
echo "========================================="
echo ""

case $PHASE in
    analyze)  phase_analyze ;;
    build)    phase_build ;;
    validate) phase_validate ;;
    all)
        phase_analyze
        phase_build
        phase_validate
        ;;
    *)
        error "Unknown phase: $PHASE (use: analyze|build|validate|all)"
        exit 1
        ;;
esac

END_TIME=$(date +"%Y-%m-%d %H:%M:%S")
log "Pipeline complete: $COMPLETED ok, $WARNED warnings."

# Final commit for any remaining changes
CHANGED=$(git status --porcelain mudlib/ docs/ | wc -l | tr -d ' ')
if [ "$CHANGED" -gt "0" ]; then
    git add mudlib/d/ mudlib/daemon/ mudlib/obj/ mudlib/doc/ docs/ 2>/dev/null || true
    STAGED=$(git diff --cached --name-only | wc -l | tr -d ' ')
    if [ "$STAGED" -gt "0" ]; then
        git commit -m "feat: auto-implement content via pipeline v2 [$END_TIME]

Phase: $PHASE | Completed: $COMPLETED | Warnings: $WARNED

Co-Authored-By: Claude Code Agent <noreply@anthropic.com>"
        git push "$GIT_REMOTE" main || warn "Push failed."
        success "Final commit pushed to $GIT_REMOTE."
    fi
fi

echo ""
echo "========================================="
echo "  Pipeline complete!"
echo "  Completed: $COMPLETED | Warnings: $WARNED"
echo "  End: $END_TIME"
echo "========================================="
