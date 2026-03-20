# ES2 MUD 實作進度報告

> 產生日期：2026-03-19
> 資料來源：ES2 Wiki (sites.google.com/site/es2mud) vs mudlib 現有程式碼

---

## 總覽

| 類別 | Wiki 需求 | 已實作 | 缺少 | 完成率 |
|------|-----------|--------|------|--------|
| 種族 (Races) | 11 | 11 | 0 | 100% |
| 職業 (Classes) | 7 | 7 | 0 | 100% |
| 門派 (Sects) | 20 | 18 | 2 | 90% |
| 城鎮 (Towns) | 3 | 3 | 0 | 100% |
| 城鎮任務 (Town Quests) | 13 | 5 | 8 | 38.5% |
| 靈魂任務 (Spirit Quests) | 2 | 1 | 1 | 50% |
| 主線劇情 (Main Story) | 9 | 0 | 9 | 0% |
| 玩家說明 (Help Texts) | 10 | 1 | 9 | 10% |
| 傳說裝備 (Legendary) | 7 | 6 | 1 | 85.7% |
| **總計** | **82** | **52** | **30** | **63.4%** |

---

## 已完成項目

### 種族系統 (11/11) - 100%

所有 11 個種族的 daemon 及 help 文本均已實作：

| 種族 | 檔案 | 功德值 | Help |
|------|------|--------|------|
| 人類 | `daemon/race/human.c` | 5 | `doc/help/player/races/human` |
| 刑天 | `daemon/race/xingtian.c` | 25 | `doc/help/player/races/xingtian` |
| 厭火 | `daemon/race/yenhold.c` | 5 | `doc/help/player/races/yenhold` |
| 夜叉 | `daemon/race/yaksha.c` | 35 | `doc/help/player/races/yaksha` |
| 巫首 | `daemon/race/malik.c` | 30 | `doc/help/player/races/malik` |
| 無腸 | `daemon/race/woochan.c` | 5 | `doc/help/player/races/woochan` |
| 焦僥 | `daemon/race/jiaojao.c` | 10 | `doc/help/player/races/jiaojao` |
| 釘靈 | `daemon/race/dingling.c` | 10 | `doc/help/player/races/dingling` |
| 阿修羅 | `daemon/race/asura.c` | 30 | `doc/help/player/races/asura` |
| 雨師妾 | `daemon/race/rainnar.c` | 25 | `doc/help/player/races/rainnar` |
| 黑齒 | `daemon/race/blackteeth.c` | 3 | `doc/help/player/races/blackteeth` |

### 職業系統 (7/7) - 100%

| 職業 | 檔案 |
|------|------|
| 武者 | `daemon/class/warrior.c` |
| 書生 | `daemon/class/scholar.c` |
| 方士 | `daemon/class/alchemist.c` |
| 道士 | `daemon/class/taoist.c` |
| 小偷 | `daemon/class/thief.c` |
| 軍人 | `daemon/class/soldier.c` |
| 和尚 | `daemon/class/monk.c` |

額外：`fighter.c`（戰鬥基礎類）、`commoner.c`（平民）

### 門派系統 (18/20) - 90%

已實作 18 個門派 daemon 及對應區域：

| 門派 | Daemon | 區域 | 房間數 |
|------|--------|------|--------|
| 封山派 | `sect/fengshan.c` | `d/fengshan/` | 5 |
| 冷梅莊 | `sect/lengmei.c` | `d/lengmei/` | 6 |
| 哭笑門 | `sect/kuxiao.c` | `d/kuxiao/` | 6 |
| 雪吟莊 | `sect/xueyin.c` | `d/xueyin/` | 6 |
| 虎刀門 | `sect/hudao.c` | `d/hudao/` | 5 |
| 瑯夷 | `sect/langyi.c` | `d/langyi/` | 6 |
| 隱教 | `sect/yinjiao.c` | `d/yinjiao/` | 6 |
| 龍圖 | `sect/longttu.c` | `d/longttu/` | 6 |
| 武陀 | `sect/wutuo.c` | `d/wutuo/` | 5 |
| 步玄派 | `sect/buxuan.c` | `d/buxuan/` | 6 |
| 玄天教 | `sect/xuantian.c` | `d/xuantian/` | 6 |
| 振武軍營 | `sect/zhenwu.c` | `d/zhenwu/` | 5 |
| 天師派 | `sect/tianshi.c` | `d/tianshi/` | 7 |
| 茅山派 | `sect/maoshan.c` | `d/maoshan/` | 5 |
| 護國白象寺 | `sect/baixiang.c` | `d/baixiang/` | 5 |
| 寶蓮寺 | `sect/baolian.c` | `d/baolian/` | 6 |
| 劍甲門 | `sect/jianjia.c` | `d/jianjia/` | 5 |
| 天邪 | `sect/tianxie.c` | `d/tianxie/` | 6 |

### 城鎮與區域

