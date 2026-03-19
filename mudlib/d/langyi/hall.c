inherit ROOM;

void create()
{
    set("short", "瑯夷堂口");
    set("long", @LONG
地下堂口出乎意料的寬敞﹐四壁點著火把﹐照得通明。正面牆上掛
著一面金蛇旗﹐旗上繡著一條盤踞的金蛇。堂中擺放著幾張桌椅﹐幾
名瑯夷弟子正在低聲議事。
LONG
    );
    set("objects", ([
        __DIR__"npc/master" : 1,
        __DIR__"npc/spy" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"passage",
        "east"  : __DIR__"training",
        "west"  : __DIR__"quarters",
        "north" : __DIR__"vault",
    ]));

    setup();
    replace_program(ROOM);
}
