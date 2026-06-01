// icemaster.c -- 天師派素衣真人（冰道師父）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("素衣真人", ({ "frost priest", "suyi", "icemaster" }));
	set("nickname", "素衣真人");
	set_attr("str", 20);
	set_attr("dex", 22);
	set_attr("int", 26);
	set_attr("wis", 25);
	set_attr("spi", 28);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("taoist");
	set("sect", "天師派");
	set("rank", "素衣長老");
	set("title", "天師派素衣長老");

	set_skill("unarmed", 60);
	set_skill("dodge", 100);
	set_skill("parry", 90);
	set_skill("force", 120);
	set_skill("magic", 150);
	set_skill("taoism-freeze", 150);
	map_skill("magic", "taoism-freeze");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 54);
	set("long",
		"這位便是天師派素衣一脈的真人﹐一身素白道袍纖塵不染﹐頭戴蓮\n"
		"花冠﹐手執一柄玉柄拂塵﹐面如冠玉﹐雙目清冷如水﹐周身隱隱透著一\n"
		"股沁人的寒氣。天師派素衣一脈以冰證道﹐素衣真人浸淫冰術數十年﹐\n"
		"一身道法已臻化境﹐江湖人稱「素衣真人」。他久居素心軒中靜參大道\n"
		"﹐唯有靈性不俗、心性沉靜的後輩﹐方有機會拜入素衣門下﹐習得這一\n"
		"身凝霜封脈的道法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("素衣真人輕拂拂塵﹐說道﹕你既已入別派﹐道緣已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入道
	if( me->query_level() < 1 ) {
		do_chat("素衣真人說道﹕你塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 冰術全憑靈性引動﹐靈性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("spi") < 14 ) {
		do_chat("素衣真人端詳了你一會﹐搖頭道﹕你靈性閉塞﹐與冰無緣﹐難學我這路道法。\n");
		return 0;
	}

	do_chat(({
		"素衣真人上下打量了你一番﹐微微頷首。\n",
		"素衣真人說道﹕我天師派素衣一脈﹐以冰證道﹐你可有這份道心﹖\n",
		"素衣真人說道﹕也罷﹐你既與冰有緣﹐我便收你入素衣門下﹐傳你天師道法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("素衣真人揮了揮拂塵﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("taoist");
		me->set("sect", "天師派");
		me->set("rank", "素衣弟子");
		me->set("title", "天師派素衣弟子");

		me->set_skill("magic", 0);
		me->set_skill("taoism-freeze", 0);
		me->map_skill("magic", "taoism-freeze");

		// 同時授予冰蠶奇功（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("polar-silkworm force", 0);
		me->map_skill("force", "polar-silkworm force");

		message_vision(
			"$N取過一道素符﹐將天師道法【冰咒】的入門口訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"素衣真人說道﹕從今日起﹐你便是我天師派素衣門下的弟子了。\n",
			"素衣真人說道﹕道法無涯﹐你且到素心軒對冰參修﹐莫負了這身道法。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
