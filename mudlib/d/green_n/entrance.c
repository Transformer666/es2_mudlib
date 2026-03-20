// Room: /d/green_n/entrance.c

inherit ROOM;

void create()
{
	set("short", "北草原入口");
	set("long", @LONG
翻過草原丘陵，眼前豁然開朗，一片更加遼闊的草原展現在面前。
這裡是北草原的邊緣，草比南邊的更加茂盛，幾乎齊腰高。寒風從北
方吹來，帶著一絲凜冽的氣息，遠處隱約可見連綿的山脈輪廓。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"south" : "/d/green/hill",
		"north" : __DIR__"windswept",
		"east"  : __DIR__"stream",
	]));

	setup();
	replace_program(ROOM);
}
