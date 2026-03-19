// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "寺院庭院");
    set("long", @LONG
一片靜謐的庭院中央生長著一棵枝葉繁茂的菩提樹，樹下鋪設著
青石小路，蜿蜒通向各處殿堂。幾位身穿灰色僧袍的僧人靜靜地沿著
小路行走，神態安詳。東邊矗立著一座鐘樓，北面是大雄寶殿。
LONG
    );
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"main_hall",
        "east"  : __DIR__"bell_tower",
    ]));

    setup();
    replace_program(ROOM);
}
