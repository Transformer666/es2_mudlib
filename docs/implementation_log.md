# ES2 MUD 實作進度報告

> 產生日期：2026-03-20
> 資料來源：ES2 Wiki (sites.google.com/site/es2mud)、es2tips Blog (120+ 篇)、mudchina/es2 原版 repo

---

## 總覽

| 類別 | 需要 | 已實作 | 缺少 | 完成度 |
|------|------|--------|------|--------|
| 種族 (Races) | 11 | 11 | 0 | **100%** |
| 職業 (Classes) | 9 | 9 | 0 | **100%** |
| 門派 (Sects) | 18 | 18 | 0 | **100%** |
| 技能 (Skills) | 71 | 27 | 44 | **38.0%** |
| 區域 (Areas) | 20 orig | 37 | 13 missing | **75%** |
| 狀態效果 (Conditions) | 7 | 2 | 5 | **28.6%** |
| 幫助文件 (Help) | ~80+ | 11 | ~70+ | **~14%** |
| 裝備武器 (Weapons) | ~42+ | 18 | ~24+ | **~43%** |
| 裝備防具 (Armor) | ~30+ | 10 | ~20+ | **~33%** |
| 消耗品 (Consumables) | ~20+ | 15 | ~5+ | **~75%** |

**整體完成度估計：~54.6%**

---

## 程式碼統計

| 項目 | 數量 |
|------|------|
| 區域 .c 檔案 | 621 |
| NPC 檔案 | 173 |
| NPC 物品檔案 | 120 |
| Daemon 檔案 | 70 |
| obj/weapon | 18 |
| obj/armor | 10 |
| obj/drug | 6 |
| obj/food | 5 |
| obj/reagent | 4 |
| Help 文件 | 11 |
| 區域目錄 | 37 |

---

## 1. 種族系統 — 100% 完成

全部 11 種族均已實作（daemon + help file）：

| Wiki 名稱 | 我們的 ID | 狀態 |
|-----------|----------|------|
| 人族 Human | human | ✅ |
| 刑天 Headless | xingtian | ✅ |
| 厭火 Yenhold | yenhold | ✅ |
| 夜叉 Yaksa | yaksha | ✅ |
| 巫首 Malik | malik | ✅ |
| 無腸 Woochan | woochan | ✅ |
| 焦僥 Jiaojao | jiaojao | ✅ |
| 釘靈 Dingling | dingling | ✅ |
| 阿修羅 Ashura | asura | ✅ |
| 雨師妾 Rainnar | rainnar | ✅ |
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

| 門派 | Daemon | 區域檔案數 | 所屬職業 |
|------|--------|-----------|----------|
| 封山派 fengshan | ✅ | 15 | 武者 |
| 冷梅莊 lengmei | ✅ | 10 | 武者 |
| 哭笑門 kuxiao | ✅ | 10 | 武者 |
| 雪吟莊 xueyin | ✅ | 10 | 武者 |
| 虎刀門 hudao | ✅ | 17 | 武者 |
| 寶蓮寺 baolian | ✅ | 11 | 和尚 |
| 天月庵 tianyue | ✅ | 11 | 和尚 |
| 白象寺 baixiang | ✅ | 17 | 和尚 |
| 天師派 tianshi | ✅ | 12 | 道士 |
| 茅山派 maoshan | ✅ | 10 | 道士 |
| 瑯夷 langyi | ✅ | 11 | 小偷 |
| 隱教 yinjiao | ✅ | 11 | 小偷 |
| 龍圖丹派 longttu | ✅ | 10 | 方士 |
| 武陀 wutuo | ✅ | 9 | 方士 |
| 步玄派 buxuan | ✅ | 11 | 書生 |
| 玄天教 xuantian | ✅ | 10 | 書生 |
| 振武軍營 zhenwu | ✅ | 19 | 軍人 |
| 天邪派 tianxie | ✅ | 14 | 跨門派 |
| 劍甲門 jianjia | ✅ | 9 | 跨門派(方士) |

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

### 低優先缺失技能 (23)

bloodystrike, bolomiduo, chanting, chaos-steps, deisword, essencemagic, fall-steps, fonxanforce, fonxansword, fork, gouyee, instruments, juechen-force, linbo-steps, liuh-ken, magic-array, meihua-shou, mysterrier, mystforce, mystsword, necromancy, nine-moon, pyrobat-steps, qidaoforce, scratching, shortsong-blade, six-chaos-sword, snowshade-force, snowshade-sword, snowwhip, spicyclaw, spider-array, spring-blade, stormdance, tao-mystery, tenderzhi, ts-fist, wu-shun, yirong

---

## 5. 區域系統 — 75% 完成

### 已實作區域 (37 個，621 個 .c 檔)

