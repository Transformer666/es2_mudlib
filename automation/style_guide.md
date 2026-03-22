# ES2 LPC 程式碼規範（精簡版）

每次寫 LPC 程式碼時必須遵守以下規則。完整範本見 automation/CLAUDE.md。

## 房間 (Room)
- `inherit ROOM`，客棧用 `#include <room.h>` + `inherit INN`
- `set("short", "地名")` + `set("long", @LONG...LONG)`
- `set("exits", ([...]))` — 所有出口必須雙向連結
- `setup()` 結尾，簡單房間加 `replace_program(ROOM)`
- 城隍廟用 `inherit TEMPLE` + `replace_program(TEMPLE)`
- 客棧加 `set("valid_startroom", 1)` + `set("no_fight", 1)`
- 使用 `__DIR__` 做相對路徑

## 技能上限 (Skill Cap)
- 拜師時用 `me->set_skill_cap("skill_name", max_level)` 設定上限
- 普通弟子上限建議 60-80，進階路線 100-120
- `advance_skill()` 會自動檢查 cap，超過不會升級
- 未設定 cap 的技能預設上限 200
- 範例（init_apprentice 中）：
  `me->set_skill_cap("fengshan sword", 80);`

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
