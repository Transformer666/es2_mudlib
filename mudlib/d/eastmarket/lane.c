// Room: /d/eastmarket/lane.c

inherit ROOM;

void create()
{
	set("short", "背巷");
	set("long", @LONG
這是市集後頭一條陰暗狹窄的背巷﹐兩側高牆夾峙﹐青苔順著牆腳
蔓延﹐巷子裡靜得只聽得見自己的腳步聲。往西可以回到市集盡頭﹐巷
子再往裡走似乎是條死巷。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
		"west" : __DIR__"market_end",
	]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
