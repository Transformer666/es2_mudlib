// hunter.c
// Quest: 莽林獵獸 (hunter_beast)
// Flow: talk about tiger/獸 -> hunter asks for help -> go to path2 search tracks
//       -> devilish tiger spawns -> defeat tiger -> get fang -> give to hunter -> reward

#include <npc.h>

inherit F_VILLAGER;

void do_reward(object player);

void create()
{
	set_name("獵人", ({"hunter", "huntsman"}));
	set_attr("str", 18);
	set_attr("con", 16);
	set_attr("dex", 20);
	set_race("human");
	set_class("commoner");
	set_level(15);

	set("age", 35);
	set("long",
		"一個身穿獸皮背心的獵人﹐皮膚被風吹日曬得黝黑粗糙。他腰\n"
		"間掛著一把獵刀﹐背上背著一張弓﹐目光銳利﹐時刻保持著警惕。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"獵人壓低聲音說道﹕別大聲﹐林子深處有黑熊出沒﹐惹不起。\n",
		"獵人看了看天色﹐說道﹕天黑前得趕回去﹐這林子夜裡更危險。\n",
		"獵人檢查了一下獵刀的鋒利程度﹐滿意地點了點頭。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("knife") )->wield();
	carry_money("coin", 60);
}

int accept_object(object who, object ob)
{
	if( !ob->id("tiger fang") && !ob->id("tiger_fang") ) return 0;

	if( who->query("quest/hunter_beast_done") ) {
		do_chat("獵人搖搖頭﹐說道﹕這個你留著吧﹐上次那個就夠了。\n");
		return 0;
	}
	if( !who->query_temp("pending/hunter_beast") ) {
		do_chat("獵人說道﹕這是什麼東西﹖\n");
		return 0;
	}
	do_chat(({
		"獵人接過虎牙﹐翻來覆去地端詳了一番。\n",
		"獵人驚喜道﹕好傢伙﹗狻猊的尖牙﹗你竟然真把那畜生給殺了﹖\n",
		"獵人激動地說道﹕太好了﹗這下林子裡的獵戶們總算能安心了﹗\n",
		"獵人拍了拍你的肩膀﹐說道﹕等等﹐我有樣東西送你。\n",
		(: do_reward, who :),
	}));
	return 1;
}

void do_reward(object player)
{
	object reward;

	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/hunter_beast_done") ) return;

	player->set("quest/hunter_beast_done", 1);
	player->delete_temp("pending/hunter_beast");
	player->gain_score("quest", 80);

	reward = new(__DIR__"obj/tiger_hide");
	reward->move(player);
	message_vision("獵人從身後取出一件虎皮背心﹐塞到$N手中。\n", player);
	tell_object(player, "( 你獲得了一件狻猊皮甲 )\n");
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "狻猊") >= 0 || strsrch(msg, "虎") >= 0
	||  strsrch(msg, "tiger") >= 0 || strsrch(msg, "獸") >= 0
	||  strsrch(msg, "危險") >= 0 || strsrch(msg, "幫忙") >= 0 ) {
		if( ob->query("quest/hunter_beast_done") ) {
			do_chat("獵人笑道﹕多虧了你﹐那頭狻猊已經不會再禍害人了。\n");
			return;
		}
		if( ob->query_temp("pending/hunter_beast") ) {
			do_chat(({
				"獵人壓低聲音說道﹕那頭狻猊就在莽林深處出沒﹐\n",
				"獵人說道﹕你仔細找找那裡的蹤跡﹐興許能引出那畜生。\n",
			}));
			return;
		}
		do_chat(({
			"獵人四下張望了一番﹐壓低聲音說道﹕\n",
			"獵人說道﹕最近莽林深處出了一頭狻猊﹐週身陰氣瀰漫﹐兇悍異常。\n",
			"獵人嘆道﹕已經有好幾個獵戶遭了毒手﹐大夥兒都不敢再深入了。\n",
			"獵人打量了你一番﹐說道﹕看你身手不凡﹐能不能幫忙除了這禍害﹖\n",
			"獵人說道﹕你到莽林深處去﹐仔細搜尋一下虎蹤﹐也許能引出那畜生。\n",
			"獵人說道﹕要是你能殺了牠﹐把牠的虎牙帶回來﹐我有好東西酬謝你﹗\n",
		}));
		ob->set_temp("pending/hunter_beast", 1);
		return;
	}
}
