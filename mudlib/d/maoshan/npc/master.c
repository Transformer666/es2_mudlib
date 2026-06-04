// master.c -- 茅山派掌教真人

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("茅山掌教", ({ "maoshan master", "master", "priest", "taoist", "maoshan" }));
	set("nickname", "青霞真人");
	set_attr("str", 20);
	set_attr("dex", 22);
	set_attr("int", 28);
	set_attr("wis", 26);
	set_attr("spi", 28);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("taoist");
	set("sect", "茅山派");
	set("rank", "掌教");
	set("title", "茅山派掌教真人");

	set_skill("unarmed", 60);
	set_skill("dodge", 100);
	set_skill("parry", 90);
	set_skill("force", 120);
	set_skill("dao force", 120);
	map_skill("force", "dao force");
	set_skill("magic", 150);
	set_skill("youmin", 150);
	map_skill("magic", "youmin");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 58);
	set("long",
		"這位便是茅山派的掌教真人﹐一身洗得發白的青布道袍﹐頭挽道髻﹐\n"
		"背插一柄桃木劍﹐面容清癯﹐雙目深邃如古井﹐周身隱隱繚繞著一縷化\n"
		"不開的霧氣。茅山一脈以符籙咒術名世﹐召雷喚風、驅鬼役神無所不能\n"
		"﹐掌教真人精研五行陰陽數十載﹐符到咒成﹐江湖人稱「青霞真人」。\n"
		"他久居三清殿中參研道法﹐唯有心性沉靜、與道有緣的後輩﹐方有機會\n"
		"拜入門下﹐習得這一身呼風喚雨的茅山道法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("茅山掌教捻著長鬚﹐說道﹕你既已入別派﹐道緣已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入道
	if( me->query_level() < 1 ) {
		do_chat("茅山掌教說道﹕你塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 符籙咒術全憑靈性與悟性引動﹐靈性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("spi") < 14 ) {
		do_chat("茅山掌教端詳了你一會﹐搖頭道﹕你靈性閉塞﹐難通鬼神之道﹐學不得我這路符籙。\n");
		return 0;
	}

	do_chat(({
		"茅山掌教上下打量了你一番﹐微微頷首。\n",
		"茅山掌教說道﹕我茅山一脈﹐以符籙咒術通鬼神、役五行﹐你可有這份道心﹖\n",
		"茅山掌教說道﹕也罷﹐你既與道有緣﹐我便收你入門下﹐傳你茅山道法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("茅山掌教拂了拂袖﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("taoist");
		me->set("sect", "茅山派");
		me->set("rank", "茅山弟子");
		me->set("title", "茅山派弟子");

		me->set_skill("magic", 0);
		me->set_skill("youmin", 0);
		me->map_skill("magic", "youmin");

		// 同時授予明道心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("dao force", 0);
		me->map_skill("force", "dao force");

		message_vision(
			"$N取過一道黃符﹐將茅山咒術【幽冥三箭】的入門口訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"茅山掌教說道﹕從今日起﹐你便是我茅山門下的弟子了。\n",
			"茅山掌教說道﹕道法無涯﹐你且到演法場對草人參修咒術﹐莫負了這身道法。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 非武者(法系/道士)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的茅山派弟子轉入
// 三大進階分支之一。比照武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀 d/hudao)、
// 道士天師(d/tianshi)、和尚白象(d/baixiang)的授技模型(門檻更高、以 sect_branch
// 標記分支、升階 rank/title)﹐惟本門為「道士(taoist)」職業﹐故所授為「法術(magic)
// /內功(force)」而非劍刀招式。
//
// 與武者門派的關鍵差異(同天師派)：
//   * "base" 一律為 "magic"(法術)﹐非 sword/blade﹔授技後 map_skill("magic", <咒>)。
//     (入門時即 map_skill("magic","youmin")(幽冥三箭)﹐進階沿此模型把 magic 改映到
//      更上乘的咒術 daemon。)
//   * 入門火候門檻以入門咒術 "youmin"(幽冥三箭)計(對應武者的 lunmay/fonxansword/
//     bawang blade、天師的 taoism-fire)。
//   * 屬性主門檻為 "spi"(靈性，道士施法根本)﹐非 str/dex/cor。
//
// 三大分支(見 docs/03-門派與武功/02-道士-天師與茅山.md「茅山派(三觀)」──茅山分裂
//   為靈雲觀、隱風觀、幻霧觀三觀)：
//   靈雲觀  ── 法術 茅山【五雷術】mao-shan lightning(承幽冥三箭一脈﹐召五行靈雷
//              傷敵﹔沿用入門明道心法 dao force)。docs 五雷術原由林正陽授(需幽冥三箭
//              ≥90)﹐此處以入門咒術火候 + 靈性門檻替代驗證(見下注)。最早開放、門檻
//              最低。
//   隱風觀  ── 內功 隱風訣 yinfeng force + 法術 茅山幻術 taoism of nature(以風御靈、
//              召獸制敵)。門檻居中。docs 隱風觀「不收夜叉/形天/厭火/黑齒」之種族門檻
//              屬入門階段驗證﹐標記為待接 TODO。
//   幻霧觀  ── 內功 幻霧訣 huanwu force + 法術 茅山奇術 taoism of darkness(以陰御鬼、
//              陰火傷敵)。門檻最高、另設第二道屬性(int)門檻。docs 幻霧觀「只收阿修羅/
//              巫首/雨師妾/無腸/夜叉」之種族門檻屬入門階段驗證﹐標記為待接 TODO。
//
// 轉職門檻(條件)為本次設計值﹐供日後平衡微調﹕      // 數值為本次設計值
//   key      level  youmin  attr 門檻              授內功         授法術(base=magic)
//   ──────── ─────  ──────  ────────────────────  ────────────  ───────────────────────────
//   靈雲觀   20     60      spi >= 18             (沿用明道心法) 茅山五雷術 mao-shan lightning
//   隱風觀   25     80      spi >= 20             隱風訣         茅山幻術 taoism of nature
//   幻霧觀   30     100     spi >= 22, int >= 20  幻霧訣         茅山奇術 taoism of darkness
//
// 註(靈雲觀 docs 原值)：docs 五雷術條件為「幽冥三箭 ≥90﹐由林正陽授」﹐並消耗先天符。
//   為與本批進階一致(只 gate level/skill/attr)﹐此處先以入門咒術火候 60 + 靈性 18
//   替代﹐林正陽授技之劇情門檻標記為待接 TODO(同冷梅虎督「拜入天邪」、虎刀鬼才
//   「5000 殺業」)。               // 設計(docs未明定): 以火候/靈性替代劇情門檻
// 註(幻霧觀 docs 原值)：docs 未明列幻霧觀二轉之屬性數字﹔本驗證線取 lv30 / youmin
//   100 / spi22 / int20(與封山劍客、冷梅虎督、虎刀太守、天師太乙真人、白象降魔尊者
//   同階)。種族收徒門檻(只收阿修羅/巫首等)標記為待接 TODO。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主咒對應的基礎技能(茅山諸進階皆以 magic 法術為主)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"靈雲觀" : ([
			"rank"    : "靈雲道人",
			"title"   : "茅山派靈雲道人",
			"level"   : 20,
			"youmin"  : 60,
			"attr"    : "spi",
			"attr_min": 18,
			"base"    : "magic",
			"force"   : 0,    // 靈雲觀沿用入門明道心法(dao force)﹐不另授內功
			"skills"  : ({ ({ "五雷術", "mao-shan lightning" }) }),
			"desc"    : "靈雲觀承幽冥三箭一脈﹐五雷術召五行靈雷傷敵﹐對殭屍鬼魂之屬"
			            "更見威能﹐每式須焚一張正陽符引氣﹐施法務留意身上符數。",
		]),
		"隱風觀" : ([
			"rank"    : "隱風道人",
			"title"   : "茅山派隱風道人",
			"level"   : 25,
			"youmin"  : 80,
			"attr"    : "spi",
			"attr_min": 20,
			"base"    : "magic",
			"force"   : ({ "隱風訣", "yinfeng force" }),
			"skills"  : ({ ({ "茅山幻術", "taoism of nature" }) }),
			"desc"    : "隱風觀以風御靈、藏形匿息﹐隱風訣護體、茅山幻術召役獸靈撲敵﹐"
			            "每式命中焚一張先天符。攻守游走兼備﹐長於纏鬥控場。",
		]),
		"幻霧觀" : ([
			"rank"    : "幻霧道人",
			"title"   : "茅山派幻霧道人",
			"level"   : 30,
			"youmin"  : 100,
			"attr"    : "spi",
			"attr_min": 22,
			"attr2"   : "int",
			"attr2_min": 20,
			"base"    : "magic",
			"force"   : ({ "幻霧訣", "huanwu force" }),
			"skills"  : ({ ({ "茅山奇術", "taoism of darkness" }) }),
			"desc"    : "幻霧觀以陰御鬼、養魂凝煞﹐幻霧訣滋煞、茅山奇術引幽冥陰火傷敵﹐"
			            "每式焚一張少陰符。陰火霸烈、最為玄詭﹐是茅山道法至深的一脈。",
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
		do_chat("茅山掌教捻著長鬚道﹕我茅山進階只有「靈雲觀」、「隱風觀」、"
		        "「幻霧觀」三觀﹐你欲入哪一觀參修道法﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為茅山派入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "茅山派" ) {
		do_chat("茅山掌教搖頭道﹕你又非我茅山門下﹐進階之事從何談起﹖且先拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("茅山掌教道﹕你既已入了「" + me->query("sect_branch") +
		        "」一觀﹐道貴專一﹐豈可見異思遷﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("茅山掌教端詳了你一會﹐搖頭道﹕你道行尚淺﹐且再潛修些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門咒術(茅山咒術【幽冥三箭】 youmin)火候門檻。
	if( me->query_skill("youmin", 1) < b["youmin"] ) {
		do_chat("茅山掌教道﹕你連我幽冥三箭的根基都未練透﹐如何駕馭這上乘道法﹖"
		        "且回演法場對草人參修去。\n");
		return notify_fail("");
	}

	// 屬性門檻（道士以靈性為本﹐部分分支另有第二道屬性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("茅山掌教搖頭道﹕你的靈性還引動不了這一觀道法﹐勉強修之徒耗心神。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("茅山掌教搖頭道﹕你悟性未足﹐尚參不透幻霧觀御鬼養魂的玄奧﹐"
		        "且去再參修參修。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳道 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔靈雲觀沿用入門明道心法﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授上乘法術﹐並把主咒對應到該分支的基礎技能（base=magic﹔多咒者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的法術火候)﹔僅當該基礎技能尚未習得時
	// 補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "magic";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 傳道氣象。
	message_vision(
		"$N取過一道黃符﹐口誦真言﹐將一身「" + branch +
		"」的上乘茅山道法傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"茅山掌教含笑道﹕善哉﹗從今日起﹐你便是我茅山派「" + b["rank"] + "」了。\n",
		"茅山掌教道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
