// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "虎刀門山門");
    set("long", @LONG
一座氣派的山門矗立眼前，門前兩尊栩栩如生的石虎怒目圓睜，彷
彿隨時要撲向來人。門楣上高懸著一面黑底金字的牌匾，上書「虎刀門
」三個蒼勁有力的大字。山門兩側的石柱上雕刻著虎紋，透出一股霸氣。
LONG
    );
    set("exits", ([
        "west" : "/d/road/road2",
        "north" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
