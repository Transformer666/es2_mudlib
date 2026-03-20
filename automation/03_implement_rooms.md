# Agent Task 03：實作房間（Rooms）& 區域

## 目標

根據 `docs/missing_content.json`，實作缺少的城鎮房間、門派 HQ、野外區域、世界道路。

---

## 前置知識

房間存放於 `mudlib/d/<area_name>/`，參考 `automation/CLAUDE.md` 範本。
**重要：所有出口必須雙向連結！**
**重要：新增區域時必須參考 `automation/CLAUDE.md` 的世界地圖，確保位置正確！**

核心模式：
```lpc
inherit ROOM;
void create() {
    set("short", "地名");
    set("long", @LONG
描述文字
LONG
    );
    set("objects", ([ __DIR__"npc/xxx" : 1 ]));
    set("exits", ([ "north" : __DIR__"other_room" ]));
    setup();
    replace_program(ROOM);
}
```

客棧：`#include <room.h>` + `inherit INN` + `set("valid_startroom", 1)` + `set("no_fight", 1)`

## 資料來源

Wiki 城鎮資料：
```
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/tian-chao-de-tu
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/tian-chao-de-tu/xueting
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/tian-chao-de-tu/wutang
https://sites.google.com/site/es2mud/home/story-lines/zhong-zu-she-ding/guo-jia-de-tu
```

Blog 地點資料：
```
https://es2tips.blogspot.com/2014/03/blog-post_7114.html              # ES2 地圖
https://es2tips.blogspot.com/2014/03/blog-post_2376.html              # 域水客棧（天寒村）
https://es2tips.blogspot.com/2014/11/es2.html                         # 書：名山書肆等地點
https://es2tips.blogspot.com/2014/02/es2_3.html                       # 坐船+釣魚地點
https://es2tips.blogspot.com/2014/02/es.html                          # 常見當鋪
https://es2tips.blogspot.com/2014/02/pot-well-bucket.html             # 水缸/水井/水桶
https://es2tips.blogspot.com/2014/02/fortune-teller-teller-zhang-fortune.html  # 算命先生位置
https://es2tips.blogspot.com/2014/10/es2.html                         # 職業師父的位置
https://es2tips.blogspot.com/2014/11/stakelionbuddhapillar.html       # 練功標靶位置
https://es2tips.blogspot.com/2013/05/es2.html                         # 鬼魂常出現的地方
```

原版 ES2 區域（`gh api repos/mudchina/es2/contents/d`）：
```
canyon（峽谷）, city（城市）, death（死亡領域）, force（修練區）
goathill（羊山）, green/green.n（草原）, ice（冰域）, jail（監獄）
latemoon（晚月）, temple（神殿）, village（村莊）, waterfog（水霧）
chuenyu（泉域）
```

## 執行步驟

### Step 1：讀取資料
```
讀取 docs/missing_content.json → missing_rooms, areas 區塊
參考 mudlib/d/snow/ 和 mudlib/d/wutang/ 現有房間
若 missing 為 0，直接跳過此 task
```

### Step 2：優先順序

1. **城鎮 stub 擴展**（龍安、京畿、康平、三掩 等已有 stub）
2. **野外區域補充**（參考原版 canyon, green, ice 等）
3. **新城鎮/區域**（天寒村、百藥谷、八寶樓等 blog 提到的地點）

### Step 3：每個區域必須

1. 建立區域目錄 `mudlib/d/<area>/`
2. 建立 `npc/` 子目錄（如需要）
3. 所有出口雙向連結
4. 與世界道路 `mudlib/d/road/` 連接

### Step 4：靜態驗證

- `inherit ROOM` 或 `inherit INN`
- `set("short"` 和 `set("exits"` 存在
- `setup()` 存在
- 所有出口目標檔案存在且雙向可達

---

## 完成條件

- [ ] 所有缺少的房間建立完成
- [ ] 所有出口雙向連結正確
- [ ] 靜態驗證通過
