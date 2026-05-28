// Room: /d/buxuan/academy.c

inherit ROOM;

void create()
{
	set("short", "步玄書院");
	set("long", @LONG
這是步玄派的書院﹐一方清幽的庭院﹐青石板鋪就的天井當中植著
一株老梅﹐樹下擺著一張石桌與幾隻石凳﹐桌上常擱著未收的棋枰與書
卷。四圍迴廊環抱﹐廊下懸著幾盞素紗燈籠﹐幾名青衫弟子捧卷往來﹐
或誦讀﹐或對弈﹐神情從容。往北是派中論劍說藝的論劍堂﹐往東是收
藏典籍的藏書閣﹐往西是弟子演武的演武場﹐往南則是派中的山門。
LONG
	);
	set("detail", ([
		"老梅" : "庭院當中的老梅虯枝盤曲﹐枝頭綴著幾點寒梅﹐暗香浮動﹐
頗有幾分孤高之氣。
",
		"石桌" : "樹下的石桌光潔溫潤﹐桌面刻著縱橫的棋盤紋路﹐想是弟子們
平日對弈推枰之處。
",
		"燈籠" : "廊下的素紗燈籠隨風輕晃﹐燈影投在白牆上﹐映出竹石的疏淡
剪影。
",
	]));
	set("outdoors", "snow");
	set("exits", ([
		"north" : __DIR__"hall",
		"east" : __DIR__"library",
		"west" : __DIR__"arena",
		"south" : __DIR__"gate",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
