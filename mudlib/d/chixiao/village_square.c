// Room: /d/chixiao/village_square.c
// Quest: 地靈封印 (diling_summon)
// Flow: pour spirit_wine into well -> use talisman -> diling emerges
//       -> defeat diling -> quest complete + rewards

inherit ROOM;

void summon_diling(object player);

void create()
{
	set("short", "赤魈村廣場");
	set("long", @LONG
這裡是赤魈村的中心廣場﹐一片不大的空地被幾間破舊的房屋圍
繞著。廣場中央有一口古老的石井﹐井台上長滿了青苔。幾個村民
蹲在牆根下曬太陽﹐面色憔悴﹐看起來生活頗為艱辛。北邊傳來一
陣若有若無的水聲﹐似乎有什麼水源在那個方向。
LONG
	);
	set("detail", ([
		"石井" : "一口用青石砌成的古井﹐井沿上佈滿了裂紋和青苔﹐"
			"看起來已經枯了。仔細一看﹐井壁上刻著一些模糊的文字﹐"
			"似乎是某種封印咒語。\n",
		"文字" : "井壁上的文字已經模糊不清﹐隱約可以辨認出﹕"
			"「以靈酒祭地﹐以符紙破封﹐地靈方出。」\n",
		"房屋" : "幾間用土坯搭建的矮房﹐屋頂鋪著發黃的茅草﹐牆壁上有不少裂縫。\n",
	]));
	set("exits", ([
		"west"  : __DIR__"entrance",
		"north" : __DIR__"wishing_pool",
		"south" : __DIR__"inn",
		"east"  : __DIR__"street",
	]));

	setup();
}

void init()
{
	add_action("do_pour", "pour");
	add_action("do_use_talisman", "use");
}

int do_pour(string arg)
{
	object player, wine;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "酒") < 0 && strsrch(arg, "wine") < 0
	&&  strsrch(arg, "spirit_wine") < 0) )
		return notify_fail("你想倒什麼？\n");

	if( player->query("quest/diling_summon_done") ) {
		write("地靈已被你擊敗﹐古井恢復了平靜。\n");
		return 1;
	}

	if( player->query_temp("pending/diling_summon_fighting") ) {
		write("地靈正在肆虐﹐你還是先對付他吧！\n");
		return 1;
	}

	if( player->query_temp("pending/diling_wine_poured") ) {
		write("靈酒已經倒入井中了﹐現在需要用符紙破除封印。\n");
		return 1;
	}

	wine = present("spirit_wine", player);
	if( !wine ) wine = present("wine", player);

	if( !wine || base_name(wine) != __DIR__"npc/obj/spirit_wine" ) {
		write("你身上沒有靈酒。\n");
		return 1;
	}

	message_vision(
		"$N將靈酒緩緩倒入古井之中﹐酒液沿著井壁流下﹐\n"
		"井壁上的古老文字忽然閃爍起微弱的紅光。\n",
		player);

	destruct(wine);
	player->set_temp("pending/diling_wine_poured", 1);

	message("vision",
		"一股低沉的轟鳴聲從井底傳來﹐大地微微顫抖。\n"
		"似乎還需要什麼東西來破除封印 ...\n",
		environment(player));

	return 1;
}

int do_use_talisman(string arg)
{
	object player, talisman;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "符") < 0 && strsrch(arg, "talisman") < 0
	&&  strsrch(arg, "charm") < 0) )
		return 0;

	if( player->query("quest/diling_summon_done") ) {
		write("地靈已被你擊敗﹐不需要再使用符紙了。\n");
		return 1;
	}

	if( player->query_temp("pending/diling_summon_fighting") ) {
		write("地靈正在肆虐﹐你還是先對付他吧！\n");
		return 1;
	}

	if( !player->query_temp("pending/diling_wine_poured") ) {
		write("你將符紙貼在井台上﹐但什麼也沒有發生。也許還缺少什麼步驟。\n");
		return 1;
	}

	talisman = present("talisman", player);
	if( !talisman ) talisman = present("charm", player);

	if( !talisman || base_name(talisman) != __DIR__"npc/obj/talisman" ) {
		write("你身上沒有符紙。\n");
		return 1;
	}

	message_vision(
		"$N將符紙貼在井台上﹐口中默念著井壁上的古老咒語。\n"
		"符紙忽然燃燒起來﹐化為一道金光射入井中！\n",
		player);

	destruct(talisman);

	message("vision",
		"剎那間﹐整座古井劇烈震動﹐井台上的青石龜裂崩塌﹗\n"
		"一道褐黃色的光柱從井底衝天而起﹐大地為之震顫﹐\n"
		"封印了不知多少年的力量終於掙脫了束縛！\n",
		environment(player));

	player->delete_temp("pending/diling_wine_poured");
	player->set_temp("pending/diling_summon_fighting", 1);
	call_out("summon_diling", 3, player);
	return 1;
}

void summon_diling(object player)
{
	object diling, env;

	if( !player ) return;
	env = environment(player);
	if( !env || base_name(env) != __DIR__"village_square" ) return;

	diling = new(__DIR__"npc/diling");
	if( !diling ) return;
	diling->move(env);

	message("vision",
		"褐黃色光柱凝聚成一個高大威猛的人形﹐地靈從井中緩緩升起。\n"
		"他的身軀如同岩石一般堅硬﹐腳下的大地隨著他的每一步而顫抖。\n"
		"地靈沉聲道﹕誰破了本靈的封印﹐膽子不小！\n",
		env);
}
