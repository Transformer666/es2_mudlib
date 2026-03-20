# ES2 MUD 實作進度報告

> 產生日期：2026-03-20
> 資料來源：ES2 Wiki (sites.google.com/site/es2mud)、es2tips Blog、mudchina/es2 原版 repo

---

## 總覽

| 類別 | 需求數 | 已實作 | 缺少 | 完成度 |
|------|--------|--------|------|--------|
| 種族 | 11 | 11 | 0 | **100%** |
| 職業 | 7 | 7 | 0 | **100%** |
| 門派 | 18 | 18 | 0 | **100%** |
| 技能 | 71* | 27 | 44** | **38%** |
| 區域 | 19* | 37 | 13** | **74%*** |
| 任務 | 11+ | ~0 | 11+ | **~0%** |
| Help 文件 | 10+ | 11 | 10+ | **52%** |
| 裝備 | 14+ | 129 obj | 14+ | 部分 |

> *以原版 mudchina/es2 為基準
> **原版有但我們缺少的數量
> ***我們有 37 個區域遠超原版 19 個，但原版 13 個區域尚未移植

---

## 1. 種族系統 — 100% ✓

所有 11 種族已完整實作：

| 種族 | Daemon | Help 檔案 |
|------|--------|-----------|
| 人類 (human) | ✓ | ✓ |
| 刑天 (xingtian) | ✓ | ✓ |
| 厭火 (yenhold) | ✓ | ✓ |
| 夜叉 (yaksha) | ✓ | ✓ |
| 巫首 (malik) | ✓ | ✓ |
| 無腸 (woochan) | ✓ | ✓ |
| 焦僥 (jiaojao) | ✓ | ✓ |
| 釘靈 (dingling) | ✓ | ✓ |
| 阿修羅 (asura) | ✓ | ✓ |
| 雨師妾 (rainnar) | ✓ | ✓ |
| 黑齒 (blackteeth) | ✓ | ✓ |

---

## 2. 職業系統 — 100% ✓

| 職業 | Daemon | 備註 |
|------|--------|------|
| 武者 (warrior) | ✓ | |
| 和尚 (monk) | ✓ | |
| 道士 (taoist) | ✓ | |
| 書生 (scholar) | ✓ | |
| 小偷 (thief) | ✓ | |
| 軍人 (soldier) | ✓ | |
| 方士 (alchemist) | ✓ | |
| 平民 (commoner) | ✓ | 額外 |
| 戰士 (fighter) | ✓ | 額外 |

---

## 3. 門派系統 — 100% ✓

所有 18 門派 daemon 已建立，location 指向的房間全部存在。

| 門派 | 職業 | Location | 驗證 |
|------|------|----------|------|
| 封山派 (fengshan) | 武者 | /d/fengshan/main_hall | ✓ |
| 冷梅莊 (lengmei) | 武者 | /d/lengmei/hall | ✓ |
| 哭笑門 (kuxiao) | 武者 | /d/kuxiao/hall | ✓ |
| 雪吟莊 (xueyin) | 武者 | /d/xueyin/hall | ✓ |
| 虎刀門 (hudao) | 武者 | /d/hudao/hall | ✓ |
| 寶蓮寺 (baolian) | 和尚 | /d/baolian/hall | ✓ |
| 天月庵 (tianyue) | 和尚 | /d/tianyue/hall | ✓ |
| 白象寺 (baixiang) | 和尚 | /d/baixiang/main_hall | ✓ |
| 天師派 (tianshi) | 道士 | /d/tianshi/hall | ✓ |
| 茅山派 (maoshan) | 道士 | /d/maoshan/lingyun | ✓ |
| 瑯夷 (langyi) | 小偷 | /d/langyi/hall | ✓ |
| 隱教 (yinjiao) | 小偷 | /d/yinjiao/hall | ✓ |
| 龍圖派 (longttu) | 方士 | /d/longttu/study | ✓ |
| 武陀堂 (wutuo) | 方士 | /d/wutuo/hall | ✓ |
| 步玄派 (buxuan) | 書生 | /d/buxuan/study | ✓ |
| 玄天教 (xuantian) | 書生 | /d/xuantian/hall | ✓ |
| 振武軍營 (zhenwu) | 軍人 | /d/zhenwu/command | ✓ |
| 天邪派 (tianxie) | 跨門派 | /d/tianxie/hall | ✓ |

