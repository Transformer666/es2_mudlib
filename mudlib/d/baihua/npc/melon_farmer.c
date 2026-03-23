// melon_farmer.c
// Quest: 瓜農的煩惱 (melon_pest)
// Flow: ask about trouble -> search melon_farm for tracks -> search garden -> boar spawns
//       -> defeat boar -> return to farmer -> reward

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void give_melon_reward(object player);

void create()
{
	set_name("瓜農", ({"melon_farmer", "farmer"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一個皮膚黝黑的老農﹐戴著一頂破草帽﹐蹲在瓜田裡忙活。他\n"
		"種的西瓜又大又甜﹐在附近幾個村子都有名氣。你可以用 list 看\n"
		"看﹐用 buy 來買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"瓜農拍了拍一個大西瓜﹐笑道﹕聽這聲音﹐準是個甜的﹗\n",
		"瓜農自言自語道﹕今年雨水充足﹐瓜長得好哇。\n",
		"瓜農皺了皺眉﹐嘀咕道﹕就是那頭畜生﹐老是來糟蹋瓜……\n",
	}));
	set("merchandise", ([
		__DIR__"obj/watermelon" : 50,
	]));

	setup();
	carry_money("coin", 40);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
	add_action("do_ask", "ask");
}

int accept_fight(object ob)
{
	do_chat("瓜農擺擺手道﹕我就是個種瓜的﹐別找我打架。\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say 好咧﹐" + item->name() + "拿好﹗");
	::deliver_merchandise(customer, item);
}

int do_ask(string arg)
{
	object me;

	me = this_player();
	if( !me ) return 0;
	if( !arg ) return 0;

	if( strsrch(arg, "瓜農") < 0 && strsrch(arg, "farmer") < 0
	&&  strsrch(arg, "煩惱") < 0 && strsrch(arg, "trouble") < 0
	&&  strsrch(arg, "野豬") < 0 && strsrch(arg, "boar") < 0
	&&  strsrch(arg, "畜生") < 0 )
		return 0;

	if( me->query("quest/melon_pest_done") ) {
		do_chat("瓜農笑道﹕多虧了你﹐那畜生再也不敢來了﹗\n");
		return 1;
	}

	if( me->query_temp("pending/melon_pest_killed") ) {
		call_out("give_melon_reward", 1, me);
		return 1;
	}

	if( me->query_temp("pending/melon_pest") ) {
		do_chat("瓜農說道﹕那畜生的腳印往北邊花園去了﹐你去找找看吧。\n");
		return 1;
	}

	if( is_chatting() ) return 1;

	do_chat(({
		"瓜農歎了口氣﹐說道﹕唉﹐別提了﹐最近可愁死我了。\n",
		"瓜農說道﹕有頭野豬﹐不知從哪裡來的﹐三天兩頭跑來偷吃我的瓜。\n",
		"瓜農說道﹕我這把老骨頭可鬥不過那畜生﹐獠牙比我手指頭還長哩。\n",
		"瓜農說道﹕你若是能幫我把那畜生趕走﹐老漢送你一筐西瓜﹗\n"
			"你在瓜田附近找找牠的蹤跡吧。\n",
		(: set_pending, me :),
	}));
	return 1;
}

void set_pending(object player)
{
	if( !player ) return;
	player->set_temp("pending/melon_pest", 1);
}

void give_melon_reward(object player)
{
	object melon;

	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/melon_pest_done") ) return;

	do_chat(({
		"瓜農高興得合不攏嘴﹐說道﹕真的﹖那畜生被你收拾了﹖\n",
		"瓜農說道﹕太好了太好了﹗老漢說話算話﹐這些西瓜你拿著﹗\n",
		"瓜農從草棚裡搬出幾個又大又圓的西瓜﹐塞到" + player->name() + "手裡。\n",
		(: complete_quest, player :),
	}));
}

void complete_quest(object player)
{
	object melon;

	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/melon_pest_done") ) return;

	player->set("quest/melon_pest_done", 1);
	player->gain_score("quest", 80);
	player->delete_temp("pending/melon_pest");
	player->delete_temp("pending/melon_pest_killed");

	melon = new(__DIR__"obj/watermelon");
	if( !melon->move(player) )
		melon->move(environment());

	player->earn_money("silver", 1);
}
