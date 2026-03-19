# ES2 天朝帝國 — Claude Code Agent 作戰手冊

## 專案概述

這是一個 LPMud 遊戲伺服器，以東方武俠故事為背景。
- 引擎：Neolith（MudOS fork）
- 語言：LPC（LPMud C）
- 編碼：UTF-8
- 遊戲根目錄：`mudlib/`

---

## 目錄結構

```
es2_mudlib/
├── mudlib/                        ← 遊戲內容根目錄
│   ├── adm/                       ← 系統核心（不可修改）
│   │   ├── daemons/               ← 系統 daemon（combatd, daemond 等）
│   │   ├── etc/                   ← 設定檔（wizlist, config）
│   │   └── obj/                   ← master.c, simul_efun.c
│   ├── std/                       ← 標準繼承物件（不可修改）
│   │   ├── room.c                 ← 房間基礎類別 (ROOM)
│   │   ├── room/                  ← 特殊房間 (inn.c, bank.c, temple.c 等)
│   │   ├── char.c                 ← 角色基礎類別 (CHARACTER)
│   │   ├── char/npc.c             ← NPC 基礎類別 (NPC)
│   │   ├── item.c                 ← 物品基礎類別 (ITEM)
│   │   ├── skill.c                ← 技能基礎類別 (SKILL)
│   │   ├── money.c                ← 貨幣類別 (MONEY)
│   │   └── race/humanoid.c        ← 種族基礎類別 (HUMANOID)
│   ├── include/                   ← 全域標頭檔（定義巨集常數）
│   │   ├── globals.h              ← 核心巨集定義（ROOM, SKILL, F_DBASE 等）
│   │   ├── npc.h                  ← NPC 巨集 + 自動繼承 NPC 基類
│   │   ├── weapon.h               ← 武器巨集 + 自動繼承 ITEM/F_EQUIP
│   │   ├── armor.h                ← 防具巨集 + 自動繼承 ITEM/F_EQUIP
│   │   ├── room.h                 ← 房間巨集（INN, BANK, TEMPLE 等）
│   │   ├── race.h                 ← 種族巨集 (HUMANOID)
│   │   └── ...                    ← 其他 38 個標頭檔
│   ├── feature/                   ← 功能模組（特性繼承）
│   │   ├── dbase.c                ← F_DBASE（資料庫特性）
│   │   ├── npc/                   ← NPC 行為模組
│   │   │   ├── fighter.c          ← F_FIGHTER（好鬥型）
│   │   │   ├── villager.c         ← F_VILLAGER（平民型）
│   │   │   ├── soldier.c          ← F_SOLDIER（軍人型）
│   │   │   ├── scholar.c          ← F_SCHOLAR（書生型）
│   │   │   ├── vendor.c           ← F_VENDOR（商人功能）
│   │   │   ├── bandit.c           ← F_BANDIT（盜匪型）
│   │   │   └── traveler.c         ← F_TRAVELER（旅行者）
│   │   ├── weapon/                ← 武器類型模組
│   │   │   ├── sword.c blade.c dagger.c needle.c
│   │   │   ├── staff.c pike.c axe.c blunt.c whip.c
│   │   └── armor/                 ← 防具類型模組
│   │       ├── armor.c cloth.c head_eq.c hand_eq.c
│   │       ├── feet_eq.c neck_eq.c finger_eq.c
│   │       ├── wrist_eq.c waist_eq.c leg_eq.c
│   ├── daemon/                    ← 遊戲 daemon（可新增/修改）
│   │   ├── race/                  ← 種族 daemon（每種族一個 .c）
│   │   ├── class/                 ← 職業 daemon（每職業一個 .c）
│   │   ├── skill/                 ← 技能 daemon（每技能一個 .c）
│   │   └── sect/                  ← 門派 daemon（每門派一個 .c）
│   ├── d/                         ← 遊戲世界區域（主要開發區域）
│   │   ├── snow/                  ← 雪亭鎮（房間 + npc/ 子目錄）
│   │   ├── wutang/                ← 五堂鎮
│   │   ├── fengshan/              ← 封山派 HQ
│   │   ├── hudao/                 ← 虎刀門 HQ
│   │   ├── tianxie/               ← 天邪派 HQ
│   │   ├── ...                    ← 每個區域一個獨立目錄
│   │   └── road/                  ← 世界道路
│   ├── obj/                       ← 共用物件
│   │   ├── area/obj/              ← 通用裝備（布衣、短刀等）
│   │   ├── weapon/                ← 傳奇武器
│   │   ├── armor/                 ← 傳奇防具
│   │   └── npc/                   ← 共用 NPC（神獸等）
│   ├── cmds/                      ← 指令實作
│   ├── doc/                       ← 遊戲文件
│   │   └── help/player/           ← 玩家 help 文本
│   └── data/                      ← 玩家存檔（不可修改）
├── automation/                    ← Agent 自動化腳本
└── .claude/                       ← Claude Code 設定
```

