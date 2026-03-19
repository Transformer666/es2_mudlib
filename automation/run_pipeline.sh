#!/bin/bash
# ES2 天朝帝國 — Agent Pipeline
# 使用方式：bash automation/run_pipeline.sh [task_number]
# 例如：bash automation/run_pipeline.sh 1  （只跑 task 01）
#        bash automation/run_pipeline.sh    （跑全部）

set -e

TASK_DIR="automation"
LOG_FILE="docs/pipeline_run.log"
START_TIME=$(date +"%Y-%m-%d %H:%M:%S")

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

log() {
    echo -e "${BLUE}[$(date +"%H:%M:%S")]${NC} $1" | tee -a $LOG_FILE
}

success() {
    echo -e "${GREEN}[OK]${NC} $1" | tee -a $LOG_FILE
}

error() {
    echo -e "${RED}[FAIL]${NC} $1" | tee -a $LOG_FILE
}

warn() {
    echo -e "${YELLOW}[WARN]${NC} $1" | tee -a $LOG_FILE
}

mkdir -p docs

echo "" >> $LOG_FILE
echo "==============================" >> $LOG_FILE
echo "Pipeline start: $START_TIME" >> $LOG_FILE
echo "==============================" >> $LOG_FILE

TASKS=(
    "01_analyze_missing.md:Analyze missing content"
    "02_implement_races.md:Implement race daemons"
    "03_implement_rooms.md:Implement rooms"
    "04_implement_npcs.md:Implement NPCs"
    "05_implement_equipment.md:Implement equipment"
)

SINGLE_TASK=${1:-""}

run_task() {
    local task_file="$1"
    local task_desc="$2"
    local task_path="$TASK_DIR/$task_file"

    if [ ! -f "$task_path" ]; then
        warn "Task file not found, skip: $task_path"
        return 0
    fi

    log "Running task: $task_desc"
    echo "--- Task: $task_desc ---" >> $LOG_FILE

    if claude -p "$(cat $task_path)" \
        --allowedTools "Read,Write,Edit,Glob,Grep,Bash,WebFetch" \
        --max-turns 40 \
        2>&1 | tee -a $LOG_FILE; then
        success "Task done: $task_desc"
    else
        error "Task failed: $task_desc"
        echo "Pipeline halted at $task_desc. See $LOG_FILE for details."
        exit 1
    fi
}

echo ""
echo "========================================="
echo "  ES2 Agent Pipeline"
echo "  Start: $START_TIME"
echo "========================================="
echo ""

if [ -n "$SINGLE_TASK" ]; then
    for task_entry in "${TASKS[@]}"; do
        task_file="${task_entry%%:*}"
        task_desc="${task_entry##*:}"
        task_num="${task_file%%_*}"
        if [ "$task_num" = "$(printf '%02d' $SINGLE_TASK)" ]; then
            run_task "$task_file" "$task_desc"
            exit 0
        fi
    done
    error "Task number not found: $SINGLE_TASK"
    exit 1
else
    for task_entry in "${TASKS[@]}"; do
        task_file="${task_entry%%:*}"
        task_desc="${task_entry##*:}"
        run_task "$task_file" "$task_desc"
        echo ""
    done
fi

END_TIME=$(date +"%Y-%m-%d %H:%M:%S")
log "All tasks completed."

echo ""
echo "========================================="
echo "  Pipeline complete!"
echo "  End: $END_TIME"
echo "========================================="
