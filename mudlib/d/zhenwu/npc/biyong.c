// vim: syntax=lpc
// Quest: 兵符失蹤 (biyong_talisman)
// Flow: talk to biyong about talisman/lost -> he tells story
//       -> search watchtower -> find talisman in crack
//       -> give to biyong -> reward

#include <npc.h>

inherit F_SOLDIER;

void give_reward(object player);

void create()
{
	set_name("必勇", ({"biyong", "junshi"}));
	set_attr("str", 20);
	set_attr("dex", 22);
	set_attr("con", 20);
	set_attr("int", 26);
	set_attr("spi", 24);
	set_attr("wis", 28);
	set_race("woochan");
	set_class("commoner");
	set_level(50);

	set_skill("tactic", 120);
	set_skill("sword", 60);
	set_skill("dodge", 60);
	set_skill("parry", 50);

	set("age", 34);
	set("gender", "male");
	set("long",
		"必勇是振武軍營的軍師，官拜百戶。他雖然年僅三十四歲，卻精通\n"
		"戰術兵法，悟性極高，深受將士們的敬重。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"必勇凝視著案上的兵法圖，若有所思。\n",
		"必勇說道：兵者，詭道也。知己知彼，方能百戰不殆。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("longsword"))->wield();
	carry_money("coin", 200);
	set_temp("apply/vision_of_ghost", 1);
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/biyong_talisman_done") )
		return;

	if( this_player()->query_temp("pending/biyong_talisman") )
		do_chat("必勇焦急地說道﹕兵符找到了嗎﹖快去瞭望塔附近找找。\n");
}

int accept_object(object who, object ob)
{
	if( !ob->id("military_talisman") && !ob->id("military talisman")
	&&  !ob->id("talisman") )
		return 0;

	if( who->query("quest/biyong_talisman_done") ) {
		do_chat("必勇說道﹕兵符已經回來了﹐多謝。\n");
		return 0;
	}
	if( !who->query_temp("pending/biyong_talisman") ) return 0;

	do_chat(({
		"必勇接過兵符﹐仔細端詳了一番﹐長舒了一口氣。\n",
		"必勇如釋重負地說道﹕就是這塊﹗振武二字清晰可辨﹐沒有損壞。\n",
		"必勇鄭重地將兵符收入懷中﹐拱手道﹕多虧了你﹐若讓統領發現兵符丟了﹐我這腦袋怕是不保。\n",
		"必勇說道﹕我這裡有本兵法殘卷﹐是我年輕時手抄的﹐送你研讀吧。\n",
		(: give_reward, who :),
	}));
	return 1;
}

void give_reward(object player)
{
	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/biyong_talisman_done") ) return;

	player->set("quest/biyong_talisman_done", 1);
	player->delete_temp("pending/biyong_talisman");
	player->gain_score("quest", 80);
	player->carry_money("silver", 3);
	player->improve_skill("tactic", 1);
	tell_object(player, "( 必勇傳授了你一些兵法要領﹐你對戰術的理解有所提升 )\n");
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "兵符") >= 0 || strsrch(msg, "talisman") >= 0
	||  strsrch(msg, "丟") >= 0 || strsrch(msg, "失蹤") >= 0
	||  strsrch(msg, "煩惱") >= 0 || strsrch(msg, "幫忙") >= 0 ) {
		if( ob->query("quest/biyong_talisman_done") ) {
			do_chat("必勇拍了拍懷中﹐微笑道﹕兵符好好的﹐多虧了你。\n");
			return;
		}
		if( ob->query_temp("pending/biyong_talisman") ) {
			do_chat("必勇焦急道﹕就在瞭望塔上面﹐我巡查時一陣大風把兵符吹落了﹐可能卡在什麼縫隙裡。\n");
			return;
		}
		do_chat(({
			"必勇左右張望了一下﹐壓低聲音說道﹕你來得正好﹐我遇到了麻煩。\n",
			"必勇說道﹕前天夜裡我去瞭望塔巡查﹐山風大得很﹐一陣猛風把我腰間的兵符吹落了。\n",
			"必勇苦著臉說道﹕那是調動兵馬的信物﹐丟了可是死罪。\n",
			"必勇說道﹕我找了半天也沒找到﹐怕是被風吹到塔上哪個縫隙裡去了。\n",
			"必勇拱手道﹕你若願意幫忙﹐去瞭望塔仔細搜搜﹐我感激不盡。\n",
		}));
		ob->set_temp("pending/biyong_talisman", 1);
		return;
	}

	if( strsrch(msg, "兵法") >= 0 || strsrch(msg, "戰術") >= 0
	||  strsrch(msg, "打仗") >= 0 ) {
		do_chat(({
			"必勇說道﹕兵法之妙﹐在於因地制宜﹐因敵制勝。\n",
			"必勇說道﹕紙上談兵終覺淺﹐得到戰場上才能真正體會。\n",
		}));
		return;
	}
}
