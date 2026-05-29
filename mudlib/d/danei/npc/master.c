// master.c -- 大內巡院統領（大內徵兵官 李天剛）
//
// 大內巡院是京畿的軍人(soldier)門派﹐與雪亭鎮的振武軍營同為軍人一脈﹐
// 故本檔結構完全比照 d/zhenwu/npc/master.c﹐沿用既有的 soldier class﹐
// 只是兵器由龍神槍法(pike)改為大內劍法(sword)、內功由瘋虎功改為大內
// 罡氣(danei force)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("李天剛", ({ "danei master", "master", "li tiangang", "official" }));
	set("nickname", "巡院統領");
	set_attr("str", 28);
	set_attr("dex", 24);
	set_attr("int", 22);
	set_attr("wis", 22);
	set_attr("spi", 20);
	set_attr("cps", 24);
	set_attr("con", 26);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("soldier");
	set("sect", "大內巡院");
	set("rank", "大內高手");
	set("title", "大內巡院高手");

	set_skill("unarmed", 60);
	set_skill("dodge", 90);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("sword", 150);
	set_skill("danei sword", 150);
	map_skill("sword", "danei sword");
	set_skill("danei force", 120);
	map_skill("force", "danei force");

	advance_stat("gin", 240);
	advance_stat("kee", 240);
	advance_stat("sen", 160);

	set("age", 50);
	set("gender", "male");
	set("long",
		"這位便是大內巡院的統領李天剛﹐一身玄色勁裝外罩繡金的緋色\n"
		"罩甲﹐腰懸一柄三尺長劍﹐身形挺拔如鬆﹐按劍而立﹐自有一股久\n"
		"鎮禁中的森嚴威儀。他面容方正﹐劍眉斜飛入鬢﹐一雙鷹目精光內\n"
		"斂﹐顧盼之間透著緝事多年的精悍幹練。大內巡院統領一脈宿衛皇\n"
		"城、護駕緝兇﹐統領浸淫大內劍法數十年﹐一柄長劍守得帝都固若\n"
		"金湯﹐人稱「巡院統領」。他奉旨在此徵募新血﹐唯有身手矯健、\n"
		"忠勇可靠的後輩﹐方有機會拜入麾下﹐學得這一身護衛天家的本事。\n");
	setup();
	carry_object("/obj/area/obj/longsword")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("李天剛按劍肅然道﹕你既已入別派﹐宿衛之職難托﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可投軍宿衛
	if( me->query_level() < 1 ) {
		do_chat("李天剛上下打量了你一眼﹐喝道﹕乳臭未乾的雛兒﹐且去歷練一番再來投效罷。\n");
		return 0;
	}

	// 宿衛禁中全憑一身膂力與筋骨﹐孱弱者扛不起這份差事（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("str") < 14 ) {
		do_chat("李天剛搖頭道﹕你這身子骨連長劍都使不穩﹐如何宿衛禁中﹖且去練壯了再來。\n");
		return 0;
	}

	if( me->query_attr("con") < 14 ) {
		do_chat("李天剛端詳片刻﹐沉聲道﹕你筋骨太過虛弱﹐熬不住巡夜值更的辛勞﹐且去將養好了再來。\n");
		return 0;
	}

	do_chat(({
		"李天剛抱起雙臂﹐將你細細打量了一番。\n",
		"李天剛朗聲道﹕我大內巡院軍法森嚴﹐宿衛禁中半點馬虎不得﹐你可擔得起這份重任﹖\n",
		"李天剛頷首一笑﹕也罷﹐瞧你還算有把子身手﹐我便收你入巡院門下﹐傳你這套護駕的劍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("李天剛把長劍一收﹐說道﹕你既已另投他處﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("soldier");
		me->set("sect", "大內巡院");
		me->set("rank", "大內高手");
		me->set("title", "大內巡院高手");

		me->set_skill("sword", 0);
		me->set_skill("danei sword", 0);
		me->map_skill("sword", "danei sword");

		// 同時授予大內罡氣（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("danei force", 0);
		me->map_skill("force", "danei force");

		message_vision(
			"$N抽出一柄長劍﹐將大內劍法的入門劍勢一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"李天剛朗聲道﹕從今日起﹐你便是我大內巡院的宿衛了。\n",
			"李天剛沉聲道﹕到校場領柄長劍勤加操練﹐劍要正、步要穩、心要忠﹐莫墮了巡院的威名。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
