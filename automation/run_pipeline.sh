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

    # --- 2a. Rooms + NPCs: analyze then build per area ---
    # Let the agent decide what each area needs based on current state
    for area_dir in mudlib/d/*/; do
        [ -d "$area_dir" ] || continue
        area=$(basename "$area_dir")

        # Skip non-area directories and already complete areas
        case "$area" in
            road|npc|obj) continue ;;
        esac

        run_step "Audit area: $area" \
"審查 mudlib/d/$area/ 區域的完整性，找出缺少的內容。

1. 讀取 automation/CLAUDE.md 的「世界地圖」確認 $area 的地理位置和類型（城鎮/門派HQ/野外）
2. 掃描 mudlib/d/$area/ 列出所有 .c 檔案（房間）
3. 掃描 mudlib/d/$area/npc/ 列出所有 NPC
4. 檢查每個房間的 set(\"exits\") 是否雙向連結
5. 檢查每個房間的 set(\"objects\") 是否指向存在的 NPC 檔案
6. 根據區域類型判斷缺少什麼：
   城鎮至少需要：廣場、街道x2、客棧(INN)、商店、城門、廟(TEMPLE)、客棧老闆、守衛、商人
   門派HQ至少需要：大門、大廳、掌門室、弟子、掌門NPC(含拜師)
   野外至少需要：入口、2-3個場景、怪物NPC(aggressive)
7. 列出缺少的房間和 NPC 清單
8. 如果什麼都不缺，輸出「$area: complete」然後結束
9. 如果有缺少的內容，建立缺少的檔案：
   - 房間：所有出口雙向連結
   - NPC：確認房間有 set(\"objects\") 載入
   - 城隍廟用 inherit TEMPLE
   - 客棧用 inherit INN + valid_startroom + no_fight
   - 掌門 lv50+ 加 vision_of_ghost
   - 野外怪物用 set(\"attitude\", \"aggressive\")
10. 輸出建立了哪些檔案" 25

        # Commit if changes were made
        if git status --porcelain "mudlib/d/$area/" 2>/dev/null | grep -q .; then
            git add "mudlib/d/$area/" 2>/dev/null
            git commit -m "feat: complete area $area (rooms + NPCs)" 2>/dev/null || true
        fi
    done

    # --- 2b. Skills: audit and build missing ones ---
    run_step "Audit skills" \
"審查技能 daemon 的完整性。

1. 列出所有 mudlib/daemon/sect/*.c 中 set(\"skills\") 引用的技能名稱
2. 檢查每個技能名稱是否有對應的 mudlib/daemon/skill/<name>.c（空格換底線）
3. 檢查每個現有 skill daemon 是否有 skill_improved 和 skill_advanced
4. 檢查每個戰鬥技能是否有至少 6 個 actions（grep -c '\"action\"'）
5. 列出所有缺少的技能和不完整的技能
6. 對於缺少的技能（最多處理 3 個），建立 daemon 檔案：
   - 讀取 automation/wiki_reference.md 確認技能屬於哪個門派
   - 參考 mudlib/daemon/skill/fengshan_sword.c（門派武功）或 mudlib/daemon/skill/maoshan_neigong.c（內功）
   - inherit SKILL + register_skill_daemon
   - 戰鬥技能：actions mapping 至少 6 招，門派武功招式用「招式名」
   - 內功：do_exercise + halt_exercise + exert_function
   - skill_improved()（門派用 learn>=1500，基礎用 learn>=500）
   - skill_advanced()（給屬性加成）
7. 輸出：缺少N個、本次建立N個、剩餘N個待下輪處理" 25

    if git status --porcelain mudlib/daemon/skill/ 2>/dev/null | grep -q .; then
        git add mudlib/daemon/skill/ 2>/dev/null
        git commit -m "feat: add missing skill daemons" 2>/dev/null || true
    fi

    # --- 2c. Quests: audit and build ---
    run_step "Audit quests" \
"審查任務系統的完整性。

1. 掃描所有 mudlib/d/*/npc/*.c 中使用 quest/ flag 的 NPC（排除拜師系統的 master）：
   grep -rl 'query(\"quest/' mudlib/d/ | grep -v master
2. 掃描所有 pending/ flag 的使用
3. 讀取 automation/wiki_reference.md 的「雪亭鎮 7 謎」和「五堂鎮 6 謎」
4. 比對哪些謎題已有對應任務，哪些還沒有
5. 對於缺少的任務（最多處理 2 個），選擇最容易實作的：
   - 優先選擇已有 NPC 但缺任務邏輯的（如 girl.c 阿寶）
   - 或建立新的簡單任務（對話 → 跑腿 → 獎勵）
6. 任務實作：
   - NPC 中加 init() 或 add_action 觸發
   - pending/<quest_id> 追蹤進度
   - quest/<quest_id>_done 標記完成
   - gain_score(\"quest\", N) 給獎勵
7. 確認任務 NPC 載入到房間
8. 輸出：已有N個任務、本次新增N個" 25

    if git status --porcelain mudlib/d/ 2>/dev/null | grep -q .; then
        git add mudlib/d/ 2>/dev/null
        git commit -m "feat: add quests" 2>/dev/null || true
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
