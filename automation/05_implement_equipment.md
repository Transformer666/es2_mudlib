# Agent Task 05：實作裝備道具

## 目標

實作所有缺少的武器、防具和特殊道具。

---

## 前置知識

裝備存放於 `mudlib/d/<area>/npc/obj/` 或 `mudlib/obj/weapon/`、`mudlib/obj/armor/`。
武器數值範圍參考 `automation/CLAUDE.md` 的「武器數值範圍」表格。

## 資料來源

Blog 裝備資料（完整清單見 `automation/01_analyze_missing.md` 1B 節）：

重點頁面：
```
# 裝備總覽
https://es2tips.blogspot.com/2013/05/blog-post_30.html                # 21件裝備總覽
https://es2tips.blogspot.com/2013/05/blog-post_493.html               # 封印雷環等12件
https://es2tips.blogspot.com/2013/05/blog-post_2462.html              # 風雷刀等8把武器

# 傳奇武器
https://es2tips.blogspot.com/2014/10/sword-of-killing-god.html        # 蔑天劍
https://es2tips.blogspot.com/2014/11/dragon-whip.html                 # 毒龍鞭
https://es2tips.blogspot.com/2014/11/golden-beast-lance.html          # 金龍豹紋槍
https://es2tips.blogspot.com/2014/08/rapid-sword.html                 # 疾風劍
https://es2tips.blogspot.com/2014/01/staff-of-ancient-snow.html       # 萬年雪
https://es2tips.blogspot.com/2014/01/thunder-claw.html                # 雷熊爪

# 傳奇防具
https://es2tips.blogspot.com/2014/11/dragon-armor-staff-huge-or-parrydodge.html  # 怒龍錦冑
https://es2tips.blogspot.com/2014/11/soul-crystal.html                # 靈魂水晶
https://es2tips.blogspot.com/2014/11/blessed-jade.html                # 萬福寶玉
https://es2tips.blogspot.com/2014/08/skull-rosary.html                # 白骨念珠
https://es2tips.blogspot.com/2014/08/dragon-soul-ring.html            # 龍戒

# 種族專屬裝備
https://es2tips.blogspot.com/2014/02/rainnar-cloth-ashura-mask.html   # 雨師妾袍+修羅之面
https://es2tips.blogspot.com/2014/02/girdle-of-headless.html          # 形天之怒
https://es2tips.blogspot.com/2014/01/woochan-ring.html                # 無腸寶珠
https://es2tips.blogspot.com/2014/01/dingling-legs.html               # 釘靈腿護
https://es2tips.blogspot.com/2014/01/jiaojaos-boots.html              # 焦僥靴
https://es2tips.blogspot.com/2014/01/yenhold-gauntlets.html           # 厭火之拳

# 聲望裝備
https://es2tips.blogspot.com/2013/06/1.html                           # 黑道聲望(1)
https://es2tips.blogspot.com/2013/06/2.html                           # 黑道聲望(2)
https://es2tips.blogspot.com/2013/06/3.html                           # 黑道聲望(3)
```

Wiki 裝備列表（Google Sheets 嵌入）：
```
https://sites.google.com/site/es2mud/home/wan-jia-yuan-chuang/equipment
```

## 執行步驟

### Step 1：讀取資料
```
讀取 docs/missing_content.json → missing_equipment 區塊
爬取 blog 裝備頁面提取屬性數值
若 missing 為 0，直接跳過此 task
```

### Step 2：裝備分類建立

1. **NPC 攜帶裝備** → `mudlib/d/<area>/npc/obj/`
2. **傳奇武器** → `mudlib/obj/weapon/`
3. **傳奇防具** → `mudlib/obj/armor/`
4. **通用裝備** → `mudlib/obj/area/obj/`

### Step 3：靜態驗證

- `#include <weapon.h>` 或 `#include <armor.h>` 正確
- 繼承正確武器/防具類型
- `setup_<type>()` 函數呼叫存在
- `setup()` 存在
- 數值在合理範圍內

---

## 完成條件

- [ ] 所有缺少的裝備建立完成
- [ ] 靜態驗證通過
