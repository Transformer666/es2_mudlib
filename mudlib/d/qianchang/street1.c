// Room: /d/qianchang/street1.c

inherit ROOM;

void create()
{
	set("short", "東大街");
	set("long", @LONG
前場鎮的東大街，街道兩旁是些低矮的磚木建築，有幾間小商鋪
和民居。門前掛著褪色的招牌和幌子，偶有店家在門口吆喝招攬生
意。街面鋪著青石板，被行人和車輪磨得光滑發亮。一個貨郎挑著
擔子沿街叫賣，引得幾個孩童追在後面跑。
LONG
	);
	set("outdoors", "city");
	set("exits", ([
		"east"  : __DIR__"egate",
		"west"  : __DIR__"square",
		"north" : __DIR__"shop",
	]));

	setup();
	replace_program(ROOM);
}
