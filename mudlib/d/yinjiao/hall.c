inherit ROOM;

void create()
{
    set("short", "隱教大殿");
    set("long", @LONG
隱教大殿深藏於地下﹐卻出乎意料的寬敞華麗。殿中燃著無數燭火
﹐將殿堂照得通明。正面高台上坐著教主的寶座﹐兩側懸掛著黑色幔帳
。殿中有數名教眾肅立。
LONG
    );
    set("objects", ([
        __DIR__"npc/master" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"gate",
        "east"  : __DIR__"training",
        "west"  : __DIR__"cell",
        "north" : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}
