# Agent Task 07：實作任務系統（Quests）

## 目標

根據 Wiki 謎題線索和 Blog 攻略，實作完整的任務系統，
涵蓋新手任務、城鎮支線、門派任務、野外探索、Boss 挑戰。

---

## 前置知識

### 任務實作模式

任務不需要獨立的 quest daemon，使用現有 NPC 對話 + flag 系統：

- **暫存 flag**：`set_temp("pending/xxx", 1)` — 對話中設定，重登消失
- **永久 flag**：`set("quest/xxx_done", 1)` — 任務完成標記，存檔保留
- **物品檢查**：`present("item_id", player)` — 檢查玩家背包
- **獎勵**：`gain_score("quest", N)` / `carry_object(path)` / `improve_skill()`

### 任務 NPC 模板

```lpc
// vim: syntax=lpc
#include <npc.h>
inherit F_VILLAGER;

void create()
{
    set_name("任務NPC", ({"quest_npc"}));
    // ... 基本設定 ...
    setup();
}

void init()
{
    ::init();
    // 玩家進入房間時自動觸發檢查
    if( !this_player()->query("quest/xxx_done")
    &&  !this_player()->query_temp("pending/xxx") ) {
        do_chat("NPC 主動搭話的內容。\n");
    }
}

// 玩家主動對話觸發
int ask_me(object me, string topic)
{
    if( topic != "quest" && topic != "任務" ) return 0;

    // 已完成
    if( me->query("quest/xxx_done") ) {
        do_chat("NPC說道：你已經幫過我了。\n");
        return 1;
    }

    // 進行中 — 檢查條件
    if( me->query_temp("pending/xxx") ) {
        object item = present("quest_item", me);
        if( item ) {
            destruct(item);
            me->set("quest/xxx_done", 1);
            me->gain_score("quest", 100);
            do_chat("NPC說道：太好了！謝謝你！\n");
            // 給予獎勵物品
            me->carry_object(__DIR__"obj/reward_item");
            return 1;
        }
        do_chat("NPC說道：東西帶來了嗎？\n");
        return 1;
    }

    // 接取任務
    do_chat(({
        "NPC說道：能幫我一個忙嗎？\n",
        "NPC說道：我需要一個xxx，能幫我找來嗎？\n",
        (: set_flag, me :),
    }));
    return 1;
}

void set_flag(object me)
{
    if( me && present(me, environment()) )
        me->set_temp("pending/xxx", 1);
}
```

### 多步驟任務模板（任務鏈）

```lpc
// 任務進度用數字追蹤
// pending/quest_name = 1 → 接取
// pending/quest_name = 2 → 第一步完成
// pending/quest_name = 3 → 第二步完成
// quest/quest_name_done = 1 → 全部完成

switch( me->query_temp("pending/quest_name") ) {
case 3:
    // 最後一步
    me->delete_temp("pending/quest_name");
    me->set("quest/quest_name_done", 1);
    me->gain_score("quest", 500);
    break;
case 2:
    // 第二步
    me->set_temp("pending/quest_name", 3);
    do_chat("NPC說道：很好，接下來去找xxx。\n");
    break;
case 1:
    // 第一步完成檢查
    if( present("item", me) ) {
        me->set_temp("pending/quest_name", 2);
        do_chat("NPC說道：不錯，再去做xxx。\n");
    }
    break;
}
```

---

## 資料來源

Wiki 任務資料：
```
https://sites.google.com/site/es2mud/home/zhu-xian-ren-wu               # 主線任務總覽
https://sites.google.com/site/es2mud/home/wan-jia-yuan-chuang/tiandiling # 天地靈任務
https://sites.google.com/site/es2mud/home/you-xi-jie-zi/noobguide01     # 新手任務
```

Blog 任務攻略：
```
https://es2tips.blogspot.com/2014/10/beggar-crone-maro-dagger-watermelon.html  # 老乞婆（棉襖+匕首+西瓜）
https://es2tips.blogspot.com/2013/05/blog-post_7503.html              # 任蕭蕭任務支線（烏金貓）
https://es2tips.blogspot.com/2013/05/blog-post_5878.html              # 八穴鬼徑走法
https://es2tips.blogspot.com/2014/02/blog-post_8.html                 # 神之心打法
https://es2tips.blogspot.com/2013/06/blog-post_7143.html              # 混沌之印+混沌獸
https://es2tips.blogspot.com/2013/05/blog-post_4347.html              # 龍安鎮+黑龍+九轉異龍珠
https://es2tips.blogspot.com/2013/05/blog-post_2986.html              # 百藥谷：赤龍+封山
https://es2tips.blogspot.com/2013/05/blog-post_9262.html              # 大蜈蚣+聖木殘根
https://es2tips.blogspot.com/2013/05/seal.html                        # 風神+風之印記
https://es2tips.blogspot.com/2013/05/blog-post_9146.html              # 桃仙+脈穴內經
https://es2tips.blogspot.com/2013/06/blog-post_9744.html              # 桐城信物（未解）
https://es2tips.blogspot.com/2013/05/blog-post_6519.html              # 動物四劍
https://es2tips.blogspot.com/2013/06/blog-post_4349.html              # 丱天樹+舍利子
https://es2tips.blogspot.com/2014/11/blog-post.html                   # 聲望：京畿神社功德箱
https://es2tips.blogspot.com/2013/05/blog-post_6121.html              # 黑道/武林聲望
https://es2tips.blogspot.com/2013/06/blog-post_9707.html              # 水龍經換奇兵精意
```

