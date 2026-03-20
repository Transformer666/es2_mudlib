// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("軍械管事", ({"armorer", "steward", "guanshi"}));
	set_attr("str", 16);
	set_attr("con", 17);
	set_race("human");
	set_class("commoner");
	set_level(16);

	set_skill("sword", 45);
	set_skill("unarmed", 30);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一位久經沙場的老兵負責管理軍械庫，仔細看管每一件武器和盔甲。\n"
		"他面容嚴肅，做事一絲不苟，整天都在清點庫存，確保每樣軍需物資\n"
		"都妥善存放。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"軍械管事拿起一把刀仔細端詳，喃喃道：這刃口又該磨了……\n",
		"軍械管事翻閱著帳冊，嘀咕道：長矛三十六支，弓箭四十二張……\n",
		"軍械管事皺眉道：軍需物資可不能馬虎，少了一根箭矢都得記錄在案。\n",
	}));
	set("no_fight", 1);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("broadsword"))->wield();
	carry_money("coin", 80);
}
