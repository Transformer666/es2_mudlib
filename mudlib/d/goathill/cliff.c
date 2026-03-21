// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "羊山懸崖");
	set("long", @LONG
山頂西面是一處令人目眩的懸崖，往下看去深不見底，只能聽到風在峽谷中迴盪的呼嘯聲。懸崖邊緣長著幾棵被風吹得歪歪斜斜的老樹，樹上掛著一些破碎的布條，不知是什麼人留下的。
LONG
	);
	set("outdoors", "wilderness");
	set("objects", ([
		__DIR__"npc/mountain_wolf" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"peak",
		"down" : __DIR__"ravine",
	]));

	setup();
	replace_program(ROOM);
}
