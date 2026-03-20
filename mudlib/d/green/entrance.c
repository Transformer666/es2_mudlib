// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "草原入口");
	set("long", @LONG
官道在此向西延伸，眼前豁然開朗，一望無際的草原在陽光下泛著金綠色的波浪。草叢中不時有野兔竄出，遠處可見幾隻鹿在悠閒地吃草。空氣中瀰漫著青草和野花的芬芳。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/shepherd" : 1,
	]));
	set("exits", ([
		"east" : "/d/road/road3",
		"north" : __DIR__"grassland_n",
		"south" : __DIR__"grassland_s",
	]));

	setup();
	replace_program(ROOM);
}
