// Room: /d/eastmarket/teahouse.c

inherit ROOM;

void create()
{
	set("short", "茶寮");
	set("long", @LONG
這是一間簡陋的茶寮﹐幾張油亮的木桌散落在屋裡﹐牆角一只大茶
爐上的銅壺正咕嚕咕嚕地冒著熱氣﹐空氣裡瀰漫著一股粗茶的清香。一
個茶博士在桌椅之間忙碌地穿梭著。茶寮的出口在南邊。
LONG
	);
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"market2",
	]));
	set("objects", ([
		__DIR__"npc/teaboy" : 1,
	]));
	set("no_fight", 1);

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
