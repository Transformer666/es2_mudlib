# ES2 MUD 實作進度報告

> 產生日期：2026-03-20
> 資料來源：ES2 Wiki (sites.google.com/site/es2mud)、es2tips Blog、mudchina/es2 原版 repo

---

## 總覽

| 類別 | 需要 | 已實作 | 缺少 | 完成度 |
|------|------|--------|------|--------|
| 種族 (Races) | 11 | 11 | 0 | **100%** |
| 職業 (Classes) | 9 | 9 | 0 | **100%** |
| 門派 (Sects) | 18 | 18 | 0 | **100%** |
| 技能 (Skills) | 71 | 27 | 44 | **38.0%** |
| 區域 (Areas) | 25 orig | 37 | 12 missing | **72%** |
| 狀態 (Conditions) | 7 | 2 | 5 | **28.6%** |
| 幫助文件 (Help) | ~80+ | 11 | ~70+ | **~14%** |
| 裝備 (Equipment) | ~50+ | 18 | ~30+ | **~36%** |

**整體完成度估計：~50.8%**

---

## 1. 種族系統 — 100% 完成

全部 11 種族均已實作（daemon + help file）：

| Wiki 名稱 | 我們的 ID | 狀態 |
|-----------|----------|------|
| 人族 Human | human | ✅ |
| 刑天 Headless | xingtian | ✅ |
| 燕侯 Yenhold | yenhold | ✅ |
| 夜叉 Yaksa | yaksha | ✅ |
| 馬力 Malik | malik | ✅ |
| 烏禪 Woochan | woochan | ✅ |
| 蛟蛟 Jiaojao | jiaojao | ✅ |
| 丁零 Dingling | dingling | ✅ |
| 阿修羅 Ashura | asura | ✅ |
| 雷納 Rainnar | rainnar | ✅ |
| 黑齒 Blackteeth | blackteeth | ✅ |

---

## 2. 職業系統 — 100% 完成

我們的職業體系與原版不同（原版有 14 種，我們重新整合為 9 種）：

| 職業 | Daemon | 狀態 |
|------|--------|------|
| 武者 warrior | ✅ | ✅ |
| 和尚 monk | ✅ | ✅ |
| 道士 taoist | ✅ | ✅ |
| 小偷 thief | ✅ | ✅ |
| 方士 alchemist | ✅ | ✅ |
| 書生 scholar | ✅ | ✅ |
| 軍人 soldier | ✅ | ✅ |
| 平民 commoner | ✅ | ✅ |
| 格鬥家 fighter | ✅ | ✅ |

---

## 3. 門派系統 — 100% 完成

全部 18 門派均有 daemon + 專屬區域，且所有 location 指向存在的房間：

| 門派 | Daemon | 區域 | 所屬職業 |
|------|--------|------|----------|
| 封山派 fengshan | ✅ | ✅ 9 files | 武者 |
| 冷梅莊 lengmei | ✅ | ✅ 10 files | 武者 |
| 哭笑門 kuxiao | ✅ | ✅ 10 files | 武者 |
| 雪吟莊 xueyin | ✅ | ✅ 10 files | 武者 |
| 虎刀門 hudao | ✅ | ✅ 9 files | 武者 |
| 寶蓮寺 baolian | ✅ | ✅ 11 files | 和尚 |
| 天月庵 tianyue | ✅ | ✅ 11 files | 和尚 |
| 白象寺 baixiang | ✅ | ✅ 9 files | 和尚 |
| 天師派 tianshi | ✅ | ✅ 12 files | 道士 |
| 茅山派 maoshan | ✅ | ✅ 10 files | 道士 |
| 瑯夷 langyi | ✅ | ✅ 11 files | 小偷 |
| 隱教 yinjiao | ✅ | ✅ 11 files | 小偷 |
| 龍圖丹派 longttu | ✅ | ✅ 10 files | 方士 |
| 武陀 wutuo | ✅ | ✅ 9 files | 方士 |
| 步玄派 buxuan | ✅ | ✅ 11 files | 書生 |
| 玄天教 xuantian | ✅ | ✅ 10 files | 書生 |
| 振武軍營 zhenwu | ✅ | ✅ 9 files | 軍人 |
| 天邪派 tianxie | ✅ | ✅ 14 files | 跨門派 |
| 劍甲門 jianjia | ✅ | ✅ 9 files | 跨門派(方士) |

---

