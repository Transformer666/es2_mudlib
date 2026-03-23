// Room: /d/chixiao/south_alley.c

inherit ROOM;

void create()
{
	set("short", "村南小巷");
	set("long", @LONG
客棧南邊的一條幽暗小巷﹐兩邊的牆壁上滲著水漬﹐角落裡長著
一層墨綠色的苔蘚。巷子裡堆著一些破舊的傢俱和碎陶罐﹐空氣
中瀰漫著一股霉味。往東走到巷子盡頭﹐有一間破舊的老宅﹐門板
歪斜﹐窗戶上的紙早已破損殆盡。
LONG
	);
	set("exits", ([
		"north" : __DIR__"inn",
		"east"  : __DIR__"old_house",
	]));

	setup();
	replace_program(ROOM);
}
