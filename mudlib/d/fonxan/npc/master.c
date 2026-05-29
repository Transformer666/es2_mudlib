// master.c -- 封山派掌門 柳東蘆

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("柳東蘆", ({ "fonxan master", "master", "sword sage" }));
	set("nickname", "青嶂劍翁");
	set_attr("str", 24);
	set_attr("dex", 25);
	set_attr("int", 22);
	set_attr("wis", 24);
	set_attr("spi", 23);
	set_attr("cps", 24);
	set_attr("con", 23);
	set_attr("cor", 24);
	set_race("human");
	set_level(40);
	set_class("fighter");
	set("sect", "封山派");
	set("rank", "掌門");

	set_skill("unarmed", 80);
	set_skill("sword", 150);
	set_skill("parry", 120);
	set_skill("dodge", 110);
	set_skill("force", 120);
	set_skill("fonxansword", 150);
	set_skill("fonxanforce", 120);
	map_skill("sword", "fonxansword");
	map_skill("force", "fonxanforce");

	advance_stat("gin", 220);
	advance_stat("kee", 220);
	advance_stat("sen", 220);

	set("age", 54);
	set("long",
		"這位便是封山派掌門柳東蘆﹐一襲洗得發白的青布長衫﹐身形清\n"
		"癯而挺拔﹐腰間懸著一柄不起眼的長劍﹐然舉手投足之間自有一股淵\n"
		"渟嶽峙的氣度。封山派是喬陰城東青嶂峰上聲名素著的劍派﹐掌門自\n"
		"幼苦修封山劍法﹐劍勢如山嶽巍然﹐守若磐石﹐攻似奔雷﹐講究以靜\n"
		"制動、以正禦邪﹐江湖人尊稱一聲「青嶂劍翁」。他平日深居山中﹐\n"
		"潛心劍道﹐唯有心性端方、根骨堪造的後輩﹐方有機會拜入門下﹐習\n"
		"得這一身守正不阿的劍法。\n");
	setup();
	carry_object("/d/snow/npc/obj/silversword")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("柳東蘆搖了搖頭﹐說道﹕你既已入別派﹐何苦再來攪擾﹖\n");
		return 0;
	}

	// 須年滿一定等級﹐心性沉穩方可習劍
	if( me->query_level() < 1 ) {
		do_chat("柳東蘆說道﹕你根基未穩﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 封山劍法守正剛猛﹐膽魄不足者持劍不穩﹐難承這一脈的劍意
	if( me->query_attr("cor") < 14 ) {
		do_chat("柳東蘆端詳了你一會﹐說道﹕你心性怯懦﹐握不住這一柄守山的劍。\n");
		return 0;
	}

	do_chat(({
		"柳東蘆上下打量了你一番﹐微微頷首。\n",
		"柳東蘆說道﹕我封山派的劍法﹐講究一個「守」字﹐守山、守正、守心﹐你可受得了這份清苦﹖\n",
		"柳東蘆說道﹕也罷﹐我便收你做個記名弟子﹐傳你封山劍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("柳東蘆揮了揮手﹐說道﹕你既已另投他師﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("fighter");
		me->set("sect", "封山派");
		me->set("rank", "劍客");
		me->set("title", "封山派劍客");

		me->set_skill("sword", 0);
		me->set_skill("fonxansword", 0);
		me->map_skill("sword", "fonxansword");

		// 同時授予封山派內功﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("fonxanforce", 0);
		me->map_skill("force", "fonxanforce");

		message_vision(
			"$N取過一柄長劍﹐將封山劍法的入門劍訣一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"柳東蘆說道﹕從今日起﹐你便是我封山派的劍客了。\n",
			"柳東蘆說道﹕劍道如山﹐你且到演武場勤加練習﹐守得住劍﹐方守得住心。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
