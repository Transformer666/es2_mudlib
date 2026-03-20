// NPC: /d/jingji/npc/official.c

#include <npc.h>

inherit F_SCHOLAR;

void create()
{
	set_name("師爺", ({"official", "shiye"}));
	set_attr("int", 22);
	set_attr("wis", 20);
	set_race("human");
	set_class("commoner");
	set_level(18);

	set_skill("unarmed", 30);
	set_skill("dodge", 40);

	set("age", 48);
	set("gender", "male");
	set("long",
		"一位身穿青色長袍的中年文士，面容清瘦，目光精明。他是衙門\n"
		"裡的師爺，專門替大人處理文書案牘。他手中拿著一卷公文，似乎\n"
		"正在核對什麼。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"師爺翻閱著手中的公文，不時皺眉搖頭。\n",
		"師爺提筆在公文上批註了幾個字。\n",
		"師爺低聲嘟囔道：這案子可不好辦啊……\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 200);
}

int accept_fight(object ob)
{
	do_chat("師爺驚道：你、你要做什麼？來人啊！\n");
	return 0;
}
