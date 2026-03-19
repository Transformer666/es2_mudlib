inherit ROOM;

void create()
{
    set("short", "書齋");
    set("long", @LONG
一間雅致的書齋﹐四壁擺滿了書架﹐上面放著各種醫書和丹方典籍
。靠窗的書桌上攤開著幾卷古籍﹐旁邊放著筆墨硯台。窗外是藥草園
﹐微風送來陣陣藥香。
LONG
    );
    set("objects", ([
        __DIR__"npc/elder" : 1,
    ]));
    set("exits", ([
        "south" : __DIR__"lab",
        "east"  : __DIR__"quarters",
    ]));

    setup();
    replace_program(ROOM);
}
