// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "軍械庫");
    set("long", @LONG
一間戒備嚴密的軍械庫，厚重的鐵門上掛著幾把大鎖。庫房內整齊
地排列著各式武器，長矛、弓箭、盾牌和刀劍各佔一方。牆上還掛著幾
副鐵甲，雖然已有些鏽跡，但仍然堅固耐用。角落裡堆放著幾箱箭矢和
一些維修武器的工具。空氣中瀰漫著鐵鏽和武器油的氣味。
LONG
    );
    set("exits", ([
        "south" : __DIR__"barracks",
    ]));
    set("no_fight", 1);
    set("objects", ([ __DIR__"npc/armorer" : 1 ]));

    setup();
}
