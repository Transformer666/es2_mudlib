// vim: syntax=lpc

inherit ROOM;

void create()
{
	set("short", "小村莊入口");
	set("long", @LONG
一條泥土小路從荒野中延伸到這裡，路的盡頭是一個樸素的小村莊。村口立著一棵老槐樹，樹下放著幾塊石頭供行人歇腳。遠處可以看到幾間茅草屋頂的農舍，炊煙裊裊升起。雞犬之聲相聞，一派寧靜的田園風光。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"north" : "/d/road/wild_path2",
		"south" : __DIR__"street",
	]));

	setup();
	replace_program(ROOM);
}
