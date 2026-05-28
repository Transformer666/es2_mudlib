// Room: /d/eastmarket/well.c

inherit ROOM;

void create()
{
	set("short", "古井");
	set("long", @LONG
這裡是東市南邊巷底的一口古井﹐青石砌成的井欄已經被汲水的繩
索磨出一道道深溝﹐井邊放著兩只破舊的木桶﹐地面溼漉漉的。往北可
以回到東市口。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
		"north" : __DIR__"market1",
	]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
