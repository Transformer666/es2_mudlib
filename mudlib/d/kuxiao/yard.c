inherit ROOM;

void create()
{
    set("short", "前堂");
    set("long", @LONG
前堂中站著幾名弟子﹐有的面帶笑容﹐有的則一臉哀愁﹐令人莫名
其妙。牆上掛著各種哭笑面具﹐大的小的﹐木的銅的﹐琳瑯滿目。
LONG
    );
    set("objects", ([
        __DIR__"npc/disciple" : 2,
    ]));
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"hall",
        "east"  : __DIR__"training",
    ]));

    setup();
    replace_program(ROOM);
}
