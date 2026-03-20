// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "練武場");
    set("long", @LONG
一片開闊的練武場，地面鋪著細沙，用來緩衝搏鬥時的衝擊。場中
豎立著數根粗壯的木樁，上面佈滿了刀砍斧劈的痕跡。幾個形似真人
的木製假人排列成陣，供士兵們練習實戰技巧。
LONG
    );
    set("exits", ([
        "east"  : __DIR__"yard",
        "north" : __DIR__"mess_hall",
    ]));

    setup();
    replace_program(ROOM);
}
