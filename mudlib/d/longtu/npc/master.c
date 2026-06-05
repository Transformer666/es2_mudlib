// master.c -- 龍圖丹派掌門 陳維俠（牙山居士）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("陳維俠", ({ "chen weixia", "master", "alchemist", "physician", "doctor" }));
	set("nickname", "牙山居士");
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
	set("sect", "龍圖丹派");
	set("rank", "掌門");
	set("title", "龍圖丹派掌門");

	set_skill("unarmed", 50);
	set_skill("dodge", 100);
	set_skill("parry", 80);
	set_skill("force", 120);
	set_skill("dragon force", 120);
	set_skill("needle", 150);
	set_skill("amazing-needle", 150);
	set_skill("alchemy-medication", 150);
	map_skill("force", "dragon force");
	map_skill("needle", "amazing-needle");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 58);
	set("long",
		"這位便是龍圖丹派的掌門陳維俠﹐一身青布道袍洗得發白﹐鬚眉皆已\n"
		"花白﹐面色卻紅潤如嬰﹐雙目溫和而有神。他腰間懸著一只盛放銀\n"
		"針的錦匣﹐袖中常帶藥香。龍圖丹派以煉丹施針、懸壺濟世名動江\n"
		"湖﹐掌門浸淫龍圖心經與武陀灸術數十年﹐一手驚異二針出神入化\n"
		"﹐針到病除﹐活人無數﹐江湖人尊稱一聲「牙山居士」。他久居醫\n"
		"館坐堂施診﹐唯有心存仁念、悟性不俗的後輩﹐方有機會拜入門下\n"
		"﹐習得這一身濟世活人的醫術針法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("陳維俠捻著鬚﹐溫言道﹕你既已入別派﹐醫緣已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("陳維俠說道﹕你塵緣未歷﹐且去江湖上走動一番再來罷。\n");
		return 0;
	}

	// 醫道針法全憑一身悟性參詳﹐悟性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("int") < 14 ) {
		do_chat("陳維俠端詳了你一會﹐搖頭道﹕你悟性閉塞﹐難參經絡藥性之奧﹐學不來我這路醫術。\n");
		return 0;
	}

	do_chat(({
		"陳維俠上下打量了你一番﹐微微頷首。\n",
		"陳維俠說道﹕我龍圖丹派以針藥濟世﹐你可有這份救人的仁心﹖\n",
		"陳維俠捻鬚一笑﹕也罷﹐你既心存仁念、悟性不俗﹐我便收你為徒﹐傳你這一身醫術針法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("陳維俠擺了擺手﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("alchemist");
		me->set("sect", "龍圖丹派");
		me->set("rank", "醫師");
		me->set("title", "龍圖丹派醫師");

		me->set_skill("needle", 0);
		me->set_skill("amazing-needle", 0);
		me->map_skill("needle", "amazing-needle");

		// 同時授予龍圖心經（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("dragon force", 0);
		me->map_skill("force", "dragon force");

		message_vision(
			"$N取出一匣銀針﹐捻起一枚﹐將武陀灸術【驚異二針】的入門針法一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"陳維俠說道﹕從今日起﹐你便是我龍圖丹派醫師門下的弟子了。\n",
			"陳維俠叮囑道﹕醫者父母心﹐你且到演武場對著銅人勤練針法﹐辨穴施針﹐莫負了這身醫術。\n",
			"陳維俠又道﹕丹房裡架著丹爐﹐你備齊藥材﹐便可在爐前 refine（煉丹）煉製丹藥。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 方士(alchemist)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的龍圖丹派醫師
// 弟子轉入三大進階分支之一。比照武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀
// d/hudao)、道士天師(d/tianshi)、和尚白象(d/baixiang)的授技模型(門檻更高、以
// sect_branch 標記分支、升階 rank/title)﹐惟本門為「方士(alchemist)」職業──
// 一個以煉丹/針法/治療為本的非戰鬥(craft/heal)職業﹐故進階所授為針法(needle)、
// 鈍器鎚法(blunt)與內功(force)﹐以此驗證通用「進階」指令 + do_advance 模型可
// 再度跨職業(武者/道士/和尚之外)套用於生產職業。
//
// 與前數門的關鍵差異(職業特性)：
//   * 入門武功為針法(needle)﹐入門時 map_skill("needle","amazing-needle")(武陀灸術
//     【驚異二針】)﹐入門火候門檻即以 "amazing-needle" 計(對應武者的 lunmay/
//     fonxansword/bawang blade、道士的 taoism-fire、和尚的 rid-evil)。
//   * 入門時亦 map_skill("force","dragon force")(龍圖心經)﹐部分進階沿此精進內功。
//   * 屬性主門檻為 "int"(悟性，方士辨穴煉丹之本)﹐非 str/dex/spi/wis。
//
// 三大分支(見 docs/03-門派與武功/07-方士-龍圖武陀.md §龍圖丹派 進階﹕醫師、
//   劍甲門傳人﹔README 對應表「龍圖丹派 → 醫師、劍甲門傳人」)：
//   杏林神手  ── 針法 金針渡劫針法 golden-needle(主)﹐沿用入門龍圖心經。針法一脈
//                的精進﹐辨穴施針、針到病除。最早開放、門檻最低。
//                設計(docs未明定分支名):承「醫師」針法一脈的精修階。
//   劍甲門傳人 ── docs 明列之兩派共通進階(本門的戰鬥/裝備強化路)。內功 靈甲術
//                lingjia force(docs 明列典型玩家 Kankichi「靈甲術 200」) + 鈍器鎚法
//                金剛鎚法 jingang-zarn(docs 明列「金剛鎚法 200」﹐基礎技能 blunt)。
//                自此方士得一身戰力與灌裝強化之能。門檻居中。
//   龍圖丹師  ── 方士最高一階(設計(docs未明定分支名):承龍圖丹派掌門「丹師」之號)。
//                內功 龍圖真經 longtu force(由龍圖心經 dragon force 精進) + 針法
//                龍圖丹針 dragon-needle(主)。門檻最高、另設第二道屬性(wis)門檻。
//                docs「龍圖心經 lv30/悟性30/內功90」標記為此階的內功成品門檻參照。
//
// 轉職門檻(條件)為本次設計值﹐供日後平衡微調﹕   // 數值為本次設計值
//   key          level  amazing-needle  attr 門檻              授內功         授武功(基礎技能)
//   ──────────── ─────  ──────────────  ────────────────────  ────────────  ────────────────────────────
//   杏林神手     20     60              int >= 18             (沿用龍圖心經) 金針渡劫針法 golden-needle (needle)
//   劍甲門傳人   25     80              int >= 20             靈甲術         金剛鎚法 jingang-zarn (blunt)
//   龍圖丹師     30     100             int >= 22, wis >= 20  龍圖真經       龍圖丹針 dragon-needle (needle)
//
// 註(劍甲門傳人 docs 依據)：docs 明列龍圖/武陀兩派共通進階「劍甲門弟子」﹐其
//   獲戰鬥力與裝備強化(enchance/灌裝備)之能﹐典型玩家 Kankichi 載「金剛鎚法 200、
//   靈甲術 200」。docs 原入門由陳學亮授﹐另載條件「法術60+lv10+兵刃精熟50000」與
//   「紫薇心經 chivi sutra」等前置﹔為與本批進階一致(只 gate level/skill/attr)﹐此
//   處先以入門針法火候 + 悟性門檻替代驗證﹐並標記陳學亮拜師/兵刃精熟50000/紫薇心經
//   為待接的故事門檻 TODO(同冷梅虎督「拜入天邪」、虎刀鬼才「5000 殺業」)。
// 註(龍圖丹師 docs 原值)：docs 龍圖心經習得門檻為「lv30、悟性30、內功90」﹔本階
//   取 lv30 / amazing-needle 100 / int22 / wis20(與封山劍客、虎刀太守、天師太乙真人、
//   白象降魔尊者同階)替代驗證。  // 設計(docs未明定): 龍圖丹師為承掌門「丹師」之號的最高階名
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(杏林神手/龍圖丹師為 needle 針法﹔劍甲門傳人
// 以鈍器鎚法證道故為 blunt)。"attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"杏林神手" : ([
			"rank"    : "杏林神手",
			"title"   : "龍圖丹派杏林神手",
			"level"   : 20,
			"amazing-needle" : 60,
			"attr"    : "int",
			"attr_min": 18,
			"base"    : "needle",
			"force"   : 0,    // 杏林神手不另授內功﹐沿用入門龍圖心經(dragon force)
			"skills"  : ({ ({ "金針渡劫針法", "golden-needle" }) }),
			"desc"    : "杏林神手乃龍圖針法的精進一脈﹐金針渡劫針針渡厄﹐辨穴施針、"
			            "針到病除。針法走 needle 槽﹐你已是醫者中的妙手。",
		]),
		"劍甲門傳人" : ([
			"rank"    : "劍甲門傳人",
			"title"   : "龍圖丹派劍甲門傳人",
			"level"   : 25,
			"amazing-needle" : 80,
			"attr"    : "int",
			"attr_min": 20,
			"base"    : "blunt",
			"force"   : ({ "靈甲術", "lingjia force" }),
			"skills"  : ({ ({ "金剛鎚法", "jingang-zarn" }) }),
			"desc"    : "劍甲門乃兩派方士共通的進階﹐自此你得一身戰力與灌裝強化之能。"
			            "靈甲術護體生甲﹐金剛鎚法走 blunt 鈍器、剛猛沉雄﹐方士不再只是"
			            "後方的郎中﹐亦能臨陣搏殺、為同道強化兵甲。",
		]),
		"龍圖丹師" : ([
			"rank"    : "龍圖丹師",
			"title"   : "龍圖丹派丹師",
			"level"   : 30,
			"amazing-needle" : 100,
			"attr"    : "int",
			"attr_min": 22,
			"attr2"   : "wis",
			"attr2_min": 20,
			"base"    : "needle",
			"force"   : ({ "龍圖真經", "longtu force" }),
			"skills"  : ({ ({ "龍圖丹針", "dragon-needle" }) }),
			"desc"    : "龍圖丹師乃本派針法、丹道之大成﹐龍圖真經內息醇厚、龍圖丹針出神"
			            "入化﹐針鋒所至、活人無數。針法走 needle 槽﹐你已盡得龍圖一脈"
			            "濟世活人的醫術真傳。",
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
		do_chat("陳維俠捻鬚道﹕我龍圖丹派進階只有「杏林神手」、「劍甲門傳人」、"
		        "「龍圖丹師」三路﹐你欲修哪一門醫術﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為龍圖丹派入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "龍圖丹派" ) {
		do_chat("陳維俠搖頭道﹕你又非我龍圖丹派門下﹐進階之事從何談起﹖且先拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("陳維俠捻鬚道﹕你既已選定「" + me->query("sect_branch") +
		        "」一脈﹐醫道貴在專精﹐豈可見異思遷﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("陳維俠端詳了你一會﹐搖頭道﹕你火候尚淺﹐且再潛修些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門針法(武陀灸術【驚異二針】 amazing-needle)火候門檻。
	if( me->query_skill("amazing-needle", 1) < b["amazing-needle"] ) {
		do_chat("陳維俠道﹕你連我驚異二針的根基都未練透﹐如何駕馭這上乘醫術﹖"
		        "且回演武場對著銅人勤練針法去。\n");
		return notify_fail("");
	}

	// 屬性門檻（方士以悟性為本﹐部分分支另有第二道屬性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("陳維俠搖頭道﹕你悟性未足﹐尚參不透這一脈醫術的奧妙﹐"
		        "勉強學之徒亂心神。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("陳維俠搖頭道﹕你慧根尚淺﹐參不透龍圖一脈丹道、針法的至理﹐"
		        "且去再參修參修。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔杏林神手沿用入門龍圖心經﹐故為 0）。
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
		"」的上乘醫術針法傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"陳維俠捻鬚含笑道﹕善哉﹗從今日起﹐你便是我龍圖丹派的「" + b["rank"] + "」了。\n",
		"陳維俠道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
