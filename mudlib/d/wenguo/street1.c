// Room: /d/wenguo/street1.c

inherit ROOM;

void create()
{
	set("short", "東大街");
	set("long", @LONG
東大街是文國縣城內最熱鬧的一條街道﹐兩旁店鋪林立﹐有茶攤
、小吃鋪、布莊等各色商家。街道上鋪著平整的青石板﹐被行人的腳
步磨得光亮。不時有挑著擔子的小販穿梭其間﹐叫賣聲此起彼伏。往
東可出城門﹐往西是縣城廣場﹐往北則有一家書鋪。
LONG
	);
	set("outdoors", "city");
	set("exits", ([
		"east" : __DIR__"egate",
		"west" : __DIR__"square",
		"north" : __DIR__"shop",
	]));

	setup();
	replace_program(ROOM);
}
