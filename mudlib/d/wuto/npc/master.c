// master.c -- 武陀灸堂香主 鬼華陀 武道通

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("武道通", ({ "wuto master", "master", "physician", "wudaotong" }));
	set("nickname", "鬼華陀");
	set_attr("str", 18);
	set_attr("dex", 26);
	set_attr("int", 28);
	set_attr("wis", 26);
	set_attr("spi", 25);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 24);
	set_race("human");
	set_level(40);
	set_class("alchemist");
	set("sect", "武陀灸堂");
	set("rank", "香主");
	set("title", "武陀灸堂香主鬼華陀");

	set_skill("unarmed", 50);
	set_skill("dodge", 100);
	set_skill("parry", 80);
	set_skill("force", 120);
	set_skill("wuto force", 120);
	set_skill("needle", 150);
	set_skill("wuto-needle", 150);
	set_skill("alchemy-medication", 150);
	map_skill("force", "wuto force");
	map_skill("needle", "wuto-needle");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 61);
	set("long",
		"這位便是武陀灸堂的香主﹐人稱「鬼華陀」武道通。他一身洗得發\n"
		"白的灰布長衫﹐鬚眉如戟﹐面色黝黑而目光如炬﹐腰間懸著一只盛\n"
		"放銀針的烏木匣﹐袖中常帶艾草的辛香。武陀灸堂以針灸艾灸救死\n"
		"扶傷名動江湖﹐香主浸淫武陀灸術數十年﹐一手五敗針法辨穴如神\n"
		"﹐針到病除﹐又能以針克敵、封脈截經﹐活人無數而罕逢敵手。他\n"
		"久居灸堂坐堂施診﹐唯有心存仁念、悟性不俗的後輩﹐方有機會拜\n"
		"入門下﹐習得這一身濟世活人的灸術針法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("武道通捻著鬚﹐沉聲道﹕你既已入別派﹐醫緣已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("武道通說道﹕你塵緣未歷﹐且去江湖上走動一番再來罷。\n");
		return 0;
	}

	// 灸術針法全憑一身悟性參詳﹐悟性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("int") < 14 ) {
		do_chat("武道通端詳了你一會﹐搖頭道﹕你悟性閉塞﹐難參經絡穴道之奧﹐學不來我這路灸術。\n");
		return 0;
	}

	do_chat(({
		"武道通上下打量了你一番﹐微微頷首。\n",
		"武道通說道﹕我武陀灸堂以針艾濟世﹐你可有這份救人的仁心﹖\n",
		"武道通捻鬚一笑﹕也罷﹐你既心存仁念、悟性不俗﹐我便收你為徒﹐傳你這一身灸術針法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("武道通擺了擺手﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("alchemist");
		me->set("sect", "武陀灸堂");
		me->set("rank", "香主弟子");
		me->set("title", "武陀灸堂香主弟子");

		me->set_skill("needle", 0);
		me->set_skill("wuto-needle", 0);
		me->map_skill("needle", "wuto-needle");

		// 同時授予武陀心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("wuto force", 0);
		me->map_skill("force", "wuto force");

		message_vision(
			"$N取出一匣銀針﹐捻起一枚﹐將武陀灸術【五敗針法】的入門針法一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"武道通說道﹕從今日起﹐你便是我武陀灸堂香主門下的弟子了。\n",
			"武道通叮囑道﹕醫者父母心﹐你且到演武場對著銅人勤練針法﹐辨穴施針﹐莫負了這身灸術。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 方士(alchemist)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的武陀灸堂香主
// 門下弟子轉入三大進階分支之一。比照同為方士(alchemist)的姊妹門「龍圖丹派」
// d/longtu/npc/master.c﹐以及武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀 d/hudao)、
// 道士天師(d/tianshi)、和尚白象(d/baixiang)的授技模型(門檻更高、以 sect_branch
// 標記分支、升階 rank/title)。武陀灸堂為「方士(alchemist)」職業──一個以針灸/
// 灸術/治療 buff 為本的非戰鬥(heal/buff)職業﹐故進階所授為針法(needle)、鈍器鎚法
// (blunt)與內功(force)。
//
// 與龍圖丹派(姊妹門)的對位與差異：
//   * 入門武功為針法(needle)﹐入門時 map_skill("needle","wuto-needle")(武陀灸術
//     【五敗針法】)﹐入門火候門檻即以 "wuto-needle" 計(龍圖以 "amazing-needle" 計﹐
//     對應武者的 lunmay/fonxansword/bawang blade、道士的 taoism-fire、和尚的 rid-evil)。
//   * 入門時亦 map_skill("force","wuto force")(武陀心法)﹐神農上人沿此精進內功。
//   * 屬性主門檻為 "int"(悟性，方士辨穴施針之本)﹐非 str/dex/spi/wis﹐與龍圖同。
//   * 「劍甲門傳人」為 docs 明列之兩派方士共通進階﹐故沿用龍圖丹派已建之共通
//     daemon﹕內功 靈甲術 lingjia force + 鈍器鎚法 金剛鎚法 jingang-zarn(base=blunt)。
//
// 三大分支(見 docs/03-門派與武功/07-方士-龍圖武陀.md §武陀灸堂 進階﹕香主、劍甲
//   門傳人﹔README 對應表「武陀灸堂 → 香主、劍甲門傳人」)：
//   香主      ── docs 明列之武陀本門進階。針法 霸甲針法 hegen-needle(主)﹐沿用入門
//                武陀心法(wuto force)。docs 載香主「霸氣針後穿滿傷害破 250﹐是團隊
//                不可或缺的 buff 來源」﹐故定位為攻補一體的上乘針法一脈。最早開放、
//                門檻最低。 // 設計(docs未明定分支名):docs 列「香主」進階﹐霸甲針法為其針法精修
//   劍甲門傳人 ── docs 明列之兩派方士共通進階(本門的戰鬥/裝備強化路)。內功 靈甲術
//                lingjia force(docs 明列典型玩家 Kankichi「靈甲術 200」) + 鈍器鎚法
//                金剛鎚法 jingang-zarn(docs 明列「金剛鎚法 200」﹐基礎技能 blunt)。
//                自此方士得一身戰力與灌裝強化之能。門檻居中。沿用龍圖丹派已建之
//                共通 daemon(daemon/skill/lingjia_force.c、jingang-zarn.c)。
//   神農上人  ── 武陀方士最高一階。內功 神農真經 shennong force(由武陀心法 wuto force
//                精進) + 針法 神農針法 shennong-needle(主)。docs 載武陀堂「可修習神農
//                之術」﹐故承神農之術一脈、針法/灸術之大成名之﹐與龍圖丹派最高階
//                「龍圖丹師」對位。門檻最高、另設第二道屬性(wis)門檻。
//                // 設計(docs未明定分支名):承武陀「神農之術」一脈的最高階名
//
// 轉職門檻(條件)為本次設計值﹐供日後平衡微調﹕   // 數值為本次設計值
//   key          level  wuto-needle  attr 門檻              授內功         授武功(基礎技能)
//   ──────────── ─────  ───────────  ────────────────────  ────────────  ────────────────────────────
//   香主         20     60           int >= 18             (沿用武陀心法) 霸甲針法 hegen-needle (needle)
//   劍甲門傳人   25     80           int >= 20             靈甲術         金剛鎚法 jingang-zarn (blunt)
//   神農上人     30     100          int >= 22, wis >= 20  神農真經       神農針法 shennong-needle (needle)
//
// 註(劍甲門傳人 docs 依據)：docs 明列龍圖/武陀兩派共通進階「劍甲門弟子」﹐其
//   獲戰鬥力與裝備強化(enchance/灌裝備)之能﹐典型玩家 Kankichi(劍甲門侍針士)載
//   「金剛鎚法 200、靈甲術 200」。docs 原入門由陳學亮授﹐另載條件「法術60+lv10+
//   兵刃精熟50000」與「紫薇心經 chivi sutra」等前置﹔為與本批進階一致(只 gate
//   level/skill/attr)﹐此處先以入門針法火候 + 悟性門檻替代驗證﹐並標記陳學亮拜師/
//   兵刃精熟50000/紫薇心經為待接的故事門檻 TODO(同冷梅虎督「拜入天邪」、虎刀鬼才
//   「5000 殺業」)。
// 註(香主 docs 原值)：docs 香主二轉條件為「驚異二針、五敗針 sk >180」。本驗證線
//   取 lv20 / wuto-needle 60 / int18(與龍圖杏林神手、各門最低階同階)替代﹐sk>180 之
//   成品門檻標記為待平衡時上修的目標值。
// 註(神農上人 docs 原值)：docs 武陀灸堂明列進階僅「香主、劍甲門傳人」二路﹔神農
//   上人為設計(docs未明定)之最高一階(與龍圖丹師對位)﹐本階取 lv30 / wuto-needle 100 /
//   int22 / wis20(與封山劍客、虎刀太守、天師太乙真人、白象降魔尊者、龍圖丹師同階)。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(香主/神農上人為 needle 針法﹔劍甲門傳人以鈍器
// 鎚法證道故為 blunt)。"attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"香主" : ([
			"rank"    : "武陀香主",
			"title"   : "武陀灸堂香主",
			"level"   : 20,
			"wuto-needle" : 60,
			"attr"    : "int",
			"attr_min": 18,
			"base"    : "needle",
			"force"   : 0,    // 香主不另授內功﹐沿用入門武陀心法(wuto force)
			"skills"  : ({ ({ "霸甲針法", "hegen-needle" }) }),
			"desc"    : "香主乃武陀針法的精進一脈﹐霸甲針法以針布甲、灌氣增傷﹐攻補一體﹐"
			            "是團隊不可或缺的 buff 來源。針法走 needle 槽﹐你已是灸堂的中流"
			            "砥柱。",
		]),
		"劍甲門傳人" : ([
			"rank"    : "劍甲門傳人",
			"title"   : "武陀灸堂劍甲門傳人",
			"level"   : 25,
			"wuto-needle" : 80,
			"attr"    : "int",
			"attr_min": 20,
			"base"    : "blunt",
			"force"   : ({ "靈甲術", "lingjia force" }),
			"skills"  : ({ ({ "金剛鎚法", "jingang-zarn" }) }),
			"desc"    : "劍甲門乃兩派方士共通的進階﹐自此你得一身戰力與灌裝強化之能。"
			            "靈甲術護體生甲﹐金剛鎚法走 blunt 鈍器、剛猛沉雄﹐方士不再只是"
			            "後方的郎中﹐亦能臨陣搏殺、為同道強化兵甲。",
		]),
		"神農上人" : ([
			"rank"    : "武陀神農上人",
			"title"   : "武陀灸堂神農上人",
			"level"   : 30,
			"wuto-needle" : 100,
			"attr"    : "int",
			"attr_min": 22,
			"attr2"   : "wis",
			"attr2_min": 20,
			"base"    : "needle",
			"force"   : ({ "神農真經", "shennong force" }),
			"skills"  : ({ ({ "神農針法", "shennong-needle" }) }),
			"desc"    : "神農上人乃本門針法、灸術之大成﹐神農真經內息醇厚、神農針法出神"
			            "入化﹐針鋒所至、活人無數。針法走 needle 槽﹐你已盡得武陀一脈"
			            "濟世活人的灸術真傳。",
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
		do_chat("武道通捻鬚道﹕我武陀灸堂進階只有「香主」、「劍甲門傳人」、"
		        "「神農上人」三路﹐你欲修哪一門針法﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為武陀灸堂入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "武陀灸堂" ) {
		do_chat("武道通搖頭道﹕你又非我武陀灸堂門下﹐進階之事從何談起﹖且先拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("武道通捻鬚道﹕你既已選定「" + me->query("sect_branch") +
		        "」一脈﹐醫道貴在專精﹐豈可見異思遷﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("武道通端詳了你一會﹐搖頭道﹕你火候尚淺﹐且再潛修些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門針法(武陀灸術【五敗針法】 wuto-needle)火候門檻。
	if( me->query_skill("wuto-needle", 1) < b["wuto-needle"] ) {
		do_chat("武道通道﹕你連我五敗針法的根基都未練透﹐如何駕馭這上乘針法﹖"
		        "且回演武場對著銅人勤練針法去。\n");
		return notify_fail("");
	}

	// 屬性門檻（方士以悟性為本﹐部分分支另有第二道屬性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("武道通搖頭道﹕你悟性未足﹐尚參不透這一脈針法的奧妙﹐"
		        "勉強學之徒亂心神。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("武道通搖頭道﹕你慧根尚淺﹐參不透神農之術、針法的至理﹐"
		        "且去再參修參修。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔香主沿用入門武陀心法﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階主招式﹐並把主招式對應到該分支的基礎技能（base﹔多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的針法/鈍器火候)﹔僅當該基礎技能尚未習得時
	// (如劍甲門傳人改習 blunt﹐入門時未授)補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "needle";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 傳藝氣象。
	message_vision(
		"$N取出一匣銀針﹐捻針凝神﹐將一身「" + branch +
		"」的上乘灸術針法傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"武道通捻鬚含笑道﹕善哉﹗從今日起﹐你便是我武陀灸堂的「" + b["rank"] + "」了。\n",
		"武道通道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
