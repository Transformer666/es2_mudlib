// master.c -- 玄天教主 東方孤冥

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("東方孤冥", ({ "xuantian master", "master", "scholar", "dongfang" }));
	set("nickname", "玄天教主");
	set_attr("str", 20);
	set_attr("dex", 27);
	set_attr("int", 29);
	set_attr("wis", 26);
	set_attr("spi", 24);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 20);
	set_race("human");
	set_level(40);
	set_class("scholar");
	set("sect", "玄天教");
	set("rank", "教主");
	set("title", "玄天教主");

	set_skill("unarmed", 60);
	set_skill("dodge", 120);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("xuantian force", 120);
	set_skill("sword", 150);
	set_skill("xuantian-sword", 150);
	map_skill("force", "xuantian force");
	map_skill("sword", "xuantian-sword");

	advance_stat("gin", 220);
	advance_stat("kee", 200);
	advance_stat("sen", 220);

	set("age", 49);
	set("long",
		"這位便是玄天教主東方孤冥﹐一襲玄色長衫﹐頭束玄玉冠﹐腰間\n"
		"斜佩著一柄古樸的長劍。他面容清癯﹐三縷長鬚飄拂胸前﹐一雙\n"
		"眸子幽深如夜﹐顧盼之間既有書生的儒雅﹐又隱隱透著一股看透\n"
		"世情的冷峻。玄天教書生一脈外託遊學論道之名﹐內操四廠諜報\n"
		"之實﹐教主浸淫玄天劍法與觀星問道之術數十年﹐一身文武已臻\n"
		"化境﹐料敵機先、來去無蹤﹐江湖人只聞其名而難見其面。他平\n"
		"日在玄天殿中參星論道、運籌帷幄﹐唯有心思靈巧、悟性不俗的\n"
		"後輩﹐方有機會拜入門下﹐習得這一身玄天劍法。\n");
	setup();
	carry_object("/d/snow/npc/obj/silversword")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("東方孤冥輕拂長鬚﹐淡淡說道﹕你既已入別派﹐道途已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("東方孤冥微微一笑﹕你塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 玄天劍法全憑悟性參詳﹐觀星問道、料敵機先﹐悟性過低者難窺門徑。
	if( me->query_attr("int") < 14 ) {
		do_chat("東方孤冥端詳了你一會﹐搖頭道﹕你悟性閉塞﹐難參我這路劍法。\n");
		return 0;
	}

	do_chat(({
		"東方孤冥幽深的目光在你身上停了停﹐微微頷首。\n",
		"東方孤冥說道﹕我玄天教書生一脈﹐外托論道、內藏機鋒﹐你可有這份慧心與城府﹖\n",
		"東方孤冥緩緩說道﹕也罷﹐你既悟性不俗﹐我便收你入玄天門下﹐傳你玄天劍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("東方孤冥拂了拂長袖﹐淡淡說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("scholar");
		me->set("sect", "玄天教");
		me->set("rank", "散人");
		me->set("title", "玄天教散人");

		me->set_skill("sword", 0);
		me->set_skill("xuantian-sword", 0);
		me->map_skill("sword", "xuantian-sword");

		// 同時授予玄天心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("xuantian force", 0);
		me->map_skill("force", "xuantian force");

		message_vision(
			"$N取過一柄長劍﹐將玄天劍法的入門劍訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"東方孤冥說道﹕從今日起﹐你便是我玄天教散人門下的弟子了。\n",
			"東方孤冥說道﹕劍道無涯﹐機鋒無形﹐你且到演武場勤加錘鍊﹐莫負了這身玄天劍法。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
