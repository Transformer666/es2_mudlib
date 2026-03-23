// Room: /d/qianchang/shop.c

inherit ROOM;

void create()
{
	set("short", "雜貨鋪");
	set("long", @LONG
一間不大的雜貨鋪，貨架上擺滿了各式日常用品和旅行補給。油鹽
醬醋、針頭線腦、火摺子、乾糧、草繩，林林總總地擺了滿滿當當。
櫃臺上放著一桿小秤和一把算盤，老闆正在整理貨物。
LONG
	);
	set("objects", ([
		__DIR__"npc/shopkeeper" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"street1",
	]));

	setup();
	replace_program(ROOM);
}
