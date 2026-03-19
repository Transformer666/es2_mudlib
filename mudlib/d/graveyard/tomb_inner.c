// Room: /d/graveyard/tomb_inner.c

inherit ROOM;

void create()
{
	set("short", "古墓內部");
	set("long", @LONG
古墓內部比想像中寬敞﹐四壁用青石砌成﹐石縫間滲出冰冷的水珠。
墓室中央放著一具石棺﹐棺蓋上刻著精美的花紋﹐不知是哪朝哪代的人
物長眠於此。牆壁上的壁畫已經剝落得差不多了﹐隱約可以看出是一些
人物和車馬的圖案。地上散落著幾件腐朽的陪葬品。
LONG
	);
	set("objects", ([
		__DIR__"npc/zombie" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"tomb",
	]));

	setup();
	replace_program(ROOM);
}
