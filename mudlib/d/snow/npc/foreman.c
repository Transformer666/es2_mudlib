// foreman.c

#include <npc.h>

inherit F_VILLAGER;

void new_crate();
void settle_wage(object me);


void create()
{
	set_name("工頭", ({ "foreman" }) );
	set_race("human");
	set_level(8);
	set_stat_maximum("kee", 60);
	set_attr("str", 18);
	set_attr("cor", 19);
	set_attr("cps", 15);
	set_attr("dex", 16);

	set("age", 48);
	set("long",
		"這位就是這家貨棧的工頭﹐負責指揮工人將貨物搬進搬出﹐如果\n"
		"你想打工賺些錢﹐可以向他打聽「打工」(ask foreman about 打工)。\n");
	set("chat_chance", 10);
	set("chat_msg", ({
		(: new_crate :),
		"工頭大聲吆喝著工人將貨物從倉庫搬出來。\n",
		"工頭大叫﹕小王呢﹖今天有沒有來﹖\n",
		"工頭說道﹕誰再去多找些人手﹐唉﹐忙死了。\n",
		"工頭說道﹕要算工錢的一個個來 ... 別急 ...\n"
	}) );

	setup();
	carry_money("coin", 220);
}

int accept_fight()
{
	do_chat("工頭說道﹕比武﹖你瘋了嗎﹖我才沒那種閒功夫。\n");
	return 0;
}

void settle_wage(object me)
{
	int amount;
	object money;

	if( !me ) return;

	if( amount = me->query_temp("wage_deserved") ) {
		money = new("/obj/money/coin");
		money->set_amount(amount);
		if( !money->move(me) ) {
			destruct(money);
			command("say 你身上的東西太多﹐連工錢都拿不動了﹐"
				"先整理整理再來領吧。");
			return;
		}
		me->delete_temp("wage_deserved");
		command("say 好﹐好 ... 總共是" + chinese_number(amount) + "文錢﹐哪﹐給你。");
		message_vision("$N交給$n一些錢。\n", this_object(), me);
	}
	else command("say 搬一個箱子二十五文錢﹐損壞的賠三倍。");
}

void relay_say(object me, string msg)
{
	if( !me || !userp(me) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "工錢") >= 0 ) {
		settle_wage(me);
		return;
	}
}

// ask foreman about 打工 / 工錢
void accept_inquiry(object who, string topic)
{
	switch( topic ) {
	case "工作":
	case "打工":
	case "搬貨":
	case "job":
	case "work":
		command("say 想賺幾文錢使喚﹖好說。你把大木箱扛起來(get crate)﹐"
			"裝上一旁的運貨驢車(load crate into wagon)便成。");
		command("say 搬一個箱子二十五文錢﹐損壞的賠三倍。"
			"搬完了跟我說聲「工錢」﹐我便結帳給你。");
		break;
	case "工錢":
	case "wage":
	case "pay":
		settle_wage(who);
		break;
	default:
		command("say 這個我可不清楚﹐我只管這貨棧搬貨的事。");
		break;
	}
}

void new_crate()
{
	object ob;

	if( !environment()
	||	sizeof(all_inventory(environment())) >= 15 ) return;

	ob = new(__DIR__"obj/crate");
	ob->move(environment());
	say("工頭說道﹕喂﹗那邊卸貨的小心一點﹐別給摔壞了﹗\n");
}

// vim: set ts=4 sw=4 syntax=lpc
