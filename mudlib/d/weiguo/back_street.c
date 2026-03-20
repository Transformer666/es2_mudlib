// Room: /d/weiguo/back_street.c

inherit ROOM;

void create()
{
	set("short", "後營小路");
	set("long", @LONG
鎮門西側的一條小路﹐路面是夯實的泥土﹐被軍靴踩得十分結實。
路旁堆放著一些木箱和糧袋﹐看起來是軍需物資。幾個士兵正在搬運
貨物﹐忙得不可開交。
LONG
	);
	set("exits", ([
		"east" : __DIR__"entrance",
		"north" : __DIR__"shop",
	]));

	setup();
	replace_program(ROOM);
}
