// wounded_merchant.c
// Quest: 受傷的商人 (wounded_merchant_medicine)
// Flow: talk -> learn he needs wild ginseng -> buy from herbalist
//       -> give ginseng to merchant -> reward

#include <npc.h>

inherit F_VILLAGER;

void give_reward(object player);

void create()
{
	set_name("受傷的商人", ({"wounded merchant", "merchant", "wounded_merchant"}));
	set_attr("str", 12);
	set_attr("dex", 10);
	set_attr("con", 14);
	set_attr("int", 16);
	set_attr("wis", 14);
	set_attr("spi", 12);
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 38);
	set("gender", "male");
	set("long",
		"一個中年商人靠在路邊的石頭上﹐臉色蒼白﹐衣衫上沾滿了血\n"
		"跡。他的右臂纏著一條撕下來的布條﹐已經被鮮血浸透﹐看起來傷\n"
		"得不輕。路邊散落著幾個被翻得亂七八糟的包袱﹐顯然剛遭遇了一\n"
		"場劫難。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"受傷的商人痛苦地呻吟了一聲。\n",
		"受傷的商人虛弱地說道﹕有人嗎 ... 救救我 ...\n",
		"受傷的商人咬著牙﹐把傷口上的布條又緊了緊。\n",
	}));

	setup();
	carry_money("silver", 3);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}

int accept_fight()
{
	do_chat("受傷的商人擺手道﹕別 ... 我已經傷成這樣了 ...\n");
	return 0;
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/wounded_merchant_done") )
		return;

	if( this_player()->query_temp("pending/wounded_merchant") )
		do_chat("受傷的商人虛弱地看著你﹐說道﹕你 ... 找到野山蔘了嗎﹖\n");
	else
		do_chat("受傷的商人掙扎著抬起頭﹐向你投來求助的目光。\n");
}

private void give_reward(object player)
{
	object money;

	if( !player || environment(player) != environment() ) return;
	if( player->query("quest/wounded_merchant_done") ) return;

	player->set("quest/wounded_merchant_done", 1);
	player->delete_temp("pending/wounded_merchant");
	player->gain_score("quest", 80);

	money = new("/obj/money/silver");
	money->set_amount(3);
	if( !money->move(player) )
		money->move(environment());
}

int accept_object(object player, object ob)
{
	if( !userp(player) ) return 0;

	if( ob->id("wild ginseng") || ob->id("ginseng") ) {
		if( player->query("quest/wounded_merchant_done") ) {
			do_chat("受傷的商人搖搖頭﹐說道﹕多謝﹐我的傷已經好多了﹐你留著吧。\n");
			return 0;
		}
		if( !player->query_temp("pending/wounded_merchant") ) {
			do_chat("受傷的商人疑惑地看著你﹐說道﹕這是 ... 給我的﹖\n");
			return 0;
		}

		do_chat(({
			"受傷的商人顫抖著接過野山蔘﹐放入口中嚼了幾口。\n",
			"受傷的商人的臉色漸漸恢復了一些血色。\n",
			"受傷的商人感激地說道﹕多謝你救了我一命﹗\n",
			"受傷的商人說道﹕我叫周成﹐從五堂鎮做藥材生意﹐沒想到在這路上遭了匪。\n",
			"受傷的商人說道﹕身上的貨物都被搶走了﹐只剩下這幾兩碎銀﹐你拿著當是我的謝禮。\n",
			(: give_reward, player :),
		}));
		return 1;
	}
	return 0;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( ob->query("quest/wounded_merchant_done") ) {
		if( strsrch(msg, "傷") >= 0 || strsrch(msg, "好") >= 0 )
			do_chat("受傷的商人感激地說道﹕多虧了你﹐我的傷已經好多了。\n");
		return;
	}

	if( strsrch(msg, "怎麼了") >= 0 || strsrch(msg, "傷") >= 0
	||  strsrch(msg, "幫忙") >= 0 || strsrch(msg, "發生") >= 0
	||  strsrch(msg, "救") >= 0 || strsrch(msg, "什麼事") >= 0 ) {
		if( ob->query_temp("pending/wounded_merchant") ) {
			do_chat("受傷的商人虛弱地說道﹕鎮上的藥鋪應該有賣野山蔘﹐拜託你了。\n");
			return;
		}
		do_chat(({
			"受傷的商人咬了咬牙﹐說道﹕我 ... 我從五堂往雪亭走﹐半路上遇到了一夥強盜。\n",
			"受傷的商人說道﹕他們搶了我的貨物不說﹐還砍了我一刀 ...\n",
			"受傷的商人說道﹕傷口一直在流血﹐再這樣下去怕是撐不住了。\n",
			"受傷的商人用懇求的目光看著你﹐說道﹕好心人﹐能不能幫我弄一根野山蔘來﹖\n",
			"受傷的商人說道﹕雪亭鎮和五堂鎮的藥鋪都有賣﹐拜託你了 ...\n",
		}));
		ob->set_temp("pending/wounded_merchant", 1);
		return;
	}

	if( strsrch(msg, "強盜") >= 0 || strsrch(msg, "匪") >= 0 ) {
		do_chat("受傷的商人說道﹕他們是三四個蒙面大漢﹐手持大刀﹐從路邊的草叢裡衝出來 ...\n");
		return;
	}

	if( strsrch(msg, "藥") >= 0 || strsrch(msg, "蔘") >= 0 ) {
		do_chat("受傷的商人說道﹕野山蔘有止血療傷的功效﹐藥鋪裡應該有賣。\n");
		return;
	}
}
