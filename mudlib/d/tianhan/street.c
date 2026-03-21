// Room: /d/tianhan/street.c

inherit ROOM;

void create()
{
    set("short", "天寒村街道");
    set("long", @LONG
一條窄小的泥土路穿過村子，路旁是幾間低矮的茅草屋。寒風從
北邊的山嶺吹來，帶著刺骨的寒意。路邊有一口古井，井沿上結著一
層薄冰。往南可以看到客棧的招牌在風中搖曳，往北則通往一片空地。
LONG
    );
    set("outdoors", "village");
    set("exits", ([
        "east" : __DIR__"entrance",
        "south" : __DIR__"inn",
        "north" : __DIR__"square",
        "west" : __DIR__"well",
    ]));

    setup();
    replace_program(ROOM);
}