| 區域 | 檔案數 | 類型 |
|------|--------|------|
| snow (雪亭鎮) | 112 | 主城（起始區域） |
| wutang (武唐城) | 50 | 主城 |
| lijun (離郡) | 21 | 城鎮 |
| choyin (喬陰) | 20 | 城鎮 |
| zhenwu (振武軍營) | 19 | 門派 |
| weiguo (衛國) | 19 | 城鎮 |
| longan (龍安) | 18 | 城鎮 |
| jingji (京畿) | 18 | 城鎮 |
| hudao (虎刀門) | 17 | 門派 |
| baixiang (白象寺) | 17 | 門派 |
| fengshan (封山派) | 15 | 門派 |
| chixiao (赤霄) | 15 | 村莊 |
| baihua (百花) | 15 | 村莊 |
| tianxie (天邪派) | 14 | 門派 |
| oldpine (古松林) | 14 | 野外 |
| heifeng (黑風) | 13 | 野外 |
| hell (地獄) | 13 | 特殊 |
| tianshi (天師派) | 12 | 門派 |
| kangping (康平) | 12 | 村莊 |
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
| wutuo (武陀) | 9 | 門派 |
| jianjia (劍甲門) | 9 | 門派 |

### 缺少的原版區域 (13 個)

| 區域 | 中文 | 優先度 |
|------|------|--------|
| city | 城市 | 高 |
| death | 死亡領域 | 高 |
| village | 村莊 | 高 |
| canyon | 峽谷 | 中 |
| chuenyu | 泉域 | 中 |
| force | 內功修練區 | 中 |
| green/green.n | 草原 | 中 |
| ice | 冰域 | 中 |
| temple | 神殿 | 中 |
| waterfog | 水霧 | 中 |
| goathill | 羊山 | 低 |
| jail | 監獄 | 低 |
| latemoon | 晚月 | 低 |

---

## 6. 狀態效果系統 — 28.6% 完成

| 狀態 | 完成 |
|------|------|
| drunk (醉酒) | ✅ |
| poison (中毒) | ✅ |
| bandaged (包紮) | ❌ |
| iceshock (冰凍) | ❌ |
| rose_poison (玫瑰毒) | ❌ |
| slumber_drug (迷藥) | ❌ |
| snake_poison (蛇毒) | ❌ |

---

## 7. 裝備系統

### 武器 — 18 件已實作 (obj/weapon/)

穿靈、盤龍針、毒龍鞭、毒刀胡惑、交歡杖、金龍豹紋槍、鐵虎、玉戒尺、蔑天劍、靈通劍、疾風劍、霹靂雷火彈、虎刀、旋芒、玄妖、銀血、域摩斧、紫金鳳頭錐

### 防具/飾品 — 10 件已實作 (obj/armor/)

萬福寶玉、布衣、腐蝕之手、怒龍錦冑、靈骨、龍戒、皮帽、霹靂雷火彈、白骨念珠、靈魂水晶

### Blog 記錄中尚未實作的裝備

**武器 (24件)：**
寒玉藥杵、清風刀、封神寶鏡、離玄光熾、玄烏杖、饕餮法杖、歸心似劍、白色長劍、萬年雪、雷熊爪、藍涎刀、藥王神劍、易羅大劍、鬼頭劈象刀、雪魂匕、追月流星劍、邪門歪刀、天都劍、水月劍、天命刃、風雷刀、追風劍、六靈妖姬鞭、古刃旋芒

**防具/飾品 (20件)：**
雨師妾袍、修羅之面、形天之怒、黃玉佩、巫首項鍊、冷雪手護、雲羅絲衣、無腸寶珠、釘靈腿護、焦僥靴、厭火之拳、雷火天狼罩、龍思羽、封印冰環、混元一氣袋、邪骨指環、九天鳳珠、舞璃戒指、鱷神系列裝備、白熊系列裝備

---

## 8. 幫助文件 — ~14% 完成

已有：11 個種族幫助文件

缺少：
- 9 個職業幫助文件
- 18 個門派幫助文件
- 27+ 個技能幫助文件
- 指令幫助文件（look, fight, inventory, etc.）
- 系統幫助文件（about, attribute, combat, etc.）
- 故事幫助文件（history, myth, story, theme）
- 新手指南系統

原版 ES2 有 36 個 help 文件：about, armor, attitude, attribute, board, channels, cmds, combat, damage, force, gift, guild, health, history, magic, map.es2, martial, material, myth, newbie, plan, quest, rank, rules, settings, setup, skill, start, stats, story, taoist, theme, topics, weapon, whatsnew, wiz_rules

---

## 9. 重要 NPC 實作狀況

### 已實作的重要 NPC

