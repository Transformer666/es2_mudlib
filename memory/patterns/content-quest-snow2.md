# 雪亭鎮新手任務 2/2 (snow_newbie2)

Follow-up to quest 1 (snow_newbie). A herb-fetching errand. Gated on quest 1 completion.

## Flag
Player attribute `quest/snow_newbie2` (int), via `me->set(...)` / `me->query(...)`.
- 0  未開始
- 1  已接任務（須到郊野向老藥農取草藥）
- 2  已取貨（草藥在身上，須帶回藥鋪交給阿杏）
- 3  已完成（領過賞，防止重複領獎）

Gate: 阿杏 only opens the quest when `quest/snow_newbie >= 3` (quest 1 done);
otherwise hints "先去客棧幫張婆婆送點心".

## Files
New:
- `d/snow/npc/axing.c`        — 阿杏 (giver), in 順生堂藥鋪. Opens quest 0→1;
  `accept_object` receives 草藥 (flag 2→3) and pays the reward.
- `d/snow/npc/herbfarmer.c`   — 老藥農 (gather target), in 郊野(field). `ask
  laoyaonong about 草藥` hands over 草藥 and pushes flag 1→2.
- `d/snow/npc/obj/herb_bundle.c` — 草藥, the quest token (id "herb bundle").

Existing-file edits (one line each, objects mapping only):
- `d/snow/herb_shop.c`  + `__DIR__"npc/axing": 1`
- `d/snow/field.c`      + `__DIR__"npc/herbfarmer": 1`

## Player command flow (assuming quest 1 already done: snow_newbie>=3)
1. (in 小藥鋪)  `ask axing about 任務`            -> flag 0→1
2. go south to 草棚 then east to 郊野 (field)
3. (in 郊野)   `ask laoyaonong about 草藥`        -> 老藥農 gives 草藥, flag 1→2
4. return to 小藥鋪 (郊野 west→草棚, north→sstreet1 ... to 廣場 ... 藥鋪)
5. (in 小藥鋪)  `give herb to axing`              -> flag 2→3, reward paid

## Reward (bigger than quest 1's 50 coin + manto)
- 100 coin  (`new("/obj/money/coin")->set_amount(100)`)
- 匕首       (`new("/obj/area/obj/dagger")`)  — basic starter weapon, F_DAGGER
- 山豬果     (`new("/obj/medication/boar_berry")`) — proteins/sen restore
- `gain_score("survive", 200)`

## APIs (mirror quest 1)
- flags: `me->set("quest/snow_newbie2", N)` / `me->query(...)`
- reward move: `if( ob->move(who) ) ob->move(environment());`
- give: `command("give herb bundle to " + who->query("id"))`
- receive: `int accept_object(object who, object ob)` + `ob->id("herb bundle")`
- xp: `who->gain_score("survive", N)` (sig: gain_score(string,int) in feature/char/score.c)

## Robustness
- Anti-double-reward: reward only when flag == 2; sets 3; `>=3` thereafter no-op.
- Lost-token recovery: 老藥農 re-issues 草藥 if flag>=2 and not carrying it.
- 阿杏 accept_object still consumes a non-quest/already-done herb (returns 1) to
  avoid items jamming, but only pays when flag==2.

## Unverified (cannot compile-test per task constraints)
- Compile of all 3 new files (mirrored quest-1 NPCs precisely; same inherits/APIs).
- That `do_chat(({ string, closure, ... }))` mixed array behaves identically here
  (cakegammer.c uses the exact same form, so high confidence).
