inherit ROOM;

void create()
{
    set("short", "弟子居所");
    set("long", @LONG
一間陰暗的居室﹐擺放著幾張簡陋的木床和矮桌。牆角放著幾個黑
色的木箱﹐裡面大概是弟子們的私人物品。窗戶用黑布遮得嚴嚴實實﹐
只有一盞油燈散發著微弱的光芒。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
