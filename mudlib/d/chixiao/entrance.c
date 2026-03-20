// Room: /d/chixiao/entrance.c

inherit ROOM;

void create()
{
	set("short", "赤魈村入口");
	set("long", @LONG
穿過荒野小徑﹐眼前出現了一個不大的村落。村口立著一塊風化
斑駁的石碑﹐上面隱約刻著「赤魈村」三個字。村裡的房屋大多是
用土坯和茅草搭建的﹐顯得十分簡陋。一條泥土小路從村口通往村
中心的廣場﹐路旁種著幾棵歪歪斜斜的老槐樹。
LONG
	);
	set("detail", ([
		"石碑" : "一塊風化嚴重的石碑﹐上面的字跡已經很模糊了﹐但仔細辨認還是能看出「赤魈村」三個字。\n",
		"老槐樹" : "幾棵枝幹彎曲的老槐樹﹐葉子稀稀落落的﹐看起來已經有不少年頭了。\n",
	]));
	set("outdoors", "wild");
	set("exits", ([
		"west"  : "/d/road/wild_path2",
		"east"  : __DIR__"village_square",
	]));

	setup();
	replace_program(ROOM);
}
