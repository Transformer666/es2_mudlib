# ES2 MUD — RD Findings Report

- **Generated**: 2026-03-20
- **Source**: QA automation dry-run analysis (room_paths.txt, npc_rooms.txt, hidden_paths.txt)
- **Scope**: 272 rooms, 535 standard exits, 5 hidden paths, 133 NPCs

---

## Priority 1: Bugs — One-Way Exits (likely unintended)

These exits work in one direction but have no reverse path. Players can get stuck or the world feels inconsistent.

| From | Direction | To | Missing Reverse | Suggested Fix |
|------|-----------|----|-----------------|---------------|
| `/d/snow/tree` | `down` | `/d/snow/square` | `up` not defined in square | Add `climb 榕樹` action in square.c (already exists — OK) |
| `/d/snow/fireplace` | `out` | `/d/snow/inn_kitchen` | `enter` not a standard exit in inn_kitchen | Hidden path `enter 大灶` exists (already exists — OK) |
| `/d/snow/mill` | `out` | `/d/snow/lane2` | `enter` not a standard exit in lane2 | Hidden path `enter 磨坊` exists (already exists — OK) |
| `/d/snow/npath2` | `north` | `/d/month/a1` | a1 has NO exits at all | **BUG**: `/d/month/a1` is a stub with no exits — add `south` exit back |
| `/d/snow/river1` | `north` | `/d/chixiao/river2` | river2 has NO exits at all | **BUG**: `/d/chixiao/river2` is a stub with no exits — add `south` exit back |
| `/d/snow/sgate` | `west` | `/d/newcamp/gate` | gate has NO exits at all | **BUG**: `/d/newcamp/gate` is a stub with no exits — add `east` exit back |
| `/d/lijun/ferry_south` | `north` | `/d/lijun/dock` | dock's `south` goes to riverbank, not ferry_south | By design (ferry) — see Priority 2 |

### Action Required

3 destination rooms are **completely broken stubs with zero exits** — players who enter cannot leave:

1. **`/d/month/a1`** — reached via `/d/snow/npath2` → `north`. Needs at minimum `south → /d/snow/npath2`.
2. **`/d/chixiao/river2`** — reached via `/d/snow/river1` → `north`. Needs at minimum `south → /d/snow/river1`.
3. **`/d/newcamp/gate`** — reached via `/d/snow/sgate` → `west`. Needs at minimum `east → /d/snow/sgate`.

---

## Priority 2: Unimplemented Feature — Ferry Transport

The ferry system between Lijun dock and the south bank has rooms and NPCs in place, but **no transport action** is implemented.

**Current state:**
- `/d/lijun/dock.c` — has ferryman NPC, but no action handler to board/ride the ferry
- `/d/lijun/ferry_south.c` — south bank destination exists, has `north → dock` exit
- `/d/wutang/dock.c` — has ferryman NPC, no transport action
- `/d/lijun/dock.c` exit `south` goes to `riverbank`, not `ferry_south`

**Suggested implementation:**
- Add `add_action("do_ferry", "ride")` or `add_action("do_board", "board")` to dock rooms
- Ferry action sends player to `ferry_south` (or cross-river destination)
- Optionally require payment (ferryman has coins)
- Consider making it NPC-interactive: `ask ferryman about ferry`

---

## Priority 3: Disconnected Areas — Town Stubs

These areas exist in the room graph but have **no inbound connections** from the main world. They appear to be planned but incomplete.

| Area | Rooms | Status |
|------|-------|--------|
| `/d/jingji/` | entrance, inn | 2 rooms, no road connecting to world |
| `/d/longan/` | entrance, inn | 2 rooms, no road connecting to world |
| `/d/weiguo/` | entrance, inn | 2 rooms, no road connecting to world |

**Suggested fix:** Connect each town's entrance to an overworld road (e.g., extend `/d/road/` paths).

---

## Priority 4: Hidden Paths — Discoverability

These 5 rooms are only accessible via `add_action()` commands. Players must know the exact Chinese command to enter. Consider adding in-room hints.

| Room | Access Command | From | Has Hint in Description? |
|------|---------------|------|--------------------------|
| `/d/snow/tree` | `climb 榕樹` | square | Yes — 大榕樹 mentioned in description |
| `/d/snow/ruin2` | `climb 樑柱` | ruin1 | Yes — 斷裂樑柱 mentioned |
| `/d/snow/fireplace` | `enter 大灶` | inn_kitchen | Needs verification — 大灶 should be in description |
| `/d/snow/mill` | `enter 磨坊` | lane2 | Needs verification — 磨坊 should be in description |
| `/d/snow/kitchen` | `climb 圍牆` | epath | Needs verification — 圍牆 should be in description |

**Recommendation:** Ensure each source room's `long` description mentions the interactable object so players can discover the action naturally.

---

## Info: Dead-End Rooms (102 total)

These rooms have only 1 exit. This is normal for leaf rooms (quarters, training grounds, shops, etc.) but worth auditing for gameplay flow. Notable ones:

| Room | Single Exit | Notes |
|------|------------|-------|
| `/d/snow/kitchen` | (NO EXITS in standard graph) | Only accessible/exitable via `climb 圍牆` |
| `/d/chixiao/river2` | (NO EXITS) | **Trap** — see Priority 1 |
| `/d/month/a1` | (NO EXITS) | **Trap** — see Priority 1 |
| `/d/newcamp/gate` | (NO EXITS) | **Trap** — see Priority 1 |
| `/d/wutang/dock` | `east` only | No south/ferry exit — see Priority 2 |

---

## QA Coverage Summary

| Metric | Value |
|--------|-------|
| Total rooms | 272 |
| Reachable from inn_hall (with hidden paths) | 265 (97.4%) |
| Unreachable rooms | 7 |
| Total NPCs | 133 |
| NPCs in reachable rooms | 133 (100%) |
| Standard exits | 535 |
| Hidden action-based exits | 5 |
| One-way exits | 7 (3 are traps) |
| Disconnected town stubs | 3 areas (6 rooms) |
| Ferry destinations (unimplemented) | 1 room |

---

## Appendix: `/d/snow/kitchen.c` Exit Gap

`/d/snow/kitchen.c` is accessible via `climb 圍牆` from `epath.c` and has a reverse `climb 圍牆` back. However, the reverse action is implemented via `add_action` in `kitchen.c` — it does NOT appear in `room_paths.txt` because it's not a standard exit. The QA hidden_paths.txt only lists the forward direction (`epath → kitchen`).

**Action:** Add reverse entry to `hidden_paths.txt`:
```
/d/snow/kitchen	climb 圍牆	/d/snow/epath	climb 圍牆
```
This ensures QA can backtrack properly if DFS enters kitchen first via a different route (currently not possible, but future-proofs the data).
