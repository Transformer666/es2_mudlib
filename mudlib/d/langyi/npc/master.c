// master.c -- 瑯夷派黑龍堂主

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("瑯夷堂主", ({ "thief master", "master", "thief", "rogue" }));
	set("nickname", "黑龍左使");
	set_attr("str", 20);
	set_attr("dex", 30);
	set_attr("int", 25);
	set_attr("wis", 24);
	set_attr("spi", 22);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 18);
	set_race("human");
	set_level(40);
	set_class("thief");
	set("sect", "瑯夷派");
	set("rank", "黑龍左使");
	set("title", "瑯夷派黑龍左使");

	set_skill("unarmed", 60);
	set_skill("dodge", 130);
	set_skill("parry", 90);
	set_skill("force", 120);
	set_skill("longyeforce", 120);
	set_skill("dagger", 150);
	set_skill("blood dagger", 150);
	map_skill("force", "longyeforce");
	map_skill("dagger", "blood dagger");

	advance_stat("gin", 220);
	advance_stat("kee", 200);
	advance_stat("sen", 200);

	set("age", 44);
	set("long",
		"這位便是瑯夷派的黑龍堂主﹐一身玄黑勁裝﹐腰束軟帶﹐帶上斜插\n"
		"著兩柄寒光森森的匕首。他身形精瘦﹐步履無聲﹐一雙眼睛深陷而\n"
		"銳利﹐顧盼之間隱隱透著一股噬人的殺氣。瑯夷派黑龍左使一脈以\n"
		"匕首暗算、潛行取命名動黑道﹐堂主浸淫血魂匕法數十年﹐出手見\n"
		"血﹐從無虛發﹐江湖人稱「黑龍左使」。他久居這地底堂口﹐唯有\n"
		"身手機敏、心性夠狠的後輩﹐方有機會拜入門下﹐學得這一身殺人\n"
		"的本事。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("瑯夷堂主把玩著手中匕首﹐冷笑道﹕你既已入別派﹐道兒已定﹐何苦再來自討沒趣﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入夥
	if( me->query_level() < 1 ) {
		do_chat("瑯夷堂主斜睨了你一眼﹐說道﹕乳臭未乾的雛兒﹐且去江湖上滾過一遭再來罷。\n");
		return 0;
	}

	// 匕法暗算全憑一身機敏﹐手腳遲鈍者難成氣候（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("dex") < 14 ) {
		do_chat("瑯夷堂主上下打量了你一番﹐搖頭道﹕你手腳這般遲鈍﹐學不來我這偷天換日的手藝。\n");
		return 0;
	}

	do_chat(({
		"瑯夷堂主眯起眼睛﹐將你細細打量了一番。\n",
		"瑯夷堂主壓低聲音道﹕入了我瑯夷派﹐刀頭舔血﹐見不得光﹐你可怕了﹖\n",
		"瑯夷堂主嘿嘿一笑﹕也罷﹐瞧你還算機靈﹐我便收你入黑龍左使門下﹐傳你這套吃飯的本事。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("瑯夷堂主把匕首一收﹐說道﹕你既已另投他處﹐快滾罷。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("thief");
		me->set("sect", "瑯夷派");
		me->set("rank", "黑龍左使");
		me->set("title", "瑯夷派黑龍左使");

		me->set_skill("dagger", 0);
		me->set_skill("blood dagger", 0);
		me->map_skill("dagger", "blood dagger");

		message_vision(
			"$N反手抽出一柄匕首﹐將血魂匕法的入門殺招一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"瑯夷堂主說道﹕從今日起﹐你便是我瑯夷派黑龍左使門下的人了。\n",
			"瑯夷堂主沉聲道﹕到演武場對著草人勤練匕法﹐出手要快、要狠、要無聲。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