### 區域目錄結構規範

每個區域（門派 HQ、城鎮等）統一使用以下結構：

```
d/<area_name>/
├── room1.c                ← 房間檔案直接放在區域根目錄
├── room2.c
├── ...
└── npc/                   ← NPC 放在 npc/ 子目錄
    ├── npc1.c
    ├── npc2.c
    └── obj/               ← NPC 攜帶的裝備放在 npc/obj/
        ├── weapon1.c
        └── armor1.c
```

---

## 重要巨集定義速查表

以下巨集定義於 `include/globals.h`，所有 .c 檔案都可直接使用：

| 巨集 | 展開路徑 | 用途 |
|------|---------|------|
| `ROOM` | `/std/room` | 房間基類 |
| `INN` | `/std/room/inn.c` | 客棧基類（需 `#include <room.h>`） |
| `BANK` | `/std/room/bank.c` | 錢莊基類（需 `#include <room.h>`） |
| `TEMPLE` | `/std/room/temple.c` | 神殿基類（需 `#include <room.h>`） |
| `JOURNEY` | `/std/room/journey.c` | 旅行基類（需 `#include <room.h>`） |
| `NPC` | `/std/char/npc` | NPC 基類（由 `npc.h` 自動繼承） |
| `CHARACTER` | `/std/char` | 角色基類 |
| `ITEM` | `/std/item` | 物品基類（由 `weapon.h`/`armor.h` 自動繼承） |
| `SKILL` | `/std/skill` | 技能基類 |
| `HUMANOID` | `/std/race/humanoid` | 種族基類（需 `#include <race.h>`） |
| `F_DBASE` | `/feature/dbase.c` | 資料庫特性 |
| `F_FIGHTER` | `/feature/npc/fighter.c` | 好鬥 NPC（需 `#include <npc.h>`） |
| `F_VILLAGER` | `/feature/npc/villager.c` | 平民 NPC（需 `#include <npc.h>`） |
| `F_SOLDIER` | `/feature/npc/soldier.c` | 軍人 NPC（需 `#include <npc.h>`） |
| `F_SCHOLAR` | `/feature/npc/scholar.c` | 書生 NPC（需 `#include <npc.h>`） |
| `F_VENDOR` | `/feature/npc/vendor.c` | 商人功能（需 `#include <npc.h>`） |
| `F_SWORD` | `/feature/weapon/sword.c` | 劍（需 `#include <weapon.h>`） |
| `F_BLADE` | `/feature/weapon/blade.c` | 刀（需 `#include <weapon.h>`） |
| `F_DAGGER` | `/feature/weapon/dagger.c` | 匕首（需 `#include <weapon.h>`） |
| `F_NEEDLE` | `/feature/weapon/needle.c` | 針（需 `#include <weapon.h>`） |
| `F_STAFF` | `/feature/weapon/staff.c` | 棍棒（需 `#include <weapon.h>`） |
| `F_PIKE` | `/feature/weapon/pike.c` | 槍矛（需 `#include <weapon.h>`） |
| `F_AXE` | `/feature/weapon/axe.c` | 斧（需 `#include <weapon.h>`） |
| `F_WHIP` | `/feature/weapon/whip.c` | 鞭（需 `#include <weapon.h>`） |
| `F_BLUNT` | `/feature/weapon/blunt.c` | 鈍器（需 `#include <weapon.h>`） |
| `F_ARMOR` | `/feature/armor/armor.c` | 鎧甲（需 `#include <armor.h>`） |
| `F_CLOTH` | `/feature/armor/cloth.c` | 布衣（需 `#include <armor.h>`） |
| `F_HEAD_EQ` | `/feature/armor/head_eq.c` | 頭飾（需 `#include <armor.h>`） |
| `F_HAND_EQ` | `/feature/armor/hand_eq.c` | 手套（需 `#include <armor.h>`） |
| `F_FEET_EQ` | `/feature/armor/feet_eq.c` | 鞋靴（需 `#include <armor.h>`） |
| `F_NECK_EQ` | `/feature/armor/neck_eq.c` | 項鍊（需 `#include <armor.h>`） |
| `F_FINGER_EQ` | `/feature/armor/finger_eq.c` | 戒指（需 `#include <armor.h>`） |
| `F_WRIST_EQ` | `/feature/armor/wrist_eq.c` | 護腕（需 `#include <armor.h>`） |
| `F_WAIST_EQ` | `/feature/armor/waist_eq.c` | 腰帶（需 `#include <armor.h>`） |
| `F_LEG_EQ` | `/feature/armor/leg_eq.c` | 腿甲（需 `#include <armor.h>`） |
| `STOCK_WEAPON(x)` | `/obj/area/obj/ + x` | 通用武器路徑 |
| `STOCK_ARMOR(x)` | `/obj/area/obj/ + x` | 通用防具路徑 |
| `STOCK_ITEM(x)` | `/obj/area/obj/ + x` | 通用物品路徑 |
| `DAEMON_D` | `/adm/daemons/daemond.c` | Daemon 管理器 |
| `COMBAT_D` | `/adm/daemons/combatd.c` | 戰鬥系統 |
| `__DIR__` | 目前檔案所在目錄 | 相對路徑捷徑 |

