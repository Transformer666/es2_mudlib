// taoist.c

#include <npc.h>

inherit F_SCHOLAR;

void create()
{
	set_name("安懶道人", ({"taoist", "anlan"}));
	set_attr("str", 20);
	set_attr("con", 25);
	set_attr("dex", 30);
	set_race("human");
	set_class("taoist");
	set_level(40);

	set_skill("sword", 120);
	set_skill("dodge", 110);
	set_skill("parry", 100);
	set_skill("internal", 100);

	set("age", 65);
	set("long",
		"一個身穿舊道袍的老道士﹐鶴髮童顏﹐面帶微笑。他手持一柄\n"
		"拂塵﹐腳踩布鞋﹐看起來懶洋洋的﹐似乎隨時都要打瞌睡。但他\n"
		"偶爾一閃的目光卻精芒四射﹐顯然是個深藏不露的高手。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"安懶道人打了個哈欠﹐自言自語道﹕無量天尊﹐又是無聊的一天。\n",
		"安懶道人靠在藤椅上﹐似睡非睡﹐嘴角掛著一絲笑意。\n",
		"安懶道人忽然睜開眼睛﹐念道﹕道可道﹐非常道……接著又閉上了眼。\n",
	}));
	setup();
	carry_money("coin", 200);
	set_temp("apply/vision_of_ghost", 1);
}
