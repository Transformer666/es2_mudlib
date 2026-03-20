# Agent Task 04：實作 NPC

## 目標

實作所有缺少的 NPC，包含一般 NPC、商人 NPC、掌門 NPC（含拜師系統）、Boss NPC。

---

## 前置知識

NPC 存放於 `mudlib/d/<area>/npc/`，參考 `automation/CLAUDE.md` 的 NPC 範本。
掌門 NPC 拜師系統參考 `mudlib/d/snow/npc/alchemist.c`。

## 資料來源

Blog NPC/Boss 資料：
```
# 門派掌門 & 師父
https://es2tips.blogspot.com/2014/10/es2.html                         # 職業師父位置總覽
https://es2tips.blogspot.com/2014/08/han-xiao.html                    # 虎刀門掌門 韓笑
https://es2tips.blogspot.com/2014/11/byun.html                        # 振武軍營軍師 必勇
https://es2tips.blogspot.com/2014/08/blog-post.html                   # 龍圖丹派醫師 江述仁

# Boss NPC
https://es2tips.blogspot.com/2014/08/black-hell-agent.html            # 黑無常
https://es2tips.blogspot.com/2014/08/white-hell-agent.html            # 白無常
https://es2tips.blogspot.com/2013/05/blog-post_29.html                # 虎刀門護衛 孫漪
https://es2tips.blogspot.com/2013/05/blog-post_3803.html              # 古劍門掌門 景愈濤
https://es2tips.blogspot.com/2013/05/seal.html                        # 風神
https://es2tips.blogspot.com/2013/05/blog-post_9262.html              # 大蜈蚣

# 八寶樓 Boss（8 層）
https://es2tips.blogspot.com/2013/05/1-book.html                      # 歐陽芝
https://es2tips.blogspot.com/2013/05/2_29.html                        # 司馬雷
https://es2tips.blogspot.com/2013/05/3_29.html                        # 崇白虎
https://es2tips.blogspot.com/2013/05/4.html                           # 馬鍾聖
https://es2tips.blogspot.com/2013/05/5_29.html                        # 公孫微
https://es2tips.blogspot.com/2013/05/6_29.html                        # 天神地鬼
https://es2tips.blogspot.com/2013/05/7.html                           # 施鈺
https://es2tips.blogspot.com/2013/05/8.html                           # 劍皇

# 一般 NPC & 任務 NPC
https://es2tips.blogspot.com/2014/10/beggar-crone-maro-dagger-watermelon.html  # 老乞婆
https://es2tips.blogspot.com/2014/02/blog-post_26.html                # 江湖藝人 張小簽
https://es2tips.blogspot.com/2014/02/fortune-teller-teller-zhang-fortune.html  # 算命先生
https://es2tips.blogspot.com/2014/10/mobnpc-swordbladepikeaxeneedlestaffunar.html  # 物理練功 Mob
https://es2tips.blogspot.com/2014/11/blog-post_9.html                 # 上古妖獸 8 隻
```

Wiki 門派資料（含掌門設定）：
```
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/wu-zhe
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/he-shang
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/xiao-tou
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/fang-shi
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/shu-sheng
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/jun-ren
https://sites.google.com/site/es2mud/home/story-lines/zhi-ye-yu-men-pai/dao-shi
```

## 執行步驟

### Step 1：讀取資料
```
讀取 docs/missing_content.json → missing_npcs 區塊
參考現有 NPC 檔案格式
若 missing 為 0，直接跳過此 task
```

### Step 2：NPC 類型與優先順序

1. **掌門/師父 NPC**（拜師系統 — accept_apprentice/init_apprentice/acquire_skill）
2. **商人 NPC**（F_VENDOR — 各城鎮商店）
3. **Boss NPC**（高等級、特殊裝備掉落）
4. **一般 NPC**（F_VILLAGER/F_FIGHTER — 城鎮居民、守衛、練功怪）

### Step 3：確認房間載入

每個新 NPC 必須確認其所在房間有 `set("objects", ([ __DIR__"npc/xxx" : 1 ]))` 載入。

### Step 4：靜態驗證

- `#include <npc.h>` 存在
- 繼承了有效 NPC 類型（F_FIGHTER/F_VILLAGER/F_SOLDIER/F_SCHOLAR）
- `set_name()`, `set_race()`, `set_level()`, `setup()` 存在
- 掌門 NPC 有完整拜師系統函數

---

## 完成條件

- [ ] 所有缺少的 NPC 建立完成
- [ ] 所有 NPC 的房間載入確認
- [ ] 掌門 NPC 拜師系統完整
- [ ] 靜態驗證通過
