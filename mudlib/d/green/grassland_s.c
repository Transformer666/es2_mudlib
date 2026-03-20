// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "南草原");
	set("long", @LONG
草原的南端，地勢微微起伏，遠處可以看到一座山丘的輪廓。草叢中散落著一些碎石，似乎曾經有人在此搭營。西面隱約可見一條通往山上的小路。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"north" : __DIR__"entrance",
		"south" : __DIR__"campsite",
		"west" : "/d/goathill/entrance",
	]));

	setup();
	replace_program(ROOM);
}
