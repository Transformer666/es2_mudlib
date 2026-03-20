#!/bin/bash
# ES2 天朝帝國 — Agent Pipeline (v2: modular small-context tasks)
# 使用方式：bash automation/run_pipeline.sh [phase]
# phase: analyze | build | validate | all (default: all)
# 例如：bash automation/run_pipeline.sh analyze
#        bash automation/run_pipeline.sh build
#        bash automation/run_pipeline.sh validate

set -e
set -o pipefail

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
run_step() {
    local desc="$1"
    local prompt="$2"
    local max_turns="${3:-25}"

    log "Step: $desc"
    echo "--- Step: $desc ---" >> $LOG_FILE

    set +e
    claude -p "$prompt" \
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
    log "=== Phase: Analyze ==="

    run_step "Scan existing content" \
"掃描 mudlib 的現有內容，產生 docs/missing_content.json。

步驟：
1. 讀取 automation/wiki_reference.md 取得應有的種族(11)/職業(7)/門派(18) 清單
2. 掃描現有檔案：
   - ls mudlib/daemon/race/*.c | wc -l（種族）
   - ls mudlib/daemon/class/*.c | wc -l（職業）
   - ls mudlib/daemon/sect/*.c | wc -l（門派）
   - ls mudlib/daemon/skill/*.c | wc -l（技能）
   - find mudlib/d/ -maxdepth 2 -name '*.c' ! -path '*/npc/*' | wc -l（房間）
   - find mudlib/d/ -path '*/npc/*.c' ! -path '*/npc/obj/*' | wc -l（NPC）
3. 比對差異
4. 輸出 docs/missing_content.json，格式：
{
  \"summary\": { \"total_missing\": N },
  \"races\": { \"required\": 11, \"implemented\": N, \"missing\": N },
  \"skills\": { \"implemented\": N, \"missing_list\": [] },
  \"areas\": { \"implemented\": N, \"stub_towns\": [] },
  \"quests\": { \"implemented\": N }
}
5. 在終端輸出摘要" 15
}

# ============================================================
# PHASE 2: BUILD — implement missing content in small steps
# ============================================================
phase_build() {
    log "=== Phase: Build ==="

    # Check what's missing
    if [ ! -f docs/missing_content.json ]; then
        warn "docs/missing_content.json not found, running analyze first."
        phase_analyze
    fi

    # --- 2a. Rooms: one area at a time ---
    # Find stub towns that need expansion
    for area in longan jingji kangping sanyen lee choyin baihua weiguo; do
        room_count=$(find "mudlib/d/$area/" -maxdepth 1 -name "*.c" 2>/dev/null | wc -l | tr -d ' ')
        if [ "$room_count" -lt 5 ]; then
            run_step "Expand area: $area" \
"擴展 mudlib/d/$area/ 區域的房間。

1. 讀取 automation/CLAUDE.md 的「世界地圖」確認 $area 的地理位置
2. 讀取 automation/CLAUDE.md 的「一般房間 (Room)」和「客棧房間 (INN)」範本
3. 掃描 mudlib/d/$area/ 現有的 .c 檔案
4. 這是一個城鎮 stub，至少需要：廣場、街道x2、客棧(INN)、商店、城門
5. 建立缺少的房間，所有出口雙向連結
6. 城隍廟用 inherit TEMPLE（需 #include <room.h>）
7. 客棧用 inherit INN + set(\"valid_startroom\", 1) + set(\"no_fight\", 1)
8. 簡單房間用 replace_program(ROOM)
9. 確認與世界道路 mudlib/d/road/ 的連接正確" 20
            # Commit after each area
            git add "mudlib/d/$area/" 2>/dev/null && \
            git commit -m "feat: expand $area area rooms" 2>/dev/null || true
        fi
    done

    # --- 2b. NPCs: one area at a time ---
    for area in longan jingji kangping sanyen choyin baihua weiguo; do
        npc_count=$(find "mudlib/d/$area/npc/" -name "*.c" ! -path "*/obj/*" 2>/dev/null | wc -l | tr -d ' ')
        if [ "$npc_count" -lt 2 ]; then
            run_step "Add NPCs: $area" \
"為 mudlib/d/$area/ 區域建立 NPC。

1. 讀取 automation/CLAUDE.md 的 NPC 範本
2. 掃描 mudlib/d/$area/npc/ 現有 NPC
3. 掃描 mudlib/d/$area/*.c 房間的 set(\"objects\") 確認已載入的 NPC
4. 城鎮至少需要：客棧老闆(F_VILLAGER)、守衛(F_SOLDIER)、商人(F_VENDOR)
5. 建立 NPC，確認房間有 set(\"objects\") 載入
6. 商人需 inherit F_VENDOR + set(\"merchandise\")
7. 守衛/士兵用 F_SOLDIER
8. 野外怪物用 set(\"attitude\", \"aggressive\")（不是 set(\"aggressive\", 1)！）" 20
            git add "mudlib/d/$area/" 2>/dev/null && \
            git commit -m "feat: add NPCs for $area" 2>/dev/null || true
        fi
    done

    # --- 2c. Skills: one at a time ---
    # Check for missing skill daemons that sects reference
    for sect_file in mudlib/daemon/sect/*.c; do
        [ -f "$sect_file" ] || continue
        skills=$(grep -o '"skills"' "$sect_file" 2>/dev/null)
        [ -z "$skills" ] && continue

        # Extract skill names from sect daemon
        while IFS= read -r skill_name; do
            [ -z "$skill_name" ] && continue
            # Convert skill name to filename
            skill_file="mudlib/daemon/skill/$(echo "$skill_name" | tr ' ' '_').c"
            if [ ! -f "$skill_file" ]; then
                run_step "Create skill: $skill_name" \
"建立技能 daemon: $skill_name

1. 讀取 automation/wiki_reference.md 確認此技能屬於哪個門派
2. 讀取 automation/06_implement_skills.md 的 Step 3A（戰鬥招式規範）
3. 參考 mudlib/daemon/skill/fengshan_sword.c 作為門派武功範本
4. 建立 mudlib/daemon/skill/$(echo "$skill_name" | tr ' ' '_').c
5. 必須有：inherit SKILL、register_skill_daemon、actions mapping（至少6招）
6. 門派武功招式要有獨特招式名（用「」包裹）
7. 必須有 skill_improved() 和 skill_advanced()
8. 門派武功用 learn >= 1500 門檻，基礎武器用 learn >= 500" 20
                git add "mudlib/daemon/skill/" 2>/dev/null && \
                git commit -m "feat: add skill daemon $skill_name" 2>/dev/null || true
            fi
        done < <(grep -A20 '"skills"' "$sect_file" | grep -oP '"[^"]+' | grep -v skills | tr -d '"')
    done

    # --- 2d. Quests: one at a time ---
    quest_count=$(grep -rl 'quest/' mudlib/d/*/npc/*.c 2>/dev/null | grep -v master | wc -l | tr -d ' ')
    if [ "$quest_count" -lt 5 ]; then
        run_step "Add newbie quests" \
"為雪亭鎮新增新手任務。

1. 讀取 automation/wiki_reference.md 的「雪亭鎮 7 謎」
2. 讀取 automation/07_implement_quests.md 的任務模板
3. 掃描 mudlib/d/snow/npc/ 已有的任務 NPC（old_beggar, postman 等）
4. 已完成的謎題：#4（送信）、#5（招兵）
5. 實作 1-2 個新任務（從 #3 搬箱子 或 #6 老宅探險 選一個）
6. 任務 flag：pending/<id> = 進行中、quest/<id>_done = 完成
7. 用 gain_score(\"quest\", N) 給獎勵
8. 確認任務 NPC 載入到房間" 25
        git add mudlib/d/snow/ 2>/dev/null && \
        git commit -m "feat: add newbie quests for xueting" 2>/dev/null || true
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
