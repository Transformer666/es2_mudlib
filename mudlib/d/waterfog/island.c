// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "霧中小島");
	set("long", @LONG
穿過木橋，來到溪流中的一座小島上。令人意外的是，小島上的霧氣反而稀薄了許多。島上長著幾棵參天大樹，樹冠如傘蓋般遮天蔽日。地面上長滿了奇異的菌類和苔蘚，散發著幽幽的冷光。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/swamp_creature" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"bridge",
		"east" : __DIR__"clearing",
	]));

	setup();
	replace_program(ROOM);
}
