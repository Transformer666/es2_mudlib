// Room: /d/chixiao/street.c

inherit ROOM;

void create()
{
	set("short", "赤魈村小路");
	set("long", @LONG
一條蜿蜒的泥土小路﹐兩旁是低矮破舊的土坯房。路面坑坑窪
窪的﹐有些地方還積著渾濁的水窪。空氣中瀰漫著一股說不清的腥
氣﹐讓人有些不安。路邊的牆角長著一些暗紅色的苔蘚﹐在這個偏僻
的村子裡﹐連植物都透著一股詭異的氣息。
LONG
	);
	set("exits", ([
		"west"  : __DIR__"village_square",
		"east"  : __DIR__"back_street",
		"south" : __DIR__"shop",
	]));

	setup();
	replace_program(ROOM);
}
