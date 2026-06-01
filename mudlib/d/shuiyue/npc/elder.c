// elder.c -- 水月村心的老村正（純氣氛閒談 + 本地掌故﹐不接任務、不動旗標）。
//            對清泉一事略知一二﹐口風裡替福安客棧的散帳支線（清泉）做個指路鋪墊﹐
//            但本身不接任務、不交物、不記任何旗標。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老村正", ({ "elder", "village head", "cunzheng" }) );
	set("nickname", "老村正");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 63);
	set("gender", "male");
	set("long",
		"水月村的老村正﹐生得清癯矍鑠﹐一把花白的長鬚﹐拄著一\n"
		"根油亮的竹杖﹐在村心的古井邊踱步閒看。他在這谷裡住了一輩\n"
		"子﹐村裡村外的掌故人情、這一脈活水的來龍去脈﹐沒有他不曉\n"
		"得的。見了生客﹐他總愛和氣地指點兩句。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"老村正拄著竹杖﹐繞著古井緩緩踱步﹐不時俯身瞧瞧井裡的水色。\n",
		"老村正捋著花白的長鬚道﹕咱這水月村﹐一村人吃用全仗瀑下這一脈活水哩。\n",
		"老村正嘆道﹕近來這井水怎的透出些苦澀﹖怕是瀑後的泉眼出了岔子﹐得尋個人去瞧瞧纔好。\n",
	}));
	setup();
	carry_money("coin", 40);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想向老村正打聽甚麼﹖（試試 ask elder about 水月村，或 ask elder about 清泉）\n");

	if( arg == "elder about 水月村"
	||  arg == "elder about 村"
	||  arg == "elder about 水月"
	||  arg == "elder about 瀑布"
	||  arg == "elder about shuiyue" ) {
		do_chat(({
			(: command, "say 後生家﹐咱這水月村僻是僻了些﹐景緻卻是極好的。村後那道水月瀑布﹐月夜裡飛瀑映月﹐水裡天上兩輪清輝﹐連江湖上的人都曉得它的名兒。" :),
			(: command, "say 村心東北上去是瀑布﹐東南柳堤下是浣月潭﹐都值得後生家去走走。咱村裡引的全是瀑下的活水﹐甜得很哪。" :),
		}));
		return 1;
	}

	// 清泉：純做指路鋪墊（指往福安客棧的掌櫃），本身不接任務、不記旗標
	if( arg == "elder about 清泉"
	||  arg == "elder about 泉"
	||  arg == "elder about 井水"
	||  arg == "elder about 活水"
	||  arg == "elder about spring" ) {
		do_chat(({
			(: command, "say 唉﹐後生家也覺出這井水的苦澀了﹖咱村裡引的是瀑後泉眼的活水﹐近來那泉眼怕是教秋汛沖的亂石壅住了﹐水才變了味。" :),
			(: command, "say 這事啊﹐福安客棧的掌櫃最是上心——他店裡的水缸也壞了味﹐正愁著呢。後生家若有心﹐不妨去客棧問問他（ask keeper about 清泉）﹐興許幫得上忙。" :),
		}));
		return 1;
	}

	return notify_fail("老村正捋鬚一笑﹕後生家問的這個﹐老朽一時也說不上來。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗後生家好生無禮﹗欺負我這把老骨頭做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
