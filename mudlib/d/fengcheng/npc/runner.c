// runner.c -- 風城衙門差役，聚風茶樓裡吃茶當值的公門中人；
//             兼風城非戰鬥支線「失算的籤筒」的第一處線索（眼尖的公門中人）。
//
// 本檔原為純風味守城差役。為支線「失算的籤筒」加掛一段線索對白：
//   玩家（已自神算子接下任務 quest/fengcheng_gua==1）ask runner about 龜甲 ->
//   差役道出曾見一拾荒小乞兒在市集邊撿著件亮晶晶的物事﹐記
//   quest/fengcheng_gua_runner = 1（線索），指引玩家轉去市集尋攤販。
// 不動差役的戰鬥屬性、配兵、既有招呼與 accept_fight。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("差役", ({ "runner", "yamen runner", "chaiyi" }) );
	set_attr("str", 20);
	set_attr("con", 18);
	set_race("human");
	set_class("fighter");
	set_level(12);

	set_skill("blade", 45);
	set_skill("parry", 40);
	set_skill("dodge", 35);
	set_skill("unarmed", 35);

	set("age", 35);
	set("gender", "male");
	set("long",
		"一個風城衙門的差役﹐頭戴暖帽﹐身披一件繡著「勇」字的羊\n"
		"皮號褂﹐腰間挎著一柄彎刀﹐手裡端著根水火棍﹐在茶樓裡一邊\n"
		"吃茶﹐一邊警惕地打量著南來北往的生面孔﹐一副公門中人的派\n"
		"頭。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"差役把水火棍往地上一頓﹐喝道﹕外鄉人到了風城﹐可得安分守己﹗\n",
		"差役斜睨著你﹐冷哼一聲﹐顯是沒把你這南邊來的客人放在眼裡。\n",
		"差役壓低聲音道﹕近來塞外的馬賊鬧得兇﹐衙門已調了人手上城頭戒備﹐城裡盤查得緊。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("broadsword") )->wield();
	carry_money("coin", 80);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( !is_fighting() )
		do_chat((: command, "say 哪裡來的生面孔﹖到風城來﹐可得規矩些﹗" :));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位差役甚麼﹖\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("差役端著茶碗﹐斜睨著你﹐沒空理你。\n");

	// 龜甲 / 卦錢：支線「失算的籤筒」的第一處線索
	if( arg == "runner about 龜甲"
	||  arg == "yamen runner about 龜甲"
	||  arg == "runner about 卦錢"
	||  arg == "runner about 龜甲卦錢"
	||  arg == "runner about gua coin"
	||  arg == "runner about coin" ) {
		object me = this_player();
		int q = me->query("quest/fengcheng_gua");

		// 已接任務、進行中：給線索，記旗標（已記過則只重述，不卡關）
		if( q == 1 ) {
			if( !me->query("quest/fengcheng_gua_runner") )
				me->set("quest/fengcheng_gua_runner", 1);
			do_chat(({
				(: command, "say 神算子那枚教風颳跑的卦錢﹖嘿﹐你問著正主兒了。本差成日在這城裡轉﹐街面上一點動靜都瞞不過我這雙眼。" :),
				(: command, "say 前幾日是颳了場大風。我記得就在那兩日﹐有個拾荒的小乞兒﹐在東邊市集那頭撿著件亮晶晶的物事﹐當寶貝似的揣懷裡跑了。多半就是那枚卦錢。" :),
				(: command, "say 那小乞兒成日在市集邊轉﹐撿了東西﹐少不得拿去換口吃食。你去市集尋那守小吃攤的婦人問問（ask 攤販 about 龜甲）﹐興許有下落。" :),
			}));
			return 1;
		}

		// 未接任務或已完成：純風味帶過，不推進旗標
		if( q >= 2 )
			do_chat((: command,
				"say 神算子的卦錢尋回來啦﹖那就好。城裡少樁丟物的閒事﹐本差也省心。" :));
		else
			do_chat((: command,
				"say 龜甲卦錢﹖那是廣場上神算子卜卦的物事﹐你問本差作甚﹖有事先去尋那神算子說去。" :));
		return 1;
	}

	return notify_fail("差役不耐煩地擺擺手﹕本差公務在身﹐沒空與你閒扯。\n");
}

int accept_fight(object ob)
{
	do_chat("差役厲聲喝道﹕好大的膽子﹗竟敢在風城撒野﹗來人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
