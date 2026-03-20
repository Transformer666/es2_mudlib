# ES2 MUD 實作進度報告

> 產生日期：2026-03-20
> 資料來源：ES2 Wiki (sites.google.com/site/es2mud) vs mudlib 現有程式碼

---

## 總覽

| 項目 | Wiki 需求 | 已實作 | 缺少 | 完成度 |
|------|----------|--------|------|--------|
| 種族 (races) | 11 | 11 | 0 | 100% |
| 職業 (classes) | 7 | 7 | 0 | 100% |
| 門派 (sects) | 18 | 18 | 0 | 100% |
| 城鎮區域 (areas) | 35 | 35 | 0 | 100% |
| 種族說明檔 | 11 | 11 | 0 | 100% |
| 職業說明檔 | 7 | 0 | 7 | 0% |
| 門派說明檔 | 18 | 0 | 18 | 0% |
| 進階職業 | 26 | 0 | 26 | 0% |
| 任務系統 | 4+ | 0 | 4+ | 0% |
| **合計** | **95+** | **62** | **33+** | **65%** |

---

## 已完成項目

### 種族系統 (11/11) - 100%

所有 11 個種族均已實作 daemon 配置及玩家說明檔：

| 種族 | ID | daemon | help file |
|------|----|--------|-----------|
| 人類 | human | daemon/race/human.c | doc/help/player/races/human |
| 刑天 | xingtian | daemon/race/xingtian.c | doc/help/player/races/xingtian |
| 厭火 | yenhold | daemon/race/yenhold.c | doc/help/player/races/yenhold |
| 夜叉 | yaksha | daemon/race/yaksha.c | doc/help/player/races/yaksha |
| 巫首 | malik | daemon/race/malik.c | doc/help/player/races/malik |
| 無腸 | woochan | daemon/race/woochan.c | doc/help/player/races/woochan |
| 焦僥 | jiaojao | daemon/race/jiaojao.c | doc/help/player/races/jiaojao |
| 釘靈 | dingling | daemon/race/dingling.c | doc/help/player/races/dingling |
| 阿修羅 | asura | daemon/race/asura.c | doc/help/player/races/asura |
| 雨師妾 | rainnar | daemon/race/rainnar.c | doc/help/player/races/rainnar |
| 黑齒 | blackteeth | daemon/race/blackteeth.c | doc/help/player/races/blackteeth |

### 職業系統 (7/7) - 100% (daemon only)

| 職業 | ID | daemon |
|------|----|--------|
| 武者 | warrior | daemon/class/warrior.c |
| 道士 | taoist | daemon/class/taoist.c |
| 和尚 | monk | daemon/class/monk.c |
| 書生 | scholar | daemon/class/scholar.c |
| 小偷 | thief | daemon/class/thief.c |
| 軍人 | soldier | daemon/class/soldier.c |
| 方士 | alchemist | daemon/class/alchemist.c |

> 注意：另有 commoner.c 和 fighter.c 兩個額外職業。

### 門派系統 (18/18) - 100% (daemon + area)

| 門派 | ID | 職業 | daemon | 區域 |
|------|----|------|--------|------|
| 封山派 | fengshan | 武者 | daemon/sect/fengshan.c | d/fengshan/ |
| 冷梅莊 | lengmei | 武者 | daemon/sect/lengmei.c | d/lengmei/ |
| 哭笑門 | kuxiao | 武者 | daemon/sect/kuxiao.c | d/kuxiao/ |
| 雪吟莊 | xueyin | 武者 | daemon/sect/xueyin.c | d/xueyin/ |
| 虎刀門 | hudao | 武者 | daemon/sect/hudao.c | d/hudao/ |
| 天師派 | tianshi | 道士 | daemon/sect/tianshi.c | d/tianshi/ |
| 茅山派 | maoshan | 道士 | daemon/sect/maoshan.c | d/maoshan/ |
| 寶蓮寺 | baolian | 和尚 | daemon/sect/baolian.c | d/baolian/ |
| 白象寺 | baixiang | 和尚 | daemon/sect/baixiang.c | d/baixiang/ |
| 步玄派 | buxuan | 書生 | daemon/sect/buxuan.c | d/buxuan/ |
| 玄天教 | xuantian | 書生 | daemon/sect/xuantian.c | d/xuantian/ |
| 瑯夷 | langyi | 小偷 | daemon/sect/langyi.c | d/langyi/ |
| 隱教 | yinjiao | 小偷 | daemon/sect/yinjiao.c | d/yinjiao/ |
| 振武軍營 | zhenwu | 軍人 | daemon/sect/zhenwu.c | d/zhenwu/ |
| 龍圖派 | longttu | 方士 | daemon/sect/longttu.c | d/longttu/ |
| 武陀堂 | wutuo | 方士 | daemon/sect/wutuo.c | d/wutuo/ |
| 劍甲門 | jianjia | 方士 | daemon/sect/jianjia.c | d/jianjia/ |
| 天邪派 | tianxie | 武者 | daemon/sect/tianxie.c | d/tianxie/ |

### 區域內容統計

