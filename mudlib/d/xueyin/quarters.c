inherit ROOM;

void create()
{
    set("short", "內院");
    set("long", @LONG
內院是莊主和貴客的起居之所﹐佈置得舒適而大氣。房中擺放著紅木
家具﹐牆上掛著名家字畫﹐桌上放著一套精緻的茶具。
LONG
    );
    set("no_fight", 1);
    set("exits", ([
        "east" : __DIR__"hall",
    ]));

    setup();
    replace_program(ROOM);
}
