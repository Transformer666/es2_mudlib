// vim: syntax=lpc

inherit ROOM;

void create()
{
    set("short", "振武軍營大門");
    set("long", @LONG
高大的營牆圍起一座戒備森嚴的軍營，一扇厚重的大門前站著兩名
全副武裝的衛兵。門楣上方懸掛著一面巨大的旗幟，上書「振武」二字
，在風中獵獵作響。營門兩側的石墩上插著長戟，散發出一股肅殺之氣。
LONG
    );
    set("objects", ([
        __DIR__"npc/guard" : 2,
    ]));
    set("exits", ([
        "south" : "/d/road/road3",
        "north" : __DIR__"yard",
        "east"  : __DIR__"watchtower",
    ]));

    setup();
    replace_program(ROOM);
}
