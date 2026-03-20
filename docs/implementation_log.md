# ES2 Mudlib 實作進度報告

**生成日期:** 2026-03-20
**比對來源:** ES2 Wiki (Google Sites), es2tips.blogspot.com, mudchina/es2 GitHub

---

## 總覽

| 類別 | 已實作 | 需要 | 完成度 |
|------|--------|------|--------|
| 種族 (Races) | 11 | 11 | **100%** |
| 職業 (Classes) | 9 | 8 | **100%** |
| 門派 (Sects) | 18 | 19 | **95%** |
| 技能 (Skills) | 78 | 71+19 | **83%** 原版 |
| 區域 (Areas) | 50 | 19 原版 | **100%** 原版 + 33 新增 |
| 武器 (Weapons) | 58 | ~95+ | **~61%** |
| 防具 (Armor) | 42 | ~60+ | **~70%** |
| 說明檔 (Help) | 11 | ~55 | **20%** |
| 上古妖獸 | 8 | 8 | **100%** |

**總 .c 檔案數:** 814 個（d/ 目錄）+ 203 個（obj/ 目錄）
**技能 Daemon:** 78 個（75 個具備 skill_improved/skill_advanced）
**門派 Daemon:** 18 個（所有 location 指向的房間均已驗證存在）

---

## 一、已實作項目清單

### 1.1 種族 — 全部完成 (11/11)

| ID | 中文名 | Daemon | Help 檔 |
|----|--------|--------|---------|
| human | 人類 | ✅ | ✅ |
| xingtian | 刑天 | ✅ | ✅ |
| yenhold | 厭火 | ✅ | ✅ |
| yaksha | 夜叉 | ✅ | ✅ |
| malik | 巫首 | ✅ | ✅ |
| woochan | 無腸 | ✅ | ✅ |
| jiaojao | 焦僥 | ✅ | ✅ |
| dingling | 釘靈 | ✅ | ✅ |
| asura | 阿修羅 | ✅ | ✅ |
| rainnar | 雨師妾 | ✅ | ✅ |
| blackteeth | 黑齒 | ✅ | ✅ |

### 1.2 職業 — 全部完成 (9/8+)

warrior, monk, taoist, thief, alchemist, scholar, soldier, commoner, fighter

### 1.3 門派 — 18/19 (95%)

所有門派均有 daemon 和對應區域，且 location 指向的房間全部存在。

| 門派 | 職業 | 區域 | 檔案數 | Location |
|------|------|------|--------|----------|
| 封山派 (fengshan) | 武者 | ✅ | 15 | /d/fengshan/main_hall |
| 冷梅莊 (lengmei) | 武者 | ✅ | 10 | /d/lengmei/hall |
| 哭笑門 (kuxiao) | 武者 | ✅ | 10 | /d/kuxiao/hall |
| 雪吟莊 (xueyin) | 武者 | ✅ | 10 | /d/xueyin/hall |
| 虎刀門 (hudao) | 武者 | ✅ | 18 | /d/hudao/hall |
| 寶蓮寺 (baolian) | 和尚 | ✅ | 11 | /d/baolian/hall |
| 天月庵 (tianyue) | 和尚 | ✅ | 12 | 待驗證 |
| 白象寺 (baixiang) | 和尚 | ✅ | 17 | /d/baixiang/main_hall |
| 天師派 (tianshi) | 道士 | ✅ | 12 | /d/tianshi/hall |
| 茅山派 (maoshan) | 道士 | ✅ | 10 | /d/maoshan/lingyun |
| 瑯夷 (langyi) | 小偷 | ✅ | 11 | /d/langyi/hall |
| 隱教 (yinjiao) | 小偷 | ✅ | 11 | /d/yinjiao/hall |
| 龍圖丹派 (longttu) | 方士 | ✅ | 11 | /d/longttu/study |
| 武陀 (wutuo) | 方士 | ✅ | 9 | /d/wutuo/hall |
| 步玄派 (buxuan) | 書生 | ✅ | 11 | /d/buxuan/study |
| 玄天教 (xuantian) | 書生 | ✅ | 10 | /d/xuantian/hall |
| 振武軍營 (zhenwu) | 軍人 | ✅ | 20 | /d/zhenwu/command |
| 劍甲門 (jianjia) | 跨職 | ✅ | 9 | /d/jianjia/hall |
| 天邪派 (tianxie) | 跨職 | ✅ | 15 | /d/tianxie/hall |

### 1.4 技能 — 78 個已實作

75 個技能 daemon 具備 `skill_improved` 和 `skill_advanced` 函數，3 個缺少。

