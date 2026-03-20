# ES2 MUD — RD Findings Report

- **Generated**: 2026-03-20 (updated)
- **Source**: QA automation dry-run analysis (room_paths.txt, npc_rooms.txt, hidden_paths.txt)
- **Scope**: 291 rooms, 581 standard exits, 5 hidden paths, 155 NPCs

---

## Priority 1: Bugs — Trap Rooms (zero exits)

3 destination rooms have **zero exits** — players who enter **cannot leave**:

| Trap Room | Reached via | Fix |
|-----------|------------|-----|
| `/d/month/a1` | `/d/snow/npath2` → `north` | Add `south → /d/snow/npath2` |
| `/d/chixiao/river2` | `/d/snow/river1` → `north` | Add `south → /d/snow/river1` |
| `/d/newcamp/gate` | `/d/snow/sgate` → `west` | Add `east → /d/snow/sgate` |

---

## Priority 2: Bugs — One-Way Exits (11 total)

These exits work in one direction but the reverse doesn't exist. Players can get lost or the world feels inconsistent.

| From | Direction | To | Issue |
|------|-----------|----|-------|
| `/d/snow/tree` | `down` | `/d/snow/square` | No `up` in square (OK — `climb 榕樹` exists) |
| `/d/snow/fireplace` | `out` | `/d/snow/inn_kitchen` | No `enter` in kitchen (OK — `enter 大灶` exists) |
| `/d/snow/mill` | `out` | `/d/snow/lane2` | No `enter` in lane2 (OK — `enter 磨坊` exists) |
| `/d/snow/npath2` | `north` | `/d/month/a1` | **TRAP** — a1 has 0 exits |
| `/d/snow/river1` | `north` | `/d/chixiao/river2` | **TRAP** — river2 has 0 exits |
| `/d/snow/sgate` | `west` | `/d/newcamp/gate` | **TRAP** — gate has 0 exits |
| `/d/lijun/ferry_south` | `north` | `/d/lijun/dock` | Ferry — dock `south` goes to riverbank |
| `/d/longan/entrance` | `south` | `/d/road/road2` | road2 has no `north → longan` |
| `/d/road/road2` | `west` | `/d/longan/entrance` | longan has no `east → road2` |
| `/d/road/mountain_road2` | `west` | `/d/tianyue/mountain_path` | tianyue has no `east → mountain_road2` |
| `/d/tianyue/mountain_path` | `south` | `/d/road/mountain_road2` | mountain_road2 has no `north → tianyue` |

**Note:** The longan and tianyue connections are mismatched — `road2 ↔ longan` uses `west/south` instead of matching directions, and `mountain_road2 ↔ tianyue` uses `west/south` instead of matching.

---

## Priority 3: Unimplemented Feature — Ferry Transport

The ferry system has rooms and NPCs but **no transport action**.

- `/d/lijun/dock.c` — ferryman NPC, no action handler
- `/d/lijun/ferry_south.c` — south bank, has `north → dock` but dock has no route back
- `/d/wutang/dock.c` — ferryman NPC, no action handler

---

## Priority 4: Disconnected Areas

These areas have no inbound path from the main world:

| Area | Rooms | Status |
|------|-------|--------|
| `/d/jingji/` | entrance, inn | No road connection |
| `/d/weiguo/` | entrance, inn | No road connection |
| `/d/longan/` | 5 rooms (expanded) | Has exits to road2, but bidirectional link broken |
| `/d/tianyue/` | 5 rooms (new area) | Has exits to mountain_road2, but bidirectional link broken |

---

## Priority 5: Hidden Paths (not testable via telnet)

These 5 rooms require Chinese action commands (`climb 榕樹`, `enter 大灶`, etc.) which don't work over macOS telnet (7-bit stripping). They are logged as WARN in QA tests.

| Room | Command | From |
|------|---------|------|
| `/d/snow/tree` | `climb 榕樹` | square |
| `/d/snow/ruin2` | `climb 樑柱` | ruin1 |
| `/d/snow/fireplace` | `enter 大灶` | inn_kitchen |
| `/d/snow/mill` | `enter 磨坊` | lane2 |
| `/d/snow/kitchen` | `climb 圍牆` | epath |

---

## QA Coverage Summary

| Metric | Value |
|--------|-------|
| Total rooms | 291 |
| Reachable via safe DFS | 271 (93.1%) |
| Unreachable rooms | 20 |
| Total NPCs | 155 |
| NPCs in reachable rooms | 144 (92.9%) |
| NPCs in unreachable rooms | 11 |
| Standard exits | 581 |
| Safe (bidirectional) exits | 570 |
| One-way exits (skipped) | 11 |
| Hidden paths (Chinese, skipped) | 5 |
| Estimated test runtime | ~10 min |
