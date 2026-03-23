// Room: /d/oldpine/cave_inner.c
// Quest: bandit_hostage_rescue
// Flow: defeat bandit_chief -> untie captive -> captive thanks player -> reward

inherit ROOM;

void give_rescue_reward(object player);

void create()
{
	set("short", "山洞深處");
	set("long", @LONG
山洞深處比想像中寬敞﹐洞頂掛著幾根石鐘乳﹐滴答滴答地往下
滴水。洞壁上有被煙燻黑的痕跡﹐地上還有一堆早已熄滅的篝火殘骸。
角落裡堆放著一些木箱和麻袋﹐看起來像是土匪藏匿贓物的地方。在
木箱旁邊﹐一個被五花大綁的行商蜷縮在角落裡﹐神情十分痛苦。
LONG
	);
	set("objects", ([
		__DIR__"npc/bandit_chief" : 1,
		__DIR__"npc/captive" : 1,
	]));
	set("exits", ([
		"south" : __DIR__"cave",
	]));

	setup();
}

void init()
{
	add_action("do_untie", "untie");
	add_action("do_untie", "rescue");
}

int do_untie(string arg)
{
	object player, captive, chief;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "行商") < 0 && strsrch(arg, "captive") < 0
	&&  strsrch(arg, "merchant") < 0 && strsrch(arg, "trader") < 0) )
		return notify_fail("你想解開誰的繩子？\n");

	captive = present("captive", environment(player));
	if( !captive )
		return notify_fail("這裡沒有被綁起來的人。\n");

	if( player->query("quest/bandit_hostage_rescue_done") ) {
		write("你已經救過這位行商了。\n");
		return 1;
	}

	if( captive->query_temp("untied") ) {
		write("行商已經被你鬆了綁﹐不需要再解了。\n");
		return 1;
	}

	// Check if bandit chief is still alive
	chief = present("bandit_chief", environment(player));
	if( chief ) {
		write("匪首還在這裡虎視眈眈﹐你不敢輕舉妄動。\n");
		return 1;
	}

	message_vision("$N蹲下來﹐小心翼翼地替行商解開繩索﹐扯掉嘴裡塞著的破布。\n",
		player);
	captive->set_temp("untied", 1);
	captive->set("long",
		"一個中年行商﹐臉上滿是烏青和血跡﹐但已經被鬆了綁。他揉著\n"
		"手腕上勒出的紅痕﹐感激地看著你。\n");

	captive->do_chat(({
		"行商大口喘著氣﹐說道﹕多 ... 多謝恩人救命之恩﹗\n",
		"行商說道﹕我叫周福﹐是從康平來的行商﹐在這林子裡被這幫土匪截住了。\n",
		"行商說道﹕他們搶走了我的貨物﹐把我綁在這裡好幾天了 ...\n",
		"行商說道﹕恩人﹐這些是我藏在鞋底的盤纏﹐請務必收下。\n",
		(: give_rescue_reward, player :),
	}));

	return 1;
}

void give_rescue_reward(object player)
{
	object captive, money;

	if( !player || environment(player) != this_object() ) return;
	if( player->query("quest/bandit_hostage_rescue_done") ) return;

	captive = present("captive", this_object());

	player->set("quest/bandit_hostage_rescue_done", 1);
	player->gain_score("quest", 80);

	money = new("/obj/money/silver");
	money->set_amount(5);
	if( !money->move(player) )
		money->move(this_object());

	if( captive )
		captive->do_chat(({
			"行商將幾錠碎銀塞進了" + player->name() + "手裡。\n",
			"行商說道﹕大恩不言謝﹐日後若到康平﹐周福定當報答。\n",
			"行商活動了一下筋骨﹐一瘸一拐地往洞口走去。\n",
		}));
}
