inherit ROOM;

void create()
{
    set("short", "居所");
    set("long", @LONG
劍甲門弟子的居所﹐陳設簡單實用。牆上掛著幾把不同階段的劍器
成品﹐看得出弟子們對鑄劍的熱愛。桌上放著幾本鑄劍的筆記。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "north" : __DIR__"hall",
    ]));

    set("objects", ([
        __DIR__"npc/disciple" : 1,
    ]));

    setup();
    replace_program(ROOM);
}