---

## LPC 程式碼範本

### 1. 一般房間 (Room)

```lpc
// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "廣場中央");
    set("long", @LONG
這裡是雪亭鎮廣場的中央，一株巨大的老榕樹盤根錯結地站在中央，
一些孩童常常爬上這株老榕嬉戲。
LONG
    );
    set("objects", ([
        __DIR__"npc/guard" : 1,
        __DIR__"npc/vendor" : 1,
    ]));
    set("exits", ([
        "east" : __DIR__"square_e",
        "north" : __DIR__"square_n",
        "west" : __DIR__"square_w",
        "south" : __DIR__"square_s",
    ]));

    setup();
    replace_program(ROOM);
}
```

**要點：**
- `inherit ROOM` — 不是 `inherit "/std/room"`，使用巨集
- 使用 `set("property", value)` — 不是 `set_short()`、`set_long()` 等
- `@LONG...LONG` 是 LPC 的 heredoc 語法，用於多行字串
- `set("objects", ([...]))` — 載入 NPC 到房間（mapping: 路徑 => 數量）
- `set("exits", ([...]))` — 定義出口（mapping: 方向 => 路徑）
- `__DIR__` — 當前檔案目錄的巨集，用於相對路徑
- `setup()` — 必須在所有 `set()` 之後呼叫
- `replace_program(ROOM)` — 簡單房間用，節省記憶體（無自訂函數時使用）
- 如果房間有自訂函數（如 `init()`、`do_climb()` 等），不要用 `replace_program()`

**可選屬性：**
```lpc
set("no_fight", 1);         // 禁止戰鬥
set("no_magic", 1);         // 禁止施法
set("detail", ([            // 可查看的細節描述
    "榕樹" : "這株榕樹少說也有兩三百歲了。\n",
    "長凳" : "十分普通的長凳。\n",
]));
```

### 2. 客棧房間 (INN)

```lpc
// vim: syntax=lpc

#include <room.h>

inherit INN;

private void create()
{
    set("short", "小客棧");
    set("long", @LONG
這裡是一家小客棧，老舊的桌椅因為經年的使用而變得烏黑黝亮。
LONG
    );
    set("objects", ([
        __DIR__"npc/innkeeper" : 1,
    ]));
    set("valid_startroom", 1);
    set("no_fight", 1);
    set("exits", ([
        "east" : __DIR__"square_w",
        "west" : __DIR__"inn_kitchen",
    ]));

    setup();
    // 注意：INN 不使用 replace_program()
}
```

**要點：**
- `#include <room.h>` — 必須引入以取得 `INN` 巨集
- `inherit INN` — 不是 `inherit ROOM`
- `set("valid_startroom", 1)` — 標記為合法起始房間
- INN **不使用** `replace_program()`

### 3. NPC — 基本型

