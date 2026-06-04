// master.c -- 玄天教主 東方孤冥

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("東方孤冥", ({ "xuantian master", "master", "scholar", "dongfang" }));
	set("nickname", "玄天教主");
	set_attr("str", 20);
	set_attr("dex", 27);
	set_attr("int", 29);
	set_attr("wis", 26);
	set_attr("spi", 24);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 20);
	set_race("human");
	set_level(40);
	set_class("scholar");
	set("sect", "玄天教");
	set("rank", "教主");
	set("title", "玄天教主");

	set_skill("unarmed", 60);
	set_skill("dodge", 120);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("xuantian force", 120);
	set_skill("sword", 150);
	set_skill("xuantian-sword", 150);
	map_skill("force", "xuantian force");
	map_skill("sword", "xuantian-sword");

	advance_stat("gin", 220);
	advance_stat("kee", 200);
	advance_stat("sen", 220);

	set("age", 49);
	set("long",
		"這位便是玄天教主東方孤冥﹐一襲玄色長衫﹐頭束玄玉冠﹐腰間\n"
		"斜佩著一柄古樸的長劍。他面容清癯﹐三縷長鬚飄拂胸前﹐一雙\n"
		"眸子幽深如夜﹐顧盼之間既有書生的儒雅﹐又隱隱透著一股看透\n"
		"世情的冷峻。玄天教書生一脈外託遊學論道之名﹐內操四廠諜報\n"
		"之實﹐教主浸淫玄天劍法與觀星問道之術數十年﹐一身文武已臻\n"
		"化境﹐料敵機先、來去無蹤﹐江湖人只聞其名而難見其面。他平\n"
		"日在玄天殿中參星論道、運籌帷幄﹐唯有心思靈巧、悟性不俗的\n"
		"後輩﹐方有機會拜入門下﹐習得這一身玄天劍法。\n");
	setup();
	carry_object("/d/snow/npc/obj/silversword")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("東方孤冥輕拂長鬚﹐淡淡說道﹕你既已入別派﹐道途已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("東方孤冥微微一笑﹕你塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 玄天劍法全憑悟性參詳﹐觀星問道、料敵機先﹐悟性過低者難窺門徑。
	if( me->query_attr("int") < 14 ) {
		do_chat("東方孤冥端詳了你一會﹐搖頭道﹕你悟性閉塞﹐難參我這路劍法。\n");
		return 0;
	}

	do_chat(({
		"東方孤冥幽深的目光在你身上停了停﹐微微頷首。\n",
		"東方孤冥說道﹕我玄天教書生一脈﹐外托論道、內藏機鋒﹐你可有這份慧心與城府﹖\n",
		"東方孤冥緩緩說道﹕也罷﹐你既悟性不俗﹐我便收你入玄天門下﹐傳你玄天劍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("東方孤冥拂了拂長袖﹐淡淡說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("scholar");
		me->set("sect", "玄天教");
		me->set("rank", "散人");
		me->set("title", "玄天教散人");

		me->set_skill("sword", 0);
		me->set_skill("xuantian-sword", 0);
		me->map_skill("sword", "xuantian-sword");

		// 同時授予玄天心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("xuantian force", 0);
		me->map_skill("force", "xuantian force");

		message_vision(
			"$N取過一柄長劍﹐將玄天劍法的入門劍訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"東方孤冥說道﹕從今日起﹐你便是我玄天教散人門下的弟子了。\n",
			"東方孤冥說道﹕劍道無涯﹐機鋒無形﹐你且到演武場勤加錘鍊﹐莫負了這身玄天劍法。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 書生(scholar)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的玄天教弟子
// 轉入三大進階分支之一。比照武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀 d/hudao)、
// 道士天師(d/tianshi)、和尚白象(d/baixiang)的授技模型(門檻更高、以 sect_branch
// 標記分支、升階 rank/title)﹐惟本門為「書生(scholar)」職業﹐以劍法佐控場、靈活
// 游走見長(docs 評分「四廠玄天 靈活 S」)——以此驗證通用「進階」指令 + do_advance
// 模型可第四度跨職業(武者/道士/和尚之外)套用。
//
// 與前數門的關鍵差異(職業特性)：
//   * 入門武功為劍法(sword)﹐入門時 map_skill("sword","xuantian-sword")(玄天劍法)﹐
//     入門火候門檻即以 "xuantian-sword" 計(對應武者的 lunmay/fonxansword/bawang
//     blade、道士的 taoism-fire、和尚的 rid-evil)。
//   * 入門時亦授玄天心法(xuantian force)為內功(map_skill("force","xuantian force"))﹐
//     部分進階分支沿用之、部分另授更上乘內功。
//   * 進階各分支的 "base" 多為 sword(劍法)﹔藏雲客一脈重身法故另授副技 dodge
//     (藏雲身法)﹐凸顯玄天「靈活 S」的定位。
//   * 屬性主門檻為 "dex"(機敏﹐玄天劍法料敵機先、身法游走之本)﹔四廠都督另設第二道
//     "int"(悟性﹐諜報心術/奇門劍訣之本﹐拜入時即驗 int)門檻。
//
// 三大分支(見 docs/03-門派與武功/04-書生-步玄玄天.md §2 玄天教 與 §玄天教評分)：
//   散人        ── docs 明列之玄天教進階(「散人進階」)。授玄天劍訣 xuantian-jue
//                  (docs「能打擊對手精、氣、神、定單一敵人」之控場劍法﹔沿用入門玄天
//                  心法)。最早開放、門檻最低。
//   藏雲客      ── 承 docs「藏雲訣(拆招招架氣不足 50% 自動脫離戰鬥)」與散人進階「脫戰
//                  入潛行」之游走脫戰一脈(分支名為設計﹐docs未明定階名)。內功 藏雲心法
//                  cangyun force + 身法 藏雲身法 cangyun steps(副技 base=dodge﹐凸顯
//                  靈活 S)。門檻居中。
//   四廠都督    ── 承 docs「四廠投靠(朝廷諜報機構)」之諜報控場一脈(docs「玄天劍訣傷害
//                  提高 25%、困天 delay 提昇為 3」﹔分支名為設計﹐docs未明定階名)。內功
//                  四廠心法 sichang force + 劍法 困天劍訣 kuntian-sword。門檻最高、另設
//                  第二道屬性(int)門檻。
//
// 轉職門檻(條件)為本次設計值(docs 只給評分/機制非確切數字)﹐供日後平衡微調﹕
//   key        level  xuantian-sword  attr 門檻              授內功         授武功(base)
//   ────────── ─────  ──────────────  ────────────────────  ────────────  ───────────────────────────
//   散人       20     60              dex >= 18             (沿用玄天心法) 玄天劍訣 xuantian-jue (sword)
//   藏雲客     25     80              dex >= 20             藏雲心法       (沿用入門玄天劍法)
//                                                                          +藏雲身法 cangyun steps (dodge)
//   四廠都督   30     100             dex >= 22, int >= 20  四廠心法       困天劍訣 kuntian-sword (sword)
//
// 註(散人 docs 依據)：docs 玄天教進階明列「散人進階」(消耗 100 神恢復 50% 精氣、脫戰
//   入潛行、對自身 1 delay)﹔玄天劍訣 docs 明列為核心控場技能。散人「消耗神/脫戰」屬
//   perform/脫戰系統 TODO﹐本檔先授玄天劍訣並 gate level/skill/attr。
// 註(四廠都督 docs 原值)：docs「投靠四廠」未給等級/數值硬條件﹐分支名「四廠都督」為設計
//   (docs未明定):承四廠諜報控場之最高一階。四廠投靠本身屬身分/聲望系統(同冷梅虎督「拜入
//   天邪」、虎刀鬼才「5000 殺業」、天師太乙「青邪戰勳 3000」之故事門檻)﹐標記為待接的
//   TODO﹔本驗證線取 lv30 / xuantian-sword 100 / dex22 / int20(與封山劍客、冷梅虎督、
//   虎刀太守、天師太乙、白象降魔尊者同階)替代。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(玄天諸進階多以 sword 劍法為主)。
// "extra" 為另授的副技﹕({ ({中文,英文,基礎技能}), ... })﹐授技後 map_skill(基礎,英文)。
// "skills" 為空陣列時表示該分支不另授主招式(沿用入門玄天劍法)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"散人" : ([
			"rank"    : "玄天散人",
			"title"   : "玄天教散人",
			"level"   : 20,
			"xuantian-sword" : 60,
			"attr"    : "dex",
			"attr_min": 18,
			"base"    : "sword",
			"force"   : 0,    // 散人不另授內功﹐沿用入門玄天心法(xuantian force)
			"skills"  : ({ ({ "玄天劍訣", "xuantian-jue" }) }),
			"desc"    : "玄天劍訣乃玄天教控場一脈的根本﹐能打擊敵手精、氣、神﹐更可定住"
			            "單一強敵﹐料敵機先、進退由心。此乃 PvP 的看家本領﹐善用之。",
		]),
		"藏雲客" : ([
			"rank"    : "玄天藏雲客",
			"title"   : "玄天教藏雲客",
			"level"   : 25,
			"xuantian-sword" : 80,
			"attr"    : "dex",
			"attr_min": 20,
			"base"    : "sword",
			"force"   : ({ "藏雲心法", "cangyun force" }),
			"skills"  : ({ }),    // 沿用入門玄天劍法﹐不另授主招式﹐專精身法
			"extra"   : ({
				({ "藏雲身法", "cangyun steps", "dodge" }),
			}),
			"desc"    : "藏雲客以藏雲訣佐藏雲身法、藏雲心法﹐藏形游走、來去無蹤﹐拆招招架"
			            "氣力不繼時更能自行脫戰潛行。藏雲身法走 dodge﹐自此你的閃躲身法便是"
			            "保命的本錢﹐是隊中最難纏的游擊。",
		]),
		"四廠都督" : ([
			"rank"    : "玄天四廠都督",
			"title"   : "玄天教四廠都督",
			"level"   : 30,
			"xuantian-sword" : 100,
			"attr"    : "dex",
			"attr_min": 22,
			"attr2"   : "int",
			"attr2_min": 20,
			"base"    : "sword",
			"force"   : ({ "四廠心法", "sichang force" }),
			"skills"  : ({ ({ "困天劍訣", "kuntian-sword" }) }),
			"desc"    : "四廠都督投靠朝廷諜報﹐以諜報心術佐玄天劍道﹐困天劍訣封困敵手、控其"
			            "進退﹐傷害更增、困天 delay 提昇﹐乃玄天控場(困天/定人)的極致。"
			            "投身廟堂、料敵千里﹐自此你便是江湖難見其面的諜中之督。",
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
		do_chat("東方孤冥輕拂長鬚道﹕我玄天教進階只有「散人」、「藏雲客」、"
		        "「四廠都督」三路﹐你欲修哪一脈劍法﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為玄天教入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "玄天教" ) {
		do_chat("東方孤冥搖頭道﹕你又非我玄天門下﹐進階之事從何談起﹖且先拜入本教再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("東方孤冥道﹕你既已選定「" + me->query("sect_branch") +
		        "」一脈﹐劍道貴在專一﹐豈可見異思遷﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("東方孤冥端詳了你一會﹐搖頭道﹕你火候尚淺﹐且再潛修些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門劍法(玄天劍法 xuantian-sword)火候門檻。
	if( me->query_skill("xuantian-sword", 1) < b["xuantian-sword"] ) {
		do_chat("東方孤冥道﹕你連我玄天劍法的根基都未練透﹐如何駕馭這上乘劍訣﹖"
		        "且回演武場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（玄天以機敏為本﹐部分分支另有第二道悟性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("東方孤冥搖頭道﹕你的根骨還撐不起這一路劍法﹐勉強習之徒耗心神。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("東方孤冥搖頭道﹕你悟性未足﹐參不透四廠諜報的奇門心術﹐"
		        "且去再參修參修。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔散人沿用入門玄天心法﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階主招式﹐並把主招式對應到該分支的基礎技能（base﹔多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的劍法火候)﹔僅當該基礎技能尚未習得時
	// 補初始 0﹐以免映射落空。skills 為空(如藏雲客專精身法)時則不動主招式映射。
	base = stringp(b["base"]) ? b["base"] : "sword";
	if( sizeof(b["skills"]) ) {
		if( undefinedp(me->query_skill(base, 1)) )
			me->set_skill(base, 0);
		for( i = 0; i < sizeof(b["skills"]); i++ )
			me->set_skill(b["skills"][i][1], 0);
		me->map_skill(base, b["skills"][0][1]);
	}

	// 授副技（身法等﹐各自掛回其基礎技能﹔如藏雲身法→dodge）。
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
		"$N橫劍於膝﹐閉目參星片刻﹐而後將一身「" + branch +
		"」的上乘劍訣傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"東方孤冥含笑道﹕好﹗從今日起﹐你便是我玄天教的「" + b["rank"] + "」了。\n",
		"東方孤冥道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
