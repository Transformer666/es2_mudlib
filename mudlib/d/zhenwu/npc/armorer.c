// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("管庫老兵", ({"armorer", "keeper", "laobing"}));
	set_attr("str", 15);
	set_attr("con", 16);
	set_race("human");
	set_class("commoner");
	set_level(18);

	set_skill("pike", 40);
	set_skill("unarmed", 30);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一名年邁的老兵正在軍械庫中逐一清點武器，嘴裡念念有詞。他雖\n"
		"已不再上陣殺敵，但對每一件兵器的來歷和狀況都瞭如指掌，管理得\n"
		"一絲不苟。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"管庫老兵數著架上的長矛，喃喃道：三十七……三十八……嗯，沒少。\n",
		"管庫老兵拿起一把刀仔細端詳，皺眉道：這把刀又捲刃了，得磨一磨。\n",
		"管庫老兵嘆了口氣，目光有些悠遠：想當年老子提著這桿槍，那可是殺得敵人片甲不留啊……\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("pike"))->wield();
	carry_money("coin", 60);
}
