// Room: /d/longan/garden.c

inherit ROOM;

void create()
{
	set("short", "城中花園");
	set("long", @LONG
城牆內側的一片小花園，雖然不大，卻打理得十分精心。幾株牡丹
正值花期，開得雍容華貴。園中有一座小石亭，亭下擺著石桌石椅，
是城中居民閒暇時散步休憩的好去處。
LONG
	);
	set("objects", ([
		__DIR__"npc/old_gardener" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"alley",
		"north" : __DIR__"lake_cave",
	]));

	setup();
	replace_program(ROOM);
}
