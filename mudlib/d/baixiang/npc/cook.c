// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("灶頭僧", ({"cook", "monk", "zhaotou"}));
	set_race("human");
	set_class("commoner");
	set_level(8);
	set_skill("unarmed", 15);

	set("age", 35);
	set("gender", "male");
	set("attitude", "peaceful");
	set("long",
		"一位身穿灰色僧袍的中年僧人﹐袖口高高捲起﹐露出結實的\n"
		"手臂。他正忙碌地在灶台前翻炒著素菜﹐額頭微微冒汗﹐臉\n"
		"上卻帶著一抹安詳的微笑。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"灶頭僧一邊翻炒著青菜﹐一邊低聲念誦佛號。\n",
		"灶頭僧說道﹕「今日的豆腐燉得恰到好處﹐清淡而有味。」\n",
		"灶頭僧擦了擦額頭的汗珠﹐往鍋中加了一把鮮筍。\n",
		"灶頭僧說道﹕「佛門素齋﹐不殺生靈﹐亦能養身養心。」\n",
	}));
	set("refuse_fight", 1);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 20);
}