```lpc
// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("阿寶", ({"arbao", "abao"}));
    set_attr("str", 15);
    set_attr("dex", 19);
    set_attr("con", 17);
    set_attr("int", 19);
    set_attr("spi", 18);
    set_race("human");
    set_class("commoner");
    set_level(10);

    set_skill("dodge", 35);
    set_skill("dagger", 40);

    set("age", 16);
    set("gender", "female");
    set("long",
        "這個十五、六歲的小姑娘就是「阿寶」了，她身上雖然穿著粗布\n"
        "衣服，但卻十足是個美人胚子。\n");

    setup();
    carry_money("coin", 30);
    carry_object(__DIR__"obj/blue_cloth")->wear();
    carry_object(STOCK_WEAPON("dagger"))->wield();
}
```

**要點：**
- `#include <npc.h>` — 必須引入，它會自動繼承 NPC 基類
- `inherit F_VILLAGER` — NPC 類型，可選 F_FIGHTER/F_VILLAGER/F_SOLDIER/F_SCHOLAR
- `set_name("中文名", ({"english_id", "alt_id"}))` — NPC 名稱
- `set_attr("attr", N)` — 屬性：str, con, dex, int, wis, spi, cor, cps
- `set_race("human")` / `set_class("commoner")` — 種族/職業
- `set_level(N)` — 等級
- `set_skill("skill_name", N)` — 技能
- `set("age", N)` / `set("gender", "male"/"female")` — 用 `set()` 而非 set_gender()
- `setup()` — 必須在屬性設定完後呼叫
- `carry_object(path)->wield()` — 攜帶武器並裝備
- `carry_object(path)->wear()` — 攜帶防具並穿戴
- `carry_money("coin"/"silver", N)` — 攜帶金錢
- `STOCK_WEAPON("longsword")` / `STOCK_ARMOR("cloth")` — 通用裝備巨集

**NPC 行為類型選擇：**

| 類型 | 巨集 | 行為 |
|------|------|------|
| 好鬥型 | `F_FIGHTER` | 主動攻擊、追擊、戰鬥 AI |
| 平民型 | `F_VILLAGER` | 和平型、不主動攻擊 |
| 軍人型 | `F_SOLDIER` | 軍事紀律、服從命令 |
| 書生型 | `F_SCHOLAR` | 學者行為模式 |
| 盜匪型 | `F_BANDIT` | 盜賊行為、攔路搶劫 |

**NPC 對話系統：**
```lpc
// 使用 do_chat() 進行對話（在函數內）
do_chat("陳維俠說道：拜我為師？呵呵。\n");

// 多段對話（依序播放）
do_chat(({
    "第一段對話。\n",
    "第二段對話。\n",
    (: some_callback :),    // 可穿插函數呼叫
}));

// 使用 set("chat_msg") 設定閒聊（隨機觸發）
set("chat_chance", 2);    // 每次心跳 2% 機率說話
set("chat_msg", ({
    "NPC 自言自語。\n",
    "NPC 看著天空。\n",
}));
```

### 4. NPC — 商人 (Vendor)

```lpc
// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("賣花姑娘", ({"flowergirl", "girl"}));
    set_race("human");
    set_class("commoner");
    set_level(3);

    set("age", 16);
    set("long",
        "一個清秀可人的少女，挎著一隻竹籃，裡面裝滿了各色鮮花，\n"
        "笑盈盈地向過路的人兜售。你可以用 list 看看，用 buy 來買。\n");
    set("merchandise", ([
        __DIR__"obj/flower" : 50,
        __DIR__"obj/wreath" : 20,
    ]));

    setup();
    carry_money("coin", 30);
}
```

**要點：**
- 同時繼承 `F_VILLAGER`（或其他 NPC 類型）和 `F_VENDOR`
- `set("merchandise", ([ path : stock_count ]))` — 設定販售物品

### 5. NPC — 掌門（含拜師系統）

參考 `d/snow/npc/alchemist.c`（陳維俠，龍圖丹派）：

