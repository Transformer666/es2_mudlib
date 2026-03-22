// Room: /d/tianhan/street2.c

inherit ROOM;

void create()
{
    set("short", "天寒村西街");
    set("long", @LONG
村子西邊的一段小路，比起東邊的街道更加狹窄荒涼。路面坑坑窪
窪，積著薄薄的霜雪。北邊有一座香火冷清的小廟，隱約傳來木魚聲
響。南邊則是一間開著門的雜貨鋪，門口掛著一塊褪色的布幡。寒風
在這條小路上肆無忌憚地呼嘯著，讓人不禁裹緊了衣裳。
LONG
    );
    set("outdoors", "village");
    set("exits", ([
        "east" : __DIR__"well",
        "north" : __DIR__"temple",
        "south" : __DIR__"shop",
    ]));

    setup();
    replace_program(ROOM);
}
