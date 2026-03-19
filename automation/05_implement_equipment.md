# Agent Task 05：實作裝備道具

## 目標

實作所有缺少的武器和防具。

---

## 前置知識

裝備存放於 `mudlib/d/<area>/npc/obj/` 或 `mudlib/obj/weapon/`、`mudlib/obj/armor/`。

武器模式：
```lpc
#include <weapon.h>
inherit F_SWORD;  // 武器類型

void create()
{
    set_name("武器名", ({"english_id"}));
    set_weight(N);
    setup_sword(min, max, wc, reach);
    if( !clonep() ) {
        set("wield_as", ({"sword"}));
        set("unit", "把");
        set("value", N);
        set("long", "描述\n");
    }
    setup();
}
```

防具模式：
```lpc
#include <armor.h>
inherit F_CLOTH;  // 防具類型

void create()
{
    set_name("防具名", "english_id");
    set_weight(N);
    setup_cloth();
    if( !clonep() ) {
        set("unit", "件");
        set("value", N);
        set("long", "描述\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([ "armor": N ]));
    }
    setup();
}
```

武器數值範圍參考 CLAUDE.md 的「武器數值範圍」表格。

## 執行步驟

### Step 1：讀取資料
```
讀取 docs/missing_content.json → missing_equipment 區塊
參考現有裝備檔案格式
```

### Step 2：建立裝備

1. `#include <weapon.h>` 或 `#include <armor.h>` — 必須
2. 選擇適當的武器/防具類型繼承
3. 使用 `!clonep()` 包裹描述屬性
4. 數值須在合理範圍內

### Step 3：靜態驗證

- 確認 include 和 inherit 正確
- 確認 `setup_<type>()` 函數呼叫存在
- 確認 `setup()` 存在
- 確認數值在合理範圍內

---

## 完成條件

- [ ] 所有缺少的裝備建立完成
- [ ] 靜態驗證通過
