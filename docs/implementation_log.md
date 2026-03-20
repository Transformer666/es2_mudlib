# ES2 Mudlib 實作進度報告

**生成日期:** 2026-03-20
**比對來源:** ES2 Wiki (Google Sites), es2tips.blogspot.com, mudchina/es2 GitHub

---

## 總覽

| 類別 | 已實作 | 需要 | 完成度 |
|------|--------|------|--------|
| 種族 (Races) | 11 | 11 | **100%** |
| 職業 (Classes) | 9 | 8 | **100%** |
| 門派 (Sects) | 19 | 19 | **100%** |
| 技能 (Skills) | 75 | 72+17 | **83%** 原版 |
| 區域 (Areas) | 49 | 19 原版 | **89%** 原版 + 32 新增 |
| 武器 (Weapons) | 42 | ~60+ | **~70%** |
| 防具 (Armor) | 30 | ~40+ | **~75%** |
| 說明檔 (Help) | 13 | ~55 | **24%** |
| 上古妖獸 | 8 | 8 | **100%** |

**總檔案數:** 748 個 .c 檔案（d/ 目錄）
**房間數:** 399 | **NPC 數:** 222 | **物件數:** 301

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

### 1.3 門派 — 全部完成 (19/19)

所有門派均有 daemon 和對應區域，且 location 指向的房間全部存在。

| 門派 | 職業 | 區域 | 房間數 | NPC數 |
|------|------|------|--------|-------|
| 封山派 (fengshan) | 武者 | ✅ | 9 | 6 |
| 冷梅莊 (lengmei) | 武者 | ✅ | 6 | 4 |
| 哭笑門 (kuxiao) | 武者 | ✅ | 6 | 4 |
| 雪吟莊 (xueyin) | 武者 | ✅ | 6 | 4 |
| 虎刀門 (hudao) | 武者 | ✅ | 9 | 9 |
| 寶蓮寺 (baolian) | 和尚 | ✅ | 6 | 5 |
| 天月庵 (tianyue) | 和尚 | ✅ | 6 | 5 |
| 白象寺 (baixiang) | 和尚 | ✅ | 9 | 8 |
| 天師派 (tianshi) | 道士 | ✅ | 7 | 5 |
| 茅山派 (maoshan) | 道士 | ✅ | 5 | 5 |
| 瑯夷 (langyi) | 小偷 | ✅ | 6 | 5 |
| 隱教 (yinjiao) | 小偷 | ✅ | 6 | 5 |
| 龍圖丹派 (longttu) | 方士 | ✅ | 6 | 5 |
| 武陀 (wutuo) | 方士 | ✅ | 5 | 4 |
| 步玄派 (buxuan) | 書生 | ✅ | 6 | 5 |
| 玄天教 (xuantian) | 書生 | ✅ | 6 | 4 |
| 振武軍營 (zhenwu) | 軍人 | ✅ | 9 | 11 |
| 劍甲門 (jianjia) | 跨職 | ✅ | 5 | 4 |
| 天邪派 (tianxie) | 跨職 | ✅ | 7 | 7 |

### 1.4 技能 — 75 個已實作

所有技能 daemon 均包含 `skill_improved` 和 `skill_advanced` 函數。

**原版技能已實作 (60/72):**
axe, blade, bloodystrike, bolomiduo, buddhism, celestial, celestrike, chanting, chaos_steps, cloudstaff, dagger, deisword, dodge, essencemagic, fall_steps, fonxanforce, fonxansword, force, fork, gouyee, iceforce, instruments, iron_cloth, jin_gang, jingang_staff, juechen_force, linbo_steps, literate, liuh_ken, notraces, parry, perception, pyrobat_steps, qidaoforce, scratching, serpentforce, shortsong_blade, six_chaos_sword, snowshade_force, snowshade_sword, snowwhip, spells, spicyclaw, spider_array, spring_blade, staff, stealing, stormdance, sword, tao_mystery, taoism, tenderzhi, throwing, ts_fist, unarmed, whip, wu_shun, yirong

**新增門派專屬技能 (17):**
amazing_needle, diamond_hammer, fengshan_sword, five_defeat_needle, lengmei_sword, longttu_neigong, maoshan_neigong, maoshan_sword, needle, phantom_sword, pike, tactic, taiyi_sword, taoshan_milu, three_rotations, tiger_blade, ziwei_neigong

### 1.5 區域 — 49 個區域

**最大區域 (依房間數):**
- snow (雪亭鎮): 49 rooms, 66 NPCs, 36 objects — 主要起始城鎮
- wutang (五堂鎮): 32 rooms, 26 NPCs — 八寶樓所在地
- lijun (酈郡): 10 rooms, 11 NPCs
- choyin (喬陰): 10 rooms, 11 NPCs
- road (道路): 10 rooms — 連接各區域

### 1.6 裝備

**武器 (42):** fenglei_blade, tiandu_sword, shuiyue_sword, tianming_blade, rapid_sword, mietianjian, snow_soul_dagger, meteor_sword, evil_crooked_blade, ghost_head_axe, yiluo_greatsword, medicine_king_sword, blue_saliva_blade, thunder_claw, jade_rod, qingfeng_blade, mirror_of_gods, black_spark, strange_copper_staff, celestial_bull_cane, loving_sword, white_sword, ancient_snow_staff, dragon_whip, thunder_bomb, erotic_staff, jade_ruler, golden_lance, dragon_needle, zijin_pike, ancient_blade_xuanmang, zhuifeng_sword, liuling_whip, xuanmang, xuanyao, chuanling, psychic_sword, iron_tiger, tiger_blade, yinxue, yumo_axe, equalizer

