// Room: /d/wutang/eastlane.c

inherit ROOM;

void create()
{
	set("short", "僻靜小巷");
	set("long", @LONG
這是一條僻靜的小巷﹐遠離了大街的喧鬧﹐兩側盡是住家的後牆﹐
牆頭探出幾枝開得正盛的桃花。巷子盡頭一口老井邊﹐一個婦人正在浣
洗衣裳﹐木杵敲打衣物的聲音在巷子裡迴盪。巷子東頭一條雜草沒徑的
小路通往鎮東荒僻的山坳﹐往西則可回到鎮中的十字路口。
LONG
	);
	set("detail", ([
		"老井" : "一口砌著青磚的老井﹐井欄被汲水的繩索勒出一道道深深的凹痕﹐井水清冽。\n",
		"桃花" : "牆頭探出的幾枝桃花開得正豔﹐替這條冷清的小巷添了幾分春色。\n",
	]));
	set("objects", ([
		__DIR__"npc/washerwoman" : 1,
	]));
	set("outdoors", "wutang");
	set("exits", ([ /* sizeof() == 2 */
		"west" : __DIR__"cross",
		"east" : __DIR__"statue",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
