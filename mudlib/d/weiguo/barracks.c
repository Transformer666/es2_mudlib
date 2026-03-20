// Room: /d/weiguo/barracks.c

inherit ROOM;

void create()
{
	set("short", "衛國營房");
	set("long", @LONG
這裡是衛國鎮駐軍的營房，一排排整齊的木架上擺放著長矛、弓箭
和盾牌。幾張簡陋的木床靠牆排列，被褥疊得方方正正，一絲不苟。牆
上掛著一張邊境地形圖，上面用紅色標記著幾處重要的哨位。角落裡堆
放著一些糧草和軍需物資，看來補給還算充足。
LONG
	);
	set("no_fight", 1);
	set("exits", ([
		"west"  : __DIR__"square",
		"east"  : __DIR__"stable",
		"north" : __DIR__"armory",
	]));
	set("objects", ([
		__DIR__"npc/quartermaster" : 1,
	]));

	setup();
	replace_program(ROOM);
}
