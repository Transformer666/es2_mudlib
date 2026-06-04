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

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 和尚(bonze)門派(天月庵)的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的天月庵比丘尼
// 轉入三大進階分支之一。比照白象寺方丈 d/baixiang/npc/master.c(同為 bonze 職業)
// 與冷梅/封山/虎刀/天師諸門的授技模型(門檻更高、以 sect_branch 標記分支、升階
// rank/title)﹐使通用「進階」指令可不改動地驅動本門。
//
// 入門技能映射(見上方 init_apprentice)：magic→太陰秘法 moon magic、
//   whip→太陰七損鞭 moon whip、force→蓮華心法 lotus force(和尚共用入門內功)。
//   故進階各分支的 "base" 須對應 bonze 入門所授的正確基礎技能(whip/sword/magic)﹐
//   入門火候門檻以入門鞭法 "moon whip" 計(對應武者的 lunmay/bawang blade、白象的
//   rid-evil、天師的 taoism-fire)。
//
// 與白象寺(同 bonze)的差異(寺院定位)：白象為武僧(杖→刀)﹐天月庵定位「治療/控制」﹐
//   以太陰月法 + 鞭/劍/槍演月之意﹐故所授偏鞭法、劍法、控制法術與身法/槍法副技。
//
// 三大分支(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md §天月庵-核心技能列出之
//   摧魂鞭法/雨花劍法/穹槍訣/落葉身法/太陰秘法/太陰七損鞭)：
//   摧魂使者  ── 高階鞭法 摧魂鞭法 destruction whip(主﹐base=whip) + 身法 落葉身法
//                falling-leaf steps(副技 dodge)。沿用入門蓮華心法。docs 明列之鞭法/
//                身法。最早開放、門檻最低、重 dex(身法輕靈)。
//   雨花仙子  ── 內功 太陰真經 taiyin force + 高階劍法 雨花劍法 rain-flower sword
//                (主﹐捨鞭習劍故 base=sword)。docs 明列之劍法。門檻居中、重 wis(慧根)。
//   太陰尊者  ── 內功 太陰真經 taiyin force + 上乘控制月法 太陰冰心訣 moon-frost magic
//                (主﹐base=magic) + 高階槍法 穹槍訣 sky_pike(副技 pike)。天月庵最高一階﹐
//                承太陰秘法控制一系與 docs 明列之穹槍訣。門檻最高、另設第二道屬性(int)門檻。
//
// 轉職門檻(條件)為本次設計值﹐供日後平衡微調﹕
//   key        level  moon whip  attr 門檻              授內功         授武功/法術(base)
//   ────────── ─────  ─────────  ────────────────────  ────────────  ──────────────────────────────────
//   摧魂使者   20     60         dex >= 18             (沿用蓮華心法) 摧魂鞭法 (whip) + 落葉身法(dodge)
//   雨花仙子   25     80         wis >= 20             太陰真經       雨花劍法 (sword)
//   太陰尊者   30     100        wis >= 22, int >= 20  太陰真經       太陰冰心訣(magic) + 穹槍訣(pike)
//
// 註(分支名)：docs 天月庵只列核心技能﹐未明列其二轉分支階名(不同於白象寺明列禪師/
//   羅漢)。分支名「摧魂使者/雨花仙子/太陰尊者」為設計(docs未明定)﹐分別承 docs 明列之
//   摧魂鞭法/雨花劍法/穹槍訣+太陰秘法控制一系而立﹐與白象寺羅漢/禪師/降魔尊者同階對位。
// 註(故事門檻)：docs 天月庵主力玩法含 zazengo(坐禪)/link 群補/conjure 等控制治療系統﹐
//   屬未接的 perform/heal 引擎工作﹔為與本批進階一致(只 gate level/skill/attr)﹐此處先
//   以等級/入門鞭法火候/屬性門檻替代﹐控制治療特效標記為待接的 TODO(見各 daemon 檔頭)。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式/法術對應的基礎技能(摧魂使者為 whip﹔雨花仙子捨鞭習劍故為 sword﹔
//   太陰尊者以控制月法證道故為 magic)。
// "extra" 為另授的副技﹕({ ({中文,英文,基礎技能}), ... })﹐授技後 map_skill(基礎,英文)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"摧魂使者" : ([
			"rank"    : "天月摧魂使者",
			"title"   : "天月庵摧魂使者",
			"level"   : 20,
			"moon whip" : 60,
			"attr"    : "dex",
			"attr_min": 18,
			"base"    : "whip",
			"force"   : 0,    // 摧魂使者不另授內功﹐沿用入門蓮華心法(lotus force)
			"skills"  : ({ ({ "摧魂鞭法", "destruction whip" }) }),
			"extra"   : ({
				({ "落葉身法", "falling-leaf steps", "dodge" }),
			}),
			"desc"    : "摧魂使者承太陰七損鞭一脈而成﹐摧魂鞭法森寒詭譎、攝魂奪魄﹐"
			            "攻勢凌厲﹐輔以落葉身法移形換步、飄忽難測。摧魂鞭法走 whip、"
			            "落葉身法精進你的閃躲身法(dodge)。",
		]),
		"雨花仙子" : ([
			"rank"    : "天月雨花仙子",
			"title"   : "天月庵雨花仙子",
			"level"   : 25,
			"moon whip" : 80,
			"attr"    : "wis",
			"attr_min": 20,
			"base"    : "sword",      // 雨花仙子捨鞭習劍﹐主招式對應 sword
			"force"   : ({ "太陰真經", "taiyin force" }),
			"skills"  : ({ ({ "雨花劍法", "rain-flower sword" }) }),
			"desc"    : "雨花仙子捨鞭習劍﹐有太陰真經護體、內力綿長﹐雨花劍法輕靈飄逸﹐"
			            "漫天劍光如天女散花、似驟雨梨花﹐清冷之中暗藏鋒芒。自此你的"
			            "劍法(sword)便是濟世度人的本錢。",
		]),
		"太陰尊者" : ([
			"rank"    : "天月太陰尊者",
			"title"   : "天月庵太陰尊者",
			"level"   : 30,
			"moon whip" : 100,
			"attr"    : "wis",
			"attr_min": 22,
			"attr2"   : "int",
			"attr2_min": 20,
			"base"    : "magic",      // 太陰尊者以控制月法證道﹐主法術對應 magic
			"force"   : ({ "太陰真經", "taiyin force" }),
			"skills"  : ({ ({ "太陰冰心訣", "moon-frost magic" }) }),
			"extra"   : ({
				({ "穹槍訣", "sky_pike", "pike" }),
			}),
			"desc"    : "太陰尊者乃天月庵最高一階﹐有太陰真經護體﹐參透太陰冰心訣這門上乘"
			            "控制月法﹐月華化作冰封寒獄、凍敵筋骨奪敵神識﹐另習穹槍訣以槍演月之意。"
			            "太陰冰心訣走 magic(可 cast 寒咒)、穹槍訣走 pike﹐你可自行 map_skill 切換。",
		]),
	]);
}

