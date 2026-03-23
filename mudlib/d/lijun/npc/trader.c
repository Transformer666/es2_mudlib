// trader.c
// Quest: trader_cargo_done - 行商失貨任務

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("行商", ({"trader", "merchant"}));
	set_attr("str", 12);
	set_attr("con", 14);
	set_attr("dex", 16);
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 40);
	set("long",
		"一個精明幹練的行商﹐穿著一身半舊的藏青色長衫﹐肩上搭著\n"
		"一條汗巾。他的攤位上擺著斗笠、竹竿之類的雜貨﹐不時吆喝幾\n"
		"聲招攬生意。你可以用 list 看看他賣些什麼﹐用 buy 購買。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"行商吆喝道﹕走過路過不要錯過﹗上好的斗笠﹐擋風遮雨﹗\n",
		"行商說道﹕這竹竿可是南邊竹林裡精挑細選的﹐結實得很﹗\n",
		"行商嘆道﹕如今走南闖北不容易﹐河匪越來越猖獗了。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/straw_hat" : 20,
		__DIR__"obj/bamboo_pole" : 20,
		__DIR__"obj/dried_fish" : 50,
	]));

	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐好眼光﹗給你﹗");
	::deliver_merchandise(customer, item);
}

int accept_object(object player, object ob)
{
	if( !userp(player) ) return 0;
	if( player->query("quest/trader_cargo_done") ) {
		do_chat("行商笑道﹕你已經幫過我了﹐這個你自己留著吧。\n");
		return 0;
	}
	if( player->query_temp("pending/trader_cargo") != 1 ) return 0;
	if( !ob->id("cargo_box") && !ob->id("cargo box") ) {
		do_chat("行商搖搖頭道﹕這不是我丟的貨啊。\n");
		return 0;
	}

	do_chat(({
		"行商接過貨箱﹐急忙打開查看﹐喜出望外。\n",
		"行商說道﹕太好了﹗裡面的南方藥材都還在﹗\n",
		"行商感激道﹕多謝你了﹐恩人﹗這些東西是我全部的本錢。\n",
		"行商說道﹕不成敬意﹐這點銀子和一頂斗笠請你收下﹗\n",
		(: give_rewards, player :),
	}));
	return 1;
}

private void give_rewards(object player)
{
	object hat;

	if( !player || environment(player) != environment() ) return;

	hat = new(__DIR__"obj/straw_hat");
	if( hat ) {
		if( hat->move(player) )
			hat->move(environment());
	}
	player->carry_money("silver", 3);
	player->set("quest/trader_cargo_done", 1);
	player->gain_score("quest", 80);
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;
	if( ob->query("quest/trader_cargo_done") ) return;

	if( ob->query_temp("pending/trader_cargo") ) {
		if( strsrch(msg, "貨") >= 0 || strsrch(msg, "箱") >= 0
		||  strsrch(msg, "cargo") >= 0 ) {
			do_chat(
				"行商說道﹕貨箱掉到河畔西邊的淺灘了﹐你去找找看吧。\n");
			return;
		}
		return;
	}

	if( strsrch(msg, "河匪") >= 0 || strsrch(msg, "貨") >= 0
	||  strsrch(msg, "失") >= 0 || strsrch(msg, "幫") >= 0
	||  strsrch(msg, "cargo") >= 0 ) {
		do_chat(({
			"行商嘆了口氣﹐說道﹕別提了﹐前幾天從南邊進了一批藥材 ...\n",
			"行商說道﹕過河的時候被河匪截住﹐拼了老命才逃上岸 ...\n",
			"行商說道﹕那箱貨掉到河裡了﹐被水沖到西邊河畔的淺灘上。\n",
			"行商懇求道﹕那箱貨是我全部的本錢﹐能不能幫我找回來﹖\n",
		}));
		ob->set_temp("pending/trader_cargo", 1);
		return;
	}
}
