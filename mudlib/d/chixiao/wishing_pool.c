// Room: /d/chixiao/wishing_pool.c
// Quest: 天靈召喚 (tianling_summon)
// Flow: throw 3 different elemental weapons into the pool -> tianling appears
//       -> defeat tianling -> quest complete + rewards

inherit ROOM;

void summon_tianling(object player);

void create()
{
	set("short", "許願池");
	set("long", @LONG
一座古老的石池出現在你的面前﹐池水清澈見底﹐微微泛著碧綠
色的光芒﹐與這個破敗的村莊格格不入。池邊的石欄上雕刻著奇異
的花紋﹐隱隱散發著一股神秘的力量。池底可以看到一些閃閃發光
的銅錢﹐大概是過往的旅人投下許願的。據傳說﹐將特定的物品投
入池中﹐會召喚出強大的靈體。
LONG
	);
	set("detail", ([
		"石池" : "池子不大﹐直徑約莫一丈﹐但池水深不見底﹐碧綠色的水面偶爾泛起一圈圈漣漪﹐彷彿水底有什麼東西在活動。\n",
		"花紋" : "石欄上雕刻的花紋十分古老﹐看起來像是某種遠古的符文﹐你完全看不懂。\n",
		"銅錢" : "池底散落著不少銅錢﹐在碧綠的池水映照下閃閃發亮。\n",
		"符文" : "仔細辨認﹐隱約看出「火」「雷」「風」「雨」四個古字﹐似乎暗示著什麼獻祭的方式。\n",
	]));
	set("exits", ([
		"south" : __DIR__"village_square",
	]));

	setup();
}

void init()
{
	add_action("do_throw", "throw");
	add_action("do_throw", "toss");
}

int do_throw(string arg)
{
	object player, ob;
	string *valid_weapons, *offered;
	string weapon_id;
	int count;

	player = this_player();
	if( !player ) return 0;

	if( !arg || (strsrch(arg, "pool") < 0 && strsrch(arg, "池") < 0
	&&  strsrch(arg, "水") < 0) ) {
		// Check if the argument contains a weapon name to throw into pool
		if( !arg ) return notify_fail("你想往池裡丟什麼？\n");
	}

	if( player->query("quest/tianling_summon_done") ) {
		write("天靈已被你擊敗﹐許願池恢復了平靜。\n");
		return 1;
	}

	if( player->query_temp("pending/tianling_summon_fighting") ) {
		write("天靈正在肆虐﹐你還是先對付他吧！\n");
		return 1;
	}

	// Check for elemental weapons
	valid_weapons = ({ "fire_weapon", "thunder_weapon", "wind_weapon", "rain_weapon" });

	foreach( string wid in valid_weapons ) {
		ob = present(wid, player);
		if( ob ) {
			weapon_id = wid;
			break;
		}
	}

	if( !ob ) {
		write("你身上沒有適合投入池中的神器。\n");
		return 1;
	}

	// Check if already offered this type
	if( !player->query_temp("pending/tianling_offerings") )
		player->set_temp("pending/tianling_offerings", ({}));

	offered = player->query_temp("pending/tianling_offerings");

	if( member_array(weapon_id, offered) >= 0 ) {
		write("你已經獻上這類神器了﹐試試其他的吧。\n");
		return 1;
	}

	// Unwield if wielded
	if( ob->query_temp("wielded") )
		ob->unwield();

	message_vision(
		"$N將" + ob->name() + "高高舉起﹐然後用力投入許願池中！\n",
		player);

	destruct(ob);

	offered += ({ weapon_id });
	player->set_temp("pending/tianling_offerings", offered);
	count = sizeof(offered);

	if( count < 3 ) {
		message("vision",
			"池水泛起一陣漣漪﹐" + ob->name() + "沉入水底﹐發出一道"
			"耀眼的光芒。池水的碧光比先前更加強烈了。\n"
			"（已獻上 " + count + "/3 件神器）\n",
			environment(player));
		return 1;
	}

	// 3 weapons offered - summon tianling
	message("vision",
		"第三件神器沉入池中的瞬間﹐整座許願池劇烈震動起來！\n"
		"碧綠的池水翻湧沸騰﹐一道耀目的金色光柱從池底沖天而起﹐\n"
		"照亮了整個赤魈村的天空！\n",
		environment(player));

	player->set_temp("pending/tianling_summon_fighting", 1);
	call_out("summon_tianling", 3, player);
	return 1;
}

void summon_tianling(object player)
{
	object tianling, env;

	if( !player ) return;
	env = environment(player);
	if( !env || base_name(env) != __DIR__"wishing_pool" ) return;

	tianling = new(__DIR__"npc/tianling");
	if( !tianling ) return;
	tianling->move(env);

	message("vision",
		"金色光柱凝聚成一道人形﹐一個半透明的身影緩緩浮現在池面上方。\n"
		"天靈睜開了如同燃燒星辰般的雙眼﹐冷冷地掃視四周﹐\n"
		"沉聲道﹕凡人竟敢以四元素之器驚擾本靈﹐找死！\n",
		env);
}
