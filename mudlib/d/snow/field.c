// Room: /d/snow/field.c -- 雪亭鎮郊野，通往練功場的一段野地。

inherit ROOM;

void create()
{
	set("short", "雪亭鎮郊野");
	set("long", @LONG
這裡是雪亭鎮南門外的一片郊野﹐草棚就在西邊不遠處。野地上長
著半人高的雜草﹐不時有野兔田鼠在草叢間鑽動。往東踩出一條被人走
得發白的小徑﹐通往鎮民平日練拳習武的練功場。
LONG
	);
	set("outdoors", "snow");
	// 沒有設 no_fight，所以可以在這裡 kill 練手。
	set("objects", ([ /* sizeof() == 3 */
		__DIR__"npc/rabbit" : 1,
		__DIR__"npc/mouse" : 1,
		__DIR__"npc/herbfarmer" : 1,
	]));
	set("exits", ([ /* sizeof() == 2 */
		"west" : __DIR__"sgate",
		"east" : __DIR__"drill",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
