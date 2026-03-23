// Room: /d/chixiao/east_path.c

inherit ROOM;

void create()
{
	set("short", "村東小路");
	set("long", @LONG
後巷東邊延伸出一條窄窄的小路﹐路旁的土坯牆上爬滿了枯藤。
小路兩側長著一些不知名的野草﹐散發出一種奇特的苦澀氣味。往
南可以看到一片荒廢的園子﹐似乎以前有人在那裡種過藥草。路上
偶爾能撿到一些乾枯的草藥殘渣。
LONG
	);
	set("exits", ([
		"west"  : __DIR__"back_street",
		"south" : __DIR__"herb_garden",
	]));

	setup();
	replace_program(ROOM);
}