```lpc
// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("掌門人", ({"master", "zhang_men"}));
    set_attr("str", 22);
    set_attr("dex", 20);
    set_attr("int", 24);
    set_attr("wis", 25);
    set_attr("con", 20);
    set_attr("spi", 22);
    set_race("human");
    set_level(60);
    set_class("commoner");
    set_skill("sword", 100);
    set_skill("parry", 80);
    set_skill("dodge", 70);

    set("age", 55);
    set("long",
        "掌門人的描述文字。\n");

    setup();
    carry_object(__DIR__"obj/master_sword")->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}

// --- 拜師系統 ---

// 設定 pending flag（由 do_chat 回呼觸發）
void set_flag(object me)
{
    if( me && present(me, environment()) ) {
        if( me->query_class() != "commoner"
        ||  me->query("title") )
            return;
        me->set_temp("pending/master_id", 1);
    }
    else
        do_chat("掌門說道：嘿 ... 人都走了。\n");
}

// 玩家執行 apprentice <npc> 時呼叫
// 第一次：多段對話 + set_flag，return 0（拒絕）
// 第二次：檢查 pending flag，return 1（接受）
int accept_apprentice(object me)
{
    if( is_chatting() ) return 0;
    if( me->query_temp("pending/master_id") ) return 1;
    if( me->query("title") ) {
        do_chat("掌門道：你已有師門，無需再拜。\n");
        return 0;
    }
    do_chat(({
        "掌門說道：拜我為師？呵呵。\n",
        "掌門說道：我看你倒還順眼，若不怕吃苦 ...\n",
        "掌門說道：便多你一個也不妨。\n",
        (: set_flag, me :)
    }));
    return 0;
}

// accept_apprentice return 1 後自動呼叫
// 設定玩家的職業、title，完成入門
int init_apprentice(object me)
{
    if( me->query_class() != "commoner" ) {
        do_chat(({
            "掌門說道：你既已入別派，豈有餘力再習本門武學？\n",
            "掌門揮揮手，說道：去吧。\n"
        }));
        return 1;
    }
    if( ::init_apprentice(me) ) {
        seteuid(getuid());
        me->set_class("warrior");       // 門派對應的職業
        me->set("title", "XX門弟子");    // 門派 title
        do_chat(({
            "掌門點了點頭，說道：好，你就是本門弟子了。\n",
            "掌門說道：先下去吧，好好練功。\n"
        }));
    }
}

// 玩家執行 acquire <skill> from <npc> 時呼叫
int acquire_skill(object ob, string skill)
{
    if( is_chatting() )
        return notify_fail("你最好等他話說完再插嘴。\n");
    if( !ob->is_apprentice_of(this_object()) ) return 0;

    switch(skill) {
    case "sword":
        say("掌門點了點頭，將劍法大要傳授給你。\n");
        message_vision("$N將本門劍法傳授給$n。\n", this_object(), ob);
        ob->improve_skill(skill, random(ob->query_attr("wis")) + 1);
        break;
    default:
        return 0;
    }

    do_chat(({
        "掌門說道：勤加練習，不可懈怠。\n",
        "掌門說道：希望你好自為之。\n",
    }));

    return 1;
}
```

**拜師流程：**
1. 玩家執行 `apprentice <npc>`
2. 系統呼叫 `accept_apprentice(player)` → 第一次 return 0，播放對話 + set_flag
3. 玩家再次 `apprentice <npc>`
4. 系統呼叫 `accept_apprentice(player)` → 檢查到 pending flag，return 1
5. 系統自動呼叫 `init_apprentice(player)` → 設定 class + title
6. 日後玩家執行 `acquire <skill> from <npc>`
7. 系統呼叫 `acquire_skill(player, skill)` → 傳授技能

### 6. 武器 (Weapon)

```lpc
// vim: syntax=lpc

#include <weapon.h>

inherit F_SWORD;

void create()
{
    set_name("洗銀劍", ({"silver sword", "sword"}));
    set_weight(7000);
    setup_sword(2, 15, 40, 4);

    if( !clonep() ) {
        set("wield_as", ({"sword"}));
        set("unit", "把");
        set("value", 19000);
        set("rigidity", 40);
        set("long", "一把銀製的短劍，鑄造得十分精美。\n");
    }
    setup();
}
```

**要點：**
- `#include <weapon.h>` — 必須引入，自動繼承 ITEM + F_EQUIP
- `inherit F_SWORD` — 武器類型（F_SWORD/F_BLADE/F_DAGGER/F_NEEDLE/F_STAFF/F_PIKE/F_AXE/F_WHIP/F_BLUNT）
- `set_name("中文名", ({"english_id"}))` — 武器名稱
- `set_weight(N)` — 重量（克）
- `setup_<type>(min, max, wc, reach)` — 武器數值設定
- `!clonep()` — 只在 master copy 設定描述等屬性
- `set("wield_as", ({"type"}))` — 裝備時的武器類型
- `set("unit", "把")` — 量詞

