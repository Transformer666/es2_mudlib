// vim: syntax=lpc
// Quest: 乞丐的消息 (beggar_clue)
// Flow: talk to beggar -> he has a mysterious token but wants food
//       -> buy roast_chicken from innkeeper -> give to beggar
//       -> beggar gives token and tells story -> take token to temple_monk -> reward

#include <npc.h>

inherit F_VILLAGER;

void give_token(object player);

void create()
{
	set_name("乞丐", ({"beggar", "qigai"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一個衣衫襤褸的乞丐蜷縮在小巷的角落裡，骯髒的衣衫勉強遮\n"
		"蔽著他瘦骨嶙峋的身軀。儘管外表潦倒，他的雙眼卻銳利而警覺，\n"
		"彷彿這座城中發生的每一件秘密他都瞭若指掌。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"乞丐伸出枯瘦的手：行行好，賞口飯吃吧。\n",
		"乞丐壓低聲音自言自語：昨晚碼頭那邊可不太平啊……\n",
		"乞丐神秘兮兮地說：江湖上最近可有不少大事發生呢。\n",
	}));

	set_skill("unarmed", 10);
	set_skill("dodge", 15);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 5);
}

void give_token(object player)
{
	object token;

	if( !player || !present(player, environment()) ) return;

	token = new(__DIR__"obj/mysterious_token");
	if( !token->move(player) )
		token->move(environment());

	tell_object(player, "( 你獲得了一塊神秘玉牌 )\n");
	player->set_temp("pending/beggar_clue", 2);
}

int accept_object(object who, object ob)
{
	if( !ob->id("chicken") && !ob->id("food")
	&&  !ob->id("roast_chicken") )
		return 0;

	if( who->query("quest/beggar_clue_done") ) {
		do_chat("乞丐擺擺手﹐嘿嘿笑道﹕不用了﹐上次那頓雞吃得飽飽的。\n");
		return 0;
	}
	if( !who->query_temp("pending/beggar_clue") ) {
		do_chat("乞丐接過食物﹐狼吞虎嚥地吃了起來﹐連聲道謝。\n");
		return 1;
	}

	do_chat(({
		"乞丐兩眼放光﹐一把接過燒雞﹐大口大口地啃了起來。\n",
		"乞丐一邊吃一邊含糊地說道﹕好人﹗好人吶﹗\n",
		"乞丐吃完後擦了擦嘴﹐壓低聲音說道﹕既然你這麼夠意思﹐我告訴你一件事。\n",
		"乞丐說道﹕前幾天夜裡﹐我看見幾個黑衣人鬼鬼祟祟地從西街經過。\n",
		"乞丐說道﹕其中一個人不小心掉了個東西﹐他們急匆匆走了沒發現。\n",
		"乞丐從懷中掏出一塊玉牌﹐說道﹕就是這個﹐上面刻著什麼字﹐我也看不太懂。\n",
		"乞丐說道﹕你拿去吧﹐也許城裡的和尚認得﹐龍安寺那個廟祝見多識廣。\n",
		(: give_token, who :),
	}));
	return 1;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "秘密") >= 0 || strsrch(msg, "消息") >= 0
	||  strsrch(msg, "碼頭") >= 0 || strsrch(msg, "大事") >= 0
	||  strsrch(msg, "黑衣人") >= 0 ) {
		if( ob->query("quest/beggar_clue_done") ) {
			do_chat("乞丐嘿嘿笑道﹕那些黑衣人再沒出現過﹐不知跑哪兒去了。\n");
			return;
		}
		if( ob->query_temp("pending/beggar_clue") >= 2 ) {
			do_chat("乞丐說道﹕玉牌拿去給龍安寺的廟祝看看吧﹐他肯定認得。\n");
			return;
		}
		if( ob->query_temp("pending/beggar_clue") == 1 ) {
			do_chat(({
				"乞丐眼珠子滴溜溜一轉﹐嘿嘿笑道﹕想知道﹖行啊。\n",
				"乞丐摸了摸肚皮﹐可憐兮兮地說道﹕就是這肚子餓得慌……\n",
				"乞丐說道﹕你要是能弄隻燒雞給我吃﹐我把我知道的全告訴你﹗\n",
				"乞丐舔了舔嘴唇﹕城裡客棧就有賣﹐龍安燒雞﹐那滋味……嘖嘖。\n",
			}));
			return;
		}
		do_chat(({
			"乞丐警覺地左右張望了一下﹐壓低聲音說道﹕嘿嘿﹐你也想聽﹖\n",
			"乞丐說道﹕前幾天夜裡﹐我看到了一些不該看到的東西……\n",
			"乞丐拍了拍肚皮﹐嘆道﹕可是我這肚子實在太餓了﹐沒力氣說話啊。\n",
		}));
		ob->set_temp("pending/beggar_clue", 1);
		return;
	}

	if( strsrch(msg, "燒雞") >= 0 || strsrch(msg, "吃") >= 0
	||  strsrch(msg, "食物") >= 0 || strsrch(msg, "餓") >= 0 ) {
		if( ob->query("quest/beggar_clue_done") ) return;
		if( !ob->query_temp("pending/beggar_clue") )
			ob->set_temp("pending/beggar_clue", 1);
		do_chat("乞丐眼巴巴地望著你﹕城裡客棧有賣龍安燒雞﹐你去買一隻給我﹐我把好東西給你看。\n");
		return;
	}

	if( strsrch(msg, "玉牌") >= 0 || strsrch(msg, "東西") >= 0
	||  strsrch(msg, "掉") >= 0 ) {
		if( ob->query("quest/beggar_clue_done") ) {
			do_chat("乞丐嘿嘿笑道﹕那玉牌的事﹐你去問廟祝就知道了。\n");
			return;
		}
		if( ob->query_temp("pending/beggar_clue") >= 2 ) {
			do_chat("乞丐說道﹕拿去給龍安寺的廟祝看看吧﹐他肯定認得。\n");
			return;
		}
		do_chat("乞丐神秘兮兮地說道﹕嘿嘿﹐想知道﹖先讓我吃飽再說。\n");
		if( !ob->query_temp("pending/beggar_clue") )
			ob->set_temp("pending/beggar_clue", 1);
		return;
	}
}
