// master.c -- 白象寺方丈

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("白象寺方丈", ({ "bonze master", "master", "monk", "abbot" }));
	set("nickname", "伏魔尊者");
	set_attr("str", 26);
	set_attr("dex", 22);
	set_attr("int", 22);
	set_attr("wis", 26);
	set_attr("spi", 24);
	set_attr("cps", 24);
	set_attr("con", 25);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("bonze");
	set("sect", "白象寺");
	set("rank", "方丈");
	set("title", "白象寺方丈");

	set_skill("unarmed", 80);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("staff", 150);
	set_skill("rid-evil", 150);
	set_skill("buddhism", 120);
	map_skill("staff", "rid-evil");
	map_skill("force", "buddhism");

	advance_stat("gin", 220);
	advance_stat("kee", 220);
	advance_stat("sen", 240);

	set("age", 62);
	set("long",
		"這位便是白象寺的方丈﹐一身灰色僧袍洗得發白﹐袒露的右肩與胸\n"
		"膛肌肉虯結﹐手中橫持一根烏沉沉的禪杖﹐杖頭銅環輕響。他面容慈\n"
		"和﹐雙目卻精光內斂﹐顧盼之間隱隱透著一股降魔伏邪的金剛之氣。\n"
		"白象寺羅漢一脈以杖法降魔證道﹐方丈浸淫金剛伏魔杖法數十年﹐一\n"
		"身武功已臻化境﹐江湖人稱「伏魔尊者」。他平日在大雄寶殿中講經\n"
		"說法﹐唯有心懷慈悲、根骨不俗的後輩﹐方有機會拜入門下﹐習得這\n"
		"一身降魔伏邪的羅漢杖法。\n");
	setup();
	carry_object("/d/snow/npc/obj/cane")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("白象寺方丈雙手合十﹐宣了聲佛號﹕施主既已入別派﹐緣分已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("白象寺方丈微笑道﹕施主塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 羅漢杖法須以慈悲心降魔﹐慧根過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("wis") < 14 ) {
		do_chat("白象寺方丈端詳了你一會﹐搖頭道﹕施主慧根閉塞﹐難參我這路佛法。\n");
		return 0;
	}

	do_chat(({
		"白象寺方丈上下打量了你一番﹐微微頷首。\n",
		"白象寺方丈道﹕我白象寺羅漢一脈﹐以杖降魔﹐施主可有這份慈悲心﹖\n",
		"白象寺方丈宣了聲佛號﹕善哉善哉﹐你既與我佛有緣﹐老衲便收你入羅漢門下﹐傳你金剛伏魔杖法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("白象寺方丈雙手合十﹐道﹕施主既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("bonze");
		me->set("sect", "白象寺");
		me->set("rank", "羅漢");
		me->set("title", "白象寺羅漢");

		me->set_skill("staff", 0);
		me->set_skill("rid-evil", 0);
		me->map_skill("staff", "rid-evil");

		// 同時授予蓮華心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("lotus force", 0);
		me->map_skill("force", "lotus force");

		message_vision(
			"$N取過一根禪杖﹐將金剛伏魔杖法的入門杖訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"白象寺方丈宣了聲佛號﹕從今日起﹐你便是我白象寺羅漢門下的弟子了。\n",
			"白象寺方丈道﹕武學無涯﹐你且到演武場勤加錘鍊﹐莫負了這身杖法。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 和尚(bonze)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的白象寺羅漢弟子
// 轉入三大進階分支之一。比照武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀 d/hudao)
// 與道士天師(d/tianshi)的授技模型(門檻更高、以 sect_branch 標記分支、升階 rank/
// title)﹐惟本門為「和尚(bonze)」職業﹐故所授為杖法/掌法/刀法/身法/佛門內功——
// 以此驗證通用「進階」指令 + do_advance 模型可第三度跨職業(武者/道士之外)套用。
//
// 與前四門的關鍵差異(職業特性)：
//   * 入門武功為杖法(staff)﹐入門時 map_skill("staff","rid-evil")(金剛伏魔杖法)﹐
//     入門火候門檻即以 "rid-evil" 計(對應武者的 lunmay/fonxansword/bawang blade、
//     道士的 taoism-fire)。
//   * 進階各分支的 "base" 視招式而異：羅漢/禪師以 staff(杖法)為主﹐降魔尊者改以
//     blade(刀法 達摩烈焰刀)證道﹔另授 unarmed(千葉掌法)、dodge(達摩移身法)等副技。
//   * 屬性門檻依分支而異：羅漢攻擊型重 str(力)、禪師防守型重 wis(慧根/禪定)、
//     降魔尊者另設第二道 con(根骨)門檻。
//
// 三大分支(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md §白象寺﹔README 對應表
//   「白象寺 → 禪師(防守)、羅漢(攻擊)」)：
//   羅漢      ── docs 明列之攻擊型分支。內功 羅漢降魔功 luohan force + 杖法 文殊杖法
//                wen-staff(主) + 掌法 千葉掌法 buddha hands + 身法 達摩移身法 damo
//                steps。最早開放、門檻最低。
//   禪師      ── docs 明列之防守型分支。沿用入門蓮華心法﹐授守勢杖法 降魔禪杖
//                zen-staff(主) + 身法 達摩移身法 damo steps。門檻居中、重慧根禪定。
//   降魔尊者  ── 武僧最高一階(設計(docs未明定分支名):承羅漢一脈以刀證道)。內功 羅漢
//                降魔功 luohan force + 刀法 達摩烈焰刀 damo blade(docs 明列之羅漢刀
//                法﹐基礎技能由 staff 改 blade)。門檻最高、另設第二道屬性(con)門檻。
//                docs「18 銅人任務(reset 任務前置)」標記為待接的故事門檻 TODO。
//
// 轉職門檻(條件)為本次設計值﹐供日後平衡微調﹕
//   key        level  rid-evil  attr 門檻              授內功           授武功(base)
//   ────────── ─────  ────────  ────────────────────  ──────────────  ───────────────────────────
//   羅漢       20     60        str >= 18             羅漢降魔功       文殊杖法 wen-staff (staff)
//                                                                      +千葉掌法+達摩移身法
//   禪師       25     80        wis >= 20             (沿用蓮華心法)   降魔禪杖 zen-staff (staff)
//                                                                      +達摩移身法
//   降魔尊者   30     100       str >= 22, con >= 20  羅漢降魔功       達摩烈焰刀 damo blade (blade)
//
// 註(羅漢/禪師 docs 依據)：docs 白象寺進階分支明列「禪師(防守)、羅漢(攻擊)」﹐羅漢
//   核心技能 luohan force / wen-staff / buddha hands / damo steps / damo blade 亦見
//   docs。禪師 docs 只給「防守型」定位未列招式﹐故守勢杖法 降魔禪杖 zen-staff 之
//   招式為設計(docs未明定)﹐與羅漢文殊杖法對位。
// 註(降魔尊者 docs 原值)：docs 未明列羅漢之上的尊者階名﹐分支名「降魔尊者」為設計
//   (docs未明定):承羅漢以刀(達摩烈焰刀﹐docs 明列)證道之最高一階。docs「18 銅人任務
//   (reset 任務前置)」屬尚未接的任務門檻﹔為與本批進階一致(只 gate level/skill/
//   attr)﹐此處先以 lv30 / rid-evil 100 / str22 / con20(與封山劍客、冷梅虎督、虎刀
//   太守、天師太乙真人同階)替代﹐18 銅人任務標記為待接的故事門檻 TODO。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(羅漢/禪師為 staff﹔降魔尊者以刀證道故為 blade)。
// "extra" 為另授的副技﹕({ ({中文,英文,基礎技能}), ... })﹐授技後 map_skill(基礎,英文)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"羅漢" : ([
			"rank"    : "白象羅漢",
			"title"   : "白象寺羅漢",
			"level"   : 20,
			"rid-evil": 60,
			"attr"    : "str",
			"attr_min": 18,
			"base"    : "staff",
			"force"   : ({ "羅漢降魔功", "luohan force" }),
			"skills"  : ({ ({ "文殊杖法", "wen-staff" }) }),
			"extra"   : ({
				({ "千葉掌法", "buddha hands", "unarmed" }),
				({ "達摩移身法", "damo steps", "dodge" }),
			}),
			"desc"    : "羅漢一脈以杖降魔、剛猛搶攻﹐有羅漢降魔功護體﹐傷害恢復俱增。"
			            "文殊杖法走 staff、千葉掌法走 unarmed﹐你可自行 map_skill 在杖、"
			            "掌之間切換﹔達摩移身法則精進你的閃躲身法。",
		]),
		"禪師" : ([
			"rank"    : "白象禪師",
			"title"   : "白象寺禪師",
			"level"   : 25,
			"rid-evil": 80,
			"attr"    : "wis",
			"attr_min": 20,
			"base"    : "staff",
			"force"   : 0,    // 禪師不另授內功﹐沿用入門蓮華心法(lotus force)
			"skills"  : ({ ({ "降魔禪杖", "zen-staff" }) }),
			"extra"   : ({
				({ "達摩移身法", "damo steps", "dodge" }),
			}),
			"desc"    : "禪師一脈以守為攻、坐如禪定﹐降魔禪杖沉穩綿密、長於格擋纏鬥與"
			            "久戰﹐輔以達摩移身法移形換步﹐是隊中最堅實的肉盾。",
		]),
		"降魔尊者" : ([
			"rank"    : "白象降魔尊者",
			"title"   : "白象寺降魔尊者",
			"level"   : 30,
			"rid-evil": 100,
			"attr"    : "str",
			"attr_min": 22,
			"attr2"   : "con",
			"attr2_min": 20,
			"base"    : "blade",
			"force"   : ({ "羅漢降魔功", "luohan force" }),
			"skills"  : ({ ({ "達摩烈焰刀", "damo blade" }) }),
			"desc"    : "降魔尊者乃白象武僧最高一階﹐捨杖習刀、以刀證道﹐達摩烈焰刀刀挾"
			            "禪火、剛猛無儔﹐傷敵之餘更削火抗。自此你的刀法(blade)便是降魔的"
			            "本錢。",
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
		do_chat("白象寺方丈雙手合十﹐宣了聲佛號﹕本寺進階只有「羅漢」、「禪師」、"
		        "「降魔尊者」三路﹐施主欲修哪一門佛法﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為白象寺入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "白象寺" ) {
		do_chat("白象寺方丈搖頭道﹕施主又非我白象寺門下﹐進階之事從何談起﹖且先拜入本寺再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("白象寺方丈宣了聲佛號﹕施主既已選定「" + me->query("sect_branch") +
		        "」一脈﹐佛法貴在精專﹐豈可見異思遷﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("白象寺方丈端詳了你一會﹐搖頭道﹕施主火候尚淺﹐且再潛修些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門杖法(金剛伏魔杖法 rid-evil)火候門檻。
	if( me->query_skill("rid-evil", 1) < b["rid-evil"] ) {
		do_chat("白象寺方丈道﹕施主連我金剛伏魔杖法的根基都未練透﹐如何駕馭這上乘武功﹖"
		        "且回演武場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（各分支重不同根骨﹕羅漢/尊者重力、禪師重慧根禪定）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("白象寺方丈搖頭道﹕施主的根骨還撐不起這一路功夫﹐勉強習之徒傷己身。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("白象寺方丈宣了聲佛號﹕施主筋骨未足以承這降魔尊者的刀法剛勁﹐"
		        "且去再淬鍊淬鍊這副皮囊。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔禪師沿用入門蓮華心法﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階主招式﹐並把主招式對應到該分支的基礎技能（base﹔多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的杖/刀火候)﹔僅當該基礎技能尚未習得時
	// (如降魔尊者改習 blade﹐入門時未授)補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "staff";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 授副技（掌法/身法等﹐各自掛回其基礎技能﹔如千葉掌法→unarmed、達摩移身法→dodge）。
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
		"$N合什誦了聲佛號﹐寶相莊嚴﹐將一身「" + branch +
		"」的上乘佛門武功傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"白象寺方丈宣了聲佛號﹕善哉﹗從今日起﹐你便是我白象寺的「" + b["rank"] + "」了。\n",
		"白象寺方丈道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
