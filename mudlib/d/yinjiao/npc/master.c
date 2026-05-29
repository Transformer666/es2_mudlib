// master.c -- 隱教聖女 利丰華

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("利丰華", ({ "yinjiao master", "master", "saint", "lifenghua" }));
	set("nickname", "隱教聖女");
	set("gender", "女性");
	set_attr("str", 18);
	set_attr("dex", 32);
	set_attr("int", 26);
	set_attr("wis", 24);
	set_attr("spi", 24);
	set_attr("cps", 24);
	set_attr("con", 20);
	set_attr("cor", 16);
	set_race("human");
	set_level(40);
	set_class("thief");
	set("sect", "隱教");
	set("rank", "聖女");
	set("title", "隱教聖女");

	set_skill("unarmed", 60);
	set_skill("dodge", 130);
	set_skill("parry", 90);
	set_skill("force", 120);
	set_skill("yinjiao force", 120);
	set_skill("dagger", 150);
	set_skill("serpent dagger", 150);
	map_skill("force", "yinjiao force");
	map_skill("dagger", "serpent dagger");

	advance_stat("gin", 220);
	advance_stat("kee", 200);
	advance_stat("sen", 200);

	set("age", 36);
	set("long",
		"這位便是隱教的聖女利丰華。她一身緊束的玄色勁裝﹐外罩一襲輕\n"
		"薄如煙的黑紗﹐面容清冷絕美﹐唯獨一雙眼睛深不見底﹐顧盼之間\n"
		"透著一股看慣了生死的漠然殺氣。她腰間斜束軟帶﹐帶上暗藏著數\n"
		"柄淬毒的薄刃匕首。隱教隱於野羊山深處﹐自金蛇門一脈分出﹐專\n"
		"事潛行暗殺、見血封喉的勾當﹐聖女浸淫金蛇匕法多年﹐出手如毒\n"
		"蛇噬人﹐無聲無息。她端坐壇上﹐冷眼旁觀來人﹐唯有身手機敏、\n"
		"心性夠狠的後輩﹐方有機會叩拜金蛇﹐拜入她門下﹐學得這一身殺\n"
		"人的本事。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("利丰華指尖撫過匕首薄刃﹐冷冷說道﹕你既已入別派﹐道兒已定﹐何苦再來自尋死路﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入夥
	if( me->query_level() < 1 ) {
		do_chat("利丰華淡淡瞥了你一眼﹐說道﹕乳臭未乾的雛兒﹐且去江湖上滾過一遭再來罷。\n");
		return 0;
	}

	// 匕法暗算全憑一身機敏﹐手腳遲鈍者難成氣候（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("dex") < 14 ) {
		do_chat("利丰華上下打量了你一番﹐搖頭道﹕你手腳這般遲鈍﹐學不來我隱教見血封喉的手藝。\n");
		return 0;
	}

	do_chat(({
		"利丰華眯起那雙深不見底的眼睛﹐將你細細打量了一番。\n",
		"利丰華壓低聲音道﹕入了我隱教﹐刀頭舔血﹐見不得光﹐你可怕了﹖\n",
		"利丰華嘴角微微一揚﹕也罷﹐瞧你還算機靈﹐你便去叩拜金蛇﹐我收你入金蛇門人之列﹐傳你這套吃飯的本事。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("利丰華薄刃一收﹐冷聲道﹕你既已另投他處﹐快滾罷。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("thief");
		me->set("sect", "隱教");
		me->set("rank", "金蛇門人");
		me->set("title", "隱教金蛇門人");

		me->set_skill("dagger", 0);
		me->set_skill("serpent dagger", 0);
		me->map_skill("dagger", "serpent dagger");

		// 同時授予隱教心法﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("yinjiao force", 0);
		me->map_skill("force", "yinjiao force");

		message_vision(
			"$N自腰間反手抽出一柄薄刃匕首﹐將金蛇匕法的入門殺招一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"利丰華說道﹕從今日起﹐你便是我隱教金蛇門下的人了。\n",
			"利丰華沉聲道﹕到演武場對著草人勤練匕法﹐出手要快、要狠、要無聲﹐如金蛇噬人。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
