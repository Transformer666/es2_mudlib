// master.c -- 大內巡院統領（大內徵兵官 李天剛）
//
// 大內巡院是京畿的軍人(soldier)門派﹐與雪亭鎮的振武軍營同為軍人一脈﹐
// 故本檔結構完全比照 d/zhenwu/npc/master.c﹐沿用既有的 soldier class﹐
// 只是兵器由龍神槍法(pike)改為大內劍法(sword)、內功由瘋虎功改為大內
// 罡氣(danei force)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("李天剛", ({ "danei master", "master", "li tiangang", "official" }));
	set("nickname", "巡院統領");
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
	set("sect", "大內巡院");
	set("rank", "大內高手");
	set("title", "大內巡院高手");

	set_skill("unarmed", 60);
	set_skill("dodge", 90);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("sword", 150);
	set_skill("danei sword", 150);
	map_skill("sword", "danei sword");
	set_skill("danei force", 120);
	map_skill("force", "danei force");

	advance_stat("gin", 240);
	advance_stat("kee", 240);
	advance_stat("sen", 160);

	set("age", 50);
	set("gender", "male");
	set("long",
		"這位便是大內巡院的統領李天剛﹐一身玄色勁裝外罩繡金的緋色\n"
		"罩甲﹐腰懸一柄三尺長劍﹐身形挺拔如鬆﹐按劍而立﹐自有一股久\n"
		"鎮禁中的森嚴威儀。他面容方正﹐劍眉斜飛入鬢﹐一雙鷹目精光內\n"
		"斂﹐顧盼之間透著緝事多年的精悍幹練。大內巡院統領一脈宿衛皇\n"
		"城、護駕緝兇﹐統領浸淫大內劍法數十年﹐一柄長劍守得帝都固若\n"
		"金湯﹐人稱「巡院統領」。他奉旨在此徵募新血﹐唯有身手矯健、\n"
		"忠勇可靠的後輩﹐方有機會拜入麾下﹐學得這一身護衛天家的本事。\n");
	setup();
	carry_object("/obj/area/obj/longsword")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("李天剛按劍肅然道﹕你既已入別派﹐宿衛之職難托﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可投軍宿衛
	if( me->query_level() < 1 ) {
		do_chat("李天剛上下打量了你一眼﹐喝道﹕乳臭未乾的雛兒﹐且去歷練一番再來投效罷。\n");
		return 0;
	}

	// 宿衛禁中全憑一身膂力與筋骨﹐孱弱者扛不起這份差事（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("str") < 14 ) {
		do_chat("李天剛搖頭道﹕你這身子骨連長劍都使不穩﹐如何宿衛禁中﹖且去練壯了再來。\n");
		return 0;
	}

	if( me->query_attr("con") < 14 ) {
		do_chat("李天剛端詳片刻﹐沉聲道﹕你筋骨太過虛弱﹐熬不住巡夜值更的辛勞﹐且去將養好了再來。\n");
		return 0;
	}

	do_chat(({
		"李天剛抱起雙臂﹐將你細細打量了一番。\n",
		"李天剛朗聲道﹕我大內巡院軍法森嚴﹐宿衛禁中半點馬虎不得﹐你可擔得起這份重任﹖\n",
		"李天剛頷首一笑﹕也罷﹐瞧你還算有把子身手﹐我便收你入巡院門下﹐傳你這套護駕的劍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("李天剛把長劍一收﹐說道﹕你既已另投他處﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("soldier");
		me->set("sect", "大內巡院");
		me->set("rank", "大內高手");
		me->set("title", "大內巡院高手");

		me->set_skill("sword", 0);
		me->set_skill("danei sword", 0);
		me->map_skill("sword", "danei sword");

		// 同時授予大內罡氣（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("danei force", 0);
		me->map_skill("force", "danei force");

		message_vision(
			"$N抽出一柄長劍﹐將大內劍法的入門劍勢一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"李天剛朗聲道﹕從今日起﹐你便是我大內巡院的宿衛了。\n",
			"李天剛沉聲道﹕到校場領柄長劍勤加操練﹐劍要正、步要穩、心要忠﹐莫墮了巡院的威名。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 軍人(soldier)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的大內巡院宿衛
// 轉入三大進階分支之一。比照武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀 d/hudao)、
// 道士天師(d/tianshi)、和尚白象(d/baixiang)的授技模型(門檻更高、以 sect_branch
// 標記分支、升階 rank/title)﹐惟本門為「軍人(soldier)」職業﹐入門兵器為大內劍法
// (基礎技能 sword)、入門內功為大內罡氣(danei force)——故進階以高階劍法/內功為主﹐
// 與同屬 soldier 一脈、卻以龍神槍法(pike)入門的振武軍營(d/zhenwu)走不同兵器路線。
//
// 與前五門共用的關鍵欄位：
//   * "base" 一律為 "sword"(劍法)﹔授技後 map_skill("sword", <英文 key>)。入門時即
//     map_skill("sword","danei sword")﹐進階沿此模型把 sword 改映到更上乘的劍訣。
//   * 入門劍法火候門檻以入門大內劍法 "danei sword" 計(對應武者的 lunmay/fonxansword
//     /bawang blade、道士的 taoism-fire、和尚的 rid-evil)。
//   * 屬性主門檻以 "str"(膂力﹐宿衛禁中、按劍護駕之本)為主﹐高階分支另設第二道屬性
//     (con 根骨)門檻﹔最高一階另設 docs 軍人尚武一脈的「男性」門檻(見下注)。
//
// 三大分支(見 docs/03-門派與武功/06-軍人-振武大內.md §2 大內巡院 soldier.royal)：
//   大內高手  ── docs 明列之大內巡院進階。授高階劍法 神威劍訣 royal-sword(承 docs
//                「穹槍訣 sky_pike：神威下攻擊對目標精傷」之意﹐惟本門以劍代槍﹐故以
//                劍訣承之)。最早開放、門檻最低。docs 條件原為 lv40﹐此處取與他門同階
//                的 lv20 驗證線(見下注)。
//   大內供奉  ── 授內功 大內心法 royal force(docs 核心技能﹐神威狀態提升護甲傷害)
//                + 高階劍法 盤龍劍訣 royal-coil-sword。神威內功一脈﹐重在護體續戰。
//                門檻居中、另設第二道屬性(con)門檻。
//   大內都統  ── 軍人最高一階(設計(docs未明定分支名):承大內高手以重擊證道)。授重擊
//                絕學 穹劍訣 sky-sword(承 docs 穹槍訣 sky_pike 精傷之意的最高一式)
//                + 大內心法 royal force。門檻最高、雙屬性(con)門檻﹐另設男性門檻。
//
// 轉職門檻(條件)為本次設計值(docs 大內高手給的 lv40 偏成品線)﹐供日後平衡微調﹕
//   key        level  danei sword  attr 門檻              其它      授內功         授劍法(base=sword)
//   ────────── ─────  ───────────  ────────────────────  ────────  ────────────  ───────────────────────
//   大內高手   20     60           str >= 18             ─         (沿用大內罡氣) 神威劍訣 royal-sword
//   大內供奉   25     80           str >= 20, con >= 18  ─         大內心法       盤龍劍訣 royal-coil-sword
//   大內都統   30     100          str >= 22, con >= 20  男性      大內心法       穹劍訣 sky-sword
//
// 註(大內高手 docs 原值)：docs 載大內巡院進階「大內高手」條件為 lv40(且不收形天/
//   阿修羅/夜叉)﹐授穹槍訣 sky_pike。本驗證線取 lv20 / danei sword 60 / str18(與冷梅
//   劍士、封山劍靈、虎刀護衛、天師朱衣真傳、白象羅漢同階)﹐待平衡時可逐步上修回 docs
//   成品值﹔「不收形天/阿修羅/夜叉」屬種族門檻﹐標記為待接的種族門檻 TODO(同冷梅虎督
//   「拜入天邪」、虎刀鬼才「5000 殺業」之故事門檻)。
// 註(穹槍訣→劍訣)：docs 穹槍訣 sky_pike(已見 data/chinese.o)為槍法﹐本門以大內劍法
//   (sword)入門﹐故大內高手/都統所授承「穹」之意改以劍訣 royal-sword / sky-sword 承之
//   (基礎技能 sword)﹐非沿用槍法 key﹐以免映射落到玩家未習的 pike 槽。
// 註(大內都統「男性」)：軍人尚武一脈剛猛傷身﹐比照虎刀太守﹐最高一階設男性門檻﹐為
//   設計(docs未明定):與他門最高階對位之硬條件。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(大內諸進階皆以 sword 劍法為主)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)﹔"male" 為設計之性別門檻。
mapping query_advance_branches()
{
	return ([
		"大內高手" : ([
			"rank"    : "大內高手",
			"title"   : "大內巡院高手",
			"level"   : 20,
			"danei sword" : 60,
			"attr"    : "str",
			"attr_min": 18,
			"base"    : "sword",
			"force"   : 0,    // 大內高手沿用入門大內罡氣(danei force)﹐不另授內功
			"skills"  : ({ ({ "神威劍訣", "royal-sword" }) }),
			"desc"    : "神威劍訣乃大內巡院進階之始﹐承穹槍訣之意以劍代槍﹐神威狀態下"
			            "劍招挾真氣劈出﹐可削敵精氣、護駕克敵﹐宜久戰宿衛。",
		]),
		"大內供奉" : ([
			"rank"    : "大內供奉",
			"title"   : "大內巡院供奉",
			"level"   : 25,
			"danei sword" : 80,
			"attr"    : "str",
			"attr_min": 20,
			"attr2"   : "con",
			"attr2_min": 18,
			"base"    : "sword",
			"force"   : ({ "大內心法", "royal force" }),
			"skills"  : ({ ({ "盤龍劍訣", "royal-coil-sword" }) }),
			"desc"    : "供奉一脈兼修大內心法﹐神威護體、提升護甲與傷害﹐盤龍劍訣綿密"
			            "纏鬥、長於續戰﹐是宿衛禁中最堅實的中堅。",
		]),
		"大內都統" : ([
			"rank"    : "大內都統",
			"title"   : "大內巡院都統",
			"level"   : 30,
			"danei sword" : 100,
			"attr"    : "str",
			"attr_min": 22,
			"attr2"   : "con",
			"attr2_min": 20,
			"male"    : 1,    // 軍人尚武一脈剛猛傷身﹐最高一階設男性門檻(比照虎刀太守)
			"base"    : "sword",
			"force"   : ({ "大內心法", "royal force" }),
			"skills"  : ({ ({ "穹劍訣", "sky-sword" }) }),
			"desc"    : "都統乃大內最高一階﹐穹劍訣承穹槍訣精傷之意化作劍法絕學﹐神威"
			            "狀態下一劍貫頂、直削敵之精氣﹐配大內心法護體﹐攻守俱臻化境。",
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
		do_chat("李天剛按劍肅然道﹕我大內巡院進階只有「大內高手」、「大內供奉」、"
		        "「大內都統」三路﹐你欲修哪一門﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為大內巡院入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "大內巡院" ) {
		do_chat("李天剛冷然道﹕你又非我大內巡院宿衛﹐進階之事從何談起﹖且先拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("李天剛搖頭道﹕你既已選定「" + me->query("sect_branch") +
		        "」一路﹐宿衛之道貴在專一﹐豈可朝三暮四﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("李天剛上下打量了你一眼﹐搖頭道﹕你火候尚淺﹐且再歷練些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門劍法(大內劍法 danei sword)火候門檻。
	if( me->query_skill("danei sword", 1) < b["danei sword"] ) {
		do_chat("李天剛沉聲道﹕你連我大內劍法的根基都未練透﹐如何學得這上乘劍訣﹖"
		        "且回校場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（軍人以膂力為本﹐高階分支另有第二道根骨門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("李天剛搖頭道﹕你這身膂力還撐不起這一路劍法﹐勉強習之徒傷己身。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("李天剛端詳片刻﹐沉聲道﹕你筋骨根基仍有所偏廢﹐熬不住這一路劍法的耗損﹐"
		        "且去再將養將養。\n");
		return notify_fail("");
	}

	// 設計之性別門檻（如大內都統須為男性）。
	if( b["male"] && me->query("gender") != "male" ) {
		do_chat("李天剛搖頭道﹕都統一脈的劍法剛猛傷身、耗元甚鉅﹐自古只傳男子﹐"
		        "你這身子骨承受不住﹐另擇一路罷。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔大內高手沿用入門大內罡氣﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階劍法﹐並把主招式對應到該分支的基礎技能（base=sword﹔多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的劍法火候)﹔僅當該基礎技能尚未習得時補初始
	// 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "sword";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 傳藝氣象。
	message_vision(
		"$N抽劍出鞘﹐肅然按劍片刻﹐而後將一身「" + branch +
		"」的上乘劍訣傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"李天剛朗聲道﹕好﹗從今日起﹐你便是我大內巡院的「" + b["rank"] + "」了。\n",
		"李天剛沉聲道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
