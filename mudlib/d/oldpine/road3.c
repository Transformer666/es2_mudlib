// Room: /d/oldpine/road3.c

inherit ROOM;

void create()
{
	set("short", "松林岔路");
	set("long", @LONG
小徑在這裡分成兩條﹐一條繼續往南延伸﹐看來是通往松林出口的
方向﹔另一條往東穿過灌木叢﹐不知通往何處。往東的路旁立著一塊石
碑﹐上面的字跡已被風雨侵蝕得模糊不清﹐依稀可辨「康平」二字。
LONG
	);
	set("outdoors", "forest");
	set("objects", ([
		__DIR__"npc/bandit" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"road2",
		"south" : __DIR__"road4",
		"northeast" : __DIR__"cliff",
		"east" : "/d/kangping/wgate",
	]));

	setup();
	replace_program(ROOM);
}
