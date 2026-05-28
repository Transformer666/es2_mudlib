// Room: /d/eastmarket/market1.c

inherit ROOM;

void create()
{
	set("short", "東市口");
	set("long", @LONG
這裡是雪亭鎮東市的入口﹐往西可以回到熱鬧的廣場北側﹐東邊是
一條兩旁擺滿攤子的市集街﹐叫賣聲此起彼落﹐南邊巷底有一口供市集
裡的人取水的古井﹐井邊終日溼漉漉的。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
		"west" : "/d/snow/square_n",
		"east" : __DIR__"market2",
		"south" : __DIR__"well",
	]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
