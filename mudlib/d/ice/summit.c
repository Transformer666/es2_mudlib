// vim: syntax=lpc
// Quest: 冰域守衛挑戰 (ice_guardian_challenge)
// Flow: meditate at summit -> guardian appears -> kill guardian -> frost_crystal drops

inherit ROOM;

void spawn_guardian(object player);

void create()
{
	set("short", "冰峰");
	set("long", @LONG
這是冰域的最高處，站在冰峰之上，四面八方都是一片銀白色的世界。
寒風凜冽，呼吸間都能看到白色的霧氣。遠處的山巒在雪霧中若隱若
現，腳下的冰層散發著藍寶石般的光澤。這裡似乎隱藏著某種古老的
力量。
LONG
	);
	set("outdoors", "wilderness");
	set("detail", ([
		"冰層" : "腳下的冰層散發著幽藍色的光澤﹐隱隱約約透出一股古老的氣息﹐"
			"似乎在這裡靜心冥想﹐也許能感應到什麼。\n",
		"光澤" : "冰層透出的藍光似乎帶有某種靈力﹐令人心神不寧。\n",
	]));
	set("exits", ([
		"west" : __DIR__"glacier",
	]));

	setup();
}

void init()
{
	add_action("do_meditate", "meditate");
	add_action("do_meditate", "冥想");
}

int do_meditate(string arg)
{
	object player;

	player = this_player();
	if( !player ) return 0;

	if( player->query("quest/ice_guardian_challenge_done") ) {
		write("你已經戰勝了冰域守衛﹐這裡的古老力量已經平息。\n");
		return 1;
	}

	if( player->query_temp("pending/ice_guardian") ) {
		write("冰域守衛已經出現了﹐準備戰鬥吧！\n");
		return 1;
	}

	if( present("ice_guardian", environment(player)) ) {
		write("冰域守衛已經在這裡了！\n");
		return 1;
	}

	message_vision(
		"$N盤膝坐下﹐閉目凝神﹐試圖感應冰峰中蘊藏的古老力量。\n",
		player);

	player->set_temp("pending/ice_guardian", 1);

	message("vision",
		"冰層中傳來一聲低沉的轟鳴﹐腳下的藍光驟然亮起。\n",
		environment(player));

	call_out("spawn_guardian", 3, player);
	return 1;
}

void spawn_guardian(object player)
{
	object guardian, env;

	if( !player ) return;
	env = environment(player);
	if( !env || base_name(env) != __DIR__"summit" ) {
		if( player ) player->delete_temp("pending/ice_guardian");
		return;
	}

	guardian = new(__DIR__"npc/ice_guardian");
	if( !guardian ) {
		player->delete_temp("pending/ice_guardian");
		return;
	}
	guardian->move(env);

	message("vision",
		"冰層轟然碎裂﹐一個渾身覆蓋著淡藍色冰晶的守衛從裂縫中緩緩升起﹐\n"
		"數百年的寒氣瞬間瀰漫四周﹐冰域守衛睜開雙眼﹐目光如寒冰般冷冽！\n",
		env);
}