**主要城鎮：**
- 雪亭鎮 (`d/snow/`) — 45 房間, 31 NPC
- 五堂鎮 (`d/wutang/`) — 29 房間, 12 NPC
- 赤魈村 (`d/chixiao/`) — 4 房間, 2 Boss NPC + 8 物品

**中型城鎮：**
- 潮陰 (`d/choyin/`) — 10 房間, 6 NPC
- 離郡 (`d/lijun/`) — 10 房間, 6 NPC
- 百花村 (`d/baihua/`) — 8 房間, 3 NPC
- 三焰 (`d/sanyen/`) — 6 房間, 3 NPC

**鄉村/小鎮：** 康平(6), 李莊(6), 龍安(2), 衛國(2)

**野外區域：** 墓地(6), 黑風寨(7), 莽林(6), 老松嶺(8), 道路(11), 競技場(2)

### 傳說裝備 (6/7) - 85.7%

- [x] `obj/weapon/chuanling.c` — 穿靈（神話神劍）
- [x] `obj/weapon/xuanyao.c` — 旋芒（神話神劍）
- [x] `obj/weapon/yinxue.c` — 飲血劍
- [x] `chixiao/npc/obj/fire_weapon.c` — 火神武器
- [x] `chixiao/npc/obj/thunder_weapon.c` — 雷神武器
- [x] `chixiao/npc/obj/wind_weapon.c` — 風神武器
- [x] `chixiao/npc/obj/rain_weapon.c` — 雨神武器

### 天地靈任務 (部分完成)

- [x] 赤魈村地圖（entrance, village_square, wishing_pool, inn）
- [x] 天靈 Boss NPC (`chixiao/npc/tianling.c`)
- [x] 天靈匕首 (`chixiao/npc/obj/tianling_dagger.c`)
- [x] 天靈眼 (`chixiao/npc/obj/tianling_eye.c`)
- [x] 地靈 Boss NPC (`chixiao/npc/diling.c`)
- [x] 地靈斧 (`chixiao/npc/obj/diling_axe.c`)
- [x] 地靈心 (`chixiao/npc/obj/diling_heart.c`)
- [x] 四神武器（火、雷、風、雨）
- [ ] 任務觸發邏輯（投擲機制）
- [ ] 天靈戰鬥 AI（隱神篇）
- [ ] 地靈任務流程道具鏈
- [ ] 地氣塔房間
- [ ] 禁止技能房間機制

### 系統架構

- 154 個玩家指令
- 24 個技能 daemon
- 125+ 個遊戲物品
- 55 個 feature 模組
- 30 個 include 標頭檔
- 完整的戰鬥系統、登入系統、頻道系統

---

## 缺少項目 — 待實作清單

### 優先級 HIGH

#### 1. 城鎮任務邏輯（8 個任務待完成）

**雪亭鎮（5 個未完成）：**
- [ ] 阿寶的等待 — 需新增 NPC 到 tree.c
- [ ] 盲眼老婦之謎 — 需確認 gammer.c 是否為此角色
- [ ] 倉庫搬運 — `warehouse.c` + `worker.c` 就緒，需加任務邏輯
- [ ] 遺失的信件 — `post_office.c` + `postman.c` 就緒，需加任務邏輯
- [x] 軍營招募 — `military_camp.c` + `recruiter.c` 已建立
- [x] 莊園秘密 — `dilapidated_manor.c` + `darkrobe.c` 已建立
- [ ] 黑袍老人的女兒 — 尋人任務未實作

**五堂鎮（3 個未完成）：**
- [ ] 飲血的下落 — 尋找傳說武器
- [x] 巫山神秘雕像 — `wushan_cave.c` 已存在
- [x] 郭布的弟子 — `guobu.c` NPC 已存在
- [x] 鎮天神廟之謎 — `temple.c` 已存在
- [ ] 官員來訪 — 需 inspector 任務邏輯
- [x] 渡河任務 — `ferryman.c` + `dock.c` 已建立

### 優先級 MEDIUM

#### 2. 天地靈任務系統完善

**天靈任務（NPC/物品就緒，缺邏輯）：**
- [ ] 許願池互動機制（投入3件四神武器觸發天靈出現）
- [ ] 天靈 Boss 戰鬥 AI（使用隱神篇，傷害基於玩家防禦力）
- [ ] 戰鬥獎勵掉落邏輯

**地靈任務（NPC/獎勵就緒，缺流程）：**
- [ ] 任務道具鏈：聖木殘根→金屋內丹→炎日箭→太陽槍
- [ ] 地氣塔頂房間（黑袍怪人所在地）
- [ ] 禁止 exert/perform 的房間機制
- [ ] Eye/Heart 扣減屬性不足10點的失敗判定

#### 3. 缺少的門派

- [ ] 天月庵（`daemon/sect/tianyue.c` + `d/tianyue/`）— 和尚門派
- [ ] 茅山派三觀分支邏輯 — 確認 `maoshan.c` 是否支持靈雲觀/隱風觀/幻霧觀選擇

### 優先級 LOW

#### 4. 玩家說明文件 (1/10)

