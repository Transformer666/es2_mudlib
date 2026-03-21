// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "冰川");
	set("long", @LONG
一座巨大的冰川橫亙在眼前，冰壁如刀削般光滑，散發著幽藍色的寒光。冰川的裂縫中不時傳來低沉的轟鳴聲，那是冰層在緩慢移動的聲音。東面有一條崎嶇的冰路通往更高處。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/ice_wolf" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"frozen_lake",
		"east" : __DIR__"summit",
	]));

	setup();
	replace_program(ROOM);
}
