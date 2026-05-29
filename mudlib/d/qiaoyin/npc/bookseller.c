// bookseller.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("書商", ({ "bookseller", "vendor" }) );
	set_race("human");
	set_class("scholar");
	set_level(8);

	set("age", 58);
	set("gender", "male");
	set("long",
		"這位是喬陰書局的老書商﹐頭戴方巾﹐身著一襲洗得發白的青\n"
		"衫﹐手裡總捧著一卷書﹐說起話來文謅謅的﹐一派斯文。你可以\n"
		"用 list 看他賣些什麼書﹐用 buy 向他買書。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"書商捻著鬚﹐搖頭晃腦地低聲吟哦著手裡的書卷。\n",
		"書商和氣地說道﹕公子是來尋書的麼﹖小店藏書雖不算多﹐倒也頗有幾本值得一讀的。\n",
		"書商歎道﹕如今肯靜下心來讀書的人﹐是越發少了。\n",
		"書商說道﹕買了書﹐尋個清靜處 study 細讀﹐方不負這滿紙的學問。\n",
		"書商壓低嗓子道﹕架上還有幾本拳、劍、刀、棍的武功秘笈﹐都是粗淺入門的功夫﹐公子若有興致﹐倒可買去 study 揣摩揣摩。\n",
	}));
	// 喬陰書局販售幾種書冊﹕蒙書、詩抄可 study 增進學識﹐話本則供消遣﹐
	// 另有幾本基礎武功秘笈﹐供初窺武道者 study 入門 (拳、劍、刀、棍、內功)。
	// TODO: 日後可增設更深的武學秘笈、各色經史子集等書籍 (新建 obj)。
	set("merchandise", ([
		"/d/qiaoyin/obj/primer" : 30,
		"/d/qiaoyin/obj/poetry" : 20,
		"/d/qiaoyin/obj/storybook" : 40,
		"/d/qiaoyin/obj/fist_manual" : 5,
		"/d/qiaoyin/obj/sword_manual" : 5,
		"/d/qiaoyin/obj/blade_manual" : 5,
		"/d/qiaoyin/obj/staff_manual" : 5,
		"/d/qiaoyin/obj/force_manual" : 5,
	]));

	setup();
	carry_money("coin", 300);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("書商連忙護住書卷﹐賠笑道﹕斯文之地﹐動什麼粗﹖公子息怒、息怒﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
