#!/usr/bin/env python3
"""Check bidirectional exit consistency for 8 stub towns."""

import os
import re
import glob

MUDLIB = "/home/arizona_cheng/es2_mudlib/mudlib"
TOWNS = ["longan", "jingji", "kangping", "sanyen", "lee", "choyin", "baihua", "weiguo"]

REVERSE = {
    "north": "south", "south": "north",
    "east": "west", "west": "east",
    "northeast": "southwest", "southwest": "northeast",
    "northwest": "southeast", "southeast": "northwest",
    "enter": "out", "out": "enter",
    "up": "down", "down": "up",
}


def parse_exits(filepath):
    """Parse set("exits", ([ ... ])) from a .c file, return dict of direction->resolved_path."""
    with open(filepath, "r", encoding="utf-8", errors="replace") as f:
        content = f.read()

    # Find the exits block
    m = re.search(r'set\(\s*"exits"\s*,\s*\(\[', content)
    if not m:
        return {}

    # Extract from ([ to ]))
    start = m.end()
    # Find matching ])
    depth = 1
    i = start
    while i < len(content) and depth > 0:
        if content[i:i+2] == '([':
            depth += 1
            i += 2
        elif content[i:i+2] == '])':
            depth -= 1
            i += 2
        else:
            i += 1
    block = content[start:i-2]

    # Determine __DIR__ value from filepath
    # filepath like .../mudlib/d/longan/alley.c -> __DIR__ = "/d/longan/"
    rel = filepath[len(MUDLIB):]  # e.g. /d/longan/alley.c
    dir_val = os.path.dirname(rel) + "/"  # e.g. /d/longan/

    # Parse entries: "direction" : __DIR__"target"  or  "direction" : "/d/road/target"
    exits = {}
    # Match patterns like "north" : __DIR__"street"  or  "east" : "/d/road/road2"
    for em in re.finditer(r'"(\w+)"\s*:\s*(?:__DIR__)?"([^"]+)"', block):
        direction = em.group(1)
        target = em.group(2)
        if not target.startswith("/"):
            # __DIR__ relative
            target = dir_val + target
        exits[direction] = target

    return exits


def resolve_path(target):
    """Convert a mud path to filesystem path."""
    return MUDLIB + target + ".c"


def main():
    # Collect all exits from all town files
    # room_path (mud path without .c) -> {direction: target_mud_path}
    all_exits = {}

    for town in TOWNS:
        town_dir = os.path.join(MUDLIB, "d", town)
        if not os.path.isdir(town_dir):
            print(f"WARNING: Town directory not found: {town_dir}")
            continue
        for cfile in sorted(glob.glob(os.path.join(town_dir, "*.c"))):
            mud_path = cfile[len(MUDLIB):-2]  # strip MUDLIB prefix and .c
            exits = parse_exits(cfile)
            if exits:
                all_exits[mud_path] = exits

    # Check bidirectional consistency
    broken = []

    for room, exits in sorted(all_exits.items()):
        for direction, target in sorted(exits.items()):
            target_file = resolve_path(target)
            rev_dir = REVERSE.get(direction)

            if not os.path.isfile(target_file):
                broken.append({
                    "room": room,
                    "direction": direction,
                    "target": target,
                    "issue": "TARGET FILE MISSING",
                })
                continue

            if rev_dir is None:
                # Unknown direction, can't check reverse
                broken.append({
                    "room": room,
                    "direction": direction,
                    "target": target,
                    "issue": f"UNKNOWN DIRECTION (no reverse mapping for '{direction}')",
                })
                continue

            # Parse target's exits
            target_exits = parse_exits(target_file)
            if rev_dir not in target_exits:
                broken.append({
                    "room": room,
                    "direction": direction,
                    "target": target,
                    "issue": f"NO REVERSE EXIT (target has no '{rev_dir}' exit)",
                })
            elif target_exits[rev_dir] != room:
                broken.append({
                    "room": room,
                    "direction": direction,
                    "target": target,
                    "issue": f"REVERSE MISMATCH (target's '{rev_dir}' -> {target_exits[rev_dir]}, expected {room})",
                })

    # Report
    print("=" * 80)
    print("BIDIRECTIONAL EXIT CONSISTENCY CHECK")
    print(f"Towns checked: {', '.join(TOWNS)}")
    print(f"Rooms scanned: {len(all_exits)}")
    print(f"Broken links found: {len(broken)}")
    print("=" * 80)

    if not broken:
        print("\nAll exits are bidirectionally consistent!")
    else:
        # Group by issue type
        by_type = {}
        for b in broken:
            by_type.setdefault(b["issue"].split("(")[0].strip(), []).append(b)

        for issue_type, items in sorted(by_type.items()):
            print(f"\n--- {issue_type} ({len(items)} issues) ---")
            for b in items:
                print(f"  {b['room']}")
                print(f"    {b['direction']} -> {b['target']}")
                print(f"    Issue: {b['issue']}")
                print()


if __name__ == "__main__":
    main()
