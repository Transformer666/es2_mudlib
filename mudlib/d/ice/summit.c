// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "冰峰");
	set("long", @LONG
這是冰域的最高處，站在冰峰之上，四面八方都是一片銀白色的世界。寒風凜冽，呼吸間都能看到白色的霧氣。遠處的山巒在雪霧中若隱若現，腳下的冰層散發著藍寶石般的光澤。這裡似乎隱藏著某種古老的力量。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/ice_guardian" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"glacier",
	]));

	setup();
	replace_program(ROOM);
}
