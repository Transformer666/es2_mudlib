// master.c -- 天月庵庵主 神尼
//
// 天月庵(bonze.moon)是和尚一脈三大寺院之一﹐與寶蓮寺、白象寺同屬和尚
// (bonze)一脈﹐以太陰(月)之力濟世度人、長於治療與控制（見 docs/03-門派
// 與武功/03-和尚-寶蓮天月白象.md §天月庵）。本檔結構比照天師派施法師父
// d/tianshi/npc/windmaster.c（法術 magic + 內功 force + 基本功）﹐並沿用
// 寶蓮/白象 master 的和尚 bonze class 與 accept/init_apprentice 收徒流程。
// 神尼以慧根(wis)參悟太陰秘法﹐故收徒門檻略重慧根﹐惟門檻甚低﹐尋常人皆
// 可入。
//
// 授徒技能﹕太陰秘法(magic→moon magic)、太陰七損鞭(whip→moon whip)﹐
// 並授太陰內功(force)。
// TODO: 太陰內功暫沿用既有的和尚內功 lotus force(蓮華心法) daemon﹐日後
//       宜另撰天月庵專屬內功（如「太陰真經」）daemon 再行替換。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("神尼", ({ "moon nun", "nun", "shenni", "master" }));
	set("nickname", "天月庵主");
	set_attr("str", 18);
	set_attr("dex", 24);
	set_attr("int", 25);
	set_attr("wis", 28);
	set_attr("spi", 26);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("bonze");
	set("sect", "天月庵");
	set("rank", "庵主");
	set("title", "天月庵主");

	set_skill("unarmed", 60);
	set_skill("dodge", 100);
	set_skill("parry", 90);
	set_skill("force", 120);
	set_skill("magic", 150);
	set_skill("moon magic", 150);
	set_skill("whip", 120);
	set_skill("moon whip", 150);
	set_skill("buddhism", 120);
	// 太陰秘法以 magic 施展﹐太陰七損鞭以 whip(鞭)施展。
	map_skill("magic", "moon magic");
	map_skill("whip", "moon whip");
	map_skill("force", "buddhism");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 58);
	set("gender", "female");
	set("long",
		"這位便是天月庵的庵主神尼﹐一身素淨的緇衣纖塵不染﹐眉目慈\n"
		"和﹐雙手合十而立﹐周身隱隱透著一股清冷如月的祥和之氣。她生得\n"
		"清臞矍鑠﹐一雙眼眸澄澈如秋水寒潭﹐顧盼之間悲憫眾生﹐卻又透著\n"
		"一縷歷盡劫波的孤寂。天月庵一脈以太陰之力濟世度人﹐長於療\n"
		"傷續命、控敵制人﹐神尼浸淫太陰秘法與七損鞭法數十年﹐功參造化\n"
		"而慈悲不滅﹐江湖人尊稱「神尼」。庵中曾遭滅門之厄﹐如今僧眾凋\n"
		"零﹐她平日在庵堂中誦經療傷﹐唯有心存慈悲、慧根不俗的有緣女子\n"
		"或男子﹐方有機會拜入門下﹐習得這一身以月證道的太陰法門。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("神尼雙手合十﹐宣了聲佛號﹕施主既已入別派﹐緣分已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("神尼微微一歎﹕施主塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 太陰秘法須以慧根參悟月華真意（門檻甚低﹐尋常人皆可入）。
	// 註﹕wis 為慧根﹐int 為悟性。天月庵重慧根﹐故慧根門檻略高於寶蓮寺。
	if( me->query_attr("wis") < 16 ) {
		do_chat("神尼端詳了你一會﹐輕輕搖頭﹕施主慧根淺薄﹐難參我這太陰月法。\n");
		return 0;
	}

	if( me->query_attr("int") < 14 ) {
		do_chat("神尼微微搖頭﹕施主悟性未開﹐這太陰秘法的精微之處﹐只怕一時難以領會。\n");
		return 0;
	}

	do_chat(({
		"神尼上下打量了你一番﹐微微頷首。\n",
		"神尼道﹕我天月庵以太陰之力濟世度人﹐施主可有這份慈悲向善之心﹖\n",
		"神尼宣了聲佛號﹕善哉善哉﹐你既與我佛有緣﹐老尼便收你入門下﹐傳你太陰秘法與七損鞭法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("神尼雙手合十﹐道﹕施主既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("bonze");
		me->set("sect", "天月庵");
		me->set("rank", "比丘尼");
		me->set("title", "天月庵比丘尼");

		// 太陰秘法（法術 magic）
		me->set_skill("magic", 0);
		me->set_skill("moon magic", 0);
		me->map_skill("magic", "moon magic");

		// 太陰七損鞭（鞭法 whip）
		me->set_skill("whip", 0);
		me->set_skill("moon whip", 0);
		me->map_skill("whip", "moon whip");

		// 同時授予太陰內功（內功 force）﹐使弟子戰鬥時力道能隨內功成長。
		// TODO: 暫沿用既有和尚內功 lotus force(蓮華心法)﹐日後改為天月庵
		//       專屬內功 daemon。
		me->set_skill("force", 0);
		me->set_skill("lotus force", 0);
		me->map_skill("force", "lotus force");

		message_vision(
			"$N合什誦了聲佛號﹐將太陰秘法與七損鞭法的入門口訣一一傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"神尼宣了聲佛號﹕從今日起﹐你便是我天月庵門下的弟子了。\n",
			"神尼道﹕太陰之力本為濟世﹐你且在庵中勤加參修﹐莫失了這份慈悲本心。\n",
		}));
	}
}
// vim: set ts=4 sw=4 syntax=lpc
