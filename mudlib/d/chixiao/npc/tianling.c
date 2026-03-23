// NPC: /d/chixiao/npc/tianling.c - 天靈 Boss NPC
// Quest-triggered: summoned by throwing 3 elemental weapons into wishing pool

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("天靈", ({"tianling", "tian_ling"}));
	set_attr("str", 28);
	set_attr("dex", 30);
	set_attr("con", 26);
	set_attr("int", 25);
	set_attr("wis", 22);
	set_attr("spi", 30);
	set_attr("cps", 28);
	set_race("spirit");
	set_class("warrior");
	set_level(70);

	set_skill("dagger", 120);
	set_skill("unarmed", 100);
	set_skill("dodge", 110);
	set_skill("parry", 100);
	set_skill("force", 110);
	set_skill("dragon force", 120);
	map_skill("force", "dragon force");

	advance_stat("gin", 300);
	advance_stat("kee", 300);
	advance_stat("sen", 200);

	set("age", 0);
	set("gender", "male");
	set("attitude", "aggressive");
	set("long",
		"一道耀眼的光芒凝聚成人形﹐這就是傳說中的天靈。他的身軀\n"
		"半透明﹐散發著淡淡的金色光芒﹐五官輪廓隱約可見﹐卻又不甚\n"
		"真實。他的雙眼如同兩顆燃燒的星辰﹐令人不敢直視。天靈的周\n"
		"圍環繞著一股強大的靈力﹐空氣中瀰漫著一種令人窒息的壓迫感。\n");

	set("chat_chance_combat", 8);
	set("chat_msg_combat", ({
		"天靈發出一聲長嘯﹐一道金光劈向你﹗\n",
		"天靈冷冷地說道﹕凡人竟敢驚擾本靈﹗\n",
		"天靈周身金光大盛﹐一股強大的靈壓向四周擴散開來。\n",
	}));

	setup();
	carry_object(STOCK_WEAPON("dagger"))->wield();
	set_temp("apply/vision_of_ghost", 1);
}

void die(object killer)
{
	object dagger, eye;

	if( killer && userp(killer) ) {
		tell_object(killer,
			"天靈的身軀漸漸消散﹐化為點點金光。\n"
			"一把閃爍著靈光的匕首和一顆散發著柔和光芒的靈眼\n"
			"從光芒中緩緩落下。\n");

		if( !killer->query("quest/tianling_summon_done") ) {
			killer->set("quest/tianling_summon_done", 1);
			killer->gain_score("quest", 300);
			killer->delete_temp("pending/tianling_summon_fighting");
			killer->delete_temp("pending/tianling_offerings");
			tell_object(killer,
				"你感到一股溫暖的靈力湧入體內﹐天靈的力量認可了你。\n");
		}

		dagger = new(__DIR__"obj/tianling_dagger");
		if( dagger ) {
			if( dagger->move(killer) )
				dagger->move(environment());
		}

		eye = new(__DIR__"obj/tianling_eye");
		if( eye ) {
			if( eye->move(killer) )
				eye->move(environment());
		}
	}
	::die(killer);
}
