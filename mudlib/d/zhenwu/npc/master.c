// master.c -- 振武軍營主將（軍隊統領）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("魯熙年", ({ "lu xinian", "soldier master", "master", "general", "commander" }));
	set("nickname", "鎮北將軍");
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
	set("sect", "振武軍營");
	set("rank", "軍隊統領");
	set("title", "振武軍營軍隊統領");

	set_skill("unarmed", 60);
	set_skill("dodge", 90);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("pike", 150);
	set_skill("dragon god", 150);
	map_skill("pike", "dragon god");

	advance_stat("gin", 240);
	advance_stat("kee", 240);
	advance_stat("sen", 160);

	set("age", 48);
	set("long",
		"這位便是振武軍營的主將﹐一身玄鐵山文甲﹐外罩猩紅戰袍﹐身\n"
		"形魁梧如鐵塔﹐按槍而立﹐自有一股久經沙場的肅殺之氣。他面如\n"
		"重棗﹐濃眉鳳目﹐頷下一部虬髯根根如戟﹐顧盼之間威猛逼人。振\n"
		"武軍營軍隊統領一脈以槍陣縱橫沙場﹐主將浸淫龍神槍法數十年﹐\n"
		"一桿長槍縱橫無敵﹐軍中尊稱「鎮北將軍」。他久鎮此營操練兵馬\n"
		"﹐唯有膂力過人、肯吃苦耐勞的後輩﹐方有機會拜入麾下﹐學得這\n"
		"一身殺敵報國的本事。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("魯熙年把長槍頓地一震﹐沉聲道﹕你既已入別派﹐軍籍難改﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可從軍
	if( me->query_level() < 1 ) {
		do_chat("魯熙年上下打量了你一眼﹐喝道﹕乳臭未乾的雛兒﹐且去歷練一番再來投軍罷。\n");
		return 0;
	}

	// 槍陣廝殺全憑一身膂力﹐筋骨孱弱者扛不起這桿長槍（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("str") < 14 ) {
		do_chat("魯熙年搖頭道﹕你這身子骨連長槍都端不穩﹐如何上陣殺敵﹖且去練壯了再來。\n");
		return 0;
	}

	do_chat(({
		"魯熙年抱起雙臂﹐將你細細打量了一番。\n",
		"魯熙年朗聲道﹕我振武軍營軍法森嚴﹐操練如熬煉鋼鐵﹐你可吃得了這份苦﹖\n",
		"魯熙年哈哈一笑﹕也罷﹐瞧你還算有把子力氣﹐我便收你入我振武軍營門下﹐傳你這套殺敵的槍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("魯熙年把長槍一收﹐說道﹕你既已另投他處﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("soldier");
		me->set("sect", "振武軍營");
		me->set("rank", "新兵");
		me->set("title", "振武軍營新兵");

		me->set_skill("pike", 0);
		me->set_skill("dragon god", 0);
		me->map_skill("pike", "dragon god");

		// 同時授予瘋虎功（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("tiger force", 0);
		me->map_skill("force", "tiger force");

		message_vision(
			"$N抄起一桿長槍﹐將龍神槍法的入門槍勢一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"魯熙年朗聲道﹕從今日起﹐你便是我振武軍營門下的一名新兵了。\n",
			"魯熙年沉聲道﹕到校場領桿長槍勤加操練﹐槍要沉、步要穩、心要狠﹐莫墮了我軍威。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 軍人(soldier)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的振武軍營弟子
// 轉入進階分支之一。比照武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀 d/hudao)、
// 道士天師(d/tianshi)與和尚白象(d/baixiang)的授技模型(門檻更高、以 sect_branch
// 標記分支、升階 rank/title)﹐惟本門為「軍人(soldier)」職業——以此驗證通用
// 「進階」指令 + do_advance 模型可第四度跨職業套用(武者/道士/和尚之外)。
//
// 與前數門的關鍵差異(職業特性)：
//   * 入門武功為槍法(pike)﹐入門時 map_skill("pike","dragon god")(龍神槍法)﹐入門
//     火候門檻即以 "dragon god" 計(對應武者的 lunmay/fonxansword/bawang blade、
//     道士的 taoism-fire、和尚的 rid-evil)。
//   * 進階各分支的 "base" 視路線而異：統領/先鋒為暴力路線﹐主技以 pike(槍法)為主﹔
//     軍師為後勤法系路線﹐戰鬥手段更像道士(戰術 + 法術)﹐故 base 改 magic(法術)﹐
//     另授 literate(古文造詣)等文書副技。
//
// 三大分支(見 docs/03-門派與武功/06-軍人-振武大內.md §進階-軍隊統領 / §進階-軍師)：
//   軍隊統領  ── docs 明列之暴力路線進階。沿用入門瘋虎功(tiger force)﹐授核心槍法
//                狂擊亂鬥之法 berserk(主﹐pike) + 強力格擋技巧 heavy_parry(副﹐parry)。
//                最早開放、門檻最低。docs「戰功25萬、狂擊達天賦、米沛拜師」標記為待接
//                的戰功/任務門檻 TODO。
//   怒濤先鋒  ── 設計(docs未明定分支名):承統領暴力一脈更進一階。內功 怒氣訣 aggressive
//                + 武功 重擊術 powerblow(主﹐pike)。重在重擊爆發﹐門檻居中。docs 統領
//                線下「怒氣 aggressive(殺業1000、berserk70)」與「重擊術 powerblow」之
//                承襲﹐殺業門檻標記為待接的業力門檻 TODO。
//   振武軍師  ── docs 明列之後勤法系路線進階。內功 紫薇心經 chivi sutra + 法術 幻劍術
//                illusion-sword(主﹐base 由 pike 改 magic) + 文書 古文造詣 archaic
//                attainment(副﹐literate)。戰鬥更像道士(戰術 + 法術)﹐門檻最高、另設
//                第二道屬性(wis)門檻。docs「lv30、悟性30、讀書90、兵法90、趙欽差觸發、
//                天風道長任務學紫薇心經」之承襲(數值見下注)。
//
// 轉職門檻(條件)：軍師的 lv30 / int(悟性) 為 docs 明定值(docs 載 lv30、悟性30)﹐讀書90/
// 兵法90/趙欽差觸發/天風道長任務屬尚未接的任務/技能門檻﹐此處先以入門火候 + 雙屬性
// 門檻替代驗證並標記為 TODO﹔統領/先鋒之等級與入門槍法火候、屬性數字為本次設計值
// (docs 統領給「戰功25萬」偏成品線﹐此處取與冷梅/封山/虎刀/天師/白象同階的偏低驗證線﹐
// 並以註解保留 docs 原值)﹐供日後平衡微調﹕
//   key        level  dragon god  attr 門檻              授內功         授武功/法術(base)         副技(extra→base)
//   ────────── ─────  ──────────  ────────────────────  ────────────  ────────────────────────  ──────────────────────
//   軍隊統領   20     60          str >= 18             (沿用瘋虎功)   狂擊亂鬥之法 berserk(pike) 強力格擋技巧→parry
//   怒濤先鋒   25     80          str >= 20             怒氣訣         重擊術 powerblow(pike)     ─
//   振武軍師   30     100         int >= 20, wis >= 20  紫薇心經       幻劍術 illusion-sword(magic) 古文造詣→literate
//
// 註(統領 docs 原值)：docs 統領條件為「戰功 ≥25 萬、狂擊達天賦、米沛拜師」。戰功/天賦/
//   拜師屬尚未接的戰功計分與任務門檻﹔為與本批進階一致(只 gate level/skill/attr)﹐此處
//   先以 lv20 / dragon god 60 / str18 替代﹐並標記為待接的故事/戰功門檻 TODO。
// 註(先鋒 怒氣 docs 原值)：docs 怒氣 aggressive 條件為「殺業 1000、berserk 70」﹐殺業屬
//   業力計分系統﹔此處先以更高的入門槍法火候 + str 門檻替代﹐殺業門檻標記為 TODO(同
//   虎刀鬼才「5000 殺業」)。怒氣訣此處實作為隨修為成長的內功(見 daemon/skill/aggressive.c)。
// 註(軍師 docs 原值)：docs 軍師條件為「lv30、悟性30、讀書90、兵法90、趙欽差觸發」並可由
//   天風道長任務學紫薇心經與法術。本驗證線取 docs 明定的 lv30 / int(悟性)20﹐另加 wis20﹐
//   並以入門槍法火候 100 替代讀書90/兵法90﹔趙欽差/天風道長任務標記為待接的故事門檻 TODO。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主技對應的基礎技能(統領/先鋒為 pike﹔軍師走法系故為 magic)。
// "force" 為另授內功({中文,英文})﹐無則 0(沿用入門瘋虎功)。
// "extra" 為另授的副技﹕({ ({中文,英文,基礎技能}), ... })﹐授技後 map_skill(基礎,英文)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"軍隊統領" : ([
			"rank"    : "振武統領",
			"title"   : "振武軍營統領",
			"level"   : 20,
			"dragon god" : 60,
			"attr"    : "str",
			"attr_min": 18,
			"base"    : "pike",
			"force"   : 0,    // 統領沿用入門瘋虎功(tiger force)﹐不另授內功
			"skills"  : ({ ({ "狂擊亂鬥之法", "berserk" }) }),
			"extra"   : ({
				({ "強力格擋技巧", "heavy_parry", "parry" }),
			}),
			"desc"    : "統領一脈以狂擊亂鬥之法縱橫沙場﹐全力搶攻、可怕攻擊力﹐然消耗精氣"
			            "甚鉅、破綻極大﹔輔以強力格擋技巧硬擋來襲。狂擊亂鬥走 pike、強力"
			            "格擋技巧可自行 map_skill 對應招架(parry)以強化減傷。",
		]),
		"怒濤先鋒" : ([
			"rank"    : "振武先鋒",
			"title"   : "振武軍營先鋒",
			"level"   : 25,
			"dragon god" : 80,
			"attr"    : "str",
			"attr_min": 20,
			"base"    : "pike",
			"force"   : ({ "怒氣訣", "aggressive" }),
			"skills"  : ({ ({ "重擊術", "powerblow" }) }),
			"desc"    : "先鋒承統領暴力一脈更進一階﹐有怒氣訣助長膽臂殺氣﹐重擊術依火候"
			            "高低增武器傷害並忽視部分抗性、可直接爆 hp。重擊術走 pike﹐重在"
			            "重擊爆發、先登陷陣。",
		]),
		"振武軍師" : ([
			"rank"    : "振武軍師",
			"title"   : "振武軍營軍師",
			"level"   : 30,
			"dragon god" : 100,
			"attr"    : "int",
			"attr_min": 20,
			"attr2"   : "wis",
			"attr2_min": 20,
			"base"    : "magic",       // 軍師捨槍習法﹐戰鬥更像道士(戰術 + 法術)
			"force"   : ({ "紫薇心經", "chivi sutra" }),
			"skills"  : ({ ({ "幻劍術", "illusion-sword" }) }),
			"extra"   : ({
				({ "古文造詣", "archaic attainment", "literate" }),
			}),
			"desc"    : "軍師乃ES2戰場後勤的核心﹐捨槍習法、戰鬥更像道士。有紫薇心經溫養"
			            "法力、幻劍術虛實傷敵﹐另習古文造詣精進文書。自此你的法術(magic)"
			            "便是殺敵的本錢﹐戰術兵法亦受法術強度加成(待戰術系統耦合)。",
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
		do_chat("魯熙年把長槍頓地一震﹐沉聲道﹕我振武軍營進階只有「軍隊統領」、"
		        "「怒濤先鋒」、「振武軍師」三路﹐你要投哪一營﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為振武軍營入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "振武軍營" ) {
		do_chat("魯熙年冷哼一聲﹕你又非我振武軍營的兵﹐進階之事從何談起﹖且先投軍入伍再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("魯熙年搖頭道﹕你既已編入「" + me->query("sect_branch") +
		        "」一營﹐軍令如山、軍籍難改﹐豈可朝三暮四﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("魯熙年上下打量了你一眼﹐搖頭道﹕你資歷尚淺﹐且再歷練些時日﹐"
		        "待戰陣磨得熟了再來罷。\n");
		return notify_fail("");
	}

	// 入門槍法(龍神槍法 dragon god)火候門檻。
	if( me->query_skill("dragon god", 1) < b["dragon god"] ) {
		do_chat("魯熙年喝道﹕你連我龍神槍法的根基都未練透﹐如何駕馭這上乘軍中絕學﹖"
		        "且回校場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（統領/先鋒重膂力﹐軍師重悟性慧根﹐部分分支另有第二道屬性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("魯熙年搖頭道﹕你的根骨還撐不起這一營的本事﹐勉強習之徒傷己身。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("魯熙年搖頭道﹕你悟性慧根未足﹐參不透軍師這套運籌帷幄的本事﹐"
		        "且去再磨練磨練。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔統領沿用入門瘋虎功﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階主技﹐並把主技對應到該分支的基礎技能（base﹔多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的槍法/法術火候)﹔僅當該基礎技能尚未習得時
	// (如軍師改習 magic﹐入門時未授)補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "pike";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 授副技（格擋/文書等﹐各自掛回其基礎技能﹔如強力格擋技巧→parry、古文造詣→literate）。
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
		"$N把長槍頓地一震﹐肅然點將﹐而後將一身「" + branch +
		"」的軍中絕學傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"魯熙年朗聲道﹕好﹗從今日起﹐你便升任我振武軍營的「" + b["rank"] + "」了。\n",
		"魯熙年沉聲道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