**武器數值範圍（setup 參數：min, max, wc, reach）：**

| 類型 | setup 函數 | min | max | wc | reach |
|------|-----------|-----|-----|-----|-------|
| 劍 sword | `setup_sword()` | 1-9 | 10-60 | 2-11 | 1-5 |
| 刀 blade | `setup_blade()` | 1-12 | 10-120 | 2-13 | 1-5 |
| 匕首 dagger | `setup_dagger()` | 1-8 | 3-25 | 1-4 | 1-2 |
| 針 needle | `setup_needle()` | 1-10 | 3-30 | 1-5 | 1-3 |
| 棍 staff | `setup_staff()` | 1-13 | 12-70 | 1-8 | 3-7 |
| 槍 pike | `setup_pike()` | 2-15 | 12-100 | 1-10 | 2-8 |
| 斧 axe | `setup_axe()` | 2-15 | 10-90 | 3-15 | 1-4 |
| 鞭 whip | `setup_whip()` | 1-10 | 5-50 | 1-6 | 4-9 |

### 7. 防具 (Armor)

```lpc
// vim: syntax=lpc

#include <armor.h>

inherit F_CLOTH;

void create()
{
    set_name("布衣", "cloth");
    set_weight(1000);
    setup_cloth();

    if( !clonep() ) {
        set("unit", "件");
        set("value", 0);
        set("long", "一套普通的棉布衣褲。\n");
        set("wear_as", "cloth");
        set("apply_armor/cloth", ([
            "armor": 1,
        ]));
    }

    setup();
}
```

**要點：**
- `#include <armor.h>` — 必須引入
- `inherit F_CLOTH` — 防具類型
- `setup_cloth()` / `setup_armor()` — 初始化防具
- `set("wear_as", "cloth")` — 穿戴部位
- `set("apply_armor/cloth", (["armor": N]))` — 防禦加成

**防具 wear_as 對應：**

| 類型 | wear_as | 說明 |
|------|---------|------|
| F_ARMOR | `"armor"` | 鎧甲 |
| F_CLOTH | `"cloth"` | 布衣 |
| F_HEAD_EQ | `"head_eq"` | 頭飾 |
| F_HAND_EQ | `"hand_eq"` | 手套 |
| F_FEET_EQ | `"feet_eq"` | 鞋靴 |
| F_NECK_EQ | `"neck_eq"` | 項鍊 |
| F_FINGER_EQ | `"finger_eq"` | 戒指 |
| F_WRIST_EQ | `"wrist_eq"` | 護腕 |
| F_WAIST_EQ | `"waist_eq"` | 腰帶 |
| F_LEG_EQ | `"leg_eq"` | 腿甲 |

### 8. 種族 Daemon (Race)

```lpc
// vim: syntax=lpc

#include <race.h>

inherit HUMANOID;

private void create()
{
    ::create();
    seteuid(getuid());

    set("karma", 5);         // 投胎業力消耗
    set("civilized", 1);     // 是否文明種族

    DAEMON_D->register_race_daemon("human");
}

void setup(object ob)
{
    ::setup(ob);
    ob->set_default_object(__FILE__);

    if( !ob->query_weight() )
        ob->set_weight(40000);

    ob->add_temp("apply/armor", 3);    // 種族天生防禦
}

void initialize(object ob)
{
    ::initialize(ob);

    ob->init_attribute(([
        "str": 13 + random(6),
        "int": 13 + random(6),
        "wis": 13 + random(6),
        "dex": 13 + random(6),
        "con": 13 + random(6),
        "spi": 13 + random(6),
        "cor": 13 + random(6),
        "cps": 13 + random(6)
    ]));

    ob->init_statistic(([
        "gin": 30,
        "kee": 30,
        "sen": 30,
    ]));

    if( !ob->query("age") )
        ob->set("age", 14);

    ob->set_default_object(__FILE__);
}
```

**要點：**
- `#include <race.h>` + `inherit HUMANOID`
- `::create()` — 呼叫父類 create
- `seteuid(getuid())` — daemon 必須設定 euid
- `DAEMON_D->register_race_daemon("race_id")` — 註冊到 daemon 管理器
- `setup(ob)` — 角色選擇種族時呼叫
- `initialize(ob)` — 初始化角色屬性

