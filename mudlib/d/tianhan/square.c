// Room: /d/tianhan/square.c

inherit ROOM;

void create()
{
    set("short", "天寒村廣場");
    set("long", @LONG
村子中央有一小片開闊的空地，算是天寒村的廣場了。地面鋪著
大小不一的青石板，縫隙間長滿了枯黃的野草。廣場中央有一棵老
槐樹，粗壯的樹幹上掛著一面銅鑼，大概是村裡有事時用來召集村
民的。幾位老人正圍坐在樹下閒聊，說著些陳年舊事。
LONG
    );
    set("outdoors", "village");
    set("objects", ([
        __DIR__"npc/elder" : 1,
    ]));
    set("detail", ([
        "老槐樹" : "一棵粗壯的老槐樹，枝幹虬曲蒼勁，看來已有上百年的樹齡。\n",
        "銅鑼" : "一面年代久遠的銅鑼，表面已經發綠。\n",
    ]));
    set("exits", ([
        "south" : __DIR__"street",
        "north" : __DIR__"clearing",
    ]));

    setup();
    replace_program(ROOM);
}
