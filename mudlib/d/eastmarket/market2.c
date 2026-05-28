// Room: /d/eastmarket/market2.c

inherit ROOM;

void create()
{
	set("short", "市集街");
	set("long", @LONG
這裡是東市最熱鬧的一段市集街﹐街道兩旁擺滿了販賣雜貨﹑布疋
與吃食的攤子﹐人來人往十分擁擠。往西是東市口﹐往東街道漸漸冷清
﹐北邊一間掛著布幌的茶寮飄出陣陣茶香。
LONG
	);
	set("exits", ([ /* sizeof() == 3 */
		"west" : __DIR__"market1",
		"east" : __DIR__"market_end",
		"north" : __DIR__"teahouse",
	]));
	set("outdoors", "snow");

	setup();
	replace_program(ROOM);
}

// vim: set ts=4 sw=4 syntax=lpc
