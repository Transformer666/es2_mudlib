// master.c -- 虎刀門門主 高慎

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("高慎", ({ "hudao master", "master", "gaoshen" }));
	set("nickname", "嘯林刀王");
	set_attr("str", 26);
	set_attr("dex", 24);
	set_attr("int", 21);
	set_attr("wis", 22);
	set_attr("spi", 23);
	set_attr("cps", 24);
	set_attr("con", 25);
	set_attr("cor", 25);
	set_race("human");
	set_level(40);
	set_class("fighter");
	set("sect", "虎刀門");
	set("rank", "門主");

	set_skill("unarmed", 80);
	set_skill("blade", 150);
	set_skill("parry", 120);
	set_skill("dodge", 110);
	set_skill("force", 120);
	set_skill("bawang blade", 150);
	set_skill("hudao force", 120);
	map_skill("blade", "bawang blade");
	map_skill("force", "hudao force");

	advance_stat("gin", 220);
	advance_stat("kee", 220);
	advance_stat("sen", 220);

	set("age", 49);
	set("long",
		"這位便是虎刀門門主高慎﹐身形魁梧如鐵塔﹐一身洗得發白的玄\n"
		"色勁裝裹著虬結的筋肉﹐左頰一道斜貫眉梢的舊刀疤﹐使那張本就剽\n"
		"悍的臉愈顯兇煞。他背負一口烏沉沉的厚背快刀﹐按刀而立﹐眉宇間\n"
		"自有一股嘯傲山林的霸烈之氣。虎刀門深藏老松林中﹐以一脈剛猛無\n"
		"匹的霸王刀招威震一方﹐高慎自幼在這林裡與猛虎搏命﹐悟出刀如虎\n"
		"撲、快狠決絕的刀道﹐江湖中人敬畏地喚他一聲「嘯林刀王」。他收\n"
		"徒不問出身﹐只重一個「膽」字﹐唯有心性剽悍、敢於亮刀的後生﹐\n"
		"方有機緣入他門下﹐習得這一身殺伐果決的快刀。\n");
	setup();
	carry_object("/obj/area/obj/blade")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("高慎冷笑一聲﹐說道﹕你既已入了別派﹐還來我虎刀門攪甚麼局﹖\n");
		return 0;
	}

	// 須略有歷練方可習刀
	if( me->query_level() < 1 ) {
		do_chat("高慎瞥了你一眼﹐說道﹕乳臭未乾的雛兒﹐且去江湖上滾過幾遭再來罷。\n");
		return 0;
	}

	// 虎刀門的刀剛猛霸烈﹐膽魄與筋力不足者﹐握不住這一口快刀。
	if( me->query_attr("str") < 14 && me->query_attr("cor") < 14 ) {
		do_chat("高慎按刀打量了你半晌﹐搖頭道﹕你筋骨綿軟、膽氣不足﹐提不動我虎刀門這口快刀。\n");
		return 0;
	}

	do_chat(({
		"高慎按著刀柄上下打量了你一番﹐眼中精光一閃。\n",
		"高慎喝道﹕我虎刀門的刀﹐講究一個「快」、一個「狠」﹐亮刀便要見血﹐你可有這份膽氣﹖\n",
		"高慎放聲大笑﹕好﹗我便收你做個記名弟子﹐傳你霸王刀招。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("高慎把手一揮﹐喝道﹕你既已另投他師﹐滾罷。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("fighter");
		me->set("sect", "虎刀門");
		me->set("rank", "護衛");
		me->set("title", "虎刀門護衛");

		me->set_skill("blade", 0);
		me->set_skill("bawang blade", 0);
		me->map_skill("blade", "bawang blade");

		// 同時授予虎刀門內功﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("hudao force", 0);
		me->map_skill("force", "hudao force");

		message_vision(
			"$N抄起一口快刀﹐將霸王刀招的入門刀訣一招一式地劈砍給$n看。\n",
			this_object(), me);
		do_chat(({
			"高慎喝道﹕從今日起﹐你便是我虎刀門的護衛了。\n",
			"高慎說道﹕刀道無他﹐唯快不破、唯狠制敵﹐你且到演武場去把這口刀劈到出神入化﹗\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
