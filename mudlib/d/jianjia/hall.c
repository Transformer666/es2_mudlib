inherit ROOM;

void create()
{
    set("short", "劍甲堂");
    set("long", @LONG
劍甲堂是劍甲門的正殿﹐牆上掛滿了各式劍器﹐從細長的繡花劍到
寬厚的斬馬劍﹐琳瑯滿目。正面牆上掛著一幅巨大的鑄劍圖﹐描繪著
一名鑄劍師在爐火前揮錘的場景。
LONG
    );
    set("objects", ([
        __DIR__"npc/master" : 1,
    ]));
    set("exits", ([
        "west"  : __DIR__"entrance",
        "north" : __DIR__"forge",
        "east"  : __DIR__"training",
        "south" : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}
