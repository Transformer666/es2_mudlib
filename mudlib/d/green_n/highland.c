// Room: /d/green_n/highland.c

inherit ROOM;

void create()
{
	set("short", "草原高地");
	set("long", @LONG
這裡是北草原的一處高地，地勢明顯比四周高出許多。站在此處放
眼望去，可以看到南方那片廣闊的草原一直延伸到天際。北方的山脈顯
得更加清晰，山頂覆蓋著皚皚白雪。高地上的風特別強勁，草叢中偶
爾閃過幾隻野兔的身影。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/wild_horse" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"windswept",
	]));

	setup();
	replace_program(ROOM);
}
