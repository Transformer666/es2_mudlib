// Room: /d/heifeng/gate.c

inherit ROOM;

void create()
{
	set("short", "黑風山寨門");
	set("long", @LONG
一座用巨木搭建的寨門矗立在山路盡頭﹐門上掛著一塊黑漆木匾﹐
上面用紅漆寫著「黑風寨」三個大字。寨門兩側各立著一根木柱﹐柱頂
插著畫戟﹐看起來殺氣騰騰。門前站著一名面目凶惡的守門人﹐正警
惕地盯著來人。
LONG
	);
	set("objects", ([
		__DIR__"npc/guard" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"road2",
		"north" : __DIR__"yard",
	]));

	setup();
	replace_program(ROOM);
}