## 4. 技能系統 — 38.0% 完成

### 已實作技能 (27/71)

所有已實作技能均有 `skill_improved` 和 `skill_advanced`：

| 技能 | 對應門派/類型 |
|------|-------------|
| sword | 基礎武器技 |
| blade | 基礎武器技 |
| axe | 基礎武器技 |
| dagger | 基礎武器技 |
| staff | 基礎武器技 |
| pike | 基礎武器技 |
| whip | 基礎武器技 |
| needle | 基礎武器技 |
| unarmed | 基礎武器技 |
| dodge | 基礎防禦技 |
| parry | 基礎防禦技 |
| force | 基礎內功 |
| fengshan_sword | 封山派劍法 |
| lengmei_sword | 冷梅莊劍法 |
| tiger_blade | 虎刀門刀法 |
| diamond_hammer | 白象寺鎚法 |
| taiyi_sword | 天師派太乙劍 |
| ziwei_neigong | 天師派紫微內功 |
| maoshan_sword | 茅山派劍法 |
| maoshan_neigong | 茅山派內功 |
| amazing_needle | 瑯夷奇針 |
| taoshan_milu | 隱教陶山迷路 |
| five_defeat_needle | 武陀五敗針 |
| longttu_neigong | 龍圖內功 |
| three_rotations | 步玄三轉劍 |
| phantom_sword | 天邪幻影劍 |
| tactic | 振武兵法 |

### 高優先缺失技能 (10)

| 技能 | 原因 |
|------|------|
| buddhism | 佛學，和尚系核心技能 |
| taoism | 道術，道士系核心技能 |
| literate | 識字，書生系核心技能 |
| stealing | 偷竊，小偷系核心技能 |
| magic | 法術，方士系核心技能 |
| spells | 咒術，多門派共用 |
| hammer | 通用鎚法（已有 diamond_hammer 但缺通用版） |
| move | 身法，所有職業基礎技能 |
| perception | 感知，所有職業基礎技能 |
| music | 音律，書生/特殊技能 |

### 中優先缺失技能 (11)

lotusforce, jingang-staff, jin-gang, iron-cloth, iceforce, serpentforce, celestial, celestrike, cloudstaff, notraces, throwing

### 低優先缺失技能 (33)

bloodystrike, bolomiduo, chanting, chaos-steps, deisword, essencemagic, fall-steps, fonxanforce, fonxansword, fork, gouyee, instruments, juechen-force, linbo-steps, liuh-ken, magic-array, meihua-shou, mysterrier, mystforce, mystsword, necromancy, nine-moon, pyrobat-steps, qidaoforce, scratching, shortsong-blade, six-chaos-sword, snowshade-force, snowshade-sword, snowwhip, spicyclaw, spider-array, spring-blade, stormdance, tao-mystery, tenderzhi, ts-fist, wu-shun, yirong

---

## 5. 區域系統 — 72% 完成

### 已實作區域 (37 個，559 個 .c 檔)

| 區域 | 檔案數 | 類型 |
|------|--------|------|
| snow (雪亭鎮) | 112 | 主城 |
| wutang (武唐城) | 50 | 主城 |
| lijun (離郡) | 21 | 城鎮 |
| choyin (喬陰) | 20 | 城鎮 |
| baihua (百花) | 15 | 村莊 |
| chixiao (赤霄) | 15 | 村莊 |
| oldpine (古松林) | 14 | 野外 |
| tianxie (天邪派) | 14 | 門派 |
| heifeng (黑風) | 13 | 野外 |
| hell (地獄) | 13 | 特殊 |
| kangping (康平) | 12 | 村莊 |
| tianshi (天師派) | 12 | 門派 |
| baolian (寶蓮寺) | 11 | 門派 |
| buxuan (步玄派) | 11 | 門派 |
| graveyard (墓園) | 11 | 野外 |
| langyi (瑯夷) | 11 | 門派 |
| lee (李家村) | 11 | 村莊 |
| manglin (莽林) | 11 | 野外 |
| sanyen (三掩) | 11 | 城鎮 |
| tianyue (天月庵) | 11 | 門派 |
| yinjiao (隱教) | 11 | 門派 |
| kuxiao (哭笑門) | 10 | 門派 |
| lengmei (冷梅莊) | 10 | 門派 |
| longttu (龍圖丹派) | 10 | 門派 |
| maoshan (茅山派) | 10 | 門派 |
| road (道路) | 10 | 連接 |
| xuantian (玄天教) | 10 | 門派 |
| xueyin (雪吟莊) | 10 | 門派 |
| jianjia (劍甲門) | 9 | 門派 |
| wutuo (武陀) | 9 | 門派 |
| jingji (京畿) | 9 | 城鎮 |
| longan (龍安) | 9 | 城鎮 |
| weiguo (衛國) | 9 | 城鎮 |
| zhenwu (振武軍營) | 9 | 門派 |
| baixiang (白象寺) | 9 | 門派 |
| fengshan (封山派) | 9 | 門派 |
| hudao (虎刀門) | 9 | 門派 |