| NPC | 位置 | 來源 |
|-----|------|------|
| 駱易 | snow | blog boss 戰鬥 |
| 梅影風 | lengmei + snow | wiki 冷梅莊莊主 |
| 劉乙忘玄 | kuxiao + snow | wiki 哭笑門門主 |
| 韓笑 | hudao | wiki 虎刀門掌門 |
| 柳東蘆 | fengshan | wiki 封山派 |
| 李東靈 | tianxie | blog 大魔頭 |
| 歐陽無極 | maoshan | wiki 茅山觀主 |
| 魚鐵山 | snow | wiki 雪吟莊莊主 |
| 天靈 | chixiao | wiki 天靈任務 |
| 地靈 | chixiao + hell | wiki 地靈任務 |
| 杞庸 | manglin | wiki 傳授武功的少年 |
| 郭布 | wutang | wiki 五堂鎮 |

### 尚未實作的重要 NPC

| NPC | 說明 | 優先度 |
|-----|------|--------|
| 黑無常 | 勾魂使者 | 中 |
| 白無常 | 勾魂使者 | 中 |
| 八寶樓 8 Boss | 歐陽芝、司馬雷、崇白虎、馬鍾聖、公孫微、天神地鬼、施鈺、劍皇 | 中 |
| 風神 | 風之印記任務 | 中 |
| 水神天龍 | 任務 Boss | 低 |
| 大蜈蚣 | 聖木殘根任務 | 低 |
| 上古妖獸 8 隻 | 鬼獫、靈狙、鸂鷘、天獒、寒蟾、鮫蛟、饕餮、狻猊 | 低 |
| 混沌獸 | 混沌之印任務 | 低 |
| 黑龍 | 龍安鎮任務 | 低 |
| 赤龍 | 百藥谷任務 | 低 |

---

## 10. 任務系統進度

### 部分實作

- 天地靈任務 — 天靈/地靈 NPC 已建立，許願池房間已有，任務物品部分完成
- 門派拜師 — 18 門派都有 master NPC，基本拜師流程存在

### 尚未實作

| 任務 | 來源 | 優先度 |
|------|------|--------|
| 主線任務系統（侮天鬼/十三靈） | wiki | 高 |
| 八寶樓 8 層 Boss rush | blog | 中 |
| 混沌之印+混沌獸 | blog | 中 |
| 龍安鎮+黑龍+九轉異龍珠 | blog | 中 |
| 百藥谷：赤龍+封山 | blog | 中 |
| 大蜈蚣+聖木殘根 | blog | 中 |
| 風神+風之印記 | blog | 中 |
| 老乞婆任務 | blog | 低 |
| 任蕭蕭任務支線 | blog | 低 |
| 八穴鬼徑走法 | blog | 低 |
| 神之心打法 | blog | 低 |

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

### P2 — 內容豐富
7. 中優先技能 daemon (lotusforce, jingang-staff, iron-cloth, etc.)
8. 野外探索區域 (canyon, ice, green, waterfog, temple)
9. 職業與門派幫助文件
10. 防具與飾品系統 (20件 blog 記錄的裝備)
11. 武器補充 (24件 blog 記錄的武器)
12. 勾魂使者 (黑白無常) NPC
13. 八寶樓任務系統

### P3 — 完善細節
14. 低優先技能 daemon
15. 剩餘野外區域 (goathill, jail, latemoon)
16. 技能幫助文件
17. 天地靈任務完善
18. 新手指南系統
19. 上古妖獸 NPC (8隻)
20. 聲望系統完善

---

## 與原版 ES2 的差異分析

### 我們有而原版沒有的
- **門派 Daemon 系統** — 原版沒有 `daemon/sect/` 目錄，我們建立了完整的18門派系統
- **種族 Daemon 系統** — 原版沒有 `daemon/race/` 目錄，我們有11種族 daemon
- **門派專屬區域** — 每個門派都有獨立的區域（房間、NPC、物品），共32個原版沒有的區域
- **更多城鎮** — wutang (50 files)、lijun (21)、baihua (15)、kangping (12)、jingji (18)、longan (18)、weiguo (19) 等
- **防具/飾品系統** — obj/armor/ 有10件獨立防具檔
- **消耗品系統** — obj/drug/ (6), obj/food/ (5), obj/reagent/ (4)

### 原版有而我們缺少的
- **44個技能 daemon** — 原版71個，我們27個
- **13個野外區域** — canyon, ice, green, waterfog 等探索區域
- **5個狀態效果** — bandaged, iceshock, rose_poison, slumber_drug, snake_poison
- **~25個 help 文件** — 原版有36個 player help 文件
- **更多職業分支** — 原版14職業我們整合為9種（設計選擇，非缺失）

### Blog 記錄中確認存在但我們缺少的內容
- **24件武器** — 從 es2tips blog 裝備實錄確認
- **20件防具/飾品** — 種族專屬裝備、套裝系列等
- **8隻上古妖獸** — 鬼獫、靈狙、鸂鷘、天獒、寒蟾、鮫蛟、饕餮、狻猊
- **8層八寶樓 Boss** — 完整的 Boss rush 任務系統
- **多條任務線** — 混沌之印、龍安黑龍、百藥谷赤龍、風神印記等
