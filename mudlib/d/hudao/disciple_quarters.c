// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "弟子房");
    set("long", @LONG
一排簡陋的木屋沿著院牆排列，每間屋內只有一張硬板床、一個刀
架和一口木箱，陳設極為簡單。虎刀門崇尚以武為尊，弟子們的生活也
如同他們的刀法一般，簡單直接，毫不拖泥帶水。牆上掛著幾幅虎形圖
，彷彿在時刻提醒弟子們不忘初心。
LONG
    );
    set("exits", ([
        "west" : __DIR__"training",
    ]));
    set("no_fight", 1);

    set("objects", ([ __DIR__"npc/disciple" : 1 ]));
    setup();
}