---

## 任務規劃（4 階段，共 30+ 任務）

### Phase 1：雪亭鎮新手任務（7 個）

對應 Wiki 雪亭鎮七大謎題，引導新玩家熟悉系統。

| # | 謎題 | 任務名 | 類型 | NPC | 獎勵 | 難度 |
|---|------|--------|------|-----|------|------|
| 1 | 阿寶等的人是誰？ | 老榕樹之約 | 對話+探索 | 阿寶(girl) | quest 經驗 + 故事線索 | ★ |
| 2 | 瞎眼婆婆的身分？ | 盲婆的秘密 | 對話鏈 | 新NPC: 瞎眼婆婆 | quest 經驗 + 特殊物品 | ★ |
| 3 | 貨棧搬箱子 | 搬運工的報酬 | 勞動(重複) | 新NPC: 貨棧管事 | coin + str 經驗 | ★ |
| 4 | 驛站遺失的信 | 遺失的信件 | 跑腿(已有) | postman+herbalist | quest 經驗(已實作) | ★ |
| 5 | 加入振武軍營 | 從軍之路 | 引導拜師(已有) | recruiter | 引導到 zhenwu(已實作) | ★ |
| 6 | 破舊老宅的秘密 | 老宅探險 | 探索+戰鬥 | 新NPC: 老宅鬼魂 | 裝備 + quest 經驗 | ★★ |
| 7 | 黑袍老人的女兒 | 尋找失蹤少女 | 多步驟 | 新NPC: 黑袍老人 | 裝備 + quest 經驗 + 劇情 | ★★ |

**已完成**：#4（送信）、#5（招兵）、部分 #1（阿寶存在但無任務邏輯）
**需新增**：#2、#3、#6、#7 + 完善 #1

### Phase 2：五堂鎮支線任務（6 個）

對應 Wiki 五堂鎮六大謎題。

| # | 謎題 | 任務名 | 類型 | 需要的新內容 | 難度 |
|---|------|--------|------|-------------|------|
| 1 | 飲血丟在哪裡？ | 失落的飲血刀 | 探索+Boss | 新區域+Boss NPC+傳奇武器 | ★★★ |
| 2 | 巫山雕像的秘密 | 巫山之謎 | 探索+謎題 | 新區域: 巫山 | ★★ |
| 3 | 郭布要收的徒弟 | 郭布的考驗 | 對話+測試 | NPC: 郭布 | ★★ |
| 4 | 鎮天神廟藏著誰 | 神廟秘聞 | 探索+戰鬥 | 新區域: 鎮天神廟 | ★★★ |
| 5 | 欽差來五堂做什麼 | 欽差大人 | 對話+劇情 | NPC: 欽差 | ★★ |
| 6 | 過河的船在哪裡 | 渡河之路 | 探索 | 新房間: 渡口 | ★ |

### Phase 3：野外 & Boss 任務（10+ 個）

從 Blog 攻略提取的中高階任務。

| 任務名 | 來源 | 涉及區域 | 獎勵 | 難度 |
|--------|------|---------|------|------|
| 風之印記 | blog: seal | 風神出沒區 | 風神之羽、風之印記 | ★★★★ |
| 聖木殘根 | blog: 大蜈蚣 | 後湖 | 聖木殘根→太陽鳥兌換 | ★★★ |
| 混沌之獸 | blog: 混沌 | 混沌領域 | 混沌之印、混沌之鏡 | ★★★★ |
| 九轉異龍珠 | blog: 龍安 | 龍安鎮 | 龍吟指環/封龍鎖/獸骨盔 | ★★★★ |
| 百藥谷赤龍 | blog: 百藥 | 百藥谷 | 赤龍系列材料 | ★★★ |
| 八寶樓闖關 | blog: 八寶樓 | 八寶樓(8層) | 各層Boss裝備 | ★★★★★ |
| 桃仙問道 | blog: 桃仙 | 桃花源 | 脈穴內經 | ★★ |
| 動物四劍 | blog: 四劍 | 各野外區 | 四把動物劍 | ★★★ |
| 烏金貓 | blog: 任蕭蕭 | 任蕭蕭所在地 | 烏金皮+移殤杖 | ★★★ |
| 丱天樹尋寶 | blog: 丱天樹 | 丱天樹區域 | 舍利子 | ★★ |

