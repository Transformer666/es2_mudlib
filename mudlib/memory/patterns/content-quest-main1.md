# Runbook: 雪亭鎮主線任務一「卯木之兆」

ES2 原有 5 條支線﹐但無主線。本 runbook 記錄第一條主線任務﹐作為「侮天鬼 /
聖木 / 封鬼慘案」大敘事的開端。新手在雪亭鎮即可接﹐機制上是一條穩固的
2-step flag quest﹐照雪亭/京畿已驗證的任務 NPC 結構逐行複製。

## 故事定位（呼應 docs/01-世界觀與劇情）

- 神話：三百年前皇城聖木被斷﹐侮天鬼元神破土（`01-神話與創世.md`、`02-歷史時間線.md`）。
- 開場小事件：雪亭鎮廣場那株老榕（鎮民喚「卯木」）入夜有異響、土地神像落淚。
  廟祝心生不祥之兆﹐寫密報請官府過目。一件小委託﹐卻在對白裡埋下大伏筆。
- 結尾鉤子：師爺提到「斐縣同僚也遇過怪事、封山派在查老榕」﹐廟祝叮囑玩家
  「卯木之事怕還沒完﹐日後留心風聲」——讀來像鏈條起點﹐但本任務自成一體。

## 任務設計（旗標：`quest/main_omen`﹐0→1→2→3）

- **委託人（giver）**：廟祝 `keeper`（土地公廟守廟老人）﹐放在 `d/snow/small_temple.c`。
  - 開任務：`ask keeper about 主線`（亦收 `about 任務`/`about quest`）→ 旗標 0→1﹐
    **交付信物**「密報」（仿 patrolman.c / cakegammer.c 的 give_* 寫法）。
  - 領賞：玩家把師爺批文 `give` 回來 → `accept_object` 推進 2→3﹐發賞。
- **送達對象（target）**：師爺 `clerk`（鄉校衙堂斷事官府師爺）﹐放在 `d/snow/court.c`。
  - `give report to clerk`：`accept_object` 收下密報﹐旗標 1→2﹐回給「批文」（仿 gateman.c）。
  - 本 NPC **不**開任務﹐只收信物、回信物、推進旗標。
- **信物**：
  - 密報 `omen_report`﹐`id`：`sealed report`/`omen report`/`report`。
  - 批文 `official_reply`﹐`id`：`official reply`/`reply`。
- **獎勵**（路徑與 score 軸均已 grep 確認）：
  - `/obj/money/coin` ->set_amount(150)
  - `/obj/food/manto`（充飢）
  - `/obj/medication/boar_berry`（提神）
  - `gain_score("survive", 200)` + `gain_score("emprise", 50)` + `gain_score("explorer fame", 50)`
  - `emprise`=俠義之舉（在 `reputation`/`聲望` 指令顯示；key 見 `data/chinese.o` 與
    `cmds/usr/reputation.c` 註解）。
- **防重複領獎**：keeper 的 `accept_object` 只在 `query("quest/main_omen") == 2` 時推進＋發賞；
  clerk 只在旗標 ==1 時推進。其餘情況仍收下信物避免卡物﹐但不重複給賞/推進。
- **遺失信物補發**：兩 NPC 在 do_ask 中若偵測玩家把信物弄丟﹐會重新補一封（仿既有任務）。

## 玩家指令流（從接任務到領賞）

從飲風客棧（`d/snow/inn_hall`﹐valid_startroom）出發：

1. `east`（→ 廣場 square_w）→ `east`（→ 廣場中央 square）→ `north`（→ square_n）
   → `north`（→ 街道 nstreet1）→ `east`（→ 土地公廟 small_temple）
2. `ask keeper about 主線`（旗標 0→1﹐拿到「密報」）
3. 往鄉校：`west`（nstreet1）→ `south`（square_n）→ `south`（square）→ `west`（square_w）
   → `south`（square_sw）→ `west`（wstreet1）→ `west`（wstreet2）→ `west`（wstreet3）
   → `north`（→ 鄉校 court）
4. `give report to clerk`（旗標 1→2﹐拿到「批文」）
5. 原路回土地公廟（`south` 出鄉校到 wstreet3﹐東行回廣場﹐北上回 nstreet1﹐東入廟）
6. `give reply to keeper`（旗標 2→3﹐得銅錢 150＋饅頭＋山豬果＋survive 200＋俠義 50＋見聞 50﹐
   並聽到後續伏筆對白）

可發現性：兩 NPC 的 `long` 都寫了 `ask ... about ...` 提示﹔`do_ask` 的 notify_fail
也給提示。新手在廣場一帶閒逛、進廟即會被廟祝 init 的 do_chat 勾起好奇。

## 動到的檔案

- 新增：`d/snow/npc/keeper.c`（giver）、`d/snow/npc/clerk.c`（target）
- 新增：`d/snow/npc/obj/omen_report.c`（密報）、`d/snow/npc/obj/official_reply.c`（批文）
- 改既有：`d/snow/small_temple.c`（objects mapping 加 `npc/keeper`﹐保留 replace_program(TEMPLE)）
- 改既有：`d/snow/court.c`（objects mapping 加 `npc/clerk`﹐既有 `npc/oldman` 黑衣老人不動）

## 風險 / 待驗

- 未能編譯實測（無 driver）。結構逐行對齊 `d/capital/npc/patrolman.c`+`gateman.c`、
  `d/snow/npc/cakegammer.c`+`axing.c`﹐理應可編。
- 中文 `ask keeper about 主線` 的 arg 比對沿用既有 NPC 寫法（直接比對整串﹐含中文 token）；
  若 driver 對中文 argument 斷詞有異﹐需改用拆字比對（同 wutang 任務的待驗點）。
- `emprise` score 軸：已確認在 `chinese.o`（俠義之舉）與 `reputation.c` 註解﹐但 mudlib 內
  尚無其他 NPC 實際 `gain_score("emprise", N)` 的先例——本任務是首次使用﹐若該軸有額外
  上限/校驗需在 `feature/char/score.c` 確認（已讀﹐gain_score 僅 add﹐無白名單﹐應安全）。
- 與既有任務無旗標衝突：`quest/main_omen` 為新 key﹐不碰 `snow_newbie`/`snow_newbie2`/
  `capital_errand`/`wutang_cargo`。clerk 與同房 oldman（id `oldman`）id 不撞。
- `small_temple.c` 用 `set("objects")`＋`replace_program(TEMPLE)`：已確認 `std/room/temple.c`
  繼承 ROOM 且未覆寫 `reset()`﹐NPC 由 `std/room.c::reset()` 讀 `query("objects")` 載入﹐
  與 court.c（ROOM）同機制﹐故 NPC 能正常 spawn。

// 對應驗收見 evals/；本檔僅為 runbook。
