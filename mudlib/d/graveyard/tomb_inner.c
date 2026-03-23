// Room: /d/graveyard/tomb_inner.c
// Quest: gravekeeper_pendant (search coffin to find jade pendant)

inherit ROOM;

void create()
{
	set("short", "古墓內部");
	set("long", @LONG
古墓內部比想像中寬敞﹐四壁用青石砌成﹐石縫間滲出冰冷的水珠。
墓室中央放著一具石棺﹐棺蓋上刻著精美的花紋﹐不知是哪朝哪代的人
物長眠於此。牆壁上的壁畫已經剝落得差不多了﹐隱約可以看出是一些
人物和車馬的圖案。地上散落著幾件腐朽的陪葬品。
LONG
	);
	set("detail", ([
		"石棺" : "石棺蓋上刻著蓮花紋飾﹐棺蓋已經裂開一條縫﹐"
			"也許可以試著搜查(search coffin)一下。\n",
		"壁畫" : "壁畫大多已經剝落﹐依稀可見一名手持長劍的武者圖像。\n",
		"陪葬品" : "幾件腐朽得幾乎辨認不出的物品﹐大概是些器皿和衣物的殘骸。\n",
	]));
	set("objects", ([
		__DIR__"npc/zombie" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"tomb",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
}

int do_search(string arg)
{
	object player, pendant, zombie;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "石棺") < 0 && strsrch(arg, "coffin") < 0
	&&  strsrch(arg, "棺") < 0) )
		return notify_fail("你想搜查什麼？\n");

	// Check if zombie is still alive
	zombie = present("zombie", environment(player));
	if( zombie ) {
		write("殭屍還在一旁虎視眈眈﹐你不敢靠近石棺。\n");
		return 1;
	}

	if( player->query_temp("pending/gravekeeper_pendant_found") ) {
		write("你已經搜過石棺了﹐裡面沒有其他值得注意的東西了。\n");
		return 1;
	}

	if( !player->query_temp("pending/gravekeeper_pendant") ) {
		message_vision(
			"$N費力地推開石棺蓋﹐往裡面看了看。\n",
			player);
		write("棺中只剩一具白骨和幾片腐爛的衣物碎片﹐沒什麼有用的東西。\n");
		return 1;
	}

	message_vision(
		"$N費力地推開石棺蓋﹐仔細地在棺中翻找。\n",
		player);

	pendant = new(__DIR__"npc/obj/jade_pendant");
	if( !pendant ) {
		write("你什麼也沒找到。\n");
		return 1;
	}

	write("你在白骨的頸部找到了一塊蓮花形狀的玉佩﹐背面果然刻著「清心」二字﹗\n");
	message("vision",
		player->name() + "從石棺中取出了一塊玉佩。\n",
		environment(player), player);

	if( !pendant->move(player) )
		pendant->move(environment(player));

	player->set_temp("pending/gravekeeper_pendant_found", 1);
	return 1;
}