### 9. 職業 Daemon (Class)

```lpc
// vim: syntax=lpc

inherit F_DBASE;

static void create()
{
}

string query_rank(object obj, string politeness)
{
    if( !politeness )
        return "武者";

    switch(politeness) {
        case "self":       return "在下";
        case "respectful": return "俠客";
        case "rude":
        default:           return "傢伙";
    }
}
```

**要點：**
- `inherit F_DBASE` — 不需要 include
- **不需要** 呼叫 `register_class_daemon()`，系統自動偵測
- 必須實作 `query_rank(object, string)` — 提供各種稱謂

**7 個職業：**

| 職業 | class ID | 檔案 |
|------|----------|------|
| 武者 | warrior | `daemon/class/warrior.c` |
| 軍人 | soldier | `daemon/class/soldier.c` |
| 和尚 | monk | `daemon/class/monk.c` |
| 道士 | taoist | `daemon/class/taoist.c` |
| 書生 | scholar | `daemon/class/scholar.c` |
| 小偷 | thief | `daemon/class/thief.c` |
| 方士 | alchemist | `daemon/class/alchemist.c` |

### 10. 技能 Daemon (Skill) — 戰鬥技能

```lpc
// vim: syntax=lpc

#include <ansi.h>

inherit SKILL;

mapping *actions = ({
    ([
        "action":       "$N持$w往$n的$l刺去",
        "dodge":        5,
        "damae":        5,
        "damage_type":  "刺傷"
    ]),
    ([
        "action":       "$N閃身上前，$w朝$n的$l劃去",
        "dodge":        -5,
        "damae":        5,
        "damage_type":  "割傷"
    ]),
});

string *interattack = ({
    "$N將$n反握在手中，身子微微前傾。\n",
});

private void create()
{
    seteuid(getuid());
    DAEMON_D->register_skill_daemon("dagger");
    setup();
}

void attack_using(object me, object opponent, object weapon)
{
    int damage;
    if( !opponent ) {
        if( me->query_temp("last_attacked_target") )
            message_vision(CYN + interattack[random(sizeof(interattack))] + NOR, me, weapon);
        return;
    }
    damage = COMBAT_D->fight(me, opponent, "dagger", actions[random(sizeof(actions))], weapon);
}

int valid_enable(string usage)
{
    return 0;
}
```

**要點：**
- `inherit SKILL` — 技能基類
- `DAEMON_D->register_skill_daemon("skill_name")` — 註冊技能
- `actions` — 攻擊動作 mapping 陣列
  - `$N` = 攻擊者, `$n` = 防禦者, `$w` = 武器, `$l` = 部位
  - `dodge` = 閃避修正, `damae`/`damage` = 傷害修正, `damage_type` = 傷害類型
  - 注意：部分現存檔案使用 "damae"（typo），新建檔案亦應使用相同拼寫以保持一致
- `interattack` — 攻擊間隔的動作描述
- `COMBAT_D->fight(me, opponent, skill_name, action, weapon)` — 執行戰鬥

### 11. 門派 Daemon (Sect)

```lpc
// vim: syntax=lpc

inherit F_DBASE;

private void create()
{
    seteuid(getuid());

    set("name", "白象寺");
    set("english_name", "baixiang");
    set("class", "monk");
    set("paths", ([
        "禪師": "Chan Master - enlightened meditation master",
        "羅漢": "Arhat - ascended warrior monk",
    ]));
    set("skills", ({
        "diamond hammer",
        "staff",
    }));
    set("location", "/d/baixiang/main_hall");

    DAEMON_D->register_object_daemon("sect:baixiang");
}

string query_sect_name() { return query("name"); }
string query_class() { return query("class"); }
mapping query_paths() { return query("paths"); }
```

**要點：**
- `inherit F_DBASE`
- `DAEMON_D->register_object_daemon("sect:<name>")` — 以 "sect:" 前綴註冊
- `set("location", path)` — 指向掌門所在房間
- `set("class", "xxx")` — 門派對應的職業 ID
- `set("paths", ([...]))` — 門派內部的進階路線
- `set("skills", ({...}))` — 門派可學習的技能列表

---

## 關鍵規則

### 出口必須雙向連結

所有房間的出口必須確保雙向可達。如果 A 有 `"north" : B`，則 B 必須有 `"south" : A`。