劍甲門 (jianjia) 另有獨立區域但非正式門派 daemon（跨門派機制）。

---

## 4. 技能系統 — 38%

### 已實作（27 技能，全部含 skill_improved/skill_advanced）

| 技能 | 對應門派/通用 |
|------|--------------|
| amazing_needle（奇針術） | 瑯夷 |
| axe（斧法） | 通用 |
| blade（刀法） | 通用 |
| dagger（匕首） | 通用 |
| diamond_hammer（金剛鎚法） | 白象寺 |
| dodge（閃避） | 通用 |
| fengshan_sword（封山劍法） | 封山派 |
| five_defeat_needle（五敗針法） | 武陀堂 |
| force（內功） | 通用 |
| lengmei_sword（冷梅劍法） | 冷梅莊 |
| longttu_neigong（龍圖內功） | 龍圖派 |
| maoshan_neigong（茅山內功） | 茅山派 |
| maoshan_sword（茅山劍法） | 茅山派 |
| needle（針法） | 通用 |
| parry（格擋） | 通用 |
| phantom_sword（幻影劍法） | 天邪派 |
| pike（槍法） | 通用 |
| staff（棍法） | 通用 |
| sword（劍法） | 通用 |
| tactic（兵法） | 振武軍營 |
| taiyi_sword（太乙劍法） | 天師派 |
| taoshan_milu（陶山迷路） | 隱教 |
| three_rotations（三轉劍法） | 步玄派 |
| tiger_blade（虎刀） | 虎刀門/哭笑門 |
| unarmed（拳法） | 通用 |
| whip（鞭法） | 通用 |
| ziwei_neigong（紫微內功） | 天師派 |

### 缺少的原版技能（60 個，按優先順序）

**高優先（核心戰鬥/門派技能）：**
- bloodystrike（血殺）、buddhism（佛學）、celestial（天功）
- celestrike（天擊）、essencemagic（元素魔法）
- iceforce（冰功）、iron-cloth（鐵布衫）、jin-gang（金剛）
- jingang-staff（金剛杖）、lotusforce（蓮花功）
- magic（法術）、spells（法術）、taoism（道法）
- stealing（偷竊）、throwing（投擲）

**中優先（進階/門派特色技能）：**
- bolomiduo、chanting、chaos-steps、cloudstaff、deisword
- fonxanforce、fonxansword、fork、gouyee、hammer
- juechen-force、linbo-steps、magic-array、meihua-shou
- move、mysterrier、mystforce、mystsword、necromancy
- nine-moon、notraces、perception、pyrobat-steps、qidaoforce
- scratching、serpentforce、shortsong-blade、six-chaos-sword
- snowshade-force、snowshade-sword、snowwhip、spicyclaw
- spider-array、spring-blade、stormdance、tao-mystery
- tenderzhi、ts-fist、wu-shun、yirong

**低優先（輔助/生活技能）：**
- fall-steps、instruments、literate、liuh-ken、music

---

## 5. 區域系統 — 74%（以原版為基準）

### 已實作區域（37 個，530 .c 檔案）

