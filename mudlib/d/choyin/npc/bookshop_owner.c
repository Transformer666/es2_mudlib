// bookshop_owner.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("書肆掌櫃", ({"bookshop_owner", "owner", "shopkeeper"}));
	set_race("human");
	set_class("commoner");
	set_level(10);

	set("age", 45);
	set("long",
		"一個文質彬彬的中年人﹐身穿灰色長袍﹐鼻樑上架著一副銅框\n"
		"眼鏡﹐手中總是捧著一卷書。他說話慢條斯理﹐一看便知是個飽讀\n"
		"詩書的人。你可以用 list 看看書目﹐用 buy 購買。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"掌櫃翻了翻書頁﹐搖頭嘆道﹕如今讀書的人越來越少了。\n",
		"掌櫃推了推眼鏡﹐說道﹕本店書籍﹐童叟無欺。\n",
		"掌櫃小心翼翼地擦拭著一冊古書﹐神情專注。\n",
	}));
	set("merchandise", ([
		__DIR__"obj/book_erta" : 30,
		__DIR__"obj/book_erta2" : 30,
	]));

	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("掌櫃連忙擺手道﹕客倌﹐小店是做學問的地方﹐可不興動武﹗\n");
	return 0;
}

void deliver_merchandise(object customer, mixed item)
{
	command("say 好的﹐" + item->name() + "﹐請拿好。");
	::deliver_merchandise(customer, item);
}
