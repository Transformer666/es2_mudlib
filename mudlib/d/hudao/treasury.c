// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "藏刀閣");
    set("long", @LONG
一間厚重石門後的密室，四壁鑲嵌著特製的刀架，上面陳列著虎刀
門歷代相傳的名刀。每把刀都用絲絨包裹著刀身，只露出造型各異的刀
柄。閣中央的玻璃罩下供奉著一把古樸的寶刀，據說是虎刀門開山祖師
的隨身兵器，刀身上的虎紋歷經百年仍然清晰可見。
LONG
    );
    set("exits", ([
        "south" : __DIR__"armory",
    ]));
    set("no_fight", 1);

    set("objects", ([ __DIR__"npc/guard" : 1 ]));
    setup();
}
