// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "飛瀑");
    set("long", @LONG
山道旁一道飛瀑從數十丈高的崖壁上傾瀉而下，水花四濺，轟鳴
聲震耳欲聾。瀑布下方是一潭碧綠的深潭，水面霧氣蒸騰。潭邊的岩
石上長滿了翠綠的苔蘚，幾棵古松斜斜地探出崖壁，在水霧中若隱若現。
據說封山派的先輩曾在這瀑布下修練劍法，以水瀑磨練劍意。
LONG
    );
    set("outdoors", "mountain");
    set("exits", ([
        "east" : __DIR__"path",
    ]));

    setup();
    replace_program(ROOM);
}
