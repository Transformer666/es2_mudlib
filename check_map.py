#!/usr/bin/env python3
"""MUD world map connectivity checker."""

import os
import re
from collections import defaultdict, deque

MUDLIB = "/home/arizona_cheng/es2_mudlib/mudlib"
D_DIR = os.path.join(MUDLIB, "d")
START = "/d/snow/square"

REVERSE_DIR = {
    "north": "south", "south": "north",
    "east": "west", "west": "east",
    "northeast": "southwest", "southwest": "northeast",
    "northwest": "southeast", "southeast": "northwest",
    "up": "down", "down": "up",
    "enter": "out", "out": "enter",
}


def find_all_rooms():
    """Find all .c files under mudlib/d/, excluding npc/ subdirs."""
    rooms = []
    for root, dirs, files in os.walk(D_DIR):
        # Skip npc directories
        rel = os.path.relpath(root, MUDLIB)
        if "/npc" in rel or rel.endswith("npc"):
            continue
        for f in files:
            if f.endswith(".c"):
                # virtual path like /d/snow/square
                full = os.path.join(root, f)
                vpath = "/" + os.path.relpath(full, MUDLIB).replace(".c", "")
                rooms.append(vpath)
    return rooms


def parse_exits(filepath, vpath):
    """Extract exits from a room file."""
    try:
        with open(filepath, "r", encoding="utf-8", errors="replace") as fh:
            content = fh.read()
    except Exception:
        return {}

    # Find set("exits", ([ ... ]));
    # Use a regex that captures the mapping block
    pattern = r'set\(\s*"exits"\s*,\s*\(\[\s*(.*?)\s*\]\)\s*\)'
    m = re.search(pattern, content, re.DOTALL)
    if not m:
        return {}

    block = m.group(1)
    dir_of_file = os.path.dirname(vpath)  # e.g. /d/snow

    exits = {}
    # Match entries like: "direction" : __DIR__"target"  or  "direction" : "/d/area/room"
    entry_pattern = r'"(\w+)"\s*:\s*(?:__DIR__)?"([^"]+)"'
    for em in re.finditer(entry_pattern, block):
        direction = em.group(1)
        target = em.group(2)
        # Check if __DIR__ was used by looking at the raw match
        raw = em.group(0)
        if "__DIR__" in raw:
            target = dir_of_file + "/" + target
        # Normalize: ensure starts with /
        if not target.startswith("/"):
            target = dir_of_file + "/" + target
        exits[direction] = target

    return exits


def main():
    all_rooms = set(find_all_rooms())
    print(f"Total room files found: {len(all_rooms)}")

    # Build graph
    graph = {}  # vpath -> {direction: target_vpath}
    rooms_with_exits = 0
    for vpath in sorted(all_rooms):
        filepath = os.path.join(MUDLIB, vpath.lstrip("/") + ".c")
        exits = parse_exits(filepath, vpath)
        graph[vpath] = exits
        if exits:
            rooms_with_exits += 1

    print(f"Rooms with exits: {rooms_with_exits}")
    print()

    # Check broken exits
    broken = []
    for vpath, exits in sorted(graph.items()):
        for direction, target in sorted(exits.items()):
            target_file = os.path.join(MUDLIB, target.lstrip("/") + ".c")
            if not os.path.exists(target_file):
                broken.append((vpath, direction, target))

    print(f"=== BROKEN EXITS (target file does not exist): {len(broken)} ===")
    for src, d, tgt in broken:
        print(f"  {src} --{d}--> {tgt}  (MISSING)")
    print()

    # Check one-way exits
    oneway = []
    for vpath, exits in sorted(graph.items()):
        for direction, target in sorted(exits.items()):
            if target not in graph:
                continue  # broken exit, already reported
            rev = REVERSE_DIR.get(direction)
            if rev is None:
                # Unknown direction, can't check reverse
                oneway.append((vpath, direction, target, f"unknown reverse for '{direction}'"))
                continue
            target_exits = graph.get(target, {})
            # Check if any exit from target leads back to vpath
            has_reverse = any(t == vpath for t in target_exits.values())
            if not has_reverse:
                # Check if reverse direction specifically exists but points elsewhere
                if rev in target_exits:
                    oneway.append((vpath, direction, target, f"reverse '{rev}' points to {target_exits[rev]}"))
                else:
                    oneway.append((vpath, direction, target, f"no '{rev}' exit in target"))

    print(f"=== ONE-WAY EXITS (no reverse link): {len(oneway)} ===")
    for src, d, tgt, reason in oneway:
        print(f"  {src} --{d}--> {tgt}  ({reason})")
    print()

    # BFS from start
    visited = set()
    queue = deque([START])
    if START in all_rooms:
        visited.add(START)
    else:
        print(f"WARNING: Start room {START} not found!")

    while queue:
        current = queue.popleft()
        for direction, target in graph.get(current, {}).items():
            if target not in visited and target in all_rooms:
                visited.add(target)
                queue.append(target)

    reachable = visited
    unreachable = all_rooms - reachable
    # Only count rooms that have exits (actual rooms, not data files)
    unreachable_rooms = sorted([r for r in unreachable if graph.get(r)])
    unreachable_no_exits = sorted([r for r in unreachable if not graph.get(r)])

    print(f"=== REACHABILITY from {START} ===")
    print(f"  Reachable rooms: {len(reachable)}")
    print(f"  Unreachable rooms (with exits): {len(unreachable_rooms)}")
    print(f"  Unreachable files (no exits, likely not rooms): {len(unreachable_no_exits)}")
    print()

    # Group unreachable rooms by area
    if unreachable_rooms:
        by_area = defaultdict(list)
        for r in unreachable_rooms:
            parts = r.split("/")
            area = parts[2] if len(parts) > 2 else "unknown"
            by_area[area].append(r)

        print(f"=== UNREACHABLE ROOMS BY AREA ({len(by_area)} areas) ===")
        for area in sorted(by_area):
            print(f"  [{area}] ({len(by_area[area])} rooms)")
            for r in sorted(by_area[area]):
                exits_info = graph.get(r, {})
                exits_str = ", ".join(f"{d}->{t}" for d, t in sorted(exits_info.items()))
                print(f"    {r}  exits: {exits_str}")
        print()

    # Find connected components among unreachable rooms
    if unreachable_rooms:
        unvisited = set(unreachable_rooms)
        components = []
        while unvisited:
            start = min(unvisited)
            comp = set()
            q = deque([start])
            comp.add(start)
            while q:
                cur = q.popleft()
                for d, t in graph.get(cur, {}).items():
                    if t in unvisited and t not in comp:
                        comp.add(t)
                        q.append(t)
                # Also check reverse: rooms that point TO cur
                for other in list(unvisited):
                    if other not in comp:
                        for d, t in graph.get(other, {}).items():
                            if t == cur:
                                comp.add(other)
                                q.append(other)
            unvisited -= comp
            components.append(sorted(comp))

        print(f"=== ISOLATED CLUSTERS (among unreachable rooms): {len(components)} ===")
        for i, comp in enumerate(components, 1):
            area_set = set(r.split("/")[2] for r in comp if len(r.split("/")) > 2)
            print(f"  Cluster {i} ({len(comp)} rooms, areas: {', '.join(sorted(area_set))})")
            for r in comp:
                print(f"    {r}")
        print()


if __name__ == "__main__":
    main()
