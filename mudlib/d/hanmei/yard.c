// Room: /d/hanmei/yard.c

inherit ROOM;

void create()
{
	set("short", "冷梅莊前院");
	set("long", @LONG
這是冷梅莊的前院﹐院中以青石鋪地﹐打掃得一塵不染。院角一方
小小的池塘結著薄冰﹐塘邊幾株疏梅斜倚著粉牆﹐暗香浮動。莊中弟子
往來其間﹐或負劍而行﹐或低聲論劍。往北是莊內弟子日常練武的演武
場﹐往東通往莊主議事的正廳﹐往南則是冷梅莊的大門。
LONG
	);
	set("detail", ([
		"池塘" : "一方小池結著薄冰﹐幾尾錦鯉在冰下緩緩游動。
",
		"疏梅" : "幾株疏梅斜倚粉牆﹐花開五瓣﹐冷香沁人﹐正是冷梅莊得名之由。
",
	]));
	set("outdoors", "snow");
	set("exits", ([
		"north" : __DIR__"arena",
		"east" : __DIR__"hall",
		"south" : __DIR__"gate",
	]));

	setup();
}
// vim: set ts=4 sw=4 syntax=lpc
