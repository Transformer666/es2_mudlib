// master.c -- 武陀灸堂香主 鬼華陀 武道通

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("武道通", ({ "wuto master", "master", "physician", "wudaotong" }));
	set("nickname", "鬼華陀");
	set_attr("str", 18);
	set_attr("dex", 26);
	set_attr("int", 28);
	set_attr("wis", 26);
	set_attr("spi", 25);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 24);
	set_race("human");
	set_level(40);
	set_class("alchemist");
	set("sect", "武陀灸堂");
	set("rank", "香主");
	set("title", "武陀灸堂香主鬼華陀");

	set_skill("unarmed", 50);
	set_skill("dodge", 100);
	set_skill("parry", 80);
	set_skill("force", 120);
	set_skill("wuto force", 120);
	set_skill("needle", 150);
	set_skill("wuto-needle", 150);
	set_skill("alchemy-medication", 150);
	map_skill("force", "wuto force");
	map_skill("needle", "wuto-needle");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 61);
	set("long",
		"這位便是武陀灸堂的香主﹐人稱「鬼華陀」武道通。他一身洗得發\n"
		"白的灰布長衫﹐鬚眉如戟﹐面色黝黑而目光如炬﹐腰間懸著一只盛\n"
		"放銀針的烏木匣﹐袖中常帶艾草的辛香。武陀灸堂以針灸艾灸救死\n"
		"扶傷名動江湖﹐香主浸淫武陀灸術數十年﹐一手五敗針法辨穴如神\n"
		"﹐針到病除﹐又能以針克敵、封脈截經﹐活人無數而罕逢敵手。他\n"
		"久居灸堂坐堂施診﹐唯有心存仁念、悟性不俗的後輩﹐方有機會拜\n"
		"入門下﹐習得這一身濟世活人的灸術針法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("武道通捻著鬚﹐沉聲道﹕你既已入別派﹐醫緣已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("武道通說道﹕你塵緣未歷﹐且去江湖上走動一番再來罷。\n");
		return 0;
	}

	// 灸術針法全憑一身悟性參詳﹐悟性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("int") < 14 ) {
		do_chat("武道通端詳了你一會﹐搖頭道﹕你悟性閉塞﹐難參經絡穴道之奧﹐學不來我這路灸術。\n");
		return 0;
	}

	do_chat(({
		"武道通上下打量了你一番﹐微微頷首。\n",
		"武道通說道﹕我武陀灸堂以針艾濟世﹐你可有這份救人的仁心﹖\n",
		"武道通捻鬚一笑﹕也罷﹐你既心存仁念、悟性不俗﹐我便收你為徒﹐傳你這一身灸術針法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("武道通擺了擺手﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("alchemist");
		me->set("sect", "武陀灸堂");
		me->set("rank", "香主弟子");
		me->set("title", "武陀灸堂香主弟子");

		me->set_skill("needle", 0);
		me->set_skill("wuto-needle", 0);
		me->map_skill("needle", "wuto-needle");

		// 同時授予武陀心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("wuto force", 0);
		me->map_skill("force", "wuto force");

		message_vision(
			"$N取出一匣銀針﹐捻起一枚﹐將武陀灸術【五敗針法】的入門針法一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"武道通說道﹕從今日起﹐你便是我武陀灸堂香主門下的弟子了。\n",
			"武道通叮囑道﹕醫者父母心﹐你且到演武場對著銅人勤練針法﹐辨穴施針﹐莫負了這身灸術。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
