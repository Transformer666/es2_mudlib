// vim: syntax=lpc
// fortune_teller.c - Quest: 算命先生的龜殼
// quest/fortune_teller_turtle_done

#include <npc.h>

inherit F_VILLAGER;

void give_quest_reward(object player);

void create()
{
	set_name("算命先生", ({"fortune_teller", "teller"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 55);
	set("gender", "male");
	set("long",
		"一個身穿青布長衫的老先生﹐頭戴方巾﹐手搖鵝毛扇﹐面前擺\n"
		"著一張小桌﹐桌上放著龜殼和銅錢。他鬚髮皆白﹐一雙眼睛卻精\n"
		"光四射﹐不時抬頭打量來往的行人﹐嘴裡唸唸有詞。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"算命先生搖著扇子說道﹕鐵口直斷﹐算盡天下事﹗來來來﹐算一卦﹗\n",
		"算命先生掐指一算﹐自言自語道﹕嗯﹐今日有貴人到此。\n",
		"算命先生撫了撫長鬚﹐若有所思。\n",
	}));
	setup();
	carry_money("coin", 50);
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/fortune_teller_turtle_done") )
		return;

	if( this_player()->query_temp("pending/fortune_turtle") )
		do_chat("算命先生急切地問道﹕找到我的龜殼了嗎﹖後巷那邊﹐仔細找找﹗\n");
}

private void give_quest_reward(object player)
{
	object money;

	if( !player || environment(player) != environment() ) return;

	player->set("quest/fortune_teller_turtle_done", 1);
	player->gain_score("quest", 80);

	money = new("/obj/money/coin");
	money->set_amount(80);
	if( !money->move(player) )
		money->move(environment());
}

int accept_object(object player, object ob)
{
	if( !userp(player) ) return 0;
	if( player->query("quest/fortune_teller_turtle_done") ) return 0;

	if( ob->id("turtle shell") || ob->id("turtle_shell") ) {
		if( !player->query_temp("pending/fortune_turtle") ) return 0;

		do_chat(({
			"算命先生接過龜殼﹐仔細端詳了一番﹐臉上露出喜色。\n",
			"算命先生說道﹕太好了﹗就是這個﹐我的寶貝龜殼﹗\n",
			"算命先生搖著扇子笑道﹕老夫鐵口直斷﹐果然算到今日會有貴人相助﹗\n",
			"算命先生掐指一算﹐說道﹕承蒙相助﹐這點銀子是老夫的一番心意。\n",
			(: give_quest_reward, player :),
		}));
		player->delete_temp("pending/fortune_turtle");
		return 1;
	}
	return 0;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( ob->query("quest/fortune_teller_turtle_done") ) return;

	if( ob->query_temp("pending/fortune_turtle") ) {
		if( strsrch(msg, "龜殼") >= 0 || strsrch(msg, "找到") >= 0 ) {
			do_chat("算命先生焦急地說道﹕你找到了嗎﹖就在後巷那邊﹐仔細翻翻那些破箱子﹗\n");
			return;
		}
		return;
	}

	if( strsrch(msg, "算命") >= 0 || strsrch(msg, "算一卦") >= 0
	||  strsrch(msg, "占卜") >= 0 || strsrch(msg, "龜殼") >= 0
	||  strsrch(msg, "怎麼了") >= 0 || strsrch(msg, "幫忙") >= 0 ) {
		do_chat(({
			"算命先生嘆了口氣﹐搖頭道﹕唉﹐今天可算不了了。\n",
			"算命先生壓低聲音道﹕前幾天我去茶樓喝茶﹐結果龜殼不知怎的掉了 ...\n",
			"算命先生說道﹕那可是我祖傳的占卜龜殼﹗刻著我爺爺親手畫的卦象﹗\n",
			"算命先生說道﹕我記得當時經過後巷﹐應該是掉在那一帶了。\n",
			"算命先生拱手道﹕大俠若是能幫我找回龜殼﹐老夫必有重謝﹗\n",
		}));
		ob->set_temp("pending/fortune_turtle", 1);
		return;
	}

	if( strsrch(msg, "喬陰") >= 0 || strsrch(msg, "縣城") >= 0 ) {
		do_chat("算命先生搖搖扇子道﹕喬陰雖是小縣城﹐但也是南來北往的要道﹐消息可靈通得很呢。\n");
		return;
	}
}