| 區域 | 檔案數 | 類型 |
|------|--------|------|
| snow（雪亭鎮） | 94 | 主城 |
| wutang（五堂鎮） | 42 | 主城 |
| choyin（喬陰） | 14 | 城鎮（原版有） |
| baihua（百花） | 15 | 村莊 |
| lijun（離鈞） | 14 | 渡口/城鎮 |
| chixiao（赤魈） | 10 | 村莊 |
| lengmei（冷梅莊） | 10 | 門派 |
| langyi（瑯夷） | 10 | 門派 |
| oldpine（古松林） | 10 | 野外（原版有） |
| kuxiao（哭笑門） | 9 | 門派 |
| xueyin（雪吟莊） | 9 | 門派 |
| yinjiao（隱教） | 9 | 門派 |
| tianshi（天師派） | 9 | 門派 |
| tianxie（天邪派） | 9 | 門派 |
| sanyen（三掩） | 9 | 城鎮（原版有） |
| kangping（康平） | 9 | 村莊 |
| heifeng（黑風） | 9 | 山寨 |
| road（道路） | 9 | 連接路 |
| graveyard（墓園） | 8 | 野外（原版有） |
| baolian（寶蓮寺） | 8 | 門派 |
| tianyue（天月庵） | 8 | 門派 |
| longttu（龍圖派） | 8 | 門派 |
| wutuo（武陀堂） | 8 | 門派 |
| buxuan（步玄派） | 8 | 門派 |
| xuantian（玄天教） | 8 | 門派 |
| lee（李村） | 8 | 村莊 |
| zhenwu（振武軍營） | 8 | 門派 |
| jianjia（劍甲門） | 8 | 門派 |
| manglin（莽林） | 8 | 野外 |
| weiguo（衛國） | 7 | 城鎮 |
| jingji（京畿） | 7 | 城鎮 |
| maoshan（茅山） | 7 | 門派 |
| hell（地獄） | 7 | 特殊 |
| hudao（虎刀門） | 6 | 門派 |
| fengshan（封山派） | 6 | 門派 |
| baixiang（白象寺） | 5 | 門派 |
| longan（龍安） | 5 | 城鎮 |

### 原版有但我們缺少的區域（13 個）

| 區域 | 名稱 | 優先度 | 備註 |
|------|------|--------|------|
| city | 城市 | 高 | 可能是主要城鎮 |
| force | 內功修練區 | 高 | 練功系統核心 |
| ice | 冰域 | 高 | 天師冰系相關 |
| temple | 神殿 | 高 | 劇情相關 |
| canyon | 峽谷 | 中 | 野外區域 |
| chuenyu | 泉域 | 中 | 野外區域 |
| goathill | 羊山 | 中 | 野外區域 |
| green/green.n | 草原 | 中 | 野外區域 |
| jail | 監獄 | 中 | 系統區域 |
| latemoon | 晚月 | 中 | 野外區域 |
| village | 村莊 | 中 | 通用村莊 |
| waterfog | 水霧 | 中 | 野外區域 |
| death | 死亡領域 | 低 | 我們有 hell 可能對應 |

---

## 6. 任務系統 — ~0%

### 缺少的任務（按優先度）

**最高優先：**
1. 侮天鬼主線任務（wiki 標記為開發中）
2. 十三靈天賦重置任務

**高優先：**
3. 天靈任務（赤魈村許願池）
4. 地靈任務（地獄塔）
5. 門派進階任務（各門派升級路線）

**中優先：**
6. 五堂鎮六大謎題
7. 雪亭鎮七大謎題
8. 殺業鍛鍊系統
9. 金蛇門人/黑龍使者進階
10. 劍甲門跨門派拜師
11. 軍人戰功升遷系統

---

## 7. 缺少的遊戲系統

| 系統 | 優先度 | 說明 |
|------|--------|------|
| 茅山幻術 | 高 | 先天符消耗的召喚獸法術（狗/猴/蛇/雨） |
| 天師四元素 | 高 | 冰火風雷元素法術系統 |
| 種族主動技能 | 高 | 11 種族各有獨特主動技能 |
| 茅山奇術/遁甲書 | 中 | fate/experience 能力 |
| 雨師妾養蛇 | 中 | 培養最多 5 條蛇作為裝備 |
| 夜叉吞鬼/吞魂 | 中 | 種族特殊能力 |
| 阿修羅吞屍 | 中 | 種族特殊能力 |
| 召喚獸系統 | 中 | 8 種召喚獸概念 |
| 天賦評級顯示 | 低 | 140-200 天賦文字描述 |