```
// A.c
set("exits", ([ "north" : __DIR__"B" ]));

// B.c
set("exits", ([ "south" : __DIR__"A" ]));
```

### 禁止事項

1. **不可修改** `mudlib/adm/` 下的核心檔案，除非明確被要求
2. **不可修改** `mudlib/std/` 下的標準物件，除非明確被要求
3. **不可修改** `mudlib/feature/` 下的功能模組，除非明確被要求
4. **不可修改** `mudlib/include/` 下的標頭檔，除非明確被要求
5. **不可修改** `mudlib/data/` 下的玩家存檔
6. **所有新 room 的 exits 必須雙向連結**

### Git 規範

- 只推送到 `mine` remote（`Transformer666/es2_mudlib.git`）
- **不可**推送到 `origin`（`taedlar/es2_mudlib.git`）
- Commit message 格式：

```
feat: 新增天邪派 HQ 區域和掌門 NPC
fix: 修正老榕樹任務觸發條件
docs: 更新雪亭鎮玩家 help 文本
refactor: 重構 NPC 對話格式
```

---

## 現有內容清單

### 區域（34 個目錄）

| 區域 | 說明 | 類型 |
|------|------|------|
| snow | 雪亭鎮 | 城鎮 |
| wutang | 五堂鎮 | 城鎮 |
| fengshan | 封山派 HQ | 門派 |
| hudao | 虎刀門 HQ | 門派 |
| zhenwu | 振武軍營 HQ | 門派 |
| maoshan | 茅山派 HQ | 門派 |
| baixiang | 白象寺 HQ | 門派 |
| tianxie | 天邪派 HQ | 門派 |
| langyi | 瑯夷 HQ | 門派 |
| longttu | 龍圖丹派 HQ | 門派 |
| tianshi | 天師派 HQ | 門派 |
| yinjiao | 隱教 HQ | 門派 |
| buxuan | 步玄派 HQ | 門派 |
| xuantian | 玄天教 HQ | 門派 |
| baolian | 寶蓮寺 HQ | 門派 |
| wutuo | 武陀 HQ | 門派 |
| jianjia | 劍甲門 HQ | 門派 |
| lengmei | 冷梅莊 HQ | 門派 |
| kuxiao | 哭笑門 HQ | 門派 |
| xueyin | 雪吟莊 HQ | 門派 |
| road | 世界道路 | 世界 |
| manglin | 莽林 | 野外 |
| oldpine | 古松林 | 野外 |
| graveyard | 墓園 | 野外 |
| heifeng | 黑風嶺 | 野外 |
| lijun | 鯉君渡 | 渡口 |
| longan | 龍安 | 城鎮stub |
| jingji | 京畿 | 城鎮stub |
| kangping | 康平 | 城鎮stub |
| sanyen | 三掩 | 城鎮stub |
| lee | 離 | 城鎮stub |
| choyin | 喬陰 | 城鎮stub |
| baihua | 百花 | 城鎮stub |
| weiguo | 衛國 | 城鎮stub |

### Daemon

- 10 個種族 daemon（`daemon/race/`）
- 7 個職業 daemon（`daemon/class/`）
- 22 個技能 daemon（`daemon/skill/`）
- 18 個門派 daemon（`daemon/sect/`）

### 待開發項目

- 任務系統（Quest）
- 新城鎮區域擴展（龍安、京畿、康平等 stub 城鎮）
- 世界地圖擴展
- 更多野外區域
- Help 文本系統

---

## 參考資料

- Wiki 資料來源：`https://sites.google.com/site/es2mud/`
- 現有 room 範例：`mudlib/d/snow/square.c`
- 現有 NPC 範例：`mudlib/d/snow/npc/child.c`
- 拜師系統範例：`mudlib/d/snow/npc/alchemist.c`
- 現有武器範例：`mudlib/d/snow/npc/obj/silversword.c`
- 現有防具範例：`mudlib/obj/area/obj/cloth.c`
- 現有商人範例：`mudlib/d/baihua/npc/flowergirl.c`
- 客棧範例：`mudlib/d/snow/inn_hall.c`
- 種族範例：`mudlib/daemon/race/human.c`
- 技能範例：`mudlib/daemon/skill/dagger.c`
- 職業範例：`mudlib/daemon/class/warrior.c`
- 門派範例：`mudlib/daemon/sect/baixiang.c`
