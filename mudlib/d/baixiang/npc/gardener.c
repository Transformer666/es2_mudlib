// vim: syntax=lpc
// Quest: 菩提枯枝 (baixiang_bodhi_tree)
// Flow: say 菩提/tree -> learn about withering branch needing sacred dew
//       -> collect dew from bell tower -> give to gardener -> reward

#include <npc.h>

inherit F_VILLAGER;

void do_reward(object player);

void create()
{
	set_name("園頭僧", ({"gardener", "monk", "yuantou"}));
	set_race("human");
	set_class("commoner");
	set_level(10);
	set_skill("unarmed", 20);

	set("age", 50);
	set("gender", "male");
	set("attitude", "peaceful");
	set("long",
		"一位年邁的僧人﹐皮膚被日曬得黝黑﹐雙手佈滿老繭。他正\n"
		"彎著腰仔細地修剪菩提樹的枝葉﹐動作輕柔而嫻熟﹐彷彿對\n"
		"待自己的孩子一般。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"園頭僧輕輕撫摸著一棵菩提樹的樹幹﹐喃喃自語。\n",
		"園頭僧說道﹕「這棵菩提樹已有百年﹐見證了多少僧人的悟道。」\n",
		"園頭僧蹲下身﹐小心翼翼地拔去花叢中的雜草。\n",
		"園頭僧說道﹕「草木有情﹐用心照料﹐它們自會回報你。」\n",
	}));
	set("refuse_fight", 1);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 15);
}

void do_reward(object player)
{
	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/baixiang_bodhi_tree_done") ) return;

	player->set("quest/baixiang_bodhi_tree_done", 1);
	player->delete_temp("pending/baixiang_bodhi_tree");
	player->gain_score("quest", 80);

	tell_object(player, "( 你完成了任務：菩提枯枝 )\n");
}

int accept_object(object who, object ob)
{
	if( !ob->id("sacred_dew") && !ob->id("dew") ) return 0;

	if( who->query("quest/baixiang_bodhi_tree_done") ) {
		do_chat("園頭僧合十道：菩提樹已經康復了﹐多謝施主的善心。\n");
		return 0;
	}
	if( !who->query_temp("pending/baixiang_bodhi_tree") ) {
		do_chat("園頭僧疑惑地看著你手裡的東西。\n");
		return 0;
	}

	destruct(ob);
	do_chat(({
		"園頭僧雙手接過那瓶金剛露﹐神色激動。\n",
		"園頭僧小心翼翼地將露水灑在枯萎的樹枝上。\n",
		"枯枝表面漸漸泛起了一層淡淡的綠意﹐彷彿在緩慢地甦醒。\n",
		"園頭僧歡喜地合掌道：阿彌陀佛﹗菩提有靈﹐果然應了﹗\n",
		"園頭僧感激地說道：施主慈悲﹐這份功德﹐佛祖必定記在心裡。\n",
		(: do_reward, who :),
	}));
	return 1;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "菩提") >= 0 || strsrch(msg, "tree") >= 0
	||  strsrch(msg, "枯") >= 0 || strsrch(msg, "樹") >= 0 ) {
		if( ob->query("quest/baixiang_bodhi_tree_done") ) {
			do_chat("園頭僧微笑道：那枝枯枝已經長出新芽了﹐多虧施主幫忙。\n");
			return;
		}
		if( ob->query_temp("pending/baixiang_bodhi_tree") ) {
			do_chat("園頭僧說道：鐘樓那口古鐘的經文上﹐清晨時會凝結金剛露﹐施主不妨去看看。\n");
			return;
		}
		do_chat(({
			"園頭僧抬頭望著菩提樹﹐臉上浮現一絲憂色。\n",
			"園頭僧說道：施主有所不知﹐這棵百年菩提最近有一枝枝幹漸漸\n"
			"枯萎﹐老僧用盡了辦法也無法挽回。\n",
			"園頭僧說道：師父在世時曾說過﹐寺裡鐘樓那口古鐘上鑄刻的佛\n"
			"經經文﹐年深日久吸收了天地靈氣﹐清晨時會在經文上凝結一層\n"
			"『金剛露』。\n",
			"園頭僧說道：這金剛露能滋養萬物﹐若是施主願意幫忙﹐到鐘樓\n"
			"上收集一些金剛露帶回來﹐也許能救活這枝枯枝。\n",
		}));
		ob->set_temp("pending/baixiang_bodhi_tree", 1);
		return;
	}
}
