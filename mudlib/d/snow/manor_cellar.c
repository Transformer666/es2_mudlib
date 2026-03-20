// vim: syntax=lpc
// Room: /d/snow/manor_cellar.c
// Quest: 謎6 破舊的老宅裡藏了什麼？

inherit ROOM;

void create()
{
	set("short", "大宅地窖");
	set("long", @LONG
沿著石階小心翼翼地走下來﹐你來到了大宅的地窖。這裡陰暗潮
濕﹐空氣中瀰漫著一股霉味。地窖的面積比想像中要大得多﹐四面的
石壁上掛著幾個生銹的鐵環﹐原本可能是用來掛燈的。地上散落著一
些破碎的酒罈和木箱殘骸﹐牆角堆放著幾捆已經腐爛的稻草。在地窖
的最深處﹐隱約可以看到牆壁上刻著一些奇怪的符號﹐似乎有人曾在
這裡留下過什麼訊息。
LONG
	);
	set("detail", ([
		"鐵環" : "生銹的鐵環釘在石壁上﹐看起來已經有很長一段時間沒有人使用了。\n",
		"酒罈" : "破碎的酒罈散落在地上﹐裡面早已空空如也﹐只剩下一股淡淡的酒味。\n",
		"符號" : "牆壁深處刻著一些奇怪的符號﹐仔細看去﹐似乎是某種暗號﹐其中一個符號像是一隻手指﹐指向牆壁的某個位置。也許可以試著 search 符號。\n",
		"木箱" : "幾個已經朽爛的木箱﹐裡面什麼也沒有﹐但箱蓋上似乎曾經烙過印記。\n",
	]));
	set("exits", ([
		"up" : __DIR__"manor_hall",
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
	object player, journal, money;

	if( !arg || (arg != "符號" && arg != "symbol" && arg != "symbols") )
		return 0;

	player = this_player();

	if( player->query("quest/manor_secret_done") ) {
		write("你仔細搜索了一遍﹐但已經沒有什麼新發現了。\n");
		return 1;
	}

	message_vision("$N沿著符號的指引﹐仔細搜索牆壁。\n", player);
	write(
		"你順著手指符號的方向摸索﹐發現那塊石壁的質感與周圍略有不同。\n"
		"用力一按﹐只聽「喀嚓」一聲﹐一塊石磚向內陷了進去﹐露出一個\n"
		"狹小的暗格。暗格裡放著一本破舊的手札和一個小布袋。\n");
	message("vision",
		player->name() + "在牆壁上發現了一個暗格﹗\n",
		environment(), player);

	journal = new(__DIR__"npc/obj/old_journal");
	if( journal->move(player) )
		journal->move(environment());

	money = new("/obj/money/silver");
	money->set_amount(3);
	if( money->move(player) )
		money->move(environment());

	write("你從暗格中取出了一本破舊手札和一小袋碎銀。\n");

	player->set("quest/manor_secret_done", 1);
	player->gain_score("quest", 60);

	return 1;
}
