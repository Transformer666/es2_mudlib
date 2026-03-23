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
		"柳樹" : "一棵老柳樹，枝條低垂，在微風中輕輕搖曳。\n",
	]));
	set("exits", ([
		"north" : __DIR__"square",
		"east"  : __DIR__"temple",
	]));

	setup();
}

void init()
{
	::init();
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object player = this_player();

	if( !arg || (strsrch(arg, "井") < 0 && strsrch(arg, "well") < 0) ) {
		return notify_fail("你想搜尋什麼？\n");
	}

	if( player->query("quest/well_jade_done") ) {
		write("你仔細看了看井裡，除了清澈的井水之外什麼也沒有。\n");
		return 1;
	}

	if( !player->query_temp("pending/well_jade") ) {
		write("你探頭往井裡看了看，幽深的井水映著天光，似乎什麼也沒有。\n");
		return 1;
	}

	write("你俯身探頭往井裡仔細察看，隱約看到井壁的石縫中卡著一個\n"
		"綠瑩瑩的東西。你小心翼翼地用木桶和繩索撈了幾次，終於將\n"
		"一塊玉佩從井中撈了上來。\n");
	say(player->query("name") + "探身往井裡撈了半天，撈出了一塊玉佩。\n");

	object pendant = new(__DIR__"npc/obj/jade_pendant");
	if( !pendant->move(player) )
		pendant->move(environment(player));

	player->set_temp("pending/well_jade", 2);
	return 1;
}
