// storyteller.c -- 百花村茶寮裡的說書先生（純氣氛閒談﹐不接任務、不動旗標）。
// 模式照 d/shuiyue/npc/porter.c：F_VILLAGER、do_ask 只擺風味、accept_fight 回 0。
// 茶寮為 no_fight 室內、且說書先生須守在高凳上，故 chat_msg 不用 random_move。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("說書先生", ({ "storyteller", "story teller", "shuoshu" }) );
	set("nickname", "說書先生");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 48);
	set("gender", "male");
	set("long",
		"一個在茶寮裡討生活的說書先生﹐穿一襲半舊的灰布長衫﹐三\n"
		"綹清鬚﹐眉目間自有一股說書人特有的精明與滄桑。他端坐在堂\n"
		"中一張高凳上﹐手裡一塊醒木﹑一把摺扇﹐口角生風地講著江湖\n"
		"上的恩怨情仇。一段書講到緊要關節﹐醒木一拍﹐滿座聽客便不\n"
		"由得屏息凝神﹐連那粗碗裡的茶都涼了也顧不得喝。\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		"說書先生把醒木在桌上一拍﹐道﹕『欲知後事如何﹐且聽下回分解』——說罷呷了口涼茶﹐惹得滿座一片噓聲。\n",
		"說書先生展開摺扇輕搖﹐悠悠道﹕列位看官﹐這江湖路遠﹐恩怨情仇﹐說不盡道不完哪……\n",
		"說書先生眉飛色舞地比劃著﹐講到那大俠一劍光寒﹑技壓群雄處﹐滿座聽客連聲喝采。\n",
	}));
	setup();
	carry_money("coin", 25);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這說書先生甚麼﹖（試試 ask storyteller about 百花村）\n");

	if( arg == "storyteller about 百花村"
	||  arg == "storyteller about 村"
	||  arg == "storyteller about flower"
	||  arg == "story teller about 百花村" ) {
		do_chat(({
			(: command, "say 客官問起這百花村麼﹖呵﹐這地方說來也奇﹕一村的脂粉風月﹑十里的紅燈繡幔﹐天南地北的三教九流﹐都愛往這紅塵窩裡鑽。" :),
			(: command, "say 老朽在這茶寮裡說了二十年的書﹐甚麼樣的英雄好漢﹑甚麼樣的痴男怨女﹐沒見過﹖一段段恩怨﹐到頭來都成了老朽口中的一回書罷了——客官且坐下吃碗茶﹐聽老朽慢慢道來。" :),
		}));
		return 1;
	}

	return notify_fail("說書先生把摺扇一合﹐笑道﹕客官問這個做甚﹖坐下吃碗茶﹐聽老朽說一段書才是正經。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗使不得使不得﹗老朽一個耍嘴皮子的﹐手無縛雞之力﹐客官饒了我罷﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
