# Runbook: 主線任務二「殘卷尋蹤」

承接主線一「卯木之兆」(`content-quest-main1.md`)﹐推進「侮天鬼 / 聖木 / 十三靈」
大敘事。機制上是一條 gated 的 2-step flag quest﹐照雪亭/京畿已驗證的任務 NPC
結構（`keeper.c`+`clerk.c`、`cakegammer.c`+`afu`）逐行複製。**未編譯實測**。

## 故事定位

- 承接：主線一結尾﹐師爺提到「斐縣同僚也遇怪事、封山派在查老榕」﹐廟祝叮囑
  「卯木之事怕還沒完」。本任務即玩家循此線索找上封山派。
- 委託人：封山派藏劍堂師叔「陸抱朴」(青嶂峰﹐喬陰城東)﹐私下追查三百年前
  皇城聖木被斷、侮天鬼破土的舊案。手有半部《封鬼遺錄》﹐缺記「斷木放出何物」
  的殘卷——該殘卷被人攜往喬陰縣衙存查。
- 送達對象：喬陰縣衙掌卷老書吏「韓書吏」。(縣衙差役 chat 早已埋了「縣太爺
  三日後審老松寨案」的鉤子﹐殘卷正是審案時翻出。)
- 結尾鉤子（鋪 beat 3）：殘卷殘文「聖木既斷﹐其下所鎮之十三 ... 出 ...
  非火非水可滅」——點出「十三靈」﹔陸抱朴領賞對白「那物只怕從未真正被鎮住 ...
  老朽還得稟過掌門﹐再從長計議」。

## 任務設計（旗標：`quest/main_omen2`﹐0→1→2→3﹔gated on `quest/main_omen>=3`）

- **入門 gate**：`elder.c` 的 `do_ask` 開頭檢查
  `me->query("quest/main_omen") < 3` → 只給提示「先去土地公廟見廟祝」﹐**不**設旗標。
  完成 beat 1 (==3) 後才往下走 quest 邏輯。
- **委託人 giver**：陸抱朴 `elder`（`d/fonxan/npc/elder.c`﹐放在 `d/fonxan/swordhall.c` 劍堂）。
  - 開任務：`ask elder about 主線`（亦收 任務/殘卷/quest/task）→ 旗標 0→1﹐交付「引薦帖」。
  - 領賞：玩家 `give fragment to elder` → `accept_object` 在旗標==2 時推進 2→3﹐發賞。
- **送達對象 target**：韓書吏 `archivist`（`d/qiaoyin/npc/archivist.c`﹐放在 `d/qiaoyin/yamen.c` 縣衙前）。
  - `give letter to archivist`：`accept_object` 驗 `id("intro letter")`﹐旗標 1→2﹐回「殘卷」。
  - 本 NPC **不**開任務﹐只驗帖、收帖、回殘卷、推進旗標。
- **信物**：
  - 引薦帖 `intro_letter`（`d/fonxan/npc/obj/`）﹐id：`intro letter`/`letter`。
  - 殘卷 `ancient_fragment`（`d/qiaoyin/npc/obj/`）﹐id：`ancient fragment`/`fragment`/`scroll`。
- **獎勵**（路徑與 score 軸均已 grep / ls 確認﹐比 beat 1 厚）：
  - `/obj/money/coin` ->set_amount(300)
  - `/d/snow/npc/obj/silversword`（洗銀劍﹐master.c/alchemist.c 已用作 reward﹐known-good）
  - `/obj/medication/boar_berry`
  - `gain_score("survive",300)`+`("emprise",100)`+`("reputation",50)`+`("explorer fame",50)`
  - `emprise`=俠義之舉、`reputation`=聲望、`explorer fame`=旅行見聞﹕均在
    `data/chinese.o`（score of ...）且 `cmds/usr/reputation.c` 高亮顯示。`praise.c`
    已實際 `gain_score("reputation",N)`﹐故 reputation 軸有先例﹐安全。
- **防重複領獎**：elder 只在 `query("quest/main_omen2")==2` 時推進+發賞﹔archivist
  只在旗標==1 時推進。其餘仍收下信物避免卡物﹐不重複給賞/推進。
- **遺失信物補發**：兩 NPC 在 do_ask 偵測旗標對應但身上無信物 → 重新補一份（仿 beat 1）。

## 玩家指令流

前提：角色須 `quest/main_omen>=3`（已完成 beat 1）。

1. 到封山派藏劍堂（`d/fonxan/swordhall`﹕山門 gate→east 前殿 hall→north 劍堂）。
2. `ask elder about 主線`（旗標 0→1﹐拿「引薦帖」）。
3. 下山到喬陰縣衙：劍堂→south 前殿→west 山門→west 喬陰市集(`d/qiaoyin/market`)
   →（穿市集/廣場往北）縣前廣場 `d/qiaoyin/square`→north 縣衙前 `d/qiaoyin/yamen`。
4. `give letter to archivist`（旗標 1→2﹐拿「殘卷」）。
5. 原路回封山派藏劍堂。
6. `give fragment to elder`（旗標 2→3﹐得 coin 300＋洗銀劍＋山豬果＋survive 300＋
   俠義 100＋聲望 50＋見聞 50﹐並聽 beat 3 伏筆對白）。

## 未完成 beat 1 的角色如何被處理

`ask elder about 主線` → elder 不設任何旗標﹐只 do_chat 提示
「少俠若也覺出蹊蹺﹐何不先去土地公廟見見那位廟祝」﹐引導去做 beat 1。
（archivist 對 `quest/main_omen2 < 1` 者亦只擋「先取憑帖再來」﹐不開任務。）

## 動到的檔案

- 新增：`d/fonxan/npc/elder.c`（giver）、`d/qiaoyin/npc/archivist.c`（target）
- 新增：`d/fonxan/npc/obj/intro_letter.c`、`d/qiaoyin/npc/obj/ancient_fragment.c`
- 改既有：`d/fonxan/swordhall.c`（新增 `objects` mapping﹐加 `npc/elder`﹔該房無 replace_program﹐ROOM::reset 載入）
- 改既有：`d/qiaoyin/yamen.c`（既有 `objects` mapping 內加 `npc/archivist`﹔既有 `npc/runner` 與 `replace_program(ROOM)` 不動﹐runner 本來就靠此機制 spawn）

## 風險 / 待驗

- 未能編譯實測（無 driver）。結構逐行對齊 beat 1 的 keeper.c/clerk.c + 既有任務。
- 中文 `ask elder about 主線` 的 arg 比對沿用既有寫法（整串比對含中文 token）﹔
  若 driver 中文斷詞有異需改拆字（同 beat 1 / wutang 待驗點）。
- **未重用 clerk.c**（依設計指示改用全新 NPC﹐beat 1 邏輯完全未動﹐零風險）。
- `quest/main_omen2` 為新 key﹐不碰 `main_omen`/`snow_newbie`/`capital_errand` 等。
- NPC id 不撞同房既有 NPC：elder(`fonxan elder`) vs master(`fonxan master`)﹔
  archivist(`yamen archivist`/`han clerk`) vs runner(`yamen runner`)——已確認不同 id。
- yamen.c 用 `set("objects")`＋`replace_program(ROOM)`：runner 已靠此 spawn﹐
  加第二個 NPC 同理可行（ROOM::reset 讀 query("objects") 全載）。

// 對應驗收見 evals/；本檔僅為 runbook。
