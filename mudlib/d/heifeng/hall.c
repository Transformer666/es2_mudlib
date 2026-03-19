// Room: /d/heifeng/hall.c

inherit ROOM;

void create()
{
	set("short", "聚義廳");
	set("long", @LONG
黑風寨的聚義廳﹐正中央擺著一把虎皮交椅﹐那是寨主的座位。
大廳兩側各排著幾張太師椅﹐牆上掛著刀槍劍戟等各式兵器。正面牆上
掛著一幅「替天行道」的匾額﹐不過以這些人的作為來看﹐這四個字實
在是有些諷刺。
LONG
	);
	set("objects", ([
		__DIR__"npc/bandit_leader" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"yard",
	]));

	setup();
	replace_program(ROOM);
}
