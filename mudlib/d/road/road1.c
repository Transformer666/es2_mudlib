// Room: /d/road/road1.c

inherit ROOM;

void create()
{
	set("short", "官道");
	set("long", @LONG
一條寬闊的官道向北延伸，路面鋪著整齊的青石板，兩旁立著石制
的里程碑，上面刻著距離各處的路程。往南不遠處便是雪亭鎮的北門，
往北則通往鳳山方向，遠處可見山巒起伏。路旁的草叢中偶爾傳來蟲
鳴，幾棵老柳樹在風中輕輕搖曳。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"south" : "/d/snow/ngate",
		"north" : __DIR__"road2",
		"northeast" : __DIR__"mountain_road1",
	]));

	setup();
	replace_program(ROOM);
}
