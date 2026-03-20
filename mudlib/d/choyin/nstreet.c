// Room: /d/choyin/nstreet.c

inherit ROOM;

void create()
{
	set("short", "北街");
	set("long", @LONG
喬陰縣城的北街﹐街道不寬﹐兩旁是些低矮的民房和小店鋪。街上
行人不多﹐偶爾有挑著擔子的小販經過﹐吆喝著賣些針頭線腦的雜貨。
東邊有一家招牌寫著「名山書肆」的書店﹐往南走便是縣城的廣場。
LONG
	);
	set("exits", ([
		"north" : __DIR__"ngate",
		"south" : __DIR__"square",
		"east" : __DIR__"bookshop",
		"west" : __DIR__"shop",
	]));

	setup();
	replace_program(ROOM);
}
