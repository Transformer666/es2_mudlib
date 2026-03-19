# Agent Task 04：實作 NPC

## 目標

實作所有缺少的 NPC，包含一般 NPC、商人 NPC、掌門 NPC（含拜師系統）。

---

## 前置知識

NPC 存放於 `mudlib/d/<area>/npc/`，參考 `CLAUDE.md` 的 NPC 範本。

核心模式：
```lpc
#include <npc.h>
inherit F_FIGHTER;  // 或 F_VILLAGER / F_SOLDIER / F_SCHOLAR

void create()
{
    set_name("中文名", ({"english_id"}));
    set_attr("str", N);
    set_race("human");
    set_class("commoner");
    set_level(N);
    set_skill("sword", N);
    set("age", N);
    set("gender", "male");
    set("long", "描述\n");
    setup();
    carry_object(__DIR__"obj/weapon")->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_money("coin", N);
}
```

掌門 NPC 拜師系統參考 `mudlib/d/snow/npc/alchemist.c`，需實作：
- `set_flag(object me)` — 設定 pending flag
- `accept_apprentice(object me)` — 第一次拒絕+對話，第二次接受
- `init_apprentice(object me)` — 設定 class + title
- `acquire_skill(object ob, string skill)` — 傳授技能

## 執行步驟

### Step 1：讀取資料
```
讀取 docs/missing_content.json → missing_npcs 區塊
參考現有 NPC 檔案格式
```

### Step 2：建立 NPC 時的規範

1. `#include <npc.h>` — 必須
2. 選擇適當的 NPC 行為類型（F_FIGHTER/F_VILLAGER/F_SOLDIER/F_SCHOLAR）
3. 商人 NPC 額外繼承 F_VENDOR + set("merchandise")
4. NPC 裝備放在 `npc/obj/` 子目錄
5. 確認 NPC 所在房間有 `set("objects")` 載入

### Step 3：確認房間載入

每個新 NPC 必須確認其所在房間有對應的 `set("objects")` 載入。

### Step 4：靜態驗證

- 確認 `#include <npc.h>` 存在
- 確認繼承了有效的 NPC 類型
- 確認 `set_name()`, `set_race()`, `set_level()` 存在
- 確認 `setup()` 存在

---

## 完成條件

- [ ] 所有缺少的 NPC 建立完成
- [ ] 所有 NPC 的房間載入確認
- [ ] 掌門 NPC 拜師系統完整
- [ ] 靜態驗證通過
