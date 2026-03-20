// Room: /d/baihua/back_street.c

inherit ROOM;

void create()
{
	set("short", "花巷");
	set("long", @LONG
一條幽靜的小巷﹐兩側的矮牆上爬滿了盛開的牽牛花和紫藤。巷
子裡很安靜﹐偶爾有蝴蝶翩翩飛過。牆角堆著幾個花盆﹐裡面種著
各種奇花異草﹐顯然是哪位村民精心培育的。
LONG
	);
	set("exits", ([
		"west" : __DIR__"square",
		"east" : __DIR__"shop",
	]));

	setup();
	replace_program(ROOM);
}
