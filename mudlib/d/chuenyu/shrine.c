// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "泉神祠");
	set("long", @LONG
一座古樸的石頭小祠堂建在碧玉潭旁的高台上，祠內供奉著一尊泉神石像，石像面目祥和，手持寶瓶。祠前的石階上生滿了青苔，兩旁各立著一根石柱，柱上刻著「泉潤萬物，澤被蒼生」八個古字。
LONG
	);
	set("objects", ([
		__DIR__"npc/spring_keeper" : 1,
	]));
	set("no_fight", 1);
	set("exits", ([
		"west" : __DIR__"pool",
	]));

	setup();
	replace_program(ROOM);
}
