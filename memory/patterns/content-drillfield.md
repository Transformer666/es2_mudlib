# 雪亭練功場 (training ground) — content pattern

A low-level practice area off 雪亭鎮 south gate so newbies can verify the
combat/leveling loop. Built by mirroring existing killable NPCs.

## Files
- `mudlib/d/snow/field.c`   — 雪亭鎮郊野 (郊野). exits: west→sgate, east→drill. objects: rabbit, mouse.
- `mudlib/d/snow/drill.c`   — 雪亭練功場. exits: west→field. objects: dummy.
- `mudlib/d/snow/npc/dummy.c`  — 練功木人 (training dummy).
- `mudlib/d/snow/npc/rabbit.c` — 野兔.
- `mudlib/d/snow/npc/mouse.c`  — 田鼠.
- Wiring edit: `mudlib/d/snow/sgate.c` exits += `"east" : __DIR__"field"` (sgate had north/west/southeast free).

## Verified mudlib facts (source of truth)
- Rooms: bare `inherit ROOM;` works — `globals.h` is GlobalInclude (neolith.conf),
  so `ROOM`, `__DIR__`, `STOCK_*` need no explicit include. NPCs `#include <npc.h>`.
- Respawn: room `set("objects", ([ file : amount ]))` + `std/room.c::reset()` re-clones
  dead/missing NPCs. This is THE respawn mechanism (no per-NPC respawn code needed).
- Fighting allowed unless room sets `no_fight` (cmds/std/kill.c). Training rooms leave it unset.
- Killable NPC shape (escort.c / woman.c / lieutenant.c): set_attr, set_race("human"),
  set_class("commoner"), set_level(N), set_skill(...), setup(). Only race "human" has
  verified attr/stat bases (daemon/race/human.c: attrs 13-18, gin/kee/sen=30, HP=con*5).
- Exp on kill: chard.c make_corpse() reads victim `query("bounty")` and calls
  killer->gain_score(course, amount) per entry. Canonical courses (lieutenant.c):
  `bounty/martial art`, `bounty/martial mastery`. Player also passively gains "survive"
  score while taking damage in kill mode (combat.c).
- F_VILLAGER accept_kill is harmless (no assist); F_SOLDIER calls soldier_assist (avoid for trainers).

## Weakness recipe (newbie must win)
Fresh L1 player: con 13-18 → HP 65-90, kee 30, 0 combat skills.
Mobs set EXPLICIT low attrs to be weaker: dummy con6(HP30)/str5, rabbit con5(HP25)/str4,
mouse con4(HP20)/str5; skills only dodge/unarmed at 3-5; no weapons. Player out-HPs and
out-damages them easily; their hits are trivial.

## Risks / unverified
- Cannot compile-test (no server access). Mirrored escort/woman/lieutenant precisely.
- All mobs are race "human" (only race with verified bases); flavor is in the NAME only
  (野兔/田鼠/木人 are humanoid under the hood). Cosmetic, not a balance issue.
- Auto-leveling needs `target_score` set by the class daemon; commoner.c sets none, so
  exp accrues (score rises) but the auto level-up line in score.c may not trigger for
  pure commoners. Core goal (win kill + gain exp) is satisfied regardless.
