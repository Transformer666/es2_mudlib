// Room: /d/snow/drill.c -- 雪亭練功場，新手練功打木人的地方。

inherit ROOM;

void create()
{
	set("short", "雪亭練功場");
	set("long", @LONG
這是一塊被踩得結結實實的空地﹐四周插著幾根練拳用的木樁﹐場
中央立著一個纏滿麻布的練功木人﹐供鎮上初學武藝的少年捶打練手。
角落堆著幾捆稻草﹐空氣裡飄著塵土跟汗水的氣味。往北是一座圍著土
牆的練武堂﹐往西沿著小徑回到郊野。
LONG
	);
	set("detail/木樁",
		"幾根半人高的木樁釘在地上﹐木頭表面被拳腳磨得光滑發亮。\n");
	set("detail/稻草",
		"幾捆乾稻草隨意堆在角落﹐大概是用來墊著歇腳的。\n");
	set("outdoors", "snow");
	// 沒有設 no_fight，所以可以在這裡 kill 木人練功。
	set("objects", ([ /* sizeof() == 1 */
		__DIR__"npc/dummy" : 1,
	]));
	set("exits", ([ /* sizeof() == 2 */
		"west" : __DIR__"field",
		"north" : __DIR__"martialhall",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
