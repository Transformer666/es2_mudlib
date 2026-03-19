#!/bin/bash
# ES2 MUD Static Validation Framework
# Usage: bash automation/run_tests.sh [category]
# category: rooms | npcs | daemons | equipment | exits | all (default: all)

MUDLIB="mudlib"
REPORT="docs/test_report.md"
CATEGORY=${1:-"all"}

TOTAL_PASS=0
TOTAL_FAIL=0
TOTAL_WARN=0

GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo "# ES2 MUD Static Validation Report" > $REPORT
echo "Run time: $(date)" >> $REPORT
echo "" >> $REPORT

pass() {
    echo -e "${GREEN}PASS${NC}: $1"
    echo "- PASS: $1" >> $REPORT
    ((TOTAL_PASS++))
}

fail() {
    echo -e "${RED}FAIL${NC}: $1"
    echo "- FAIL: $1" >> $REPORT
    ((TOTAL_FAIL++))
}

warn_msg() {
    echo -e "${YELLOW}WARN${NC}: $1"
    echo "- WARN: $1" >> $REPORT
    ((TOTAL_WARN++))
}

# ========================
# Test: Room files
# ========================
test_rooms() {
    echo "" >> $REPORT
    echo "## Room Validation" >> $REPORT
    echo "=== Validating Rooms ==="

    for file in $(find $MUDLIB/d/ -maxdepth 2 -name "*.c" ! -path "*/npc/*" 2>/dev/null); do
        name=$(basename $file .c)
        dir=$(dirname $file | sed "s|$MUDLIB/||")

        # Check inherit ROOM or INN
        if grep -q 'inherit ROOM\|inherit INN' "$file"; then
            pass "Room inherit: $dir/$name"
        else
            fail "Room inherit missing: $dir/$name"
        fi

        # Check set("short")
        if grep -q 'set("short"' "$file"; then
            pass "Room short desc: $dir/$name"
        else
            fail "Room short desc missing: $dir/$name"
        fi

        # Check setup()
        if grep -q 'setup()' "$file"; then
            pass "Room setup(): $dir/$name"
        else
            fail "Room setup() missing: $dir/$name"
        fi
    done
}

# ========================
# Test: NPC files
# ========================
test_npcs() {
    echo "" >> $REPORT
    echo "## NPC Validation" >> $REPORT
    echo "=== Validating NPCs ==="

    for file in $(find $MUDLIB/d/ -path "*/npc/*.c" ! -path "*/npc/obj/*" 2>/dev/null); do
        name=$(basename $file .c)
        dir=$(dirname $file | sed "s|$MUDLIB/||")

        # Check #include <npc.h>
        if grep -q '#include <npc.h>' "$file"; then
            pass "NPC include: $dir/$name"
        else
            fail "NPC #include <npc.h> missing: $dir/$name"
        fi

        # Check inherit F_FIGHTER/F_VILLAGER/F_SOLDIER/F_SCHOLAR
        if grep -qE 'inherit F_(FIGHTER|VILLAGER|SOLDIER|SCHOLAR|BANDIT)' "$file"; then
            pass "NPC inherit: $dir/$name"
        else
            fail "NPC type inherit missing: $dir/$name"
        fi

        # Check set_name
        if grep -q 'set_name(' "$file"; then
            pass "NPC set_name: $dir/$name"
        else
            fail "NPC set_name missing: $dir/$name"
        fi

        # Check setup()
        if grep -q 'setup()' "$file"; then
            pass "NPC setup(): $dir/$name"
        else
            fail "NPC setup() missing: $dir/$name"
        fi
    done
}