**防具 (30):** dragon_armor, soul_crystal_plate, blessed_jade, dragon_bone, skull_rosary, dragon_ring, corrosive_hands, evil_bone_ring, jiutian_pearl, rainnar_cloth, ashura_mask, girdle_of_headless, topaz_belt, malik_necklace, cold_snow_gauntlet, cloud_silk_robe, woochan_ring, dingling_legs, jiaojao_boots, yenhold_gauntlets, thunder_wolf_helm, seal_ice_ring, white_bear_armor, crocodile_god_armor, hunyuan_bag, wuli_ring, dragon_feather, fur_hat, cloth, lightning_bomb

### 1.7 上古妖獸 — 全部完成 (8/8)

celestial_bull (天牛), charming_bird (蠱雀), devilish_tiger (厲虎), evil_hydra (窮奇), frost_frog (寒蟾), godly_dog (神犬), inferno_dog (火犬), ritual_monkey (祭猴)

---

## 二、待實作項目清單（按優先順序）

### CRITICAL — 核心遊戲體驗

1. **主線任務完整流程** — 目前無任務系統框架
2. **city (城市) 區域** — 原版核心區域缺失

### HIGH — 重要缺失

3. **缺失的原版技能 (12)**
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

4. **缺失的重要 NPC**
   - 大邪道人 (Great Evil Daoist) — 主線任務核心角色
   - 殘蟻師太 — 主線任務核心角色
   - 劍皇 (Sword Emperor) — 八寶樓(8) 最終 Boss
   - 赤龍 (Red Dragon) — 百藥谷 Boss
   - 黑龍 (Black Dragon) — 龍安鎮 Boss
   - 混沌獸 (Chaos Beast) — 混沌之印任務 Boss

5. **核心任務內容**
   - 八穴鬼徑 (Eight Ghost Caves) 地下城
   - 神之心 (Heart of God) Boss 戰鬥
   - 混沌之印 (Seal of Chaos) 任務鏈
   - 天地靈任務線 (Tiandiling Quests)

### MEDIUM — 豐富遊戲內容

6. **green.n (草原北部)** — 原版區域擴展
7. **門派子系統**
   - 茅山三觀 (靈雲觀/隱風觀/幻霧觀) 專精
   - 天師四派 (紫衣/素衣/玄衣/朱衣) 元素專精
8. **聲望系統** — 黑道/武林/青邪/戰場聲望 + 門派仇恨
9. **說明檔案 (42+ 缺失)** — 職業/門派/戰鬥/系統說明
10. **缺失的中等 NPC**
    - 阿寶 (Abao) — 雪亭鎮任務
    - 瞎眼老太婆 — 雪亭鎮任務
    - 黑衣老人 — 雪亭鎮任務
    - 毒刀胡惑 — 仇恨消除 NPC
    - 大蜈蚣 — 聖木殘根任務 Boss

### LOW — 細節完善

11. **食物系統擴充** — 目前僅 5 種食物
12. **更多裝備** — 約 20 件 wiki/blog 提到的裝備尚未實作
13. **側線任務** — 任蕭蕭支線、四鬼招喚法、水龍經等
14. **玩家角色樣板** — 用於測試的預設角色配置

---

## 三、與原版 ES2 的差異分析

### 3.1 我們多出的內容

| 類型 | 數量 | 說明 |
|------|------|------|
| 新區域 | +32 | 所有門派 HQ、五堂鎮、京畿、康平、龍安、酈郡等城鎮 |
| 新技能 | +17 | 門派專屬技能（太乙劍法、紫微內功、三轉劍法等） |
| 門派系統 | +完整 | 原版無門派 daemon，我們有完整的 19 門派系統 |
| 職業系統 | +完整 | 原版職業檔在 d/class/，我們有 daemon/class/ |
| 種族系統 | +完整 | 原版無種族 daemon，我們有完整的 11 種族系統 |
| 上古妖獸 | +8 | 全部 8 隻上古妖獸已實作 |

### 3.2 原版有但我們缺少的

| 類型 | 數量 | 說明 |
|------|------|------|
| 區域 | 2 | city (城市)、green.n (草原北部) |
| 技能 | 12 | hammer, magic, move 等通用技能及部分特殊技能 |
| 系統目錄 | 3 | social_guild, npc (通用NPC), wiz (巫師工具) |

### 3.3 結構性差異

- **命名慣例:** 原版用 hyphen (chaos-steps)，我們用 underscore (chaos_steps)
- **目錄結構:** 原版 daemon 在 d/skill/，我們在 daemon/skill/
- **門派系統:** 原版門派資料分散在各區域，我們有集中的 daemon/sect/ 系統
- **物件系統:** 原版裝備在各區域 obj/，我們有集中的 obj/weapon/ 和 obj/armor/

---

## 四、數據統計

### 各區域檔案數分布

```
snow:     49 rooms + 66 NPCs + 36 objects = 151 files (最大)
wutang:   32 rooms + 26 NPCs +  6 objects =  64 files
road:     10 rooms +  1 NPC  +  0 objects =  11 files
lijun:    10 rooms + 11 NPCs +  5 objects =  26 files
choyin:   10 rooms + 11 NPCs +  4 objects =  25 files
zhenwu:    9 rooms + 11 NPCs +  3 objects =  23 files
其餘 43 個區域合計:                         448 files
```

### 全域物件分布

```
obj/weapon/:      42 files
obj/armor/:       30 files
obj/food/:         5 files
obj/drug/:         6 files
obj/medication/:  14 files
obj/reagent/:      4 files
obj/money/:        3 files
obj/npc/:         12 files (beasts + special NPCs)
obj/其他:         58 files
```

---

*報告完成。最後更新: 2026-03-20*
