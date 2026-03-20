// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "廚房");
    set("long", @LONG
一間煙火氣十足的廚房，灶台上架著幾口大鐵鍋，鍋裡燉著熱氣
騰騰的飯菜。牆角堆著劈好的柴火，旁邊掛著幾串風乾的臘肉和辣椒。
虎刀門的弟子們練功消耗極大，這裡每天要備足數十人的飯食。一股濃
郁的肉香瀰漫在空氣中，讓人食指大動。
LONG
    );
    set("exits", ([
        "east" : __DIR__"hall",
    ]));

    set("objects", ([ __DIR__"npc/cook" : 1 ]));
    setup();
}
