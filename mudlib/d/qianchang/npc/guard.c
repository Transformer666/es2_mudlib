// NPC: /d/qianchang/npc/guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("城門守衛", ({"guard", "gate guard"}));
	set_race("human");
	set_class("fighter");
	set_level(12);

	set("age", 30);
	set("gender", "male");
	set("long",
		"一名前場鎮的城門守衛，穿著一身簡單的皮甲，腰間佩著一把\n"
		"長劍。他神情警惕地注視著來往的行人和商隊，時不時盤問幾句。\n"
		"雖然只是小鎮守衛，卻也盡忠職守。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"城門守衛喝道：站住！進城的都要檢查一下貨物。\n",
		"城門守衛抱著長劍靠在城牆邊，打了個哈欠。\n",
		"城門守衛對同伴說道：最近路上不太平，要多留個心眼。\n",
	}));

	setup();
	carry_object(STOCK_WEAPON("longsword"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 30);
}
