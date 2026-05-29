// master.c -- 天師派掌教真人

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("天師掌教", ({ "taoist master", "master", "priest" }));
	set("nickname", "朱衣真人");
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
	set("rank", "掌教");
	set("title", "天師派掌教真人");

	set_skill("unarmed", 60);
	set_skill("dodge", 100);
	set_skill("parry", 90);
	set_skill("force", 120);
	set_skill("magic", 150);
	set_skill("taoism-fire", 150);
	map_skill("magic", "taoism-fire");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 56);
	set("long",
		"這位便是天師派的掌教真人﹐一身朱紅道袍﹐頭戴蓮花冠﹐手執一\n"
		"柄拂塵﹐面色紅潤﹐雙目炯炯有神﹐周身隱隱透著一股溫煦的火氣。天\n"
		"師派朱衣一脈以火證道﹐掌教真人浸淫火術數十年﹐一身道法已臻化境\n"
		"﹐江湖人稱「朱衣真人」。他久居三清殿中潛修大道﹐唯有靈性不俗、\n"
		"與火有緣的後輩﹐方有機會拜入朱衣門下﹐習得這一身焚天煉地的道法\n"
		"。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("天師掌教輕拂拂塵﹐說道﹕你既已入別派﹐道緣已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入道
	if( me->query_level() < 1 ) {
		do_chat("天師掌教說道﹕你塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 火術全憑靈性引動﹐靈性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("spi") < 14 ) {
		do_chat("天師掌教端詳了你一會﹐搖頭道﹕你靈性閉塞﹐與火無緣﹐難學我這路道法。\n");
		return 0;
	}

	do_chat(({
		"天師掌教上下打量了你一番﹐微微頷首。\n",
		"天師掌教說道﹕我天師派朱衣一脈﹐以火證道﹐你可有這份道心﹖\n",
		"天師掌教說道﹕也罷﹐你既與火有緣﹐我便收你入朱衣門下﹐傳你天師道法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("天師掌教揮了揮拂塵﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("taoist");
		me->set("sect", "天師派");
		me->set("rank", "朱衣弟子");
		me->set("title", "天師派朱衣弟子");

		me->set_skill("magic", 0);
		me->set_skill("taoism-fire", 0);
		me->map_skill("magic", "taoism-fire");

		// 同時授予丹陽神功（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("sun force", 0);
		me->map_skill("force", "sun force");

		message_vision(
			"$N取過一道朱符﹐將天師道法【火術】的入門口訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"天師掌教說道﹕從今日起﹐你便是我天師派朱衣門下的弟子了。\n",
			"天師掌教說道﹕道法無涯﹐你且到演法場對火參修﹐莫負了這身道法。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
