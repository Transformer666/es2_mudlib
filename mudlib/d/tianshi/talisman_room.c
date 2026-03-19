inherit ROOM;

void create()
{
    set("short", "符籙房");
    set("long", @LONG
符籙房中擺放著一張寬大的書桌﹐桌上散落著朱砂、黃紙和各種繪
符的工具。牆上掛滿了各式各樣的符籙﹐有鎮宅符、驅邪符、平安符
等﹐五花八門。
LONG
    );
    set("objects", ([
        __DIR__"npc/talisman_maker" : 1,
    ]));
    set("exits", ([
        "west" : __DIR__"courtyard",
    ]));

    setup();
    replace_program(ROOM);
}
