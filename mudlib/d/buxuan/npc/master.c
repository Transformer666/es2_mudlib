// master.c -- 步玄派掌門

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("步玄掌門", ({ "scholar master", "master", "scholar", "teacher" }));
	set("nickname", "玄機居士");
	set_attr("str", 20);
	set_attr("dex", 26);
	set_attr("int", 28);
	set_attr("wis", 25);
	set_attr("spi", 24);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("scholar");
	set("sect", "步玄派");
	set("rank", "掌門");
	set("title", "步玄派掌門");

	set_skill("unarmed", 60);
	set_skill("dodge", 120);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("myst-force", 120);
	set_skill("myst-steps", 120);
	set_skill("sword", 150);
	set_skill("buxuan-sword", 150);
	map_skill("force", "myst-force");
	map_skill("dodge", "myst-steps");
	map_skill("sword", "buxuan-sword");

	advance_stat("gin", 220);
	advance_stat("kee", 200);
	advance_stat("sen", 220);

	set("age", 52);
	set("long",
		"這位便是步玄派的掌門﹐一襲洗得發白的青布長衫﹐頭束方巾﹐手中\n"
		"輕搖一柄折扇﹐腰間斜佩著一柄古樸的長劍。他面容清癯﹐三縷長鬚\n"
		"飄拂胸前﹐雙目澄澈如水﹐顧盼之間既有書生的儒雅﹐又隱隱透著一\n"
		"股劍客的鋒芒。步玄派書生一脈以劍法佐控場、以文心參武道﹐掌門\n"
		"浸淫步玄劍法與乾坤三轉之術數十年﹐一身文武已臻化境﹐江湖人稱\n"
		"「玄機居士」。他平日在論劍堂中讀書論劍﹐唯有心思靈巧、悟性不\n"
		"俗的後輩﹐方有機會拜入門下﹐習得這一身步玄劍法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("步玄掌門輕搖折扇﹐說道﹕你既已入別派﹐道途已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("步玄掌門微笑道﹕你塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 步玄劍法全憑悟性參詳﹐悟性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("int") < 14 ) {
		do_chat("步玄掌門端詳了你一會﹐搖頭道﹕你悟性閉塞﹐難參我這路劍法。\n");
		return 0;
	}

	do_chat(({
		"步玄掌門上下打量了你一番﹐微微頷首。\n",
		"步玄掌門說道﹕我步玄派書生一脈﹐以劍佐文、以步藏機﹐你可有這份慧心﹖\n",
		"步玄掌門合扇笑道﹕也罷﹐你既悟性不俗﹐我便收你入步玄門下﹐傳你步玄劍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("步玄掌門搖了搖折扇﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("scholar");
		me->set("sect", "步玄派");
		me->set("rank", "居士");
		me->set("title", "步玄派居士");

		me->set_skill("sword", 0);
		me->set_skill("buxuan-sword", 0);
		me->map_skill("sword", "buxuan-sword");

		message_vision(
			"$N取過一柄長劍﹐將小步玄劍的入門劍訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"步玄掌門說道﹕從今日起﹐你便是我步玄派居士門下的弟子了。\n",
			"步玄掌門說道﹕劍道無涯﹐你且到演武場勤加錘鍊﹐莫負了這身劍法。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
