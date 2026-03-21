// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "羊山半山腰");
	set("long", @LONG
沿著崎嶇的山路攀爬到半山腰，四周盡是裸露的岩石和低矮的灌木叢。山風呼嘯而過，帶著一股涼意。往上可以看到山頂的輪廓，東面的岩壁上有一個黑漆漆的山洞入口。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/mountain_wolf" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"peak",
		"east" : __DIR__"cave",
	]));

	setup();
	replace_program(ROOM);
}
