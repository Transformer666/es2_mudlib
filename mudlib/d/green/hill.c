// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "草原丘陵");
	set("long", @LONG
站在這座低矮的丘陵上，可以俯瞰整片草原的壯麗景色。四面八方都是翠綠的草地，微風吹過時草浪翻滾，如同碧綠的海洋。丘頂有幾塊巨石，上面長滿了苔蘚，看起來年代久遠。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/godly_dog" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"grassland_n",
	]));

	setup();
	replace_program(ROOM);
}
