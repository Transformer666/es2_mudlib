// Room: /d/green_n/windswept.c

inherit ROOM;

void create()
{
	set("short", "風嘯草原");
	set("long", @LONG
狂風在這片開闊的草原上肆虐，將齊腰的野草吹得東倒西歪。偶
爾有幾隻飛鷹在天空盤旋，發出尖銳的啼叫。腳下的泥土鬆軟潮
濕，留下一串串深淺不一的腳印。遠處有幾座突兀的岩石堆，像是大
地上長出的牙齒。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/wild_wolf" : 2,
	]));
	set("exits", ([
		"south" : __DIR__"entrance",
		"north" : __DIR__"rock_formation",
		"west"  : __DIR__"highland",
	]));

	setup();
	replace_program(ROOM);
}