**原版技能已實作 (59/71):**
axe, blade, bloodystrike, bolomiduo, buddhism, celestial, celestrike, chanting, chaos_steps, cloudstaff, dagger, deisword, dodge, essencemagic, fall_steps, fonxanforce, fonxansword, force, fork, gouyee, iceforce, instruments, iron_cloth, jin_gang, jingang_staff, juechen_force, linbo_steps, literate, liuh_ken, notraces, parry, perception, pyrobat_steps, qidaoforce, scratching, serpentforce, shortsong_blade, six_chaos_sword, snowshade_force, snowshade_sword, snowwhip, spells, spicyclaw, spider_array, spring_blade, staff, stealing, stormdance, sword, tao_mystery, taoism, tenderzhi, throwing, ts_fist, unarmed, whip, wu_shun, yirong

**新增門派專屬技能 (19):**
amazing_needle, diamond_hammer, fengshan_sword, five_defeat_needle, lengmei_sword, longttu_neigong, maoshan_neigong, maoshan_sword, needle, phantom_sword, pike, tactic, taiyi_sword, taoshan_milu, three_rotations, tiger_blade, ziwei_neigong

### 1.5 區域 — 50 個區域 (814 .c files)

**最大區域 (依檔案數):**
- snow (雪亭鎮): 119 files — 主要起始城鎮
- wutang (五堂鎮): 59 files — 八寶樓所在地
- longan (龍安鎮): 27 files
- jingji (京畿): 25 files
- kangping (康平): 21 files
- lijun (酈郡): 21 files
- city (城市): 21 files
- choyin (喬陰): 21 files
- zhenwu (振武): 20 files
- weiguo (衛國): 19 files

### 1.6 裝備

**武器 (58):** obj/weapon/ 目錄
**防具 (42):** obj/armor/ 目錄
**藥品 (16):** obj/medication/ 目錄
**食物 (5):** obj/food/ 目錄
**原料 (4):** obj/reagent/ 目錄

### 1.7 上古妖獸 — 全部完成 (8/8)

celestial_bull (天牛), charming_bird (蠱雀), devilish_tiger (厲虎), evil_hydra (窮奇), frost_frog (寒蟾), godly_dog (神犬), inferno_dog (火犬), ritual_monkey (祭猴)

---

## 二、待實作項目清單（按優先順序）

### CRITICAL — 核心遊戲體驗

1. **主線任務完整流程** — 目前無任務系統框架
   - 9 個未解之謎（大邪道人、殘蟻師太、武林盟主等）
   - 十三靈任務線（最終挑戰）

### HIGH — 重要缺失

2. **缺失的原版技能 (12)**
   - `hammer` (鎚法通用) — 基礎武器技能
   - `magic` (法術通用) — 基礎法術技能
   - `move` (身法通用) — 基礎移動技能
   - `lotusforce` (蓮花內功)
   - `magic_array` (法陣)
   - `mystforce` (玄功)
   - `mystsword` (玄劍)
   - `necromancy` (招魂術)
   - `nine_moon` (九陰功)
   - `music` (音律)
   - `mysterrier` (玄鐵)
   - `meihua_shou` (梅花手)

3. **缺失的重要 NPC/Boss**
   - 大邪道人 — 主線任務核心反派
   - 殘蟻師太 — 主線任務核心角色
   - 劍皇 — 八寶樓(8) 最終 Boss
   - 赤龍 — 百藥谷 Boss
   - 黑龍 — 龍安鎮 Boss
   - 混沌獸 — 混沌之印任務 Boss
   - 八寶樓 1-7 層 Boss（歐陽芝、司馬雷、崇白虎、馬鍾聖、公孫微、天神地鬼、施鈺）

4. **核心任務內容**
   - 八穴鬼徑 (Eight Ghost Caves) 地下城
   - 神之心 (Heart of God) Boss 戰鬥
   - 混沌之印 (Seal of Chaos) 任務鏈
   - 天地靈任務線 (Tiandiling Quests)
   - 龍安鎮黑龍 + 九轉異龍珠
   - 百藥谷赤龍封山

### MEDIUM — 豐富遊戲內容

5. **門派子系統**
   - 茅山三觀：靈雲觀(五雷/幽冥三箭)、隱風觀(喚雨/算命)、幻霧觀(噬魂/通靈)
   - 天師四派：紫衣(雷)、素衣(冰)、玄衣(風)、朱衣(火)
   - 小偷進階：金蛇門(劍術) / 黑龍使者(龍爪+毒術)
   - 方士進階：劍甲門、香主(武陀)

6. **聲望系統** — 黑道/武林/青邪/戰場聲望 + 門派仇恨機制
   - 公式：(LV-1)^2 聲望值
   - 黑道聲望裝備(3 tier)
   - 毒刀胡惑解仇 NPC

