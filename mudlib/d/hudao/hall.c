// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "虎刀門大廳");
    set("long", @LONG
寬敞的大廳兩側牆壁上掛滿了猛虎的畫作，或嘯或撲，栩栩如生。
正中央的主座椅背雕刻著一頭張口咆哮的猛虎，威風凜凜。大廳兩旁
陳列著各式各樣的刀具，從厚背砍刀到薄刃柳葉刀，琳瑯滿目。
LONG
    );
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"inner_hall",
        "east"  : __DIR__"training",
    ]));

    set("objects", ([
        __DIR__"npc/hanxiao" : 1,
    ]));

    setup();
    replace_program(ROOM);
}