| 區域 | 房間數 | NPC數 | 物品數 | 備註 |
|------|--------|-------|--------|------|
| snow (雪亭鎮) | 45 | 60 | 32 | 最完整，新手起始區 |
| wutang (五堂鎮) | 29 | 18 | 6 | 第二大城鎮 |
| choyin (朝陽城) | 10 | 10 | 4 | 城市區域 |
| lijun (利郡) | 10 | 11 | 5 | 河港貿易區 |
| road (道路) | 10 | 0 | 0 | 連接道路 |
| baihua (百花) | 8 | 7 | 3 | |
| oldpine (古松) | 8 | 6 | 2 | |
| heifeng (黑風寨) | 7 | 6 | 2 | |
| tianshi (天師派) | 7 | 5 | 2 | |
| 其他 26 個區域 | 各2-6間 | 各0-5個 | 各0-2個 | |
| **合計** | **~280** | **~200** | **~90** | |

### 技能系統 (24 skills)

已實作 24 種技能：amazing_needle, axe, blade, dagger, diamond_hammer, fengshan_sword, five_defeat_needle, lengmei_sword, longttu_neigong, maoshan_neigong, maoshan_sword, needle, phantom_sword, pike, staff, sword, tactic, taiyi_sword, taoshan_milu, three_rotations, tiger_blade, unarmed, whip, ziwei_neigong

### 物品系統

- **武器**: 20 種 (obj/weapon/)
- **防具**: 10 種 (obj/armor/)
- **藥品**: 16 種 (obj/medication/)
- **食物**: 5 種 (obj/food/)
- **藥材**: 4 種 (obj/reagent/)
- **草藥**: 6 種 (obj/drug/)
- **貨幣**: 3 種 (obj/money/)

---

## 缺少項目

### 1. 職業說明檔 (0/7) - 優先級：高

缺少所有 7 個職業的玩家說明檔 (`doc/help/player/classes/`)：
- warrior (武者)、taoist (道士)、monk (和尚)、scholar (書生)
- thief (小偷)、soldier (軍人)、alchemist (方士)

### 2. 門派說明檔 (0/18) - 優先級：高

缺少所有 18 個門派的玩家說明檔 (`doc/help/player/sects/`)。

### 3. 進階職業系統 (0/26) - 優先級：中

Wiki 中提到的 26 個進階職業均未實作：

**武者進階 (15):**
- 封山派 → 劍靈、山人、劍客
- 冷梅莊 → 劍士、古劍門傳人、虎督
- 哭笑門 → 護法、素衣衛、使者
- 雪吟莊 → 浪人、棄徒、天邪派弟子
- 虎刀門 → 護衛、鬼才、太守

**和尚進階 (2):** 白象寺 → 禪師、羅漢

**書生進階 (2):** 步玄派 → 居士 / 玄天教 → 散人

**小偷進階 (2):** 金蛇門、黑龍使者

**軍人進階 (2):** 軍隊統領、軍師

**方士進階 (2):** 龍圖派 → 醫師 / 武陀堂 → 香主

**道士進階 (1):** 茅山劍士

### 4. 任務系統 - 優先級：高

目前完全沒有結構化的任務系統。Wiki 定義了以下任務：

**主線任務 - 侮天鬼傳說 (9 個謎團):**
1. 大邪道人和殘蟻師太的關係
2. 魚鐵山和劉乙忘玄的陰謀
3. 失蹤的武林盟主
4. 白象寺的秘密
5. 封鬼慘案的真兇
6. 梅影風妻子的病情
7. 朝廷對侮天鬼傳說的了解
8. 虎刀門二師兄的下落
9. 阿寶在老榕樹下等的人

**十三靈任務鏈:**
- 天靈 (赤魈村許願池召喚)
- 地靈 (多步驟召喚流程)
- 其餘 11 個精靈相關任務

**城鎮支線任務:**
- 雪亭鎮 7 個謎題
- 五堂鎮 6 個謎題

---

## 建議實作優先順序

### Phase 1 - 說明檔補齊 (預估工作量：小)
1. 建立 7 個職業說明檔
2. 建立 18 個門派說明檔

### Phase 2 - 任務框架 (預估工作量：大)
1. 建立任務 daemon 基礎架構
2. 實作雪亭鎮新手任務
3. 實作五堂鎮支線任務

### Phase 3 - 進階職業 (預估工作量：大)
1. 設計進階職業轉職系統
2. 逐門派實作進階職業 daemon
3. 新增進階職業技能

### Phase 4 - 主線任務 (預估工作量：最大)
1. 實作侮天鬼主線劇情
2. 實作十三靈任務鏈
3. 連接各區域的劇情線索

---

## 程式碼統計

```
d/      目錄：489 個 .c 檔案（35 個區域）
daemon/ 目錄： 67 個 .c 檔案（種族/職業/門派/技能）
obj/    目錄：125 個 .c 檔案（武器/防具/藥品等）
doc/    目錄： 12 個說明檔（11 種族 + 1 topics）
────────────────────────────────
總計：         693 個檔案
```
