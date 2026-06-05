// master.c -- 步玄派掌門 駱易（玄機居士）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("駱易", ({ "luo yi", "scholar master", "master", "scholar", "teacher" }));
	set("nickname", "玄機居士");
	set_attr("str", 20);
	set_attr("dex", 26);
	set_attr("int", 28);
	set_attr("wis", 25);
	set_attr("spi", 24);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("scholar");
	set("sect", "步玄派");
	set("rank", "掌門");
	set("title", "步玄派掌門");

	set_skill("unarmed", 60);
	set_skill("dodge", 120);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("myst-force", 120);
	set_skill("myst-steps", 120);
	set_skill("sword", 150);
	set_skill("buxuan-sword", 150);
	map_skill("force", "myst-force");
	map_skill("dodge", "myst-steps");
	map_skill("sword", "buxuan-sword");

	advance_stat("gin", 220);
	advance_stat("kee", 200);
	advance_stat("sen", 220);

	set("age", 52);
	set("long",
		"這位便是步玄派的掌門﹐一襲洗得發白的青布長衫﹐頭束方巾﹐手中\n"
		"輕搖一柄折扇﹐腰間斜佩著一柄古樸的長劍。他面容清癯﹐三縷長鬚\n"
		"飄拂胸前﹐雙目澄澈如水﹐顧盼之間既有書生的儒雅﹐又隱隱透著一\n"
		"股劍客的鋒芒。步玄派書生一脈以劍法佐控場、以文心參武道﹐掌門\n"
		"浸淫步玄劍法與乾坤三轉之術數十年﹐一身文武已臻化境﹐江湖人稱\n"
		"「玄機居士」。他平日在論劍堂中讀書論劍﹐唯有心思靈巧、悟性不\n"
		"俗的後輩﹐方有機會拜入門下﹐習得這一身步玄劍法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("駱易輕搖折扇﹐說道﹕你既已入別派﹐道途已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("駱易微笑道﹕你塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 步玄劍法全憑悟性參詳﹐悟性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("int") < 14 ) {
		do_chat("駱易端詳了你一會﹐搖頭道﹕你悟性閉塞﹐難參我這路劍法。\n");
		return 0;
	}

	do_chat(({
		"駱易上下打量了你一番﹐微微頷首。\n",
		"駱易說道﹕我步玄派書生一脈﹐以劍佐文、以步藏機﹐你可有這份慧心﹖\n",
		"駱易合扇笑道﹕也罷﹐你既悟性不俗﹐我便收你入步玄門下﹐傳你步玄劍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("駱易搖了搖折扇﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("scholar");
		me->set("sect", "步玄派");
		me->set("rank", "居士");
		me->set("title", "步玄派居士");

		me->set_skill("sword", 0);
		me->set_skill("buxuan-sword", 0);
		me->map_skill("sword", "buxuan-sword");

		// 同時授予步玄心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("myst-force", 0);
		me->map_skill("force", "myst-force");

		message_vision(
			"$N取過一柄長劍﹐將小步玄劍的入門劍訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"駱易說道﹕從今日起﹐你便是我步玄派居士門下的弟子了。\n",
			"駱易說道﹕劍道無涯﹐你且到演武場勤加錘鍊﹐莫負了這身劍法。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 書生(scholar)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的步玄派居士
// 弟子轉入三大進階分支之一。比照武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀
// d/hudao)、道士天師(d/tianshi)、和尚白象(d/baixiang)、書生玄天(d/xuantian)
// 的授技模型(門檻更高、以 sect_branch 標記分支、升階 rank/title)。本門與其
// 同職業(scholar)的姊妹派玄天教(d/xuantian)對位﹕玄天偏 PvP 控場(scholar.sky)﹐
// 步玄偏 PvE 練功、雙劍輕功(scholar.myst)﹐docs 評分「居士步玄 攻 B/防 B/續戰 S
// /靈活 B」﹐故進階主軸是「乾坤三轉」循環內功 + 雙劍/奇門/虛空劍法 + 逍遙身法。
//
// 與其它門派的關鍵差異(職業特性)：
//   * 入門武功為劍法(sword)﹐入門時 map_skill("sword","buxuan-sword")(小步玄劍)﹐
//     入門火候門檻即以 "buxuan-sword" 計(對應武者的 lunmay/fonxansword/bawang
//     blade、道士的 taoism-fire、和尚的 rid-evil、玄天的 xuantian-sword)。
//   * 入門時亦授步玄心法(myst-force)為內功、步玄七絕(myst-steps)為身法﹔部分
//     進階分支沿用步玄心法、部分另授更上乘的乾坤三轉心法(qiankun-force)。
//   * 進階各分支的 "base" 多為 sword(劍法)﹔逍遙居士一脈另授副技 dodge(逍遙遊)﹐
//     凸顯步玄「身法輕盈、更像武者」的定位。
//   * 屬性主門檻為 "dex"(機敏﹐步玄雙劍步法輕盈之本)﹔逍遙居士另設第二道 "int"
//     (悟性﹐步玄「升級需念書、逍遙遊視悟性恢復精氣」之本﹐拜入時即驗 int)門檻。
//
// 三大分支(見 docs/03-門派與武功/04-書生-步玄玄天.md §1 步玄派)：
//   居士        ── docs 明列之步玄派進階(「居士進階：乾坤三轉」)。主授步玄雙龍劍氣
//                  dual-dragon-sword(docs §9/2 平衡「步玄雙龍劍氣 必兩次命中」﹔
//                  沿用入門步玄心法)。最早開放、門檻最低。
//   奇門劍士    ── 承 docs「奇門劍訣(累積七點後發動、出招機率跟 int 有關)」與居士進階
//                  「乾坤三轉…下次攻擊觸發奇門劍訣」之奇門控場一脈(分支名為設計﹐
//                  docs未明定階名)。內功 乾坤三轉心法 qiankun-force(docs「乾坤三轉:
//                  步玄心法增加 rotate」) + 主劍法 奇門劍訣 qimen-sword。門檻居中。
//   逍遙居士    ── 承 docs「虛空斬 vacancy ax」與「逍遙遊(120 級恢復精氣、四倍躲閃)」
//                  之最上乘一脈(分支名為設計(docs未明定階名):承居士以虛空斬、逍遙遊
//                  證道之最高一階)。內功 乾坤三轉心法 qiankun-force + 主劍法 虛空斬
//                  vacancy-ax + 副技身法 逍遙遊 xiaoyao-steps(base=dodge)。門檻最高、
//                  另設第二道屬性(int)門檻。
//
// 轉職門檻(條件)為本次設計值(docs 只給評分/機制非確切數字)﹐供日後平衡微調﹕
//   key        level  buxuan-sword  attr 門檻              授內功         授武功(base)
//   ────────── ─────  ────────────  ────────────────────  ────────────  ───────────────────────────
//   居士       20     60            dex >= 18             (沿用步玄心法) 步玄雙龍劍氣 dual-dragon-sword (sword)
//   奇門劍士   25     80            dex >= 20             乾坤三轉心法   奇門劍訣 qimen-sword (sword)
//   逍遙居士   30     100           dex >= 22, int >= 20  乾坤三轉心法   虛空斬 vacancy-ax (sword)
//                                                                        +逍遙遊 xiaoyao-steps (dodge)
//
// 註(居士 docs 依據)：docs 步玄派進階明列「居士進階：乾坤三轉」(步玄心法 rotate、
//   消耗 100 神恢復 50% 精氣、下次攻擊觸發奇門劍訣)﹔步玄雙龍劍氣 docs §9/2 平衡
//   明列為居士看家劍法。乾坤三轉「rotate/消耗神」屬 perform/精氣循環系統 TODO﹐
//   居士分支先授步玄雙龍劍氣並 gate level/skill/attr。
// 註(逍遙居士 docs 原值)：docs「逍遙遊」明載「120 級後…獲得四倍躲閃」﹐屬 120 級
//   高階 perform/精氣系統(同冷梅虎督「拜入天邪」、虎刀鬼才「5000 殺業」、天師太乙
//   「青邪戰勳 3000」、玄天四廠都督「投靠四廠」之故事/系統門檻)﹐標記為待接的 TODO﹔
//   本驗證線取 lv30 / buxuan-sword 100 / dex22 / int20(與封山劍客、冷梅虎督、虎刀
//   太守、天師太乙、白象降魔尊者、玄天四廠都督同階)替代。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(步玄諸進階皆以 sword 劍法為主)。
// "extra" 為另授的副技﹕({ ({中文,英文,基礎技能}), ... })﹐授技後 map_skill(基礎,英文)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"居士" : ([
			"rank"    : "步玄居士",
			"title"   : "步玄派居士",
			"level"   : 20,
			"buxuan-sword" : 60,
			"attr"    : "dex",
			"attr_min": 18,
			"base"    : "sword",
			"force"   : 0,    // 居士不另授內功﹐沿用入門步玄心法(myst-force)
			"skills"  : ({ ({ "步玄雙龍劍氣", "dual-dragon-sword" }) }),
			"desc"    : "步玄雙龍劍氣乃步玄居士的看家劍訣﹐雙劍合璧、雙龍出海﹐一招兩擊、"
			            "必兩次命中﹐攻防一體而續戰綿長﹐宜久戰纏鬥。善用之。",
		]),
		"奇門劍士" : ([
			"rank"    : "步玄奇門劍士",
			"title"   : "步玄派奇門劍士",
			"level"   : 25,
			"buxuan-sword" : 80,
			"attr"    : "dex",
			"attr_min": 20,
			"base"    : "sword",
			"force"   : ({ "乾坤三轉心法", "qiankun-force" }),
			"skills"  : ({ ({ "奇門劍訣", "qimen-sword" }) }),
			"desc"    : "奇門劍士以乾坤三轉心法佐奇門劍訣﹐內力周天循環、生生不息﹐劍走"
			            "奇正相生、五行佈陣﹐封困敵手、料敵機先﹐乃步玄控場(奇門/定人)的"
			            "看家本領。",
		]),
		"逍遙居士" : ([
			"rank"    : "步玄逍遙居士",
			"title"   : "步玄派逍遙居士",
			"level"   : 30,
			"buxuan-sword" : 100,
			"attr"    : "dex",
			"attr_min": 22,
			"attr2"   : "int",
			"attr2_min": 20,
			"base"    : "sword",
			"force"   : ({ "乾坤三轉心法", "qiankun-force" }),
			"skills"  : ({ ({ "虛空斬", "vacancy-ax" }) }),
			"extra"   : ({
				({ "逍遙遊", "xiaoyao-steps", "dodge" }),
			}),
			"desc"    : "逍遙居士乃步玄居士武學的極致﹐虛空斬劍意斬空、無中生有﹐劍氣縱橫"
			            "如裂虛空﹐輔以逍遙遊身法身隨意走、來去逍遙。虛空斬走 sword、逍遙"
			            "遊走 dodge﹐自此你便是步玄登峰造極的劍客。",
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
		do_chat("駱易輕搖折扇道﹕我步玄派進階只有「居士」、「奇門劍士」、"
		        "「逍遙居士」三路﹐你欲修哪一脈劍法﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為步玄派入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "步玄派" ) {
		do_chat("駱易搖頭道﹕你又非我步玄門下﹐進階之事從何談起﹖且先拜入本派再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("駱易道﹕你既已選定「" + me->query("sect_branch") +
		        "」一脈﹐劍道貴在專一﹐豈可見異思遷﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("駱易端詳了你一會﹐搖頭道﹕你火候尚淺﹐且再潛修些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門劍法(小步玄劍 buxuan-sword)火候門檻。
	if( me->query_skill("buxuan-sword", 1) < b["buxuan-sword"] ) {
		do_chat("駱易道﹕你連我小步玄劍的根基都未練透﹐如何駕馭這上乘劍訣﹖"
		        "且回演武場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（步玄以機敏為本﹐逍遙居士另有第二道悟性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("駱易搖頭道﹕你的根骨還撐不起這一路劍法﹐勉強習之徒耗心神。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("駱易搖頭道﹕你悟性未足﹐參不透虛空斬與逍遙遊的玄奧﹐"
		        "且去多念些書再參修參修。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔居士沿用入門步玄心法﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階主招式﹐並把主招式對應到該分支的基礎技能（base﹔多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的劍法火候)﹔僅當該基礎技能尚未習得時
	// 補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "sword";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 授副技（身法等﹐各自掛回其基礎技能﹔如逍遙遊→dodge）。
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
		"$N橫劍於膝﹐閉目凝神片刻﹐而後將一身「" + branch +
		"」的上乘劍訣傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"駱易合扇笑道﹕好﹗從今日起﹐你便是我步玄派的「" + b["rank"] + "」了。\n",
		"駱易道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
