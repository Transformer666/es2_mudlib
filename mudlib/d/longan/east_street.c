// Room: /d/longan/east_street.c

inherit ROOM;

void create()
{
	set("short", "東街");
	set("long", @LONG
龍安城東街兩側排列著一座座青磚倉房﹐大門上貼著封條或掛著鐵鎖。
幾個身材壯碩的腳夫扛著沉重的貨包﹐來回穿梭在倉房之間。地上散
落著些許稻草和麻繩﹐空氣中瀰漫著陳年穀物和木箱的氣味。
LONG
	);
	set("exits", ([
		"west"  : __DIR__"market",
		"south" : __DIR__"weapon_shop",
	]));

	setup();
	replace_program(ROOM);
}
