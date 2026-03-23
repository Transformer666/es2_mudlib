// Room: /d/oldpine/camp.c
// Quest: bandit_camp_search - 匪營搜贓
// Requires: bandit_hostage_rescue_done
// Flow: search tent/camp -> find hidden chest -> get ledger + silver

inherit ROOM;

void give_loot(object player);

void create()
{
	set("short", "土匪營地");
	set("long", @LONG
松林中一塊被清理出來的空地﹐搭著幾個簡陋的帳篷﹐中間是一
堆還冒著煙的篝火。地上丟著吃剩的骨頭和空酒罈﹐一面破舊的旗幟
歪歪斜斜地插在地上﹐上面繡著一個「松」字。這裡便是老松寨土匪們
的營地了。
LONG
	);
	set("objects", ([
		__DIR__"npc/bandit" : 2,
	]));
	set("detail", ([
		"帳篷" : "幾個用樹枝和獸皮搭成的簡陋帳篷﹐裡面亂七八糟地堆著雜物。\n",
		"篝火" : "一堆還冒著煙的篝火﹐旁邊放著幾個烤得焦黑的肉串。\n",
		"旗幟" : "一面破舊的旗幟﹐上面繡著一個「松」字﹐邊緣已經磨損了。\n",
	]));
	set("exits", ([
		"east" : __DIR__"road2",
	]));

	setup();
}

void init()
{
	add_action("do_search", "search");
	add_action("do_search", "搜");
	add_action("do_search", "翻");
}

int do_search(string arg)
{
	object player, bandit;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "帳篷") < 0 && strsrch(arg, "tent") < 0
	&&  strsrch(arg, "camp") < 0 && strsrch(arg, "營地") < 0
	&&  strsrch(arg, "雜物") < 0) )
		return notify_fail("你想搜索什麼？\n");

	if( player->query("quest/bandit_camp_search_done") ) {
		write("你已經搜過這裡了﹐沒有更多有價值的東西了。\n");
		return 1;
	}

	// Must have completed the rescue quest first
	if( !player->query("quest/bandit_hostage_rescue_done") ) {
		write("土匪們虎視眈眈地看著你﹐你可不敢在這裡亂翻。\n");
		return 1;
	}

	// Check if bandits are still alive in this room
	bandit = present("bandit", environment(player));
	if( bandit ) {
		write("營地裡還有土匪在﹐你得先把他們解決掉才能安心搜索。\n");
		return 1;
	}

	if( player->query_temp("pending/bandit_camp_search") ) {
		write("你已經找到了暗格﹐看看裡面有什麼吧。\n");
		call_out("give_loot", 1, player);
		return 1;
	}

	message_vision(
		"$N開始翻找帳篷裡的雜物﹐掀開了幾塊破布和獸皮。\n", player);

	player->set_temp("pending/bandit_camp_search", 1);

	write(
		"你在最大的帳篷角落裡發現了一塊鬆動的地板﹐掀開來下面是一\n"
		"個用木板蓋住的暗格。\n");

	call_out("give_loot", 2, player);
	return 1;
}

void give_loot(object player)
{
	object ledger, money;

	if( !player || environment(player) != this_object() ) return;
	if( player->query("quest/bandit_camp_search_done") ) return;

	message("vision",
		"暗格裡面放著幾袋銀兩和一本帳冊﹐看起來是土匪從行商那裡\n"
		"搶來的贓物。\n",
		this_object());

	ledger = new(__DIR__"npc/obj/trade_ledger");
	if( ledger ) {
		if( ledger->move(player) )
			ledger->move(this_object());
	}

	money = new("/obj/money/silver");
	if( money ) {
		money->set_amount(8);
		if( money->move(player) )
			money->move(this_object());
	}

	player->set("quest/bandit_camp_search_done", 1);
	player->gain_score("quest", 60);
	player->delete_temp("pending/bandit_camp_search");

	write(
		"你取出帳冊和銀兩。帳冊封面寫著「周記商行」——這想必是那位\n"
		"被綁架的行商周福的東西。\n");
}
