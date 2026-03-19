// Room: /d/heifeng/buddha.c

inherit ROOM;

void create()
{
	set("short", "石佛像");
	set("long", @LONG
路旁的草叢中有一尊半埋在土裡的石佛像﹐佛像已經殘破不堪﹐面
容模糊﹐但仍然可以看出是一尊結跏趺坐的佛陀像。佛像前面的地上
散落著一些野花﹐似乎有人偶爾會來此祭拜。石佛背後刻著幾行模糊
的字跡﹐已難以辨認。
LONG
	);
	set("exits", ([
		"west" : __DIR__"road2",
	]));

	setup();
	replace_program(ROOM);
}