# ========================
# Test: Daemon files
# ========================
test_daemons() {
    echo "" >> $REPORT
    echo "## Daemon Validation" >> $REPORT
    echo "=== Validating Daemons ==="

    # Race daemons
    for file in $MUDLIB/daemon/race/*.c; do
        [ -f "$file" ] || continue
        name=$(basename $file .c)

        if grep -q 'inherit HUMANOID' "$file"; then
            pass "Race daemon inherit: $name"
        else
            fail "Race daemon inherit HUMANOID missing: $name"
        fi

        if grep -q 'register_race_daemon' "$file"; then
            pass "Race daemon register: $name"
        else
            fail "Race daemon register missing: $name"
        fi
    done

    # Skill daemons
    for file in $MUDLIB/daemon/skill/*.c; do
        [ -f "$file" ] || continue
        name=$(basename $file .c)

        if grep -q 'inherit SKILL' "$file"; then
            pass "Skill daemon inherit: $name"
        else
            fail "Skill daemon inherit SKILL missing: $name"
        fi

        if grep -q 'register_skill_daemon' "$file"; then
            pass "Skill daemon register: $name"
        else
            fail "Skill daemon register missing: $name"
        fi
    done

    # Sect daemons
    for file in $MUDLIB/daemon/sect/*.c; do
        [ -f "$file" ] || continue
        name=$(basename $file .c)

        if grep -q 'inherit F_DBASE' "$file"; then
            pass "Sect daemon inherit: $name"
        else
            fail "Sect daemon inherit F_DBASE missing: $name"
        fi

        if grep -q 'register_object_daemon' "$file"; then
            pass "Sect daemon register: $name"
        else
            fail "Sect daemon register missing: $name"
        fi
    done

    # Class daemons
    for file in $MUDLIB/daemon/class/*.c; do
        [ -f "$file" ] || continue
        name=$(basename $file .c)

        if grep -q 'inherit F_DBASE' "$file"; then
            pass "Class daemon inherit: $name"
        else
            fail "Class daemon inherit F_DBASE missing: $name"
        fi

        if grep -q 'query_rank' "$file"; then
            pass "Class daemon query_rank: $name"
        else
            fail "Class daemon query_rank missing: $name"
        fi
    done
}

# ========================
# Test: Equipment files
# ========================
test_equipment() {
    echo "" >> $REPORT
    echo "## Equipment Validation" >> $REPORT
    echo "=== Validating Equipment ==="

    for file in $(find $MUDLIB/d/ -path "*/npc/obj/*.c" 2>/dev/null) \
                $(find $MUDLIB/obj/weapon/ -name "*.c" 2>/dev/null) \
                $(find $MUDLIB/obj/armor/ -name "*.c" 2>/dev/null); do
        [ -f "$file" ] || continue
        name=$(basename $file .c)
        dir=$(dirname $file | sed "s|$MUDLIB/||")

        # Check weapon or armor include
        if grep -q '#include <weapon.h>' "$file"; then
            pass "Weapon include: $dir/$name"
            if grep -qE 'inherit F_(SWORD|BLADE|DAGGER|NEEDLE|STAFF|PIKE|AXE|WHIP|BLUNT)' "$file"; then
                pass "Weapon inherit: $dir/$name"
            else
                fail "Weapon type inherit missing: $dir/$name"
            fi
        elif grep -q '#include <armor.h>' "$file"; then
            pass "Armor include: $dir/$name"
            if grep -qE 'inherit F_(ARMOR|CLOTH|HEAD_EQ|HAND_EQ|FEET_EQ|NECK_EQ|FINGER_EQ|WRIST_EQ|WAIST_EQ|LEG_EQ)' "$file"; then
                pass "Armor inherit: $dir/$name"
            else
                fail "Armor type inherit missing: $dir/$name"
            fi
        else
            warn_msg "No weapon/armor include: $dir/$name (may be a generic item)"
        fi

        # Check setup()
        if grep -q 'setup()' "$file"; then
            pass "Equipment setup(): $dir/$name"
        else
            fail "Equipment setup() missing: $dir/$name"
        fi
    done
}

# ========================
# Test: Bidirectional exits
# ========================
test_exits() {
    echo "" >> $REPORT
    echo "## Exit Bidirectional Validation" >> $REPORT
    echo "=== Validating Bidirectional Exits ==="

    local exit_errors=0

    for file in $(find $MUDLIB/d/ -maxdepth 2 -name "*.c" ! -path "*/npc/*" 2>/dev/null); do
        # Extract exits using grep
        while IFS= read -r line; do
            # Parse direction and target from exit lines
            dir=$(echo "$line" | grep -oP '"(north|south|east|west|northeast|northwest|southeast|southwest|up|down)"' | tr -d '"')
            target=$(echo "$line" | grep -oP ': *[^,)]+' | sed 's/^: *//' | tr -d ' "')

            [ -z "$dir" ] || [ -z "$target" ] && continue

            # Determine reverse direction
            case "$dir" in
                north) rev="south" ;;
                south) rev="north" ;;
                east) rev="west" ;;
                west) rev="east" ;;
                northeast) rev="southwest" ;;
                southwest) rev="northeast" ;;
                northwest) rev="southeast" ;;
                southeast) rev="northwest" ;;
                up) rev="down" ;;
                down) rev="up" ;;
                *) continue ;;
            esac

            # Resolve target path
            if echo "$target" | grep -q '__DIR__'; then
                target_dir=$(dirname "$file")
                target_name=$(echo "$target" | sed 's/__DIR__//' | tr -d '"')
                target_file="$target_dir/$target_name.c"
            elif echo "$target" | grep -q '^/'; then
                target_file="$MUDLIB${target}.c"
            else
                continue
            fi

            # Check if target file has reverse exit back
            if [ -f "$target_file" ]; then
                source_basename=$(basename "$file" .c)
                source_dir=$(dirname "$file")
                if ! grep -q "\"$rev\"" "$target_file" 2>/dev/null; then
                    fail "Exit $dir -> $(basename $target_file .c) has no $rev exit back (from $(basename $file .c))"
                    ((exit_errors++))
                fi
            fi
        done < <(grep -E '"(north|south|east|west|northeast|northwest|southeast|southwest|up|down)"' "$file" 2>/dev/null)
    done

    if [ "$exit_errors" -eq 0 ]; then
        pass "All exits are bidirectional"
    fi
}

# ========================
# Main
# ========================
echo "========================================="
echo "  ES2 MUD Static Validation Framework"
echo "========================================="
echo ""

case $CATEGORY in
    "rooms")     test_rooms ;;
    "npcs")      test_npcs ;;
    "daemons")   test_daemons ;;
    "equipment") test_equipment ;;
    "exits")     test_exits ;;
    "all")
        test_rooms
        test_npcs
        test_daemons
        test_equipment
        test_exits
        ;;
esac

# Summary
echo "" >> $REPORT
echo "## Summary" >> $REPORT
echo "| Result | Count |" >> $REPORT
echo "|--------|-------|" >> $REPORT
echo "| PASS | $TOTAL_PASS |" >> $REPORT
echo "| FAIL | $TOTAL_FAIL |" >> $REPORT
echo "| WARN | $TOTAL_WARN |" >> $REPORT

echo ""
echo "========================================="
echo -e "Done: ${GREEN}$TOTAL_PASS passed${NC} / ${RED}$TOTAL_FAIL failed${NC} / ${YELLOW}$TOTAL_WARN warnings${NC}"
echo "Full report: $REPORT"
echo "========================================="

exit $TOTAL_FAIL
