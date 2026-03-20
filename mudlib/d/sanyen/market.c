// Room: /d/sanyen/market.c

inherit ROOM;

void create()
{
	set("short", "簡陋市集");
	set("long", @LONG
焱硝村中一處簡陋的市集，不過是幾個用木板搭起的攤位。賣的
東西也不多，無非是些粗糧蔬菜和日常用品。偶爾有從山上下來的獵
人，帶著幾張獸皮和一些山貨來交易。
LONG
	);
	set("objects", ([
		__DIR__"npc/pilgrim" : 1,
		__DIR__"npc/merchant" : 1,
	]));
	set("exits", ([
		"east" : __DIR__"back_alley",
		"west" : __DIR__"square",
	]));

	setup();
	replace_program(ROOM);
}
