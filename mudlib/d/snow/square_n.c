// Room: /d/snow/square_n.c

inherit ROOM;

void create()
{
	set("short", "廣場");
	set("long", @LONG
這裡是雪亭鎮廣場北邊﹐平常是附近孩童嬉戲遊玩的地方﹐初一十
五則是市集的所在﹐往南可以看見一株大榕樹﹐往北則是一條筆直的街
道。西北角一片修竹掩映﹐隱約可見一座書卷氣的門樓﹐想是步玄派的
山門。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"north" : __DIR__"nstreet1",
		"south" : __DIR__"square",
		"east" : "/d/eastmarket/market1",
		"northwest" : "/d/buxuan/gate",
	]));
	set("objects", ([
		__DIR__"npc/child1" : 1,
		__DIR__"npc/child2" : 1
	]) );
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}
