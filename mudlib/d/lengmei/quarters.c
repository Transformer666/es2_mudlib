inherit ROOM;

void create()
{
    set("short", "內室");
    set("long", @LONG
一間雅致的內室﹐佈置得十分清雅。窗前擺著一張書桌﹐桌上放著
一壺清茶和幾本劍譜。牆上掛著一幅梅花圖和一把裝飾用的古劍。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
