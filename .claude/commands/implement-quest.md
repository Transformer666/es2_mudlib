根據描述建立任務。

## 輸入

$ARGUMENTS = 任務描述（如 "雪亭鎮 老宅探險" 或 "xueting riddle 6"）

## 步驟

1. 讀取 `automation/wiki_reference.md` 的「城鎮謎題」和「主線任務」段落
2. 讀取 `automation/07_implement_quests.md` 的任務模板和 flag 慣例
3. 確認任務涉及的區域和 NPC：
   - 已有的 NPC 可以加任務邏輯
   - 需要新 NPC 則建立在 `mudlib/d/<area>/npc/`
4. 任務 flag 慣例：
   - 進行中：`set_temp("pending/<quest_id>", step_number)`
   - 完成：`set("quest/<quest_id>_done", 1)`
5. 任務 NPC 實作模式：
   ```lpc
   void init() {
       ::init();
       // 自動觸發或 add_action
   }
   ```
   - 用 `do_chat()` 做對話
   - 用 `present("item", player)` 檢查物品
   - 用 `gain_score("quest", N)` 給獎勵
6. 如需任務物品，建立在 `npc/obj/` 下
7. 確認任務 NPC 已載入到房間
8. 輸出：任務流程、涉及的 NPC 和物品、獎勵
