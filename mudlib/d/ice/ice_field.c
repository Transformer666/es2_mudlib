// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "冰原");
	set("long", @LONG
一望無際的冰原在眼前展開，地面上的冰層厚達數尺，在陽光下折射出七彩的光芒。寒風如刀，刮在臉上生疼。遠處隱約可見一面結了冰的湖泊，東面則有一個冰洞的入口。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/frost_frog" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"frozen_lake",
		"east" : __DIR__"ice_cave",
	]));

	setup();
	replace_program(ROOM);
}
