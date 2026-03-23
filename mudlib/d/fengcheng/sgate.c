// Room: /d/fengcheng/sgate.c

inherit ROOM;

void create()
{
    set("short", "風城南門");
    set("long", @LONG
這裡是風城的南門﹐兩扇沉重的鐵皮大門日夜敞開著﹐門洞上方
的石額上刻著「迎風門」三個大字。城門外是一條蜿蜒南下的山路﹐
通往野羊山方向。進出城門的多半是往來於天山各處的旅人和商隊﹐
守門的兵士盤查得倒也不甚嚴格。
LONG
    );
    set("outdoors", "town");
    set("objects", ([
        __DIR__"npc/guard" : 2,
    ]));
    set("exits", ([
        "north" : __DIR__"street1",
        "south" : "/d/goathill/peak",
    ]));

    setup();
    replace_program(ROOM);
}
