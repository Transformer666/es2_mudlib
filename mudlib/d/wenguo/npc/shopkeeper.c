// NPC: /d/wenguo/npc/shopkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("書鋪掌櫃", ({"shopkeeper", "book seller"}));
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 55);
	set("gender", "male");
	set("long",
		"一個鬚髮花白的老者﹐鼻樑上架著一副老花眼鏡﹐正埋頭翻閱\n"
		"一本泛黃的古書。他是這間書鋪的掌櫃﹐學問淵博﹐對各種典籍瞭\n"
		"若指掌﹐常有學子前來向他請教。你可以用 list 看看他賣些什麼﹐\n"
		"用 buy 購買。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"書鋪掌櫃翻了一頁書﹐搖頭嘆道﹕如今肯靜下心讀書的人越來越少了。\n",
		"書鋪掌櫃說道﹕書中自有黃金屋﹐書中自有顏如玉啊。\n",
		"書鋪掌櫃推了推眼鏡﹐繼續埋頭看書。\n",
	}));
	set("merchandise", ([
		STOCK_ITEM("ration") : 40,
		STOCK_ITEM("torch") : 20,
	]));

	setup();
	carry_money("coin", 150);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("書鋪掌櫃驚道﹕斯文掃地﹗你怎可在書鋪動粗﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say " + item->name() + "﹐好﹐拿去吧。");
	::deliver_merchandise(customer, item);
}
