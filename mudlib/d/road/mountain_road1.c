// Room: /d/road/mountain_road1.c

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
一條狹窄的山間小徑陡峭地向上攀升，兩旁生長著蒼勁的古松，
枝幹虯結，樹齡怕有數百年之久。山風吹來，松濤陣陣，令人精神一
振。這條山路通往鳳山劍派的所在，往南則可以回到山下的官道。腳下
的石階已被歲月磨得光滑，看來走過這條路的人不在少數。
LONG
	);
	set("outdoors", "road");
	set("exits", ([
		"south" : __DIR__"road1",
		"north" : "/d/fengshan/gate",
	]));

	setup();
	replace_program(ROOM);
}