int do_advance(object me, string branch)
{
	mapping branches, b;
	string base;
	int i;

	if( is_chatting() ) return 0;
	if( !objectp(me) ) return 0;

	branches = query_advance_branches();

	// 分支名無效（含未指定）。
	if( !branch || undefinedp(branches[branch]) ) {
		do_chat("神尼雙手合十﹐宣了聲佛號﹕本庵進階只有「摧魂使者」、「雨花仙子」、"
		        "「太陰尊者」三路﹐施主欲修哪一門月法﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為天月庵入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "天月庵" ) {
		do_chat("神尼搖頭道﹕施主又非我天月庵門下﹐進階之事從何談起﹖且先拜入本庵再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("神尼宣了聲佛號﹕施主既已選定「" + me->query("sect_branch") +
		        "」一脈﹐月法貴在精專﹐豈可見異思遷﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("神尼端詳了你一會﹐輕輕搖頭﹕施主火候尚淺﹐且再潛修些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門鞭法(太陰七損鞭 moon whip)火候門檻。
	if( me->query_skill("moon whip", 1) < b["moon whip"] ) {
		do_chat("神尼道﹕施主連我太陰七損鞭的根基都未練透﹐如何駕馭這上乘月法﹖"
		        "且回庵中勤加參修去。\n");
		return notify_fail("");
	}

	// 屬性門檻（各分支重不同根骨﹕摧魂使者重機敏、雨花/太陰重慧根﹐部分另有第二道屬性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("神尼輕輕搖頭﹕施主的根骨慧根還撐不起這一路月法﹐勉強習之徒傷己身。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("神尼宣了聲佛號﹕施主悟性未足﹐尚參不透太陰冰心訣的精微玄奧﹐"
		        "且去再參修參修。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔摧魂使者沿用入門蓮華心法﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階主招式/法術﹐並把主技對應到該分支的基礎技能（base﹔多技者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的鞭/劍/法術火候)﹔僅當該基礎技能尚未習得時
	// (如雨花仙子改習 sword、太陰尊者沿用入門 magic)補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "whip";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 授副技（身法/槍法等﹐各自掛回其基礎技能﹔如落葉身法→dodge、穹槍訣→pike）。
	if( arrayp(b["extra"]) ) {
		for( i = 0; i < sizeof(b["extra"]); i++ ) {
			string ebase = b["extra"][i][2];
			if( undefinedp(me->query_skill(ebase, 1)) )
				me->set_skill(ebase, 0);
			me->set_skill(b["extra"][i][1], 0);
			me->map_skill(ebase, b["extra"][i][1]);
		}
	}

	// 傳藝氣象。
	message_vision(
		"$N合什誦了聲佛號﹐寶相清冷﹐將一身「" + branch +
		"」的上乘太陰月法傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"神尼宣了聲佛號﹕善哉﹗從今日起﹐你便是我天月庵的「" + b["rank"] + "」了。\n",
		"神尼道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
