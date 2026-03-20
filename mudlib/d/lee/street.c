// Room: /d/lee/street.c

inherit ROOM;

void create()
{
	set("short", "李家村");
	set("long", @LONG
李家村的主街﹐是一條青石板鋪成的小路。路兩旁是整齊的民房﹐
門前種著幾棵桃樹﹐此時正是花開時節﹐粉色的桃花開得正盛。空氣
中瀰漫著一股豆腐的香味﹐村裡的李家豆腐遠近聞名。
LONG
	);
	set("objects", ([
		__DIR__"npc/elder" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"square",
		"north" : __DIR__"inn",
		"south" : __DIR__"farm",
		"east" : __DIR__"ancestral_hall",
	]));

	setup();
	replace_program(ROOM);
}
