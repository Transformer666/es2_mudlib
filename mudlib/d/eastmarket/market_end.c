// Room: /d/eastmarket/market_end.c

inherit ROOM;

void create()
{
	set("short", "市集盡頭");
	set("long", @LONG
這裡是東市市集街的盡頭﹐攤販到了這一段就稀稀落落﹐地上散著
一些被人丟棄的菜葉與爛果。往西可以回到熱鬧的市集街﹐往東則拐進
一條人跡罕至的背巷。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
		"west" : __DIR__"market2",
		"east" : __DIR__"lane",
	]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
