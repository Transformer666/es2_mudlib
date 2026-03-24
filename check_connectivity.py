#!/usr/bin/env python3
"""ES2 Mudlib World Map Connectivity Checker.

Scans all .c room files under mudlib/d/, extracts exit mappings,
builds a directed graph, and reports connectivity issues.
"""

import os
import re
import sys
from collections import deque

BASE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "mudlib")
D_DIR = os.path.join(BASE, "d")

# Reverse direction map
REVERSE = {
    "north": "south", "south": "north",
    "east": "west", "west": "east",
    "northeast": "southwest", "southwest": "northeast",
    "northwest": "southeast", "southeast": "northwest",
    "up": "down", "down": "up",
    "enter": "out", "out": "enter",
}

def file_to_room(filepath):
    """Convert absolute filepath to MUD room path like /d/snow/square"""
    rel = os.path.relpath(filepath, BASE)
    if rel.endswith(".c"):
        rel = rel[:-2]
    return "/" + rel

def room_to_file(room_path):
    """Convert MUD room path to absolute filepath"""
    return os.path.join(BASE, room_path.lstrip("/") + ".c")

def is_room_file(filepath):
    """Check if a .c file is likely a room (has set("exits", ...))"""
    # We only care about files that have exits - checked during parsing
    return True

def parse_exits(filepath):
    """Parse set("exits", ([...])) from an LPC room file.
    Returns dict of {direction: room_path} or None if no exits found.
    """
    try:
        with open(filepath, "r", encoding="utf-8", errors="replace") as f:
            content = f.read()
    except (IOError, OSError):
        return None

    # Find set("exits", ([...]))
    # Handle multiline: grab from set("exits" to the matching ]))
    m = re.search(r'set\(\s*"exits"\s*,\s*\(\[', content)
    if not m:
        return None

    start = m.end()
    # Find the closing ]))
    end = content.find("]));\n", start)
    if end == -1:
        end = content.find("]))", start)
    if end == -1:
        return None

    block = content[start:end]

    # Determine __DIR__ for this file
    room_path = file_to_room(filepath)
    dir_path = os.path.dirname(room_path) + "/"

    exits = {}
    # Match patterns like:
    #   "direction" : __DIR__"target",
    #   "direction" : "/d/area/room",
    for m2 in re.finditer(
        r'"(\w+)"\s*:\s*(?:__DIR__\s*"([^"]+)"|"(/[^"]+)")',
        block
    ):
        direction = m2.group(1)
        if m2.group(2):
            # __DIR__"target" -> resolve relative to room's directory
            target = dir_path + m2.group(2)
        else:
            target = m2.group(3)
        exits[direction] = target

    return exits if exits else None


