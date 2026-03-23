// vim: syntax=lpc
// Quest support: beggar_clue (temple monk identifies the mysterious token)

#include <npc.h>

inherit F_VILLAGER;

void do_reward(object player);

void create()
{
	set_name("廟祝", ({"monk", "miaozhu"}));
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 55);
	set("gender", "male");
	set("long",
		"一位年邁的僧人，身披素淨的袈裟，正細心地照料著殿中的香\n"
		"火供品。他以慈祥的微笑迎接每一位來訪者，雙手合十以示問候。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"廟祝雙手合十：阿彌陀佛，施主有禮了。\n",
		"廟祝輕聲說道：心誠則靈，佛祖自會保佑善心之人。\n",
		"廟祝緩緩添上幾柱清香，口中默默誦念經文。\n",
	}));

	set_attr("wis", 16);
	set_attr("spi", 15);
	set_skill("unarmed", 20);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 30);
	set_temp("apply/vision_of_ghost", 1);
}

int accept_fight(object ob)
{
	do_chat("廟祝搖頭道：阿彌陀佛，佛門清淨之地，不可妄動干戈。\n");
	return 0;
}

void do_reward(object player)
{
	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/beggar_clue_done") ) return;

	player->set("quest/beggar_clue_done", 1);
	player->delete_temp("pending/beggar_clue");
	player->gain_score("quest", 80);

	player->carry_money("silver", 2);
	tell_object(player, "( 你獲得了二兩銀子 )\n");
}

int accept_object(object who, object ob)
{
	if( !ob->id("mysterious token") && !ob->id("token")
	&&  !ob->id("jade token") )
		return 0;

	if( who->query("quest/beggar_clue_done") ) {
		do_chat("廟祝雙手合十﹐說道﹕此事已了﹐施主不必掛懷。\n");
		return 0;
	}
	if( !who->query_temp("pending/beggar_clue") ) {
		do_chat("廟祝接過玉牌看了看﹐說道﹕這玉牌倒是有些來歷﹐施主從何處得來﹖\n");
		return 0;
	}

	do_chat(({
		"廟祝接過玉牌﹐湊到燭火下仔細端詳。\n",
		"廟祝臉色微變﹐低聲說道﹕阿彌陀佛﹐這是……\n",
		"廟祝說道﹕這玉牌上刻的「安」字﹐是龍安城安家的家徽。\n",
		"廟祝嘆道﹕安家三十年前遭逢大難﹐滿門被滅﹐這玉牌是安家嫡系才有的信物。\n",
		"廟祝說道﹕如今竟有人攜帶此物出現在城中……恐怕不是什麼好事。\n",
		"廟祝將玉牌收好﹐雙手合十說道﹕多謝施主將此物送來﹐老衲會稟報城中長老。\n",
		"廟祝從功德箱中取出幾兩銀子﹐說道﹕這是佛前的供養﹐施主行善積德﹐理應受此。\n",
		(: do_reward, who :),
	}));
	return 1;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "玉牌") >= 0 || strsrch(msg, "安家") >= 0
	||  strsrch(msg, "黑衣人") >= 0 || strsrch(msg, "秘密") >= 0 ) {
		if( ob->query("quest/beggar_clue_done") ) {
			do_chat("廟祝雙手合十﹐說道﹕阿彌陀佛﹐此事老衲已在處理﹐施主放心。\n");
			return;
		}
		if( ob->query_temp("pending/beggar_clue") >= 2 ) {
			do_chat(({
				"廟祝若有所思﹐說道﹕施主所言之事﹐確實令人不安。\n",
				"廟祝說道﹕你若是有什麼線索或物件﹐不妨拿來讓老衲過目。\n",
			}));
			return;
		}
		do_chat("廟祝微微搖頭﹐說道﹕阿彌陀佛﹐老衲不問世間是非﹐施主另請高明吧。\n");
		return;
	}
}