### Phase 4：主線任務 & 終盤內容（5+ 個）

來自 Wiki 主線任務頁面的故事線。

| 任務名 | 主題 | 涉及 NPC | 難度 |
|--------|------|---------|------|
| 封鬼慘案 | 追查真相 | 多個門派掌門 | ★★★★ |
| 武林盟主失蹤 | 調查失蹤 | 各城鎮NPC | ★★★★ |
| 虎刀門二當家 | 門派內鬥 | 韓笑、孫漪 | ★★★ |
| 天地靈任務 | 終盤挑戰 | 赤魈村+地獄 | ★★★★★ |
| 十三靈 | 最終任務 | 全世界 | ★★★★★ |

---

## 執行步驟

### Step 1：檢查現有任務

```bash
# 已實作的任務 NPC
grep -rl 'quest/' mudlib/d/ | grep -v master | sort

# 已有的任務物品
find mudlib -name "*quest*" -not -path "*/.git/*"

# pending flag 使用情況
grep -rh 'pending/' mudlib/d/ | grep -oP 'pending/\w+' | sort -u
```

### Step 2：Phase 1 實作（優先）

針對雪亭鎮 7 個謎題：

1. **完善阿寶 (girl.c)**：加入對話任務邏輯，提示玩家探索
2. **新增瞎眼婆婆 NPC**：`d/snow/npc/blind_woman.c` + 對應房間
3. **新增貨棧管事 NPC**：`d/snow/npc/warehouse_manager.c` + 搬箱子任務
4. **新增老宅房間**：`d/snow/old_house.c` + 鬼魂 NPC + 隱藏物品
5. **新增黑袍老人 NPC**：`d/snow/npc/dark_elder.c` + 多步驟尋人任務

每個任務需要：
- 任務 NPC（有 `init()` 或 `ask_me()` 觸發）
- 任務物品（如需要，放在 `npc/obj/`）
- 房間載入（`set("objects")` 確認）
- `pending/` flag 做進度追蹤
- `quest/xxx_done` flag 做完成標記
- `gain_score("quest", N)` 給予獎勵

### Step 3：Phase 2 實作

五堂鎮任務需先確認 `d/wutang/` 有足夠的房間和 NPC。
可能需要先跑 Task 03（房間）和 Task 04（NPC）。

### Step 4：Phase 3 實作

野外任務需要：
- 新的野外區域（風神出沒區、百藥谷、八寶樓 等）
- Boss NPC（高等級、特殊掉落）
- 傳奇裝備物品
- 多步驟任務鏈

### Step 5：靜態驗證

```bash
# 檢查所有任務 NPC 的 flag 使用
echo "=== Quest flags ==="
grep -rh 'quest/' mudlib/d/ | grep -oP 'quest/\w+' | sort -u

echo "=== Pending flags ==="
grep -rh 'pending/' mudlib/d/ | grep -oP 'pending/\w+' | sort -u

echo "=== Quest rewards ==="
grep -rn 'gain_score.*quest' mudlib/d/

echo "=== Quest NPCs loaded in rooms ==="
for npc in $(grep -rl 'quest/' mudlib/d/*/npc/*.c 2>/dev/null); do
    npc_path=$(echo "$npc" | sed 's|mudlib||;s|\.c||')
    if grep -rq "$npc_path\|$(basename $npc .c)" mudlib/d/*/[!n]*.c 2>/dev/null; then
        echo "OK: $(basename $npc)"
    else
        echo "NOT LOADED: $(basename $npc)"
    fi
done
```

---

## 完成條件

### Phase 1（最低要求）
- [ ] 雪亭鎮 7 個謎題中至少 5 個有對應任務
- [ ] 每個任務有接取→進行→完成的完整流程
- [ ] 每個任務有 `quest/xxx_done` 完成標記
- [ ] 每個任務有獎勵（經驗 / 物品 / 金錢）
- [ ] 所有任務 NPC 正確載入到房間

### Phase 2
- [ ] 五堂鎮至少 3 個任務可運作

### Phase 3
- [ ] 至少 3 個野外/Boss 任務可運作
- [ ] 八寶樓至少 1 層可挑戰

### Phase 4
- [ ] 至少 1 條主線任務可推進