def main():
    # Step 1: Find all .c files under d/
    all_c_files = []
    for root, dirs, files in os.walk(D_DIR):
        # Skip npc/, obj/, skill/ subdirectories - they are not rooms
        dirs[:] = [d for d in dirs if d not in ("npc", "obj", "skill")]
        for f in files:
            if f.endswith(".c"):
                all_c_files.append(os.path.join(root, f))

    # Step 2: Parse exits from all room files
    graph = {}  # room_path -> {direction: target_room_path}
    all_rooms = set()

    for filepath in all_c_files:
        exits = parse_exits(filepath)
        if exits:
            room = file_to_room(filepath)
            graph[room] = exits
            all_rooms.add(room)

    print(f"=== ES2 World Map Connectivity Report ===\n")
    print(f"Total room files with exits: {len(all_rooms)}")

    # Step 3: Collect all referenced targets
    all_targets = set()
    for room, exits in graph.items():
        for d, target in exits.items():
            all_targets.add(target)

    # Step 4a: Check missing target files
    missing = []
    for target in sorted(all_targets):
        fpath = room_to_file(target)
        if not os.path.isfile(fpath):
            # Find which rooms reference this missing target
            refs = []
            for room, exits in graph.items():
                for d, t in exits.items():
                    if t == target:
                        refs.append(f"  {room} -> {d} -> {target}")
            missing.append((target, refs))

    print(f"\n--- Missing Exit Targets ({len(missing)}) ---")
    if missing:
        for target, refs in missing:
            for r in refs:
                print(r)
    else:
        print("None - all exit targets exist on disk.")

    # Step 4b: Check one-way exits (no reverse link)
    one_way = []
    for room, exits in sorted(graph.items()):
        for direction, target in sorted(exits.items()):
            rev_dir = REVERSE.get(direction)
            if rev_dir is None:
                # Unknown direction, skip
                continue
            if target not in graph:
                # Target has no exits at all (might be missing or not a room)
                continue
            target_exits = graph[target]
            # Check if target has a reverse exit back to this room
            if rev_dir not in target_exits or target_exits[rev_dir] != room:
                one_way.append((room, direction, target, rev_dir))

    print(f"\n--- One-Way Exits ({len(one_way)}) ---")
    if one_way:
        for room, direction, target, rev_dir in one_way:
            target_exits = graph.get(target, {})
            if rev_dir in target_exits:
                actual = target_exits[rev_dir]
                print(f"  {room} -{direction}-> {target}  (reverse '{rev_dir}' goes to {actual} instead)")
            else:
                print(f"  {room} -{direction}-> {target}  (no '{rev_dir}' exit back)")
    else:
        print("None - all exits are bidirectional.")

    # Step 4c: BFS from /d/snow/square
    start_room = "/d/snow/square"
    if start_room not in graph:
        print(f"\nERROR: Start room {start_room} not found!")
        return

    visited = set()
    queue = deque([start_room])
    visited.add(start_room)
    while queue:
        current = queue.popleft()
        if current not in graph:
            continue
        for direction, target in graph[current].items():
            if target not in visited and target in all_rooms:
                visited.add(target)
                queue.append(target)

    reachable = len(visited)
    unreachable = all_rooms - visited

    print(f"\n--- BFS from {start_room} ---")
    print(f"Reachable rooms: {reachable} / {len(all_rooms)}")

    if unreachable:
        # Group unreachable rooms by area
        areas = {}
        for room in sorted(unreachable):
            parts = room.split("/")
            area = parts[2] if len(parts) > 2 else "unknown"
            areas.setdefault(area, []).append(room)

        print(f"\n--- Unreachable Areas ({len(unreachable)} rooms) ---")
        for area in sorted(areas.keys()):
            rooms = areas[area]
            print(f"  [{area}] ({len(rooms)} rooms):")
            for r in rooms:
                print(f"    {r}")
    else:
        print("\nAll rooms are reachable from the start point!")

    # Step 5: Focus on the three new towns
    print(f"\n--- New Town Connection Check ---")
    new_towns = {
        "shuilan": {
            "label": "水嵐縣",
            "key_exit": ("/d/shuilan/ngate", "northeast", "/d/lijun/ferry_south"),
            "new_rooms": ["dock", "sgate", "market", "teahouse"],
        },
        "luocheng": {
            "label": "羅城",
            "key_exit": ("/d/luocheng/wgate", "southwest", "/d/lee/r2"),
            "new_rooms": ["street2", "egate", "market", "teahouse"],
        },
        "fengcheng": {
            "label": "風城",
            "key_exit": ("/d/fengcheng/sgate", "south", "/d/goathill/peak"),
            "new_rooms": ["ngate", "street2", "market", "forge"],
        },
    }

    for area, info in new_towns.items():
        print(f"\n  [{info['label']}] /d/{area}/")
        src, direction, expected_target = info["key_exit"]

        # Check outbound link
        if src in graph and direction in graph[src]:
            actual_target = graph[src][direction]
            if actual_target == expected_target:
                print(f"    OK: {src} -{direction}-> {expected_target}")
            else:
                print(f"    MISMATCH: {src} -{direction}-> {actual_target} (expected {expected_target})")
        else:
            print(f"    MISSING: {src} has no '{direction}' exit")

        # Check reverse link
        rev_dir = REVERSE.get(direction)
        if expected_target in graph and rev_dir in graph[expected_target]:
            rev_target = graph[expected_target][rev_dir]
            if rev_target == src:
                print(f"    OK: {expected_target} -{rev_dir}-> {src}")
            else:
                print(f"    MISMATCH: {expected_target} -{rev_dir}-> {rev_target} (expected {src})")
        else:
            print(f"    MISSING: {expected_target} has no '{rev_dir}' exit back")

        # Check new rooms exist and are reachable
        for room_name in info["new_rooms"]:
            room_path = f"/d/{area}/{room_name}"
            fpath = room_to_file(room_path)
            exists = os.path.isfile(fpath)
            reachable_flag = room_path in visited
            status = "OK" if (exists and reachable_flag) else ""
            issues = []
            if not exists:
                issues.append("FILE MISSING")
            if not reachable_flag:
                issues.append("UNREACHABLE")
            status = ", ".join(issues) if issues else "OK"
            print(f"    Room {room_name}: {status}")


if __name__ == "__main__":
    main()
