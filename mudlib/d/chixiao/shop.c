// Room: /d/chixiao/shop.c

inherit ROOM;

void create()
{
	set("short", "赤魈村雜貨鋪");
	set("long", @LONG
一間用茅草和木板搭成的簡陋棚子﹐勉強算是個雜貨鋪。貨架上
稀稀落落地擺著一些東西﹕幾瓶不知名的藥酒、一些粗製的符紙、
還有些零碎的日用品。攤主是個精明的中年人﹐正坐在櫃臺後面打
盹。
LONG
	);
	set("objects", ([
		__DIR__"npc/merchant" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"street",
	]));

	setup();
	replace_program(ROOM);
}
