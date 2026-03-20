#!/bin/bash
# run_qa.sh — Main QA test runner for ES2 MUD
# Usage:
#   bash qa_automation/run_qa.sh [host] [port] [test_name]
# Examples:
#   bash qa_automation/run_qa.sh 35.234.25.153 4000           # run all tests
#   bash qa_automation/run_qa.sh 35.234.25.153 4000 login     # run login only
#   bash qa_automation/run_qa.sh 35.234.25.153 4000 rooms     # run room walk only

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
TESTS_DIR="$SCRIPT_DIR/tests"
REPORTS_DIR="$SCRIPT_DIR/reports"
DATA_DIR="$SCRIPT_DIR/data"

HOST="${1:-35.234.25.153}"
PORT="${2:-4000}"
FILTER="${3:-all}"

REPORT_FILE="$REPORTS_DIR/qa_report.md"
TIMESTAMP=$(date '+%Y-%m-%d %H:%M:%S')

# --------------------------------------------------------------------------
# Pre-flight checks
# --------------------------------------------------------------------------

# Check expect is installed
if ! command -v expect &>/dev/null; then
    echo "ERROR: 'expect' is not installed."
    echo "  macOS:  brew install expect"
    echo "  Ubuntu: sudo apt install -y expect"
    exit 1
fi

# Check test data files exist (only the placeholder header means not generated)
room_lines=$(wc -l < "$DATA_DIR/room_paths.txt" 2>/dev/null || echo "0")
if [[ "$room_lines" -lt 5 ]]; then
    echo "WARNING: Test data files not populated. Running generate_test_data.sh..."
    bash "$SCRIPT_DIR/generate_test_data.sh"
fi

# Create reports directory
mkdir -p "$REPORTS_DIR"

# --------------------------------------------------------------------------
# Initialize report
# --------------------------------------------------------------------------
cat > "$REPORT_FILE" <<EOF
# ES2 MUD QA Report

- **Date**: $TIMESTAMP
- **Host**: $HOST:$PORT
- **Filter**: $FILTER

EOF

# --------------------------------------------------------------------------
# Test mapping (bash 3 compatible — no associative arrays)
# --------------------------------------------------------------------------
get_test_script() {
    case "$1" in
        login)      echo "01_login.exp" ;;
        rooms)      echo "02_room_walk.exp" ;;
        npcs)       echo "03_npc_presence.exp" ;;
        apprentice) echo "04_apprentice.exp" ;;
        vendor)     echo "05_vendor.exp" ;;
        equipment)  echo "06_equipment.exp" ;;
        commands)   echo "07_basic_commands.exp" ;;
        *)          echo "" ;;
    esac
}

ALL_TESTS="login rooms npcs apprentice vendor equipment commands"

# --------------------------------------------------------------------------
# Run tests
# --------------------------------------------------------------------------
TOTAL_FAILURES=0

run_test() {
    local name="$1"
    local script
    script=$(get_test_script "$name")

    if [[ -z "$script" ]]; then
        echo "ERROR: Unknown test '$name'"
        return 1
    fi

    local test_path="$TESTS_DIR/$script"

    if [[ ! -f "$test_path" ]]; then
        echo "ERROR: Test script not found: $test_path"
        return 1
    fi

    echo ""
    echo "================================================================"
    echo "Running: $name ($script)"
    echo "================================================================"

    set +e
    expect "$test_path" "$HOST" "$PORT" "$REPORT_FILE"
    local exit_code=$?
    set -e

    TOTAL_FAILURES=$((TOTAL_FAILURES + exit_code))

    if [[ $exit_code -eq 0 ]]; then
        echo ">>> $name: ALL PASSED"
    else
        echo ">>> $name: $exit_code FAILURE(S)"
    fi

    # Small delay between tests to let MUD clean up sessions
    sleep 2

    return 0
}

if [[ "$FILTER" == "all" ]]; then
    for test_name in $ALL_TESTS; do
        run_test "$test_name"
    done
else
    script=$(get_test_script "$FILTER")
    if [[ -n "$script" ]]; then
        run_test "$FILTER"
    else
        echo "ERROR: Unknown test '$FILTER'"
        echo "Available tests: $ALL_TESTS"
        exit 1
    fi
fi

# --------------------------------------------------------------------------
# Final summary
# --------------------------------------------------------------------------
echo ""
echo "================================================================"
echo "QA Run Complete"
echo "================================================================"
echo "Total failures: $TOTAL_FAILURES"
echo "Report: $REPORT_FILE"
echo ""

if [[ $TOTAL_FAILURES -gt 0 ]]; then
    echo "RESULT: SOME TESTS FAILED ($TOTAL_FAILURES failures)"
else
    echo "RESULT: ALL TESTS PASSED"
fi

# Append final summary to report
cat >> "$REPORT_FILE" <<EOF
---

## Overall Result

- **Total failures**: $TOTAL_FAILURES
- **Completed at**: $(date '+%Y-%m-%d %H:%M:%S')
EOF

exit "$TOTAL_FAILURES"
