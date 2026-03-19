// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "封山派大殿");
    set("long", @LONG
一座以黑色山石建成的宏偉大殿，四壁刻滿了密密麻麻的劍譜銘文，
記載著封山派歷代祖師的劍法精要。正面的神龕上供奉著歷代掌門的靈
位，香煙繚繞。大殿東面通往劍道場，西面是弟子房。
LONG
    );
    set("exits", ([
        "south" : __DIR__"path",
        "east"  : __DIR__"sword_arena",
        "west"  : __DIR__"quarters",
    ]));

    set("objects", ([
        __DIR__"npc/liudonglu" : 1,
    ]));

    setup();
    replace_program(ROOM);
}