---

## 8. 與原版 ES2 的差異分析

### 我們的優勢
- **區域數量**：37 個 vs 原版 19 個（+18 個原創區域）
- **門派完整度**：18 門派全部建立 vs 原版無 sect daemon
- **種族完整度**：11 種族全部建立 vs 原版無 race daemon
- **自創技能**：17 個原版沒有的技能（如奇針術、金剛鎚法、封山劍法等）
- **內容規模**：729 個 .c 檔案，包含豐富的 NPC 和物件

### 原版的優勢
- **技能數量**：71 個 vs 我們 27 個
- **特殊區域**：ice、force、temple 等劇情/系統區域
- **職業多樣性**：原版有 assassin、ninja、lama 等額外職業

### 結構差異
- 原版無 `daemon/sect/` 和 `daemon/race/` 目錄（我們已補齊）
- 原版的 `d/` 下有 class、skill、npc、social_guild 等系統目錄（功能已整合至其他位置）
- 我們的架構更模組化，門派/種族/職業各有獨立 daemon

---

## 9. 房間補齊記錄（2026-03-20）

### 新增房間（6 間）

**雪亭鎮（snow）— 謎題關聯房間：**

| 房間 | 檔案 | 連結自 | 對應謎題 |
|------|------|--------|----------|
| 大宅正堂 | `d/snow/manor_hall.c` | dilapidated_manor (south) | 謎題 6：破舊大宅裡面躲著甚麼 |
| 大宅地窖 | `d/snow/manor_cellar.c` | manor_hall (down) | 謎題 6：大宅深處的秘密 |
| 河邊小屋 | `d/snow/old_house.c` | riverbank (east) | 謎題 7：黑衣老人的閨女跑去了哪裡 |

**五堂鎮（wutang）— 謎題關聯房間：**

| 房間 | 檔案 | 連結自 | 對應謎題 |
|------|------|--------|----------|
| 神殿密室 | `d/wutang/temple_inner.c` | temple (south) | 謎題 4：鎮天神廟內藏著誰 |
| 巫山密室 | `d/wutang/wushan_secret.c` | wushan_cave (down) | 謎題 2：巫山雕像有何秘密 |
| 河灣 | `d/wutang/river_bend.c` | dock (south) | 謎題 1：飲血丟在了哪裡 |

### 修改的既有房間（5 間，新增出口）

| 檔案 | 新增出口 |
|------|----------|
| `d/snow/dilapidated_manor.c` | south → manor_hall |
| `d/snow/riverbank.c` | east → old_house |
| `d/wutang/temple.c` | south → temple_inner |
| `d/wutang/wushan_cave.c` | down → wushan_secret |
| `d/wutang/dock.c` | south → river_bend |

### 驗證結果

- 所有新房間含 `inherit ROOM`、`set("short")`、`set("exits")`、`setup()` ✓
- 所有 6 對出口雙向連結驗證通過 ✓
- 所有出口目標檔案存在 ✓

---

## 建議優先實作順序

1. **技能系統補齊** — 補齊核心戰鬥技能（佛學、偷竊、法術、元素魔法等）
2. **任務系統** — 實作天靈/地靈任務作為範本
3. **缺少的區域** — 優先實作 city、force、ice、temple
4. **遊戲系統** — 茅山幻術、天師四元素、種族主動技能
5. **Help 文件** — 補齊 cmds、class、newbie 等核心說明文件
6. **裝備補齊** — 神話武器、任務獎勵、門派專屬裝備
