// Room: /d/longan/back_street.c

inherit ROOM;

void create()
{
	set("short", "後街");
	set("long", @LONG
這條後街比大街冷清不少，兩旁是低矮的民居，門前晾著衣物。
幾個孩童在巷口追逐嬉戲，一位老嫗坐在門檻上曬著太陽。街邊有
幾棵老槐樹，樹下擺著一張破舊的棋盤。
LONG
	);
	set("objects", ([
		__DIR__"npc/peddler" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"teahouse",
		"east" : __DIR__"west_street",
	]));

	setup();
	replace_program(ROOM);
}
