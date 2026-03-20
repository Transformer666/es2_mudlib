// lidongling.c - 大魔頭李東靈

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("李東靈", ({"lidongling", "li dongling", "dongling", "li"}));
	set("nickname", "大魔頭");
	set_attr("str", 30);
	set_attr("dex", 28);
	set_attr("con", 28);
	set_attr("int", 26);
	set_attr("wis", 24);
	set_attr("spi", 26);
	set_attr("cps", 30);
	set_race("human");
	set_class("warrior");
	set_level(80);

	set_skill("sword", 130);
	set_skill("blade", 120);
	set_skill("unarmed", 110);
	set_skill("dodge", 120);
	set_skill("parry", 110);
	set_skill("force", 130);

	advance_stat("gin", 400);
	advance_stat("kee", 400);
	advance_stat("sen", 300);

	set("age", 50);
	set("gender", "male");
	set("attitude", "aggressive");
	set("long",
		"李東靈﹐人稱「大魔頭」﹐是當世武林中最令人畏懼的邪道高\n"
		"手。他身形高大﹐一襲血紅色的長袍﹐面容冷峻如鐵﹐雙目中透\n"
		"著嗜血的光芒。他的武功已臻化境﹐一身邪氣沖天﹐令人不寒而\n"
		"慄。據傳他曾單手滅了三個門派﹐江湖中人聞其名無不色變。\n");

	set("chat_chance_combat", 10);
	set("chat_msg_combat", ({
		"李東靈仰天長笑﹐笑聲中充滿了不屑﹕就憑你也想與我為敵？\n",
		"李東靈身形一閃﹐掌中凝聚著恐怖的邪氣﹗\n",
		"李東靈冷笑道﹕螻蟻之輩﹐不自量力﹗\n",
		"李東靈一掌拍出﹐空氣中發出爆裂的聲響﹗\n",
	}));

	set("chat_chance", 2);
	set("chat_msg", ({
		"李東靈冷冷地掃視著四周﹐目光如刀。\n",
		"李東靈輕嗤一聲﹐說道﹕這天下﹐遲早是我的。\n",
	}));

	setup();
	carry_object(__DIR__"obj/blood_blade")->wield();
	carry_money("gold", 200);
	set_temp("apply/vision_of_ghost", 1);
}

void die(object killer)
{
	if( killer && userp(killer) ) {
		tell_object(killer,
			"李東靈口吐鮮血﹐難以置信地瞪大了雙眼﹐說道﹕\n"
			"不可能 ... 我李東靈怎會敗在你手中 ...\n"
			"李東靈的身軀轟然倒地﹐一股強大的邪氣從他體內爆發出來﹐\n"
			"隨即漸漸消散。\n");
	}
	::die(killer);
}
