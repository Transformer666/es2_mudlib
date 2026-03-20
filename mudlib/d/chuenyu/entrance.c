// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "泉域入口");
	set("long", @LONG
空氣中瀰漫著溫暖的水汽，腳下的泥土變得柔軟而潮濕。前方是一片被溫泉和溪流環繞的神秘區域，到處都冒著白色的蒸汽。岩石上長滿了翠綠的苔蘚和蕨類植物，空氣中帶著一股淡淡的硫磺味。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"north" : "/d/village/farm",
		"east" : __DIR__"spring_path",
	]));

	setup();
	replace_program(ROOM);
}
