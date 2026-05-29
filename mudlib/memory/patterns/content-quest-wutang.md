# Runbook: 五堂鎮支線任務「尋回鏢物」

五堂鎮（`/d/wutang/`）原本沒有任務，本 runbook 記錄已建好的一條 flag-based
支線，給該鎮一個存在的理由（呼應鏢局設定）。完全照雪亭/京畿已驗證的任務
NPC 結構複製。

## 任務設計（旗標：`quest/wutang_cargo`，0→1→2→3）

- **委託人（giver）**：鏢頭 `biaotou`（鎮遠鏢局總鏢頭），放在 `agency.c`。
  - 開任務：`ask biaotou about 任務` → 旗標設 1（**不**交付信物，只指路）。
  - 收貨領賞：玩家把鏢物 `give` 回來 → 旗標 2→3，發賞。
- **取貨對象（holder）**：浣衣婦 `washerwoman`（既有 NPC，加掛任務角色），在 `eastlane`。
  - `ask washerwoman about 鏢物` → 交出鏢物，旗標推進 1→2（推進在 holder，仿 gateman.c）。
- **信物**：鏢物 `escort_cargo`（描金漆盒），`id` 為 `escort cargo`/`cargo`/`lacquer box`。
- **獎勵**（路徑均已 grep 確認存在）：
  - `/obj/money/coin` ->set_amount(200)
  - `/obj/area/obj/dagger`（防身）
  - `/obj/food/mooncake`（充飢）
  - `gain_score("survive", 200)` + `gain_score("explorer fame", 100)`
- **防重複領獎**：`accept_object` 只在 `query("quest/wutang_cargo") == 2` 時推進並發賞；
  其餘情況仍收下信物避免卡物，但不發賞。holder 只在旗標 ==1 時推進。

## 玩家指令流（從接任務到領賞）

1. 在鎮遠鏢局：`ask biaotou about 任務`（旗標 0→1）
2. `south`（到十字路口）→ `east`（到僻靜小巷）
3. `ask washerwoman about 鏢物`（拿到鏢物，旗標 1→2）
4. `west`（回十字路口）→ `north`（回鏢局）
5. `give cargo to biaotou`（旗標 2→3，得銅錢＋匕首＋月餅＋經驗）

## 動到的檔案

- 新增：`d/wutang/npc/biaotou.c`、`d/wutang/npc/obj/escort_cargo.c`
- 改既有：`d/wutang/npc/washerwoman.c`（加 do_ask/init/give_cargo，仿 gateman.c）
- 改既有：`d/wutang/agency.c`（objects mapping 加 `npc/biaotou`）

## 風險 / 待驗

- 未能編譯實測（無 driver）。結構逐行對齊 `d/capital/npc/patrolman.c`+`gateman.c`、
  `d/snow/npc/cakegammer.c`+`axing.c`，理應可編。
- 中文 `ask X about 鏢物` 的 arg 比對沿用既有 NPC 寫法（直接比對整串）；
  若 driver 對中文 argument 斷詞有異，需改用拆字比對。
- `give` 交付走 `accept_object(who, ob)` + `ob->id(...)`，與既有任務一致。

// 對應驗收見 evals/；本檔僅為 runbook。
