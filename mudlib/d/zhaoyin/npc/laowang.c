// laowang.c -- 老王燒烤的攤主老王（F_VENDOR 供應既有的食物物件）

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("烤肉攤主", ({ "laowang", "lao wang", "vendor", "cook" }) );
	set("nickname", "老王");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 44);
	set("gender", "male");
	set("long",
		"這便是兆隱縣城裡無人不曉的老王了。他是個敞著懷的胖漢\n"
		"子﹐圓滾滾的肚皮上繫著條油得發亮的圍裙﹐一張紅臉膛被炭\n"
		"火燻得油光發亮﹐笑起來一臉的褶子。他一手執扇搧火﹐一手\n"
		"翻著肉串﹐忙得不亦樂乎。你可以用 list 看他烤些什麼﹐用\n"
		"buy 向他買來吃。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老王把肉串翻了個面﹐扯著嗓子吆喝﹕新鮮出爐的烤肉哩﹐外焦裡嫩﹐客官來上幾串﹖\n",
		"老王搧著炭火﹐笑呵呵地道﹕咱這手藝﹐方圓百里可是獨一份﹐打喬陰縣都有人專程來嚐哩﹗\n",
		"老王抹了把汗﹐嘟囔道﹕這炭火可真旺﹐烤得我這身肉都快熟嘍﹗\n",
	}));
	// 燒烤攤﹐沿用既有的食物物件販售（烤肉饅頭餃子之屬）。
	set("merchandise", ([
		"/obj/food/pork" : 35,
		"/obj/food/manto" : 25,
		"/obj/food/dumpling" : 30,
	]));

	setup();
	carry_money("coin", 80);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("老王把蒲扇一撂﹐瞪眼嚷道﹕哎喲喂﹗光天化日的﹐衝我這賣烤肉的撒甚麼野﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
