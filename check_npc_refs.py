#!/usr/bin/env python3
"""Check if all NPC object references in stub town room files actually exist."""

import os
import re
import glob

MUDLIB = "/home/arizona_cheng/es2_mudlib/mudlib"
TOWNS = ["longan", "jingji", "kangping", "sanyen", "lee", "choyin", "baihua", "weiguo"]

missing = []

for town in TOWNS:
    town_dir = os.path.join(MUDLIB, "d", town)
    if not os.path.isdir(town_dir):
        print(f"WARNING: town directory not found: {town_dir}")
        continue

    # Get .c files directly in town dir (not in subdirectories)
    room_files = glob.glob(os.path.join(town_dir, "*.c"))

    for room_file in sorted(room_files):
        with open(room_file, "r", encoding="utf-8", errors="replace") as f:
            content = f.read()

        # Find set("objects", ([ ... ])) blocks
        # Match the entire block, allowing nested content
        obj_pattern = re.compile(
            r'set\(\s*"objects"\s*,\s*\(\[\s*(.*?)\s*\]\)\s*\)',
            re.DOTALL
        )

        for m in obj_pattern.finditer(content):
            block = m.group(1)
            # Extract paths: __DIR__"npc/something" : N
            # Also handle cases without __DIR__
            ref_pattern = re.compile(r'__DIR__\s*"([^"]+)"')
            for ref in ref_pattern.finditer(block):
                relative_path = ref.group(1)
                # __DIR__ resolves to /d/<town>/
                resolved = f"/d/{town}/{relative_path}"
                full_path = MUDLIB + resolved + ".c"
                if not os.path.isfile(full_path):
                    rel_room = os.path.relpath(room_file, MUDLIB)
                    missing.append((rel_room, resolved + ".c"))

            # Also check for absolute paths (without __DIR__)
            abs_pattern = re.compile(r'(?<!")(/[^"]+)"')
            # Better: look for string literals that are paths but not preceded by __DIR__
            entry_pattern = re.compile(r'(?<!__DIR__)"(/[^"]+)"\s*:')
            for ref in entry_pattern.finditer(block):
                path = ref.group(1)
                full_path = MUDLIB + path + ".c"
                if not os.path.isfile(full_path):
                    rel_room = os.path.relpath(room_file, MUDLIB)
                    missing.append((rel_room, path + ".c"))

if missing:
    print(f"Found {len(missing)} missing NPC/object file(s):\n")
    for room, ref in missing:
        print(f"  Room: {room}")
        print(f"    Missing: {ref}\n")
else:
    print("All referenced NPC/object files exist.")