### 缺少的原版區域 (12 個)

| 區域 | 中文 | 優先度 |
|------|------|--------|
| canyon | 峽谷 | 中 |
| chuenyu | 泉域 | 中 |
| city | 城市 | 高 |
| death | 死亡領域 | 高 |
| force | 內功修練區 | 中 |
| goathill | 羊山 | 低 |
| green/green.n | 草原 | 中 |
| ice | 冰域 | 中 |
| jail | 監獄 | 低 |
| latemoon | 晚月 | 低 |
| temple | 神殿 | 中 |
| village | 村莊 | 中 |
| waterfog | 水霧 | 中 |

---

## 6. 狀態效果系統 — 28.6% 完成

| 狀態 | 狀態 |
|------|------|
| drunk (醉酒) | ✅ |
| poison (中毒) | ✅ |
| bandaged (包紮) | ❌ |
| iceshock (冰凍) | ❌ |
| rose_poison (玫瑰毒) | ❌ |
| slumber_drug (迷藥) | ❌ |
| snake_poison (蛇毒) | ❌ |

---

## 7. 幫助文件 — ~14% 完成

已有：11 個種族幫助文件

缺少：
- 9 個職業幫助文件
- 18 個門派幫助文件
- 27+ 個技能幫助文件
- 指令幫助文件（look, fight, inventory, etc.）
- 新手指南系統

---

## 8. 裝備系統 — ~36% 完成

已有 18 件 obj/weapon/ 裝備 + 散落在各 NPC obj 中的裝備

缺少：
- 系統化的防具體系（頭盔、鎧甲、護腕、靴子）
- 飾品系統（戒指、項鏈、腰帶）
- 天地靈裝備套組
- 裝備強化/升級系統

---

## 待實作優先順序

### P0 — 核心系統完善
1. 高優先技能 daemon (buddhism, taoism, literate, stealing, magic, spells, move, perception)
2. 狀態效果 daemon (bandaged, iceshock, rose_poison, slumber_drug, snake_poison)
3. 主線任務系統框架

### P1 — 區域擴展
4. city (城市) 區域 — 重要的遊戲核心區域
5. death (死亡領域) — 死亡系統相關
6. village (村莊) — 基礎野外區域
7. ~~擴展現有小區域~~ ✅ 已完成 — hudao, baixiang, fengshan, longan, jingji, weiguo, zhenwu 各增加 4 房間（共 28 間）

### P2 — 內容豐富
8. 中優先技能 daemon (lotusforce, jingang-staff, iron-cloth, etc.)
9. 野外探索區域 (canyon, ice, green, waterfog, temple)
10. 職業與門派幫助文件
11. 防具與飾品系統

### P3 — 完善細節
12. 低優先技能 daemon
13. 剩餘野外區域 (goathill, jail, latemoon)
14. 技能幫助文件
15. 天地靈任務與裝備
16. 新手指南系統

---

## 與原版 ES2 的差異分析

### 我們有而原版沒有的
- **門派 Daemon 系統** — 原版沒有 `daemon/sect/` 目錄，我們建立了完整的18門派系統
- **種族 Daemon 系統** — 原版沒有 `daemon/race/` 目錄，我們有11種族 daemon
- **門派專屬區域** — 每個門派都有獨立的區域（房間、NPC、物品）
- **更多城鎮** — wutang、lijun、baihua、kangping、jingji、longan、weiguo 等

### 原版有而我們缺少的
- **44個技能 daemon** — 原版71個，我們27個
- **12個野外區域** — canyon, ice, green, waterfog 等探索區域
- **5個狀態效果** — bandaged, iceshock, rose_poison, slumber_drug, snake_poison
- **更多職業分支** — 原版14職業我們整合為9種（設計選擇，非缺失）
