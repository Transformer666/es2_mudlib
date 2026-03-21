inherit ROOM;

void create()
{
    set("short", "步玄正堂");
    set("long", @LONG
步玄正堂裝飾得莊重典雅﹐正面牆上掛著一幅「文武雙全」的匾額
。堂中擺放著一張講學用的几案和幾排座椅﹐看起來是門生們聽講的地
方。
LONG
    );
    set("exits", ([
        "south" : __DIR__"study",
        "east"  : __DIR__"training",
        "north" : __DIR__"quarters",
    ]));

    set("objects", ([
        __DIR__"npc/disciple" : 2,
    ]));

    setup();
    replace_program(ROOM);
}
