// Room: /d/lee/shop.c

inherit ROOM;

void create()
{
	set("short", "雜貨舖");
	set("long", @LONG
村後小路邊搭了一間簡陋的棚子﹐幾塊木板拼成的貨架上擺著些
日常用品。一盞油燈在風中搖曳﹐照亮了角落裡堆放的草蓆和竹
簍。雖然貨物不多﹐但對這個偏僻小村來說已是難得的便利。
LONG
	);
	set("objects", ([
		__DIR__"npc/shopkeeper" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"back_street",
	]));

	setup();
	replace_program(ROOM);
}
