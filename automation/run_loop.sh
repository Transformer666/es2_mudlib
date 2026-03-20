#!/bin/bash
# ES2 天朝帝國 — Continuous Agent Pipeline
# 使用方式：bash automation/run_loop.sh [interval_minutes] [max_rounds]
# 例如：bash automation/run_loop.sh 10 5   （每 10 分鐘跑一輪，最多 5 輪）
#        bash automation/run_loop.sh 30      （每 30 分鐘跑一輪，無限）
#        bash automation/run_loop.sh          （預設每 15 分鐘，無限）

INTERVAL=${1:-15}
MAX_ROUNDS=${2:-0}
ROUND=0
LOG_DIR="docs/loop_logs"

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

mkdir -p "$LOG_DIR"

echo ""
echo "========================================="
echo "  ES2 Continuous Agent Pipeline"
echo "  Interval: ${INTERVAL} minutes"
echo "  Max rounds: $([ "$MAX_ROUNDS" -eq 0 ] && echo 'unlimited' || echo $MAX_ROUNDS)"
echo "  Started: $(date)"
echo "  Press Ctrl+C to stop"
echo "========================================="
echo ""

cleanup() {
    echo ""
    echo -e "${YELLOW}[$(date +"%H:%M:%S")]${NC} Pipeline stopped after $ROUND rounds."
    exit 0
}
trap cleanup SIGINT SIGTERM

while true; do
    ROUND=$((ROUND + 1))

    if [ "$MAX_ROUNDS" -gt 0 ] && [ "$ROUND" -gt "$MAX_ROUNDS" ]; then
        echo -e "${GREEN}[$(date +"%H:%M:%S")]${NC} Completed $MAX_ROUNDS rounds. Exiting."
        break
    fi

    ROUND_LOG="$LOG_DIR/round_$(date +"%Y%m%d_%H%M%S").log"

    echo -e "${BLUE}[$(date +"%H:%M:%S")]${NC} === Round $ROUND starting ==="
    echo "Round $ROUND - $(date)" > "$ROUND_LOG"

    # Run the pipeline
    bash automation/run_pipeline.sh 2>&1 | tee -a "$ROUND_LOG"
    EXIT_CODE=${PIPESTATUS[0]}

    if [ "$EXIT_CODE" -eq 0 ]; then
        echo -e "${GREEN}[$(date +"%H:%M:%S")]${NC} Round $ROUND completed successfully."
    else
        echo -e "${YELLOW}[$(date +"%H:%M:%S")]${NC} Round $ROUND finished with warnings (exit: $EXIT_CODE)."
    fi

    # Check if there's more work to do
    # Only stop if total_missing is 0 (all categories complete)
    if [ -f docs/missing_content.json ]; then
        TOTAL_MISSING=$(grep -o '"total_missing":[[:space:]]*[0-9]*' docs/missing_content.json 2>/dev/null | grep -o '[0-9]*$')
        if [ -n "$TOTAL_MISSING" ] && [ "$TOTAL_MISSING" -eq 0 ]; then
            echo -e "${GREEN}[$(date +"%H:%M:%S")]${NC} All content implemented (total_missing=0)! Stopping."
            break
        else
            echo -e "${BLUE}[$(date +"%H:%M:%S")]${NC} Remaining missing items: ${TOTAL_MISSING:-unknown}"
        fi
    fi

    if [ "$MAX_ROUNDS" -gt 0 ] && [ "$ROUND" -ge "$MAX_ROUNDS" ]; then
        echo -e "${GREEN}[$(date +"%H:%M:%S")]${NC} Completed $MAX_ROUNDS rounds. Exiting."
        break
    fi

    echo -e "${BLUE}[$(date +"%H:%M:%S")]${NC} Sleeping ${INTERVAL} minutes before next round..."
    sleep $((INTERVAL * 60))
done

echo ""
echo "========================================="
echo "  Pipeline loop finished"
echo "  Total rounds: $ROUND"
echo "  Ended: $(date)"
echo "========================================="
