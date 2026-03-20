# Agent Task 07：實作任務系統（Quests）

## 目標

實作基礎任務框架和初始任務內容，包含新手任務和城鎮支線任務。

---

## 前置知識

任務系統需要：
1. NPC 對話觸發（`do_chat()`, `accept_apprentice()` 等現有模式）
2. 物品交付/檢查（`present()` 檢查玩家背包）
3. Flag 管理（`set_temp("pending/xxx")`, `query("quest/xxx")`）
4. 獎勵發放（`gain_score()`, `carry_object()`, `improve_skill()`）

## 資料來源

Wiki 任務資料：
```
https://sites.google.com/site/es2mud/home/zhu-xian-ren-wu               # 主線任務
https://sites.google.com/site/es2mud/home/wan-jia-yuan-chuang/tiandiling # 天地靈任務
https://sites.google.com/site/es2mud/home/you-xi-jie-zi/noobguide01     # 新手任務
```

Blog 任務資料：
```
https://es2tips.blogspot.com/2014/10/beggar-crone-maro-dagger-watermelon.html  # 老乞婆任務
https://es2tips.blogspot.com/2013/05/blog-post_7503.html              # 任蕭蕭任務支線
https://es2tips.blogspot.com/2013/05/blog-post_5878.html              # 八穴鬼徑走法
https://es2tips.blogspot.com/2014/02/blog-post_8.html                 # 神之心打法
https://es2tips.blogspot.com/2013/06/blog-post_7143.html              # 混沌之印+混沌獸
https://es2tips.blogspot.com/2013/05/blog-post_4347.html              # 龍安鎮+黑龍+九轉異龍珠
https://es2tips.blogspot.com/2013/05/blog-post_2986.html              # 百藥谷：赤龍+封山
https://es2tips.blogspot.com/2013/05/blog-post_9262.html              # 大蜈蚣+聖木殘根
https://es2tips.blogspot.com/2013/05/seal.html                        # 風神+風之印記
https://es2tips.blogspot.com/2013/05/blog-post_9146.html              # 桃仙+脈穴內經
https://es2tips.blogspot.com/2013/06/blog-post_9744.html              # 桐城信物
```

Wiki 雪亭鎮謎題（可作為任務線索）：
```
1. 阿寶在老榕樹等的人是誰？
2. 瞎眼婆婆的真實身分？
3. 貨棧搬箱子算不算勞動？
4. 驛站遺失了幾封信？
5. 想不想加入振武軍營？
6. 破舊的老宅裡藏了什麼？
7. 黑袍老人的女兒去了哪裡？
```

## 執行步驟

### Step 1：設計任務框架

任務不需要獨立的 quest daemon，使用現有 NPC 對話 + flag 系統即可：

```lpc
// NPC 中的任務觸發範例
void init()
{
    ::init();
    add_action("do_give_quest", "ask");
}

int do_give_quest(string arg)
{
    object me = this_player();
    if( arg != query("id") ) return 0;

    if( me->query("quest/old_beggar_done") ) {
        do_chat("老乞婆說道：你已經幫過我了，謝謝你。\n");
        return 1;
    }

    if( me->query_temp("pending/old_beggar") ) {
        // 檢查是否帶了任務物品
        if( present("watermelon", me) ) {
            // 完成任務
            me->set("quest/old_beggar_done", 1);
            do_chat("老乞婆說道：太好了！謝謝你！\n");
            me->gain_score("quest", 100);
            return 1;
        }
        do_chat("老乞婆說道：西瓜呢？快去買一個來。\n");
        return 1;
    }

    // 第一次對話
    do_chat(({
        "老乞婆說道：小伙子，能幫我買個西瓜嗎？\n",
        (: $1->set_temp("pending/old_beggar", 1) :),
    }));
    return 1;
}
```

### Step 2：優先實作

1. **雪亭鎮新手任務**（老乞婆、搬箱子、送信）
2. **拜師引導任務**（引導玩家找到門派師父）
3. **城鎮探索任務**（收集物品、對話 NPC）

### Step 3：任務測試

確認任務 NPC 已載入到房間，對話觸發正確。

---

## 完成條件

- [ ] 至少 3 個新手任務可運作
- [ ] 任務 NPC 正確載入到房間
- [ ] 任務可正常完成並給予獎勵
