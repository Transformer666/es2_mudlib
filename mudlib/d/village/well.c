// vim: syntax=lpc
// Quest support: 老乞婆的秘密 - search well for jade pendant

inherit ROOM;

void create()
{
	set("short", "水井旁");
	set("long", @LONG
村子東南角有一口古老的水井，井沿用青石砌成，上面架著一個轆轤。井水清涼甘甜，是村民們日常飲水的來源。井旁放著幾個木桶和一條長繩，看來經常有人來此打水。
LONG
	);
	set("outdoors", "wilderness");
	set("exits", ([
		"west" : __DIR__"farm",
	]));
	set("objects", ([
		__DIR__"npc/merchant" : 1,
	]));
	set("detail", ([
		"水井" : "一口古老的水井﹐井沿上的青石被磨得光滑如鏡。往下望去﹐"
			"隱約可以看見井水的波光。也許用井邊的木桶和繩子可以撈撈看。\n",
		"木桶" : "幾個打水用的木桶﹐旁邊放著一條粗麻繩。\n",
	]));

	setup();
}

void init()
{
	add_action("do_search_well", "search");
	add_action("do_search_well", "撈");
}

int do_search_well(string arg)
{
	object player, pendant;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "井") < 0 && strsrch(arg, "well") < 0
	&&  strsrch(arg, "水") < 0 && strsrch(arg, "bucket") < 0) )
		return notify_fail("你想搜索什麼﹖\n");

	if( player->query("quest/beggar_secret_done") ) {
		write("你往井裡看了看﹐清澈的井水中什麼也沒有。\n");
		return 1;
	}

	if( !player->query_temp("pending/beggar_secret") ) {
		write("你用木桶在井裡撈了撈﹐除了冰涼的井水什麼也沒撈到。\n");
		return 1;
	}

	if( player->query_temp("pending/beggar_secret") == 2 ) {
		write("你已經撈到了翠玉墜子﹐快拿去給老乞婆看看吧。\n");
		return 1;
	}

	message_vision("$N拿起木桶﹐繫上繩子﹐慢慢地放入井中。\n", player);
	write("你仔細地在井底來回撈了幾次﹐忽然感覺木桶碰到了什麼硬物。\n");
	write("你小心翼翼地把木桶提上來﹐在桶底發現了一枚翠玉墜子﹗\n");

	pendant = new(__DIR__"npc/obj/jade_pendant");
	if( pendant->move(player) )
		pendant->move(environment(player));

	player->set_temp("pending/beggar_secret", 2);
	return 1;
}
