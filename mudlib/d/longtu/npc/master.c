// master.c -- 龍圖丹派掌門神醫

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("龍圖丹師", ({ "alchemist master", "master", "physician", "doctor" }));
	set("nickname", "杏林神醫");
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
	set("sect", "龍圖丹派");
	set("rank", "掌門");
	set("title", "龍圖丹派掌門神醫");

	set_skill("unarmed", 50);
	set_skill("dodge", 100);
	set_skill("parry", 80);
	set_skill("force", 120);
	set_skill("dragon force", 120);
	set_skill("needle", 150);
	set_skill("amazing-needle", 150);
	set_skill("alchemy-medication", 150);
	map_skill("force", "dragon force");
	map_skill("needle", "amazing-needle");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 58);
	set("long",
		"這位便是龍圖丹派的掌門神醫﹐一身青布道袍洗得發白﹐鬚眉皆已\n"
		"花白﹐面色卻紅潤如嬰﹐雙目溫和而有神。他腰間懸著一只盛放銀\n"
		"針的錦匣﹐袖中常帶藥香。龍圖丹派以煉丹施針、懸壺濟世名動江\n"
		"湖﹐掌門浸淫龍圖心經與武陀灸術數十年﹐一手驚異二針出神入化\n"
		"﹐針到病除﹐活人無數﹐江湖人尊稱一聲「杏林神醫」。他久居醫\n"
		"館坐堂施診﹐唯有心存仁念、悟性不俗的後輩﹐方有機會拜入門下\n"
		"﹐習得這一身濟世活人的醫術針法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("龍圖丹師捻著鬚﹐溫言道﹕你既已入別派﹐醫緣已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("龍圖丹師說道﹕你塵緣未歷﹐且去江湖上走動一番再來罷。\n");
		return 0;
	}

	// 醫道針法全憑一身悟性參詳﹐悟性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("int") < 14 ) {
		do_chat("龍圖丹師端詳了你一會﹐搖頭道﹕你悟性閉塞﹐難參經絡藥性之奧﹐學不來我這路醫術。\n");
		return 0;
	}

	do_chat(({
		"龍圖丹師上下打量了你一番﹐微微頷首。\n",
		"龍圖丹師說道﹕我龍圖丹派以針藥濟世﹐你可有這份救人的仁心﹖\n",
		"龍圖丹師捻鬚一笑﹕也罷﹐你既心存仁念、悟性不俗﹐我便收你為徒﹐傳你這一身醫術針法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("龍圖丹師擺了擺手﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("alchemist");
		me->set("sect", "龍圖丹派");
		me->set("rank", "醫師");
		me->set("title", "龍圖丹派醫師");

		me->set_skill("needle", 0);
		me->set_skill("amazing-needle", 0);
		me->map_skill("needle", "amazing-needle");

		// 同時授予龍圖心經（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("dragon force", 0);
		me->map_skill("force", "dragon force");

		message_vision(
			"$N取出一匣銀針﹐捻起一枚﹐將武陀灸術【驚異二針】的入門針法一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"龍圖丹師說道﹕從今日起﹐你便是我龍圖丹派醫師門下的弟子了。\n",
			"龍圖丹師叮囑道﹕醫者父母心﹐你且到演武場對著銅人勤練針法﹐辨穴施針﹐莫負了這身醫術。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
