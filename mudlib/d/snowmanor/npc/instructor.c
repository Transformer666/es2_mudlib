// instructor.c -- 雪吟莊教頭 屠九 (Tu jiu)
//
// 設定（依 docs/03-門派與武功/01-武者-五大門派.md §4 雪吟莊）：
//   雪吟莊莊主魚鐵山(yu_tieshan.c)是主線反派﹐城府極深、不收徒。莊主底下
//   另設一名「教頭」屠九﹐專司操演莊丁、為莊主廣納門人——浪人一脈即由他
//   傳授。雪吟莊本門武功並無獨到﹐然源自外邦天邪國的天邪神功(tianxie-force)
//   強悍﹔浪人強化「數字刀」(deepblade)﹐攻勢凌厲﹐是新手推薦的入門武者門派。
//   適合種族﹕夜叉、阿修羅、焦僥、刑天、人類。
//
//   * 拜師 NPC（浪人入門）﹕accept_apprentice 僅要求 commoner + level>=1﹐
//     保持新手可入﹔對膽識另有一句帶氣勢的話﹐但不硬性擋人。
//   * init_apprentice 授予 fighter / 雪吟莊 / 浪人 / 數字刀 / 天邪神功。
//   * 切勿與莊主魚鐵山混淆——魚鐵山不收徒﹐拜師一律找這位教頭屠九。
//
// 本 NPC 比照封山派掌門 d/fonxan/npc/master.c 撰寫（fighter 拜師樣板）﹐
// 基礎兵器由 sword 改為 blade（雪吟莊慣用單刀﹐見 retainer.c / yu_tieshan.c﹐
// 皆 wield /obj/area/obj/blade）﹐簽名武學改為數字刀(deepblade)＋天邪神功
// (tianxie-force)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("屠九", ({ "tu jiu", "tu", "instructor", "manor instructor" }));
	set("nickname", "雪吟莊教頭");
	set_attr("str", 26);
	set_attr("dex", 23);
	set_attr("int", 20);
	set_attr("wis", 20);
	set_attr("spi", 22);
	set_attr("cps", 22);
	set_attr("con", 24);
	set_attr("cor", 23);
	set_race("human");
	set_level(33);
	set_class("fighter");
	set("sect", "雪吟莊");
	set("rank", "教頭");

	set_skill("unarmed", 90);
	set_skill("blade", 140);
	set_skill("parry", 110);
	set_skill("dodge", 100);
	set_skill("force", 120);
	set_skill("deepblade", 140);
	set_skill("tianxie-force", 120);
	map_skill("blade", "deepblade");
	map_skill("force", "tianxie-force");

	advance_stat("gin", 200);
	advance_stat("kee", 210);
	advance_stat("sen", 200);

	set("gender", "male");
	set("age", 46);
	set("long",
		"這位是雪吟莊的教頭屠九﹐一身藏青勁裝緊束在精悍的身板上﹐臂膀\n"
		"虯結﹐太陽穴高高鼓起﹐一望便知是個外家功夫練到了家的狠角色。他\n"
		"按著一柄寒光隱隱的單刀﹐神情冷峻﹐目光如刀﹐在你身上一掃便似已\n"
		"將你的斤兩掂量了個透。雪吟莊本門武功並無甚獨到﹐然莊主魚鐵山自\n"
		"外邦天邪國得來的天邪神功端的雄渾詭譎﹐這位教頭便奉莊主之命﹐日\n"
		"日在演武場督練莊丁、廣納浪人﹐將那一脈剛猛綿密的數字刀傳授下去。\n"
		"他治下極嚴﹐出手狠辣﹐莊中無人不畏他三分。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"屠九按著腰間單刀﹐冷冷地將你上下打量了一番。\n",
		"屠九沉聲道﹕想學雪吟莊的數字刀﹖先掂量掂量自己的膽子。\n",
		"屠九淡淡道﹕莊主的天邪神功﹐豈是人人練得起的。\n",
	}));
	setup();
	carry_object("/obj/area/obj/blade")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("屠九搖了搖頭﹐說道﹕你既已入別派﹐還來雪吟莊作甚﹖\n");
		return 0;
	}

	// 新手門派﹐只須略具根基便收——保持可入(newbie entry)。
	if( me->query_level() < 1 ) {
		do_chat("屠九瞥了你一眼﹐說道﹕乳臭未乾﹐且去歷練歷練再來。\n");
		return 0;
	}

	// 數字刀剛猛﹐膽小者使來不夠狠——只作一句激將﹐不硬性擋人(新手可入)。
	if( me->query_attr("cor") < 12 )
		do_chat("屠九哼了一聲﹕你這膽子﹐使起刀來怕是要自己先軟了手——也罷﹐進來罷。\n");

	do_chat(({
		"屠九上下打量了你一番﹐微微頷首。\n",
		"屠九沉聲道﹕雪吟莊收的是浪人﹐使的是數字刀﹐練的是天邪神功﹐你可吃得了這份苦﹖\n",
		"屠九說道﹕也罷﹐我便收你做個浪人﹐傳你莊上的刀法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("屠九揮了揮手﹐說道﹕你既已另投他師﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("fighter");
		me->set("sect", "雪吟莊");
		me->set("rank", "浪人");
		me->set("title", "雪吟莊浪人");

		me->set_skill("blade", 0);
		me->set_skill("deepblade", 0);
		me->map_skill("blade", "deepblade");

		// 同時授予雪吟莊源自天邪國的內功﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("tianxie-force", 0);
		me->map_skill("force", "tianxie-force");

		message_vision(
			"$N取過一柄單刀﹐將數字刀的入門刀訣一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"屠九沉聲道﹕從今日起﹐你便是我雪吟莊的浪人了。\n",
			"屠九說道﹕到演武場去勤練數字刀﹐運起天邪神功﹐莫墮了莊主的威名。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
