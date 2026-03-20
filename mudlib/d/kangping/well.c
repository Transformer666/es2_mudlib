// Room: /d/kangping/well.c

inherit ROOM;

void create()
{
	set("short", "古井旁");
	set("long", @LONG
村子南邊有一口古老的石井，井欄上磨出了深深的繩溝。井邊放著
一隻木桶和一根粗麻繩。井水清冽甘甜，是全村人飲水的來源。井旁
長著一棵老柳樹，垂下的柳枝幾乎觸到了井口。
LONG
	);
	set("objects", ([
		__DIR__"npc/old_woman" : 1,
	]));
	set("detail", ([
		"古井" : "井口不大，探頭看去，可以看到幽深的井水反射著天空的光芒。\n",
	]));
	set("exits", ([
		"north" : __DIR__"square",
	]));

	setup();
	replace_program(ROOM);
}
