// Room: /d/longan/smithy.c

inherit ROOM;

void create()
{
	set("short", "鐵匠鋪");
	set("long", @LONG
一間煙火繚繞的鐵匠鋪，爐火正旺，鐵砧上火星四濺。牆上掛著
各式鍛造工具，角落裡堆放著一些半成品的刀劍。空氣中瀰漫著炭火
和鐵鏽的味道，讓人不禁掩鼻。
LONG
	);
	set("objects", ([
		__DIR__"npc/blacksmith" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"weapon_shop",
		"west"  : __DIR__"north_street",
	]));

	setup();
	replace_program(ROOM);
}
