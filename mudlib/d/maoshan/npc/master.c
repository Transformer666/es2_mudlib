// master.c -- 茅山派掌教真人

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("茅山掌教", ({ "maoshan master", "master", "priest", "taoist", "maoshan" }));
	set("nickname", "青霞真人");
	set_attr("str", 20);
	set_attr("dex", 22);
	set_attr("int", 28);
	set_attr("wis", 26);
	set_attr("spi", 28);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("taoist");
	set("sect", "茅山派");
	set("rank", "掌教");
	set("title", "茅山派掌教真人");

	set_skill("unarmed", 60);
	set_skill("dodge", 100);
	set_skill("parry", 90);
	set_skill("force", 120);
	set_skill("dao force", 120);
	map_skill("force", "dao force");
	set_skill("magic", 150);
	set_skill("youmin", 150);
	map_skill("magic", "youmin");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 58);
	set("long",
		"這位便是茅山派的掌教真人﹐一身洗得發白的青布道袍﹐頭挽道髻﹐\n"
		"背插一柄桃木劍﹐面容清癯﹐雙目深邃如古井﹐周身隱隱繚繞著一縷化\n"
		"不開的霧氣。茅山一脈以符籙咒術名世﹐召雷喚風、驅鬼役神無所不能\n"
		"﹐掌教真人精研五行陰陽數十載﹐符到咒成﹐江湖人稱「青霞真人」。\n"
		"他久居三清殿中參研道法﹐唯有心性沉靜、與道有緣的後輩﹐方有機會\n"
		"拜入門下﹐習得這一身呼風喚雨的茅山道法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("茅山掌教捻著長鬚﹐說道﹕你既已入別派﹐道緣已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入道
	if( me->query_level() < 1 ) {
		do_chat("茅山掌教說道﹕你塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 符籙咒術全憑靈性與悟性引動﹐靈性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("spi") < 14 ) {
		do_chat("茅山掌教端詳了你一會﹐搖頭道﹕你靈性閉塞﹐難通鬼神之道﹐學不得我這路符籙。\n");
		return 0;
	}

	do_chat(({
		"茅山掌教上下打量了你一番﹐微微頷首。\n",
		"茅山掌教說道﹕我茅山一脈﹐以符籙咒術通鬼神、役五行﹐你可有這份道心﹖\n",
		"茅山掌教說道﹕也罷﹐你既與道有緣﹐我便收你入門下﹐傳你茅山道法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("茅山掌教拂了拂袖﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("taoist");
		me->set("sect", "茅山派");
		me->set("rank", "茅山弟子");
		me->set("title", "茅山派弟子");

		me->set_skill("magic", 0);
		me->set_skill("youmin", 0);
		me->map_skill("magic", "youmin");

		// 同時授予明道心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("dao force", 0);
		me->map_skill("force", "dao force");

		message_vision(
			"$N取過一道黃符﹐將茅山咒術【幽冥三箭】的入門口訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"茅山掌教說道﹕從今日起﹐你便是我茅山門下的弟子了。\n",
			"茅山掌教說道﹕道法無涯﹐你且到演法場對草人參修咒術﹐莫負了這身道法。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
