inherit ROOM;

void create()
{
    set("short", "道觀庭院");
    set("long", @LONG
道觀的庭院寬敞整潔﹐中央種著一棵古老的銀杏樹﹐樹冠如傘蓋般
遮蔽了大半個庭院。樹下放著一張石桌和幾個石凳﹐看起來是道士們平
日聚會論道之所。
LONG
    );
    set("objects", ([
        __DIR__"npc/acolyte" : 2,
    ]));
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"hall",
        "east"  : __DIR__"talisman_room",
    ]));

    setup();
    replace_program(ROOM);
}
