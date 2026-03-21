// NPC: /d/lijun/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("掌櫃", ({"innkeeper", "boss"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一個精瘦的中年男子﹐穿著一件洗得發白的灰布長衫﹐腰間繫\n"
		"著一條圍裙。他是清月樓的掌櫃﹐雖然話不多﹐但眼神精明﹐把客\n"
		"棧的帳目管理得井井有條。你可以用 list 看看他賣些什麼。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐嘴裡唸唸有詞。\n",
		"掌櫃擦了擦櫃臺﹐招呼道﹕客倌﹐需要些什麼﹖\n",
		"掌櫃嘆道﹕這年頭生意不好做啊﹐過路客越來越少了。\n",
	}));
	set("merchandise", ([
		STOCK_ITEM("ration") : 50,
		STOCK_ITEM("torch") : 50,
	]));

	setup();
	carry_money("coin", 80);
}

int accept_fight(object ob)
{
	do_chat("掌櫃連忙後退一步﹕客倌息怒﹐有話好說﹐有話好說﹗\n");
	return 0;
}
