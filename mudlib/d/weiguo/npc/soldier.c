// NPC: /d/weiguo/npc/soldier.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("老兵", ({"soldier", "veteran"}));
	set_attr("str", 20);
	set_attr("con", 20);
	set_attr("dex", 16);
	set_race("human");
	set_class("fighter");
	set_level(18);

	set_skill("pike", 70);
	set_skill("sword", 55);
	set_skill("parry", 60);
	set_skill("dodge", 45);

	set("age", 50);
	set("long",
		"一位飽經風霜的老兵，臉上有一道長長的刀疤，身穿磨損的皮甲，\n"
		"正坐在旗桿下擦拭著他的長矛。他的眼神沉穩而銳利，一看便知是\n"
		"在沙場上歷練多年的老手。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"老兵嘆了口氣，說道：邊境這些年不太平啊……\n",
		"老兵仔細地擦拭著長矛上的鏽跡。\n",
		"老兵目光遠眺，似乎在回憶著什麼。\n",
	}));
	set("vendetta_mark", "authority");

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("pike"))->wield();
	carry_money("coin", 80);
}

void protect(object ob)
{
	command("emote 大喝一聲，抄起長矛擋在前面！");
	command("wield pike");
	guard_ob(ob);
}