`mudlib/doc/help/player/` 目錄：
- [x] `races/` — 種族介紹（11 個種族 help 文本已建立）
- [ ] `classes` — 職業介紹
- [ ] `sects` — 門派介紹
- [ ] `combat` — 戰鬥系統說明
- [ ] `skills` — 技能系統說明
- [ ] `equipment` — 裝備系統說明
- [ ] `quests` — 任務系統說明
- [ ] `newbie` — 新手指南
- [ ] `towns` — 城鎮導覽
- [ ] `mythology` — 世界觀與神話背景

#### 5. 主線劇情（大型系統工程）

Wiki 提到的 9 個主線劇情謎團：
- [ ] 大邪道人與殘蟻師太的關係
- [ ] 魚鐵山與劉乙忘玄的陰謀
- [ ] 武林盟主失蹤事件
- [ ] 白象寺隱藏秘密
- [ ] 封鬼慘案真兇
- [ ] 梅影風妻子劇情
- [ ] 朝廷對侮天鬼傳說的態度
- [ ] 虎刀門二師父下落
- [ ] 阿寶的榕樹等待對象

---

## Task 03 完成記錄 — 房間出口雙向連結修復

> 完成日期：2026-03-19

### 修復內容

修復了 14 個檔案中的出口方向問題，確保所有房間出口雙向連結正確：

**新增缺少的反向出口（4 個）：**
- `d/hudao/inner_hall.c` — 新增 east→armory（原本 armory→west→inner_hall 單向）
- `d/maoshan/lingyun.c` — 新增 north→altar（原本 altar→south→lingyun 單向）
- `d/wutang/street1.c` — 新增 west→store（原本 store→east→street1 單向）
- `d/wutang/court.c` — 新增 north→ngate（串連 square_n→street2→court→ngate 路線）

**修正路網拓撲（crossroad 插入）：**
- `d/road/road3.c` — east 從 road4 改為 crossroad
- `d/road/road4.c` — west 從 road3 改為 crossroad
- （crossroad 原本被跳過，road3↔road4 直連）

**修正方向不對稱：**
- `d/road/road1.c` — 新增 northeast→mountain_road1
- `d/road/mountain_road1.c` — south 改為 southwest→road1
- `d/road/mountain_road2.c` — west 改為 south→crossroad（配合 crossroad→north）
- `d/road/road5.c` — south 改為 southwest→maoshan/gate
- `d/maoshan/gate.c` — south 改為 northeast→road5（消除雙方都用 south 的矛盾）
- `d/hudao/gate.c` — south 改為 west→road2（配合 road2→east）
- `d/baixiang/gate.c` — south 改為 west→mountain_road2（配合 mountain_road2→east）

**路線調整：**
- `d/wutang/ngate.c` — south 從 street2 改為 court（形成 street2→court→ngate 正確鏈路）

### 已確認為設計意圖的單向出口

以下使用 action 機制（climb/enter）而非標準 exit，屬正常設計：
- `snow/tree.c` ↔ `square.c` — climb 榕樹
- `snow/fireplace.c` ↔ `inn_kitchen.c` — enter 大灶
- `snow/mill.c` ↔ `lane2.c` — enter 磨坊
- `snow/kitchen.c` — climb 圍牆（無標準 exit）
- `lijun/ferry_south.c` → `dock.c` — 渡船機制

### 驗證結果

- 掃描 270 個 .c 檔案，267 個房間
- 檢查 529 個出口
- 0 個斷鏈目標
- 0 個未修復的單向出口

### 關於 missing_rooms

`missing_content.json` 中唯一的 missing_room 為 `wutang/guest_house`（別館/欽差住所）。
經檢查，此功能已由 `wutang/residence.c`（御史別院）實現，inspector NPC 位於 `court.c`，
court→east→residence 連結完整。無需新建房間。

---

## 建議實作順序

1. **Phase 1 — 任務邏輯**：為已有房間/NPC的城鎮任務加上任務觸發和完成邏輯
2. **Phase 2 — 天地靈任務**：完善赤魈村的天靈/地靈任務系統
3. **Phase 3 — 門派補完**：新增天月庵，確認茅山派三觀分支
4. **Phase 4 — 說明文件**：撰寫玩家說明文件
5. **Phase 5 — 主線劇情**：規劃並實作主線任務系統

---

## 現有程式碼統計

```
總 .c 檔案數量
├── d/ (遊戲區域)     489 檔案 (房間 + NPC + NPC物品 + 其他)
├── daemon/            67 檔案 (11 種族 + 9 職業 + 18 門派 + 24 技能 + 5 其他)
├── obj/              125 檔案 (武器/防具/藥品/食物/NPC)
├── cmds/             154 檔案 (管理/玩家/巫師指令)
├── std/               21 檔案 (基礎類別)
├── feature/           55 檔案 (功能模組)
├── adm/               22 檔案 (系統管理)
└── include/           30 檔案 (標頭定義)
                      ───
                      963 檔案
```
