// vim: syntax=lpc
#include <npc.h>

inherit F_SCHOLAR;

void create()
{
	set_name("藏書長老", ({"librarian", "elder", "zhang_lao"}));
	set_attr("int", 20);
	set_attr("wis", 22);
	set_race("human");
	set_class("commoner");
	set_level(25);

	set_skill("sword", 50);
	set_skill("dodge", 40);
	set_skill("parry", 35);

	set("age", 60);
	set("gender", "male");
	set("long",
		"一位白髮蒼蒼的長老，目光銳利而深邃，負責管理封山派的劍譜\n"
		"與武學典籍。雖已退隱不再下山比武，但他對劍法的鑽研極深，門\n"
		"中弟子遇到劍術疑難時常來此請教。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"藏書長老翻開一卷泛黃的竹簡，仔細端詳著上面的劍招圖解。\n",
		"藏書長老輕聲嘆道：前輩的劍意，非一朝一夕能領悟啊。\n",
		"藏書長老提筆在書頁空白處批註了幾行小字。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 50);
}

int accept_fight(object ob)
{
	do_chat("藏書長老冷冷道：藏書閣內不得動武，出去。\n");
	return 0;
}
