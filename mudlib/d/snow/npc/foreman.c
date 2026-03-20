// foreman.c
// Quest: load 3+ crates onto wagon, collect wage -> first-time bonus

#include <npc.h>

inherit F_VILLAGER;

void new_crate();
void give_quest_bonus(object me);


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
		"你想打工賺些錢﹐可以跟他談談看。\n");
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

private void give_quest_bonus(object me)
{
	object money;

	if( !me || environment(me) != environment() ) return;

	me->set("quest/foreman_crate_done", 1);
	me->gain_score("quest", 50);

	money = new("/obj/money/coin");
	money->set_amount(100);
	money->move(this_object());
	command("give coin to " + me->query("id"));
}

void relay_say(object me, string msg)
{
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "工錢") >= 0 ) {
		int amount;
		object money;

		if( amount = me->query_temp("wage_deserved") ) {
			money = new("/obj/money/coin");
			money->set_amount(amount);
			money->move(this_object());
			command("say 好﹐好 ... 總共是" + chinese_number(amount) + "文錢﹐哪﹐給你。");
			me->delete_temp("wage_deserved");

			// First-time quest bonus: loaded 3+ crates (75+ coins worth)
			if( !me->query("quest/foreman_crate_done") && amount >= 75 ) {
				do_chat(({
					(: command, "give coin to " + me->query("id") :),
					"工頭打量了你一下﹐點了點頭。\n",
					"工頭說道﹕不錯嘛小伙子﹐第一次做就這麼賣力。\n",
					"工頭說道﹕這一百文是額外獎勵﹐以後常來啊。\n",
					(: give_quest_bonus, me :),
				}));
			} else {
				do_chat((: command, "give coin to " + me->query("id"):));
			}
		}
		else do_chat("工頭說道﹕搬一個箱子二十五文錢﹐損壞的賠三倍。\n");
		return;
	}

	if( strsrch(msg, "打工") >= 0 || strsrch(msg, "搬") >= 0
	||	strsrch(msg, "幫忙") >= 0 ) {
		if( me->query("quest/foreman_crate_done") )
			do_chat("工頭說道﹕老熟人了﹐不用多說﹐搬完了來算工錢。\n");
		else
			do_chat(({
				"工頭說道﹕想打工﹖好啊﹐正缺人手呢。\n",
				"工頭說道﹕把地上的箱子搬(get)上驢車(load crate into wagon)就行了。\n",
				"工頭說道﹕搬完了跟我說「工錢」﹐搬一箱給你二十五文。\n",
			}));
		return;
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
