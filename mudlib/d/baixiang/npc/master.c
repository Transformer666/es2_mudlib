// master.c -- 白象寺方丈

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("白象寺方丈", ({ "bonze master", "master", "monk", "abbot" }));
	set("nickname", "伏魔尊者");
	set_attr("str", 26);
	set_attr("dex", 22);
	set_attr("int", 22);
	set_attr("wis", 26);
	set_attr("spi", 24);
	set_attr("cps", 24);
	set_attr("con", 25);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("bonze");
	set("sect", "白象寺");
	set("rank", "方丈");
	set("title", "白象寺方丈");

	set_skill("unarmed", 80);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("staff", 150);
	set_skill("rid-evil", 150);
	set_skill("buddhism", 120);
	map_skill("staff", "rid-evil");
	map_skill("force", "buddhism");

	advance_stat("gin", 220);
	advance_stat("kee", 220);
	advance_stat("sen", 240);

	set("age", 62);
	set("long",
		"這位便是白象寺的方丈﹐一身灰色僧袍洗得發白﹐袒露的右肩與胸\n"
		"膛肌肉虯結﹐手中橫持一根烏沉沉的禪杖﹐杖頭銅環輕響。他面容慈\n"
		"和﹐雙目卻精光內斂﹐顧盼之間隱隱透著一股降魔伏邪的金剛之氣。\n"
		"白象寺羅漢一脈以杖法降魔證道﹐方丈浸淫金剛伏魔杖法數十年﹐一\n"
		"身武功已臻化境﹐江湖人稱「伏魔尊者」。他平日在大雄寶殿中講經\n"
		"說法﹐唯有心懷慈悲、根骨不俗的後輩﹐方有機會拜入門下﹐習得這\n"
		"一身降魔伏邪的羅漢杖法。\n");
	setup();
	carry_object("/d/snow/npc/obj/cane")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("白象寺方丈雙手合十﹐宣了聲佛號﹕施主既已入別派﹐緣分已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("白象寺方丈微笑道﹕施主塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 羅漢杖法須以慈悲心降魔﹐慧根過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("wis") < 14 ) {
		do_chat("白象寺方丈端詳了你一會﹐搖頭道﹕施主慧根閉塞﹐難參我這路佛法。\n");
		return 0;
	}

	do_chat(({
		"白象寺方丈上下打量了你一番﹐微微頷首。\n",
		"白象寺方丈道﹕我白象寺羅漢一脈﹐以杖降魔﹐施主可有這份慈悲心﹖\n",
		"白象寺方丈宣了聲佛號﹕善哉善哉﹐你既與我佛有緣﹐老衲便收你入羅漢門下﹐傳你金剛伏魔杖法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("白象寺方丈雙手合十﹐道﹕施主既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("bonze");
		me->set("sect", "白象寺");
		me->set("rank", "羅漢");
		me->set("title", "白象寺羅漢");

		me->set_skill("staff", 0);
		me->set_skill("rid-evil", 0);
		me->map_skill("staff", "rid-evil");

		message_vision(
			"$N取過一根禪杖﹐將金剛伏魔杖法的入門杖訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"白象寺方丈宣了聲佛號﹕從今日起﹐你便是我白象寺羅漢門下的弟子了。\n",
			"白象寺方丈道﹕武學無涯﹐你且到演武場勤加錘鍊﹐莫負了這身杖法。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
