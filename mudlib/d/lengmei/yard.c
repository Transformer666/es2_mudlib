inherit ROOM;

void create()
{
    set("short", "冷梅莊前院");
    set("long", @LONG
前院寬敞整潔﹐地面鋪著青石板。院中有一座假山和一口小池﹐池邊
種著幾株梅花。幾名白衣弟子在院中練劍﹐劍光如梅花綻放。
LONG
    );
    set("objects", ([
        __DIR__"npc/disciple" : 2,
    ]));
    set("exits", ([
        "south" : __DIR__"gate",
        "north" : __DIR__"hall",
        "east"  : __DIR__"plum_garden",
    ]));

    setup();
    replace_program(ROOM);
}
