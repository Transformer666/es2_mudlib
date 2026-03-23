// vim: syntax=lpc
// Quest: 遺失的劍譜 (fengshan_lost_manual)
// Flow: say 劍譜/scroll -> learn about lost scroll on cliff -> search cliff
//       -> find scroll -> give to librarian -> reward

#include <npc.h>

inherit F_SCHOLAR;

void do_reward(object player);

void create()
{
	set_name("藏書長老", ({"librarian", "elder", "zhang_lao"}));
	set_attr("int", 20);
	set_attr("wis", 22);
	set_race("human");
	set_class("commoner");
	set_level(25);

	set_skill("sword", 50);
	set_skill("dodge", 40);
	set_skill("parry", 35);

	set("age", 60);
	set("gender", "male");
	set("long",
		"一位白髮蒼蒼的長老，目光銳利而深邃，負責管理封山派的劍譜\n"
		"與武學典籍。雖已退隱不再下山比武，但他對劍法的鑽研極深，門\n"
		"中弟子遇到劍術疑難時常來此請教。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"藏書長老翻開一卷泛黃的竹簡，仔細端詳著上面的劍招圖解。\n",
		"藏書長老輕聲嘆道：前輩的劍意，非一朝一夕能領悟啊。\n",
		"藏書長老提筆在書頁空白處批註了幾行小字。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 50);
}

int accept_fight(object ob)
{
	do_chat("藏書長老冷冷道：藏書閣內不得動武，出去。\n");
	return 0;
}

void do_reward(object player)
{
	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/fengshan_lost_manual_done") ) return;

	player->set("quest/fengshan_lost_manual_done", 1);
	player->delete_temp("pending/fengshan_lost_manual");
	player->gain_score("quest", 80);

	carry_money("silver", 2);
	message_vision("藏書長老從袖中取出二兩碎銀遞給$N。\n", player);
	command("give 2 silver to " + player->query("id"));

	tell_object(player, "( 你完成了任務：遺失的劍譜 )\n");
}

int accept_object(object who, object ob)
{
	if( !ob->id("sword_scroll") && !ob->id("scroll") ) return 0;

	if( who->query("quest/fengshan_lost_manual_done") ) {
		do_chat("藏書長老微笑道：劍譜已經找回來了﹐多謝你的幫忙。\n");
		return 0;
	}
	if( !who->query_temp("pending/fengshan_lost_manual") ) {
		do_chat("藏書長老看了看﹐說道：這不是我們丟失的劍譜。\n");
		return 0;
	}

	destruct(ob);
	do_chat(({
		"藏書長老接過竹簡﹐雙手微微顫抖。\n",
		"藏書長老仔細翻閱著竹簡﹐連連點頭。\n",
		"藏書長老說道：沒想到真的找回來了﹗雖然有些破損﹐但劍招圖解\n"
		"還算清晰﹐太好了﹗\n",
		"藏書長老感激地說道：多虧了你﹐這卷劍譜是二代祖師親筆所著﹐\n"
		"失落多年﹐今日終於物歸原處。\n",
		(: do_reward, who :),
	}));
	return 1;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "劍譜") >= 0 || strsrch(msg, "劍法") >= 0
	||  strsrch(msg, "scroll") >= 0 || strsrch(msg, "典籍") >= 0
	||  strsrch(msg, "竹簡") >= 0 ) {
		if( ob->query("quest/fengshan_lost_manual_done") ) {
			do_chat("藏書長老說道：多虧你找回了那卷二代祖師的劍譜﹐如今已經妥善保管了。\n");
			return;
		}
		if( ob->query_temp("pending/fengshan_lost_manual") ) {
			do_chat("藏書長老說道：那卷劍譜應該還在斷崖附近﹐崖壁上也許能找到。\n");
			return;
		}
		do_chat(({
			"藏書長老嘆了口氣﹐說道：說起劍譜﹐倒有一件憾事。\n",
			"藏書長老說道：二代祖師親手所著的『封山劍法殘譜』﹐記載著\n"
			"幾招失傳已久的劍招﹐一直是本閣的鎮閣之寶。\n",
			"藏書長老說道：數年前一名弟子將劍譜帶到斷崖練功﹐不慎被一\n"
			"陣山風捲走﹐從此下落不明。\n",
			"藏書長老說道：也許那卷劍譜還卡在崖壁的石縫裡﹐若是有人能\n"
			"在斷崖找到它﹐老夫感激不盡。\n",
		}));
		ob->set_temp("pending/fengshan_lost_manual", 1);
		return;
	}
}
