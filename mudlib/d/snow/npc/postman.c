// NPC: /d/snow/npc/postman.c
// Quest: deliver a letter to the herbalist (藥鋪掌櫃)

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("驛站官員", ({"postman", "officer", "__ID_POSTMAN__"}));
	set_attr("str", 12);
	set_attr("dex", 14);
	set_attr("con", 13);
	set_attr("int", 16);
	set_attr("wis", 15);
	set_attr("spi", 12);
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 32);
	set("gender", "male");
	set("long",
		"這位驛站官員穿著一身深藍色的公服﹐腰間掛著一串銅鑰匙和\n"
		"一個皮革信袋。他的眼神銳利而專注﹐不時低頭翻閱著手中的收\n"
		"發簿冊﹐偶爾抬頭望向門外﹐似乎在等待送信的快馬。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"驛站官員翻了翻手中的簿冊﹐喃喃自語道：這幾封信怎麼還沒到 ...\n",
		"驛站官員整理著架上的信件﹐神色頗為忙碌。\n",
		"驛站官員嘆了口氣﹐說道：最近路上不太平﹐信件常常延誤。\n",
	}));

	setup();
	carry_money("coin", 50);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}

int accept_fight()
{
	do_chat("驛站官員皺眉道﹕這裡是驛站﹐請勿生事。\n");
	return 0;
}

private void give_letter(object player)
{
	object letter;

	if( !player || environment(player) != environment() ) return;

	letter = new(__DIR__"obj/quest_letter");
	if( !letter->move(player) )
		letter->move(environment());
}

private void give_reward(object player)
{
	object money;

	if( !player || environment(player) != environment() ) return;

	money = new("/obj/money/coin");
	money->set_amount(100);
	if( !money->move(player) )
		money->move(environment());

	player->set("quest/postman_delivery_done", 1);
	player->gain_score("quest", 100);
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/postman_delivery_done") )
		return;

	if( this_player()->query_temp("pending/postman_done") ) {
		do_chat(({
			"驛站官員高興地說道﹕你把信送到了﹖太好了﹗\n",
			"驛站官員說道﹕這是一點酬勞﹐請你收下。\n",
			(: give_reward, this_player() :),
		}));
		this_player()->delete_temp("pending/postman_done");
		return;
	}

	if( this_player()->query_temp("pending/postman_deliver") )
		do_chat("驛站官員說道﹕麻煩你把那封信送到藥鋪去﹐交給藥鋪掌櫃就行了。\n");
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( ob->query("quest/postman_delivery_done") ) return;

	int stage = ob->query_temp("pending/postman_deliver");

	if( !stage || stage == 0 ) {
		if( strsrch(msg, "幫") >= 0 || strsrch(msg, "送信") >= 0
		||	strsrch(msg, "信") >= 0 || strsrch(msg, "忙") >= 0 ) {
			do_chat(({
				"驛站官員眼睛一亮﹐說道﹕你願意幫忙送信﹖\n",
				"驛站官員說道﹕最近路上不太平﹐送信的人手也不夠 ...\n",
				"驛站官員說道﹕有一封信要送到鎮上的藥鋪﹐交給藥鋪掌櫃就行了。\n",
				"驛站官員說道﹕事成之後回來找我﹐我給你一些酬勞。\n",
				(: give_letter, ob :),
			}));
			ob->set_temp("pending/postman_deliver", 1);
			return;
		}
	}

	if( stage == 1 ) {
		if( strsrch(msg, "藥鋪") >= 0 || strsrch(msg, "哪") >= 0 ) {
			do_chat("驛站官員說道﹕藥鋪在北邊的街上﹐你往北走就能看到了。\n");
			return;
		}
	}
}
