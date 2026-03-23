// ferryman.c
// Quest: 老艄公的信物 (ferryman_memento)
// Flow: talk about 妻/pendant/信物 -> ferryman tells story -> go to riverside_e
//       -> defeat river bandit -> search stash -> find jade pendant
//       -> give pendant to ferryman -> reward

#include <npc.h>

inherit F_VILLAGER;

void do_reward(object player);

void create()
{
	set_name("老艄公", ({"ferryman", "boatman"}));
	set_attr("str", 16);
	set_attr("con", 20);
	set_attr("dex", 14);
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 60);
	set("long",
		"一個鬚髮皆白的老艄公﹐皮膚被日曬雨淋得黝黑粗糙﹐雙手\n"
		"佈滿老繭。他穿著一件洗得發白的粗布短衫﹐腰間繫著一條草繩﹐\n"
		"赤著雙腳站在船頭﹐一副見慣了風浪的模樣。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"老艄公撐著竹篙﹐說道﹕這羿水啊﹐看著平靜﹐底下暗流可凶著呢。\n",
		"老艄公吸了口旱煙﹐吐出一口煙圈﹐望著河面出神。\n",
		"老艄公說道﹕要過河的趕緊﹐等下起風就不好擺渡了。\n",
		"老艄公哼著不知名的漁歌﹐手中的竹篙有節奏地點著水面。\n",
	}));
	setup();
	carry_money("coin", 80);
}

int accept_object(object who, object ob)
{
	if( !ob->id("jade pendant") && !ob->id("jade_pendant") ) return 0;

	if( who->query("quest/ferryman_memento_done") ) {
		do_chat("老艄公搖搖頭﹐說道﹕玉佩已經回來了﹐你留著吧。\n");
		return 0;
	}
	if( !who->query_temp("pending/ferryman_memento") ) {
		do_chat("老艄公看了看那塊玉佩﹐說道﹕這東西不是我的。\n");
		return 0;
	}
	do_chat(({
		"老艄公接過玉佩﹐雙手微微顫抖。\n",
		"老艄公用袖子仔細擦拭著玉佩上的汙漬﹐眼眶漸漸泛紅。\n",
		"老艄公哽咽道﹕翠蓮 ... 你的東西 ... 總算是回來了 ...\n",
		"老艄公深吸了一口氣﹐抹去眼角的淚﹐轉向你鄭重地抱了抱拳。\n",
		"老艄公說道﹕恩人﹐老漢一輩子在這河上討生活﹐沒什麼值錢的。\n",
		"老艄公說道﹕這個 ... 是早年在河底摸到的﹐送給你吧。\n",
		(: do_reward, who :),
	}));
	return 1;
}

void do_reward(object player)
{
	object reward;

	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/ferryman_memento_done") ) return;

	player->set("quest/ferryman_memento_done", 1);
	player->delete_temp("pending/ferryman_memento");
	player->gain_score("quest", 80);

	reward = new(__DIR__"obj/river_pearl");
	reward->move(player);
	message_vision("老艄公從懷中掏出一顆圓潤的珍珠﹐塞到$N手中。\n", player);
	tell_object(player, "( 你獲得了一顆羿水明珠 )\n");
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "妻") >= 0 || strsrch(msg, "信物") >= 0
	||  strsrch(msg, "玉佩") >= 0 || strsrch(msg, "pendant") >= 0
	||  strsrch(msg, "河匪") >= 0 || strsrch(msg, "bandit") >= 0
	||  strsrch(msg, "煩惱") >= 0 || strsrch(msg, "幫忙") >= 0 ) {
		if( ob->query("quest/ferryman_memento_done") ) {
			do_chat("老艄公摸了摸懷中的玉佩﹐感激地說道﹕多虧了你﹐翠蓮的信物回來了。\n");
			return;
		}
		if( ob->query_temp("pending/ferryman_memento") ) {
			do_chat(({
				"老艄公嘆道﹕那些河匪就在東邊的河畔出沒﹐\n",
				"老艄公說道﹕他們搶了我的玉佩﹐多半藏在蘆葦叢裡。\n",
			}));
			return;
		}
		do_chat(({
			"老艄公吸了口旱煙﹐緩緩說道﹕\n",
			"老艄公說道﹕前些日子﹐我在河邊洗船﹐被幾個河匪堵住了。\n",
			"老艄公黯然道﹕他們搶走了我亡妻翠蓮留下的玉佩 ...\n",
			"老艄公說道﹕那是她臨終前交給我的信物﹐跟了我二十多年了。\n",
			"老艄公看著你﹐說道﹕我老了﹐打不過那些歹人 ...\n",
			"老艄公說道﹕那些河匪就在碼頭東邊的河畔一帶活動﹐\n",
			"老艄公說道﹕你要是願意幫忙﹐把玉佩找回來﹐老漢感激不盡。\n",
		}));
		ob->set_temp("pending/ferryman_memento", 1);
		return;
	}
}
