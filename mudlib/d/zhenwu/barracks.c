// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "營房");
    set("long", @LONG
一排排整齊的木架床鋪沿著牆壁排列，每張床鋪旁都有一個上了鎖
的儲物木箱。營房內一塵不染，被褥疊得整整齊齊，顯示出嚴格的軍紀。
牆上掛著幾把備用的刀劍，空氣中瀰漫著淡淡的皮革和鐵鏽的氣味。
LONG
    );
    set("exits", ([
        "west"  : __DIR__"yard",
        "north" : __DIR__"armory",
    ]));

    setup();
    replace_program(ROOM);
}
