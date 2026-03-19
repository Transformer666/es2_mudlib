# Agent Task 03：實作房間（Rooms）

## 目標

實作城鎮、門派 HQ、世界地圖的所有缺少房間。

---

## 前置知識

房間存放於 `mudlib/d/<area_name>/`，參考 `CLAUDE.md` 的「一般房間 (Room)」範本。

核心模式：
```lpc
inherit ROOM;

void create()
{
    set("short", "地名");
    set("long", @LONG
描述文字
LONG
    );
    set("objects", ([           // 載入 NPC（可選）
        __DIR__"npc/xxx" : 1,
    ]));
    set("exits", ([
        "north" : __DIR__"other_room",
    ]));

    setup();
    replace_program(ROOM);      // 無自訂函數時使用
}
```

客棧模式：
```lpc
#include <room.h>
inherit INN;
// set("valid_startroom", 1); set("no_fight", 1);
// 不使用 replace_program()
```

**重要：所有出口必須雙向連結！**

## 執行步驟

### Step 1：讀取資料
```
讀取 docs/missing_content.json → missing_rooms 區塊
讀取 docs/wiki_content.json → towns 區塊
參考 mudlib/d/snow/ 和 mudlib/d/wutang/ 現有房間
```

### Step 2：建立房間時的規範

每個房間檔案必須：
1. `inherit ROOM`（客棧用 `#include <room.h>` + `inherit INN`）
2. 使用 `set("short", ...)`, `set("long", @LONG...LONG)`, `set("exits", ([...]))`
3. NPC 用 `set("objects", ([ __DIR__"npc/xxx" : 1 ]))`
4. 結尾呼叫 `setup()`
5. 簡單房間加 `replace_program(ROOM)`
6. 使用 `__DIR__` 做相對路徑

### Step 3：出口雙向連結驗證

建立出口 mapping 後，逐一驗證每個出口的反向連結存在。

### Step 4：靜態驗證

對每個新建的房間 .c 檔案：
- 確認 `inherit ROOM` 或 `inherit INN` 存在
- 確認 `set("short"` 和 `set("exits"` 存在
- 確認 `setup()` 存在
- 確認所有出口的目標檔案存在
- 確認所有出口雙向可達

---

## 完成條件

- [ ] 所有缺少的房間建立完成
- [ ] 所有出口雙向連結正確
- [ ] 靜態驗證通過
- [ ] `docs/implementation_log.md` 更新完成
