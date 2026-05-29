// Room: /d/snow/martialhall.c -- 雪亭練武堂，擺著各式練習標靶、由武師坐鎮的習武場。
// 接在練功場(drill)北邊。沒設 no_fight，所以可在此 kill 標靶練功。

inherit ROOM;

void create()
{
	set("short", "雪亭練武堂");
	set("long", @LONG
這是一座四面圍著土牆的練武堂﹐地上夯得平整結實。場中立著一
座纏滿麻布的木樁假人﹐角落蹲著一頭雕工古樸的石獅子﹐另一邊還埋
著一根半人合抱的青石柱﹐都是供人捶打練功的標靶。牆邊的兵器架上
插著幾把練功用的木刀木劍﹐一位精壯的武師正負手立在場中﹐瞧著後
生晚輩習武。往南可回到練功場。
LONG
	);
	set("detail/標靶",
		"場中的木樁假人、石獅子與石柱﹐都是給人捶打練拳腳兵器的死靶﹐"
		"任你怎麼打也不還手。\n");
	set("detail/兵器架",
		"牆邊一排木製兵器架﹐插著幾把鈍頭的木刀木劍﹐都是練功用的傢伙﹐"
		"傷不了人。\n");
	set("detail/土牆",
		"四面齊整的夯土矮牆﹐把這方練武場圍了起來﹐擋住場外的風塵。\n");
	set("outdoors", "snow");
	// 沒有設 no_fight，所以可以在這裡 kill 標靶練功（mirror drill.c）。
	set("objects", ([ /* sizeof() == 4 */
		__DIR__"npc/stake" : 1,
		__DIR__"npc/lion" : 1,
		__DIR__"npc/pillar" : 1,
		__DIR__"npc/instructor" : 1,
	]));
	set("exits", ([ /* sizeof() == 1 */
		"south" : __DIR__"drill",
	]));

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
