// Room: /d/snow/square_sw.c

inherit ROOM;

void create()
{
	set("short", "廣場");
	set("long", @LONG
這裡是雪亭鎮廣場的西南邊﹐廣場中央的大榕樹就在你的東北方不
遠處﹐這裡的北邊可以看見一家客棧﹐往西是一條街道﹐東邊穿過一個
路口可看見一家打鐵鋪子。南邊有一條小路﹐通往一座破舊的莊園。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
		"west" : __DIR__"wstreet1",
		"east" : __DIR__"square_s",
		"north" : __DIR__"square_w",
		"south" : __DIR__"dilapidated_manor",
]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
