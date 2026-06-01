// porter.c -- 水月谷口歇腳的挑夫（純氣氛閒談 + 本地指路﹐不接任務、不動旗標）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("挑夫", ({ "porter", "carrier", "tiaofu" }) );
	set("nickname", "挑夫");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 39);
	set("gender", "male");
	set("long",
		"一個替村裡往風城販貨的挑夫﹐生得精瘦結實﹐裹著件汗濕\n"
		"的短褐﹐方歇下擔子在谷口抹汗喘氣。他成年累月在這條谷口土\n"
		"道上來回﹐谷裡谷外的門路最是熟絡﹐見了生客﹐倒也樂得歇腳\n"
		"閒話兩句。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"挑夫放下擔子﹐捶著痠痛的肩膀﹐長長地吁了一口氣。\n",
		"挑夫抹了把汗道﹕這谷口一進一出﹐風城的乾冷與谷裡的水潤﹐竟像兩個天地。\n",
		"挑夫朝你拱了拱手道﹕客官面生﹐是頭一回進水月村罷﹖順著溪走﹐錯不了。\n",
	}));
	setup();
	carry_money("coin", 20);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這挑夫甚麼﹖（試試 ask porter about 水月村）\n");

	if( arg == "porter about 水月村"
	||  arg == "porter about 村"
	||  arg == "porter about 谷口"
	||  arg == "porter about 路"
	||  arg == "porter about shuiyue"
	||  arg == "porter about way" ) {
		do_chat(({
			(: command, "say 客官順著這溪往東走﹐便是村心了﹕北邊福安客棧﹐東邊映月茶寮﹐南邊雜貨鋪﹐打尖歇腳樣樣便當。" :),
			(: command, "say 村後那道水月瀑布﹐是江湖上掛了名的好景緻﹐村心東北一條石徑上去就是﹔東南柳堤下還有一泓浣月潭﹐都值得一瞧。往西出谷﹐便是風城南門了。" :),
		}));
		return 1;
	}

	return notify_fail("挑夫憨憨一笑﹕客官問這個做甚﹖歇歇腳﹐喝口水﹐這便進村去罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖咱一個挑擔子的苦力﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
