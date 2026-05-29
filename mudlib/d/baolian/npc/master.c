// master.c -- 寶蓮寺方丈 善想上人
//
// 寶蓮寺是善想禪宗三大寺院之一﹐與白象寺同屬和尚(bonze)一脈﹐故本檔
// 結構完全比照 d/baixiang/npc/master.c﹐沿用既有的 bonze class﹐只是
// 兵器/招式由金剛伏魔杖法(staff/rid-evil)改為慈顏除障手(unarmed/
// buddha_zarn)、內功由蓮華心法(lotus force)改為寶蓮心法(baolian force)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("善想上人", ({ "baolian master", "master", "monk", "shanxiang" }));
	set("nickname", "寶蓮方丈");
	set_attr("str", 22);
	set_attr("dex", 24);
	set_attr("int", 26);
	set_attr("wis", 26);
	set_attr("spi", 26);
	set_attr("cps", 24);
	set_attr("con", 24);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("bonze");
	set("sect", "寶蓮寺");
	set("rank", "方丈");
	set("title", "寶蓮寺方丈");

	set_skill("unarmed", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("buddha_zarn", 150);
	set_skill("buddhism", 120);
	map_skill("unarmed", "buddha_zarn");
	map_skill("force", "buddhism");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 65);
	set("gender", "male");
	set("long",
		"這位便是寶蓮寺的方丈善想上人﹐一身漿洗得發白的灰色袈裟﹐\n"
		"身形清瞿﹐鬚眉如雪﹐面容慈和恬淡﹐一雙眼眸澄澈如水﹐顧盼之\n"
		"間流露出一股悲天憫人的祥和之氣。他垂手而立﹐神態淵默﹐周身\n"
		"卻隱隱有股深不可測的內力韻致﹐似已將一身武功盡數收斂於慈眉\n"
		"善目之中。寶蓮寺善想一脈以慈悲心濟世度人﹐上人浸淫慈顏除障\n"
		"手與寶蓮心法數十年﹐功參造化而不滯於物﹐人稱「寶蓮方丈」。\n"
		"他平日在大雄寶殿中誦經說法﹐唯有心存善念、根器不俗的後輩﹐\n"
		"方有機會拜入門下﹐習得這一身以慈化障的佛門掌法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("善想上人雙手合十﹐宣了聲佛號﹕施主既已入別派﹐緣分已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("善想上人微笑道﹕施主塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 慈顏除障手須以慧根參悟佛理（門檻甚低﹐尋常人皆可入）。
	// 註﹕int 為悟性﹐wis 為慧根。
	if( me->query_attr("wis") < 14 ) {
		do_chat("善想上人端詳了你一會﹐搖頭道﹕施主慧根閉塞﹐難參我這路佛法。\n");
		return 0;
	}

	if( me->query_attr("int") < 14 ) {
		do_chat("善想上人微微搖頭﹕施主悟性未開﹐這慈顏除障手的精微之處﹐只怕一時難以領會。\n");
		return 0;
	}

	do_chat(({
		"善想上人上下打量了你一番﹐微微頷首。\n",
		"善想上人道﹕我寶蓮寺善想一脈﹐以慈悲度世﹐施主可有這份向善之心﹖\n",
		"善想上人宣了聲佛號﹕善哉善哉﹐你既與我佛有緣﹐老衲便收你入門下﹐傳你慈顏除障手。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("善想上人雙手合十﹐道﹕施主既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("bonze");
		me->set("sect", "寶蓮寺");
		me->set("rank", "善想弟子");
		me->set("title", "寶蓮寺僧人");

		me->set_skill("unarmed", 0);
		me->set_skill("buddha_zarn", 0);
		me->map_skill("unarmed", "buddha_zarn");

		// 同時授予寶蓮心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("baolian force", 0);
		me->map_skill("force", "baolian force");

		message_vision(
			"$N合什誦了聲佛號﹐將慈顏除障手的入門掌訣一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"善想上人宣了聲佛號﹕從今日起﹐你便是我寶蓮寺善想門下的弟子了。\n",
			"善想上人道﹕武學乃濟世之具﹐你且到演武場勤加錘鍊﹐莫失了這份慈悲本心。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
