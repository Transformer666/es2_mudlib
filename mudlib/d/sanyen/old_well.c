// Room: /d/sanyen/old_well.c
// Quest: 乞丐的往事 — 在枯井中搜尋玉佩

inherit ROOM;

int do_search(string arg);

void create()
{
	set("short", "枯井旁");
	set("long", @LONG
村子邊緣一口早已乾涸的老井﹐井沿的石頭被歲月侵蝕得斑駁不堪。
井邊倒著一只破木桶﹐繩索已經腐朽斷裂。井口黑洞洞的﹐往下望去
深不見底﹐偶爾有陣陰冷的風從井底吹上來﹐令人不寒而慄。附近的野
草長得格外茂盛﹐彷彿在掩蓋著什麼不為人知的秘密。
LONG
	);
	set("detail", ([
		"井" : "往井底望去﹐似乎隱約能看到一些東西的反光。\n",
		"枯井" : "往井底望去﹐似乎隱約能看到一些東西的反光。\n",
		"野草" : "雜草叢生﹐長得比人膝蓋還高。\n",
	]));
	set("exits", ([
		"north" : __DIR__"east_lane",
		"west" : __DIR__"back_alley",
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
	object player, pendant;

	if( !arg || (strsrch(arg, "井") < 0 && strsrch(arg, "well") < 0) )
		return notify_fail("你要搜尋什麼﹖\n");

	player = this_player();

	if( player->query("quest/sanyen_beggar_jade_done") ) {
		write("你仔細搜索了井底﹐除了淤泥和碎石﹐什麼也沒發現。\n");
		return 1;
	}

	if( player->query_temp("pending/sanyen_beggar_jade") != 2 ) {
		write("你往井底望了望﹐黑漆漆的﹐什麼也看不清。\n");
		return 1;
	}

	if( present("jade pendant", player) ) {
		write("你已經找到了玉佩﹐應該拿去還給那個乞丐。\n");
		return 1;
	}

	message_vision("$N小心翼翼地攀著井壁往下爬﹐摸索了好一會兒。\n",
		player);
	write("你在井底的淤泥中摸索著﹐忽然手指碰到一樣硬硬的東西 ...\n");
	write("你把它拿起來一看﹐是一塊沾滿泥垢的玉佩﹗\n");

	pendant = new(__DIR__"npc/obj/jade_pendant");
	if( !pendant->move(player) ) {
		pendant->move(environment(player));
		write("你的負重太多﹐玉佩掉在了地上。\n");
	}

	message_vision("$N從井底爬了上來﹐手裡多了一樣東西。\n", player);
	return 1;
}
