// Room: /d/chixiao/herb_garden.c

inherit ROOM;

void create()
{
	set("short", "荒廢藥圃");
	set("long", @LONG
一片荒廢已久的藥圃﹐用竹籬圍出的畦田大多已經坍塌﹐雜草長
得比人還高。不過仔細看去﹐雜草間還殘存著一些頑強生長的藥材
﹕幾株半枯的金銀花纏繞在竹籬上﹐牆角長著幾叢野生的當歸和黃
芪。一個佝僂著腰的老藥農正在草叢間翻翻撿撿﹐小心翼翼地採
摘著那些倖存的藥草。
LONG
	);
	set("detail", ([
		"金銀花" : "幾株半枯的金銀花﹐花朵已經不多了﹐但殘存的幾朵仍散發著淡淡的清香。\n",
		"當歸" : "幾叢野生的當歸﹐葉片有些發黃﹐但根莖看起來還算粗壯。\n",
		"竹籬" : "用竹竿紮成的籬笆﹐大部分已經倒塌腐朽﹐只剩下幾段還勉強立著。\n",
	]));
	set("objects", ([
		__DIR__"npc/herbalist" : 1,
	]));
	set("exits", ([
		"north" : __DIR__"east_path",
	]));

	setup();
	replace_program(ROOM);
}
