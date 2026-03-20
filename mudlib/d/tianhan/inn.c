// Room: /d/tianhan/inn.c

#include <room.h>

inherit INN;

private void create()
{
    set("short", "域水客棧");
    set("long", @LONG
域水客棧雖然地處偏僻，卻在方圓百里內頗有名氣。據說這裡的
廚子是從京城退下來的御廚，手藝精湛，遠近馳名。客棧裡擺著幾張
粗木桌椅，牆上掛著幾幅褪色的字畫。空氣中飄散著飯菜的香氣，夾
雜著淡淡的酒香。東邊有一道樓梯通往二樓的客房。
LONG
    );
    set("objects", ([
        __DIR__"npc/waiter" : 1,
    ]));
    set("valid_startroom", 1);
    set("no_fight", 1);
    set("detail", ([
        "字畫" : "幾幅褪色的山水畫，年代看來頗為久遠。\n",
        "桌椅" : "粗木打造的桌椅，雖然簡陋卻擦得乾乾淨淨。\n",
    ]));
    set("exits", ([
        "north" : __DIR__"street",
        "up" : __DIR__"inn_2f",
    ]));

    setup();
}
