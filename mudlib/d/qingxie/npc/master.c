// master.c -- 哭笑門主 劉乙忘玄

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("劉乙忘玄", ({ "grimace master", "master", "kuxiao" }));
	set("nickname", "哭笑判官");
	set_attr("str", 25);
	set_attr("dex", 22);
	set_attr("int", 22);
	set_attr("wis", 23);
	set_attr("spi", 24);
	set_attr("cps", 25);
	set_attr("con", 26);
	set_attr("cor", 18);
	set_race("human");
	set_level(40);
	set_class("fighter");
	set("sect", "哭笑門");
	set("rank", "門主");

	set_skill("unarmed", 80);
	set_skill("staff", 150);
	set_skill("parry", 130);
	set_skill("dodge", 110);
	set_skill("force", 130);
	set_skill("chin_staff", 150);
	set_skill("huge force", 130);
	map_skill("staff", "chin_staff");
	map_skill("force", "huge force");

	advance_stat("gin", 220);
	advance_stat("kee", 240);
	advance_stat("sen", 220);

	set("age", 56);
	set("long",
		"這位便是哭笑門主劉乙忘玄﹐一襲玄黑長袍﹐手按一根烏沉沉的鐵\n"
		"杖﹐臉上一半在笑一半在哭﹐叫人捉摸不透。哭笑門是江湖上聞之色\n"
		"變的邪派﹐門主修得一身詭譎剛猛的青邪杖法與大邪心法﹐杖出如鬼\n"
		"嘯﹐守若銅牆﹐縱是成名高手亦難在他杖下討得便宜﹐人稱「哭笑判\n"
		"官」。他坐鎮青邪宮中﹐極少現身﹐唯有心志夠狠、根骨夠硬的人﹐\n"
		"方有機會拜入門下﹐習得這一身護法絕學。\n");
	setup();
	carry_object("/d/snow/npc/obj/cane")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("劉乙忘玄似笑非笑地瞥了你一眼﹕你既已入別派﹐還來我青邪宮作甚﹖\n");
		return 0;
	}

	// 須年滿一定等級﹐方有資格修習邪功
	if( me->query_level() < 1 ) {
		do_chat("劉乙忘玄冷哼一聲﹕你這身子骨還嫩得很﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 護法之學講究守得住、扛得起﹐筋骨孱弱者扛不住這份剛猛內勁
	if( me->query_attr("con") < 18 ) {
		do_chat("劉乙忘玄端詳了你半晌﹕你體魄太過孱弱﹐扛不住我這路邪功的反噬。\n");
		return 0;
	}

	do_chat(({
		"劉乙忘玄上上下下將你打量了一番﹐臉上的哭笑霎時凝住。\n",
		"劉乙忘玄陰惻惻地說道﹕我哭笑門的功夫﹐入門容易出門難﹐你可想清楚了﹖\n",
		"劉乙忘玄說道﹕也罷﹐我便收你做個護法弟子﹐傳你青邪杖法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("劉乙忘玄袍袖一拂﹕你既已另投他師﹐滾罷。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("fighter");
		me->set("sect", "哭笑門");
		me->set("rank", "護法");
		me->set("title", "哭笑門護法");

		me->set_skill("staff", 0);
		me->set_skill("chin_staff", 0);
		me->map_skill("staff", "chin_staff");

		// 同時授予大邪心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("huge force", 0);
		me->map_skill("force", "huge force");

		message_vision(
			"$N抄起一根烏沉沉的鐵杖﹐將青邪杖法的入門杖訣一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"劉乙忘玄陰陰一笑﹕從今日起﹐你便是我哭笑門的護法了。\n",
			"劉乙忘玄沉聲道﹕到演武場領根鐵杖勤加操演﹐杖要狠、樁要穩、心要冷﹐莫墮了我哭笑門的兇名。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
