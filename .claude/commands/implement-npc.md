根據指定的區域建立 NPC。

## 輸入

$ARGUMENTS = 區域名稱（如 "fengshan" 或 "封山派"）

## 步驟

1. 讀取 `automation/wiki_reference.md` 中該門派/區域的相關段落（掌門名稱、職業、技能）
2. 讀取 `automation/CLAUDE.md` 的 NPC 範本（基本型、商人、掌門拜師系統）
3. 掃描 `mudlib/d/$ARGUMENTS/npc/` 目錄，列出已有的 NPC
4. 掃描房間的 `set("objects")` 確認哪些 NPC 已被載入
5. 根據區域類型決定需要哪些 NPC：
   - 門派HQ：掌門（含拜師）、弟子、守衛、雜工
   - 城鎮：商人(F_VENDOR)、守衛、居民、客棧老闆、任務NPC
   - 野外：怪物(F_FIGHTER + aggressive)、動物、旅人
6. 掌門 NPC 必須有完整拜師系統：
   - `set_flag()` / `accept_apprentice()` / `init_apprentice()` / `acquire_skill()`
   - 參考 `mudlib/d/snow/npc/alchemist.c`
7. 確認 NPC 所在房間有 `set("objects", ([ __DIR__"npc/xxx" : 1 ]))`
8. 高等級掌門（lv50+）加 `set_temp("apply/vision_of_ghost", 1)`
9. 野外怪物用 `set("attitude", "aggressive")`（不是 `set("aggressive", 1)`！）
10. 輸出建立了哪些檔案
