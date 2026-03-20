// Room: /d/kangping/shop.c

inherit ROOM;

void create()
{
	set("short", "雜貨鋪");
	set("long", @LONG
農舍旁邊搭了一間簡陋的棚子﹐權當雜貨鋪。幾塊木板搭成的貨
架上擺著一些日常用品﹕油鹽醬醋、針頭線腦、草鞋斗笠。雖然東西
不多﹐卻是這偏僻小村裡唯一能買到東西的地方。
LONG
	);
	set("objects", ([
		__DIR__"npc/merchant" : 1,
	]));
	set("exits", ([
		"west" : __DIR__"cottage",
	]));

	setup();
	replace_program(ROOM);
}
