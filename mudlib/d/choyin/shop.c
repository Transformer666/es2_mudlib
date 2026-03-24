// Room: /d/choyin/shop.c

inherit ROOM;

void create()
{
	set("short", "雜貨鋪");
	set("long", @LONG
一間不大的雜貨鋪﹐貨架上擺著各種日常用品﹐從油鹽醬醋到針頭
線腦﹐一應俱全。雖然店面不大﹐倒也收拾得井井有條。掌櫃站在
櫃台後面﹐熱情地招呼著客人。
LONG
	);
	set("objects", ([
		__DIR__"npc/merchant" : 1,
	]));
	set("exits", ([
		"east"  : __DIR__"nstreet",
		"south" : __DIR__"back_alley",
	]));

	setup();
	replace_program(ROOM);
}
