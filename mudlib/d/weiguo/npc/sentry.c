// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
	set_name("哨兵", ({"sentry", "guard", "shaobing"}));
	set_attr("str", 16);
	set_attr("con", 15);
	set_attr("dex", 14);
	set_race("human");
	set_class("fighter");
	set_level(16);

	set_skill("sword", 50);
	set_skill("dodge", 35);
	set_skill("parry", 40);

	set("age", 25);
	set("gender", "male");
	set("long",
		"一名警覺的年輕哨兵站在瞭望塔上，手持長弓，目光銳利地掃視著\n"
		"遠方的地平線。他對值守任務極為認真，片刻也不敢懈怠。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"哨兵瞇眼眺望遠方，低聲道：那邊好像有動靜……\n",
		"哨兵挺直腰桿，警惕地注視著四周：站崗可不能打盹兒。\n",
		"哨兵摸了摸箭壺，喃喃道：但願今晚太平無事。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("broadsword"))->wield();
	carry_money("coin", 50);
}
