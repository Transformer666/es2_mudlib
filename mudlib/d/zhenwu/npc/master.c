// master.c -- 振武軍營主將（軍隊統領）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("振武統領", ({ "soldier master", "master", "general", "commander" }));
	set("nickname", "鎮北將軍");
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
	set("sect", "振武軍營");
	set("rank", "軍隊統領");
	set("title", "振武軍營軍隊統領");

	set_skill("unarmed", 60);
	set_skill("dodge", 90);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("pike", 150);
	set_skill("dragon god", 150);
	map_skill("pike", "dragon god");

	advance_stat("gin", 240);
	advance_stat("kee", 240);
	advance_stat("sen", 160);

	set("age", 48);
	set("long",
		"這位便是振武軍營的主將﹐一身玄鐵山文甲﹐外罩猩紅戰袍﹐身\n"
		"形魁梧如鐵塔﹐按槍而立﹐自有一股久經沙場的肅殺之氣。他面如\n"
		"重棗﹐濃眉鳳目﹐頷下一部虬髯根根如戟﹐顧盼之間威猛逼人。振\n"
		"武軍營軍隊統領一脈以槍陣縱橫沙場﹐主將浸淫龍神槍法數十年﹐\n"
		"一桿長槍縱橫無敵﹐軍中尊稱「鎮北將軍」。他久鎮此營操練兵馬\n"
		"﹐唯有膂力過人、肯吃苦耐勞的後輩﹐方有機會拜入麾下﹐學得這\n"
		"一身殺敵報國的本事。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("振武統領把長槍頓地一震﹐沉聲道﹕你既已入別派﹐軍籍難改﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可從軍
	if( me->query_level() < 1 ) {
		do_chat("振武統領上下打量了你一眼﹐喝道﹕乳臭未乾的雛兒﹐且去歷練一番再來投軍罷。\n");
		return 0;
	}

	// 槍陣廝殺全憑一身膂力﹐筋骨孱弱者扛不起這桿長槍（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("str") < 14 ) {
		do_chat("振武統領搖頭道﹕你這身子骨連長槍都端不穩﹐如何上陣殺敵﹖且去練壯了再來。\n");
		return 0;
	}

	do_chat(({
		"振武統領抱起雙臂﹐將你細細打量了一番。\n",
		"振武統領朗聲道﹕我振武軍營軍法森嚴﹐操練如熬煉鋼鐵﹐你可吃得了這份苦﹖\n",
		"振武統領哈哈一笑﹕也罷﹐瞧你還算有把子力氣﹐我便收你入軍隊統領門下﹐傳你這套殺敵的槍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("振武統領把長槍一收﹐說道﹕你既已另投他處﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("soldier");
		me->set("sect", "振武軍營");
		me->set("rank", "軍隊統領");
		me->set("title", "振武軍營軍隊統領");

		me->set_skill("pike", 0);
		me->set_skill("dragon god", 0);
		me->map_skill("pike", "dragon god");

		message_vision(
			"$N抄起一桿長槍﹐將龍神槍法的入門槍勢一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"振武統領朗聲道﹕從今日起﹐你便是我振武軍營軍隊統領門下的兵了。\n",
			"振武統領沉聲道﹕到校場領桿長槍勤加操練﹐槍要沉、步要穩、心要狠﹐莫墮了我軍威。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
