// Room: /d/wutang/lane2.c

inherit ROOM;

void create()
{
	set("short", "後巷");
	set("long", @LONG
這是一條僻靜的後巷﹐鮮少有人經過。巷子兩側是民居的後牆﹐牆
上爬滿了常春藤。往東望去﹐可以看到遠處蒼翠的山巒﹐那便是巫山的
方向﹐據說山上住著不少隱居的修行之人。往西回到廣場北邊。一陣山
風吹來﹐帶著松柏的清香。
LONG
	);
	set("exits", ([
		"west" : __DIR__"square_n",
		"east" : __DIR__"wushan_foot",
		"down" : "/d/langyi/tunnel",
	]));

	setup();
	replace_program(ROOM);
}
