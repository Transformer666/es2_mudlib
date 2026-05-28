// master.c -- 冷梅莊主

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("冷梅莊主", ({ "lunmay master", "master", "lunmay" }));
	set("nickname", "傲梅劍客");
	set_attr("str", 24);
	set_attr("dex", 26);
	set_attr("int", 22);
	set_attr("wis", 23);
	set_attr("spi", 22);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 24);
	set_race("human");
	set_level(40);
	set_class("fighter");
	set("sect", "冷梅莊");
	set("rank", "莊主");

	set_skill("unarmed", 80);
	set_skill("sword", 150);
	set_skill("parry", 120);
	set_skill("dodge", 110);
	set_skill("force", 120);
	set_skill("lunmay", 150);
	set_skill("hainmay force", 120);
	map_skill("sword", "lunmay");
	map_skill("force", "hainmay force");

	advance_stat("gin", 220);
	advance_stat("kee", 220);
	advance_stat("sen", 220);

	set("age", 48);
	set("long",
		"這位便是冷梅莊主﹐一身月白長袍﹐腰懸長劍﹐眉宇間透著一股清\n"
		"冷孤傲之氣。冷梅莊是雪亭鎮一帶聲名卓著的劍派﹐莊主自幼苦練家\n"
		"傳的冷梅劍法﹐劍勢如寒梅綻放﹐冷冽中暗藏凌厲殺機﹐江湖人稱「\n"
		"傲梅劍客」。他平日深居莊中﹐潛心劍道﹐唯有資質清正的年輕人才\n"
		"有機會拜入他的門下﹐習得這一身傲視群雄的劍法。\n");
	setup();
	carry_object("/d/snow/npc/obj/silversword")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("冷梅莊主搖了搖頭﹐說道﹕你既已入別派﹐何苦再來攪擾﹖\n");
		return 0;
	}

	// 須年滿一定等級﹐心性沉穩方可習劍
	if( me->query_level() < 1 ) {
		do_chat("冷梅莊主說道﹕你根基未穩﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 冷梅劍法講究靈動﹐機敏不足者難窺堂奧
	if( me->query_attr("dex") < 18 ) {
		do_chat("冷梅莊主端詳了你一會﹐說道﹕你筋骨太過遲鈍﹐學不得我這路劍法。\n");
		return 0;
	}

	do_chat(({
		"冷梅莊主上下打量了你一番﹐微微頷首。\n",
		"冷梅莊主說道﹕我冷梅莊的劍法﹐講究一個「傲」字﹐你可受得了這份清苦﹖\n",
		"冷梅莊主說道﹕也罷﹐我便收你做個記名弟子﹐傳你冷梅劍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("冷梅莊主揮了揮手﹐說道﹕你既已另投他師﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("fighter");
		me->set("sect", "冷梅莊");
		me->set("rank", "劍士");
		me->set("title", "冷梅莊劍士");

		me->set_skill("sword", 0);
		me->set_skill("lunmay", 0);
		me->map_skill("sword", "lunmay");

		message_vision(
			"$N取過一柄長劍﹐將冷梅劍法的入門劍訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"冷梅莊主說道﹕從今日起﹐你便是我冷梅莊的劍士了。\n",
			"冷梅莊主說道﹕劍道無窮﹐你且到演武場勤加練習﹐莫負了這身劍法。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
