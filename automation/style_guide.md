# ES2 LPC 程式碼規範（精簡版）

每次寫 LPC 程式碼時必須遵守以下規則。完整範本見 automation/CLAUDE.md。

## 天條（絕對禁止違反）

1. **不得修改 adm/ 下的核心檔案**（logind.c, combatd.c, chard.c, securityd.c 等），除非明確被要求
2. **不得修改 std/ 下的標準物件**（char.c, room.c, skill.c 等），除非明確被要求
3. **不得修改 feature/ 下的功能模組**（skill.c, combat.c, attack.c 等），除非明確被要求
4. **不得修改 include/ 下的標頭檔**，除非明確被要求
5. **不得修改 data/ 下的玩家存檔和系統資料**（login/, user/, chinese.o 等）
6. **不得修改 obj/login.c, obj/user.c, obj/master.c** 等系統物件
7. **不得引入會導致 compile error 的程式碼** — LPC 不支援 forward reference（函數必須先定義才能呼叫），不支援 `$var` 語法
8. **新增的程式碼不得影響現有玩家的登入、存檔、戰鬥等核心流程**
9. **修改任何檔案前必須先讀取該檔案** — 不可盲目修改
10. **建立 NPC 前必須先搜尋是否已有同名 NPC** — `grep -r 'set_name.*"中文名"' mudlib/d/` 確認無重複
11. **不得在錯誤的位置載入有名字的 NPC** — 有劇情的 NPC 位置由故事決定，不可隨意放

違反天條可能導致：所有玩家無法登入、存檔損壞、遊戲崩潰、NPC 重複。

## 房間 (Room)
- `inherit ROOM`，客棧用 `#include <room.h>` + `inherit INN`
- `set("short", "地名")` + `set("long", @LONG...LONG)`
- `set("exits", ([...]))` — 所有出口必須雙向連結
- `setup()` 結尾，簡單房間加 `replace_program(ROOM)`
- 城隍廟用 `inherit TEMPLE` + `replace_program(TEMPLE)`
- 客棧加 `set("valid_startroom", 1)` + `set("no_fight", 1)`
- 使用 `__DIR__` 做相對路徑

## 技能上限 (Skill Cap / 天賦)
- 每個角色第一次學到技能時，自動 random 一個上限（20 為一階）
- 上限範圍：20/40/60/80/100/120/140/160/180/200
- 代表角色在該技能的天賦天花板
- `skills` 指令會顯示天賦描述：不堪造就(20) → 萬中無一(200)
- `set_skill_cap("skill", N)` 可由特殊事件調整（如任務獎勵）
- `query_skill_cap("skill")` 查詢當前上限
- `advance_skill()` 自動檢查 cap，到達上限不再升級

## NPC
- `#include <npc.h>` + `inherit F_FIGHTER/F_VILLAGER/F_SOLDIER/F_SCHOLAR`
- `set_name("中文", ({"english"}))` + `set_race` + `set_class` + `set_level`
- `set("age", N)` + `set("gender", "male"/"female")` — 用 set() 不是 set_gender()
- `setup()` 後才 `carry_object`/`carry_money`
- 商人加 `inherit F_VENDOR` + `set("merchandise", ([...]))`
- 主動攻擊用 `set("attitude", "aggressive")` — 不是 `set("aggressive", 1)`
- 掌門 lv50+ 加 `set_temp("apply/vision_of_ghost", 1)`
- NPC 裝備放 `npc/obj/` 子目錄

## 武器
- `#include <weapon.h>` + `inherit F_SWORD/F_BLADE/...`
- `set_weight(N)` + `setup_<type>(min, max, wc, reach)`
- `!clonep()` 包裹描述，`set("wield_as", ({"type"}))`

## 防具
- `#include <armor.h>` + `inherit F_CLOTH/F_ARMOR/...`
- `setup_<type>()` + `set("wear_as", "type")`

## 技能 Daemon
- `inherit SKILL` + `DAEMON_D->register_skill_daemon("name")`
- 戰鬥技能：`actions` mapping 至少 6 招 + `attack_using()`
- 門派武功招式用「招式名」包裹
- `damae` 不是 `damage`（歷史拼法，保持一致）
- 必須有 `skill_improved()` + `skill_advanced()`
- 內功：`do_exercise()` + `halt_exercise()` + `exert_function()`

## 禁止事項
- 不可修改 `adm/`、`std/`、`feature/`、`include/` 除非明確要求
- 不可修改 `data/` 玩家存檔
- 出口必須雙向

## 巨集速查
- `STOCK_WEAPON(x)` = `/obj/area/obj/` + x
- `STOCK_ARMOR(x)` = `/obj/area/obj/` + x
- `__DIR__` = 當前檔案目錄