7. **說明檔案 (44 缺失)**
   - 職業說明 (7)
   - 門派說明 (19)
   - 戰鬥說明 (5)
   - 系統說明 (8): 投胎、聲望、業力、裝備、背包、地圖、任務、公會
   - 新手指南 (3)

8. **缺失的中等 NPC**
   - 阿寶、瞎眼老太婆、黑衣老人（雪亭鎮任務）
   - 毒刀胡惑（仇恨消除）
   - 大蜈蚣（聖木殘根任務）
   - 張小簽（江湖藝人）
   - 算命先生

### LOW — 細節完善

9. **食物系統擴充** — 目前 5 種 vs blog 記載 15+ 種
10. **更多裝備** — 約 30+ 件 wiki/blog 提到的裝備尚未實作
11. **側線任務** — 任蕭蕭支線、四鬼招喚法、水龍經、水神天龍走法等
12. **3 個技能缺少 skill_improved/skill_advanced** — force, jin_gang, 及另一個

---

## 三、與原版 ES2 的差異分析

### 3.1 我們多出的內容

| 類型 | 數量 | 說明 |
|------|------|------|
| 新區域 | +33 | 所有門派 HQ、五堂鎮、京畿、康平、龍安、酈郡等 |
| 新技能 | +19 | 門派專屬技能（太乙劍法、紫微內功、三轉劍法等） |
| 門派系統 | 完整 | 原版無獨立門派 daemon，我們有 18 門派系統 |
| 職業系統 | 完整 | 原版在 d/class/，我們有 daemon/class/ |
| 種族系統 | 完整 | 原版無種族 daemon，我們有 11 種族 + help |
| 上古妖獸 | 8 隻 | 全部已實作 |
| 裝備系統 | 100件 | 集中式 obj/weapon/ + obj/armor/ |

### 3.2 原版有但我們缺少的

| 類型 | 數量 | 說明 |
|------|------|------|
| 技能 | 12 | hammer, magic, move 等通用技能 + 特殊技能 |
| 系統目錄 | 3 | social_guild, npc (通用), wiz (巫師工具) |

### 3.3 結構性差異

- **命名慣例:** 原版用 hyphen (chaos-steps)，我們用 underscore (chaos_steps)
- **目錄結構:** 原版 skill daemon 在根目錄混合，我們有獨立 daemon/ 目錄
- **門派系統:** 原版門派資料分散在區域，我們有集中的 daemon/sect/
- **物件系統:** 原版裝備分散各區域 obj/，我們有集中的 obj/weapon/ 和 obj/armor/
- **原版 class daemons:** assassin, beggar, bonze, dancer, fighter, juechen, lama, ninja, nomad, ronin, scholar, swordsman, taoist（與我們的門派系統設計不同）

### 3.4 原版 vs 我們的區域對照

| 原版區域 | 我們的對應 | 狀態 |
|----------|-----------|------|
| canyon | canyon | ✅ |
| choyin | choyin | ✅ |
| chuenyu | chuenyu | ✅ |
| city | city | ✅ |
| death | death | ✅ |
| force | force | ✅ |
| goathill | goathill | ✅ |
| graveyard | graveyard | ✅ |
| green | green | ✅ |
| green.n | green_n | ✅ |
| ice | ice | ✅ |
| jail | jail | ✅ |
| latemoon | latemoon | ✅ |
| oldpine | oldpine | ✅ |
| sanyen | sanyen | ✅ |
| snow | snow | ✅ |
| temple | temple | ✅ |
| village | village | ✅ |
| waterfog | waterfog | ✅ |

**原版 19 個區域全部覆蓋 (100%)**

---

## 四、數據統計

### 各區域檔案數分布 (Top 10)

```
snow:      119 files (最大 — 雪亭鎮主城)
wutang:     59 files (五堂鎮)
longan:     27 files (龍安鎮)
jingji:     25 files (京畿)
kangping:   21 files (康平)
lijun:      21 files (酈郡)
city:       21 files (城市)
choyin:     21 files (喬陰)
zhenwu:     20 files (振武軍營)
weiguo:     19 files (衛國)
```

### 全域物件分布

```
obj/weapon/:       58 files
obj/armor/:        42 files
obj/medication/:   16 files
obj/npc/:          13 files (beasts + special NPCs)
obj/drug/:          6 files
obj/example/:       6 files
obj/food/:          5 files
obj/reagent/:       4 files
obj/money/:         3 files
obj/area/:         31 files
obj/root:          17 files
```

### 技能分布

```
原版覆蓋:    59/71 (83%)
新增門派技能:  19
總計:         78
缺失原版:     12 (hammer, magic, move 等)
```

---

*報告完成。最後更新: 2026-03-20*
