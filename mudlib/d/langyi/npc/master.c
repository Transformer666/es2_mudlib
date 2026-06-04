// master.c -- 瑯夷派黑龍堂主

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("瑯夷堂主", ({ "thief master", "master", "thief", "rogue" }));
	set("nickname", "黑龍左使");
	set_attr("str", 20);
	set_attr("dex", 30);
	set_attr("int", 25);
	set_attr("wis", 24);
	set_attr("spi", 22);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 18);
	set_race("human");
	set_level(40);
	set_class("thief");
	set("sect", "瑯夷派");
	set("rank", "黑龍左使");
	set("title", "瑯夷派黑龍左使");

	set_skill("unarmed", 60);
	set_skill("dodge", 130);
	set_skill("parry", 90);
	set_skill("force", 120);
	set_skill("longyeforce", 120);
	set_skill("dagger", 150);
	set_skill("blood dagger", 150);
	map_skill("force", "longyeforce");
	map_skill("dagger", "blood dagger");

	advance_stat("gin", 220);
	advance_stat("kee", 200);
	advance_stat("sen", 200);

	set("age", 44);
	set("long",
		"這位便是瑯夷派的黑龍堂主﹐一身玄黑勁裝﹐腰束軟帶﹐帶上斜插\n"
		"著兩柄寒光森森的匕首。他身形精瘦﹐步履無聲﹐一雙眼睛深陷而\n"
		"銳利﹐顧盼之間隱隱透著一股噬人的殺氣。瑯夷派黑龍左使一脈以\n"
		"匕首暗算、潛行取命名動黑道﹐堂主浸淫血魂匕法數十年﹐出手見\n"
		"血﹐從無虛發﹐江湖人稱「黑龍左使」。他久居這地底堂口﹐唯有\n"
		"身手機敏、心性夠狠的後輩﹐方有機會拜入門下﹐學得這一身殺人\n"
		"的本事。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("瑯夷堂主把玩著手中匕首﹐冷笑道﹕你既已入別派﹐道兒已定﹐何苦再來自討沒趣﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入夥
	if( me->query_level() < 1 ) {
		do_chat("瑯夷堂主斜睨了你一眼﹐說道﹕乳臭未乾的雛兒﹐且去江湖上滾過一遭再來罷。\n");
		return 0;
	}

	// 匕法暗算全憑一身機敏﹐手腳遲鈍者難成氣候（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("dex") < 14 ) {
		do_chat("瑯夷堂主上下打量了你一番﹐搖頭道﹕你手腳這般遲鈍﹐學不來我這偷天換日的手藝。\n");
		return 0;
	}

	do_chat(({
		"瑯夷堂主眯起眼睛﹐將你細細打量了一番。\n",
		"瑯夷堂主壓低聲音道﹕入了我瑯夷派﹐刀頭舔血﹐見不得光﹐你可怕了﹖\n",
		"瑯夷堂主嘿嘿一笑﹕也罷﹐瞧你還算機靈﹐我便收你入黑龍左使門下﹐傳你這套吃飯的本事。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("瑯夷堂主把匕首一收﹐說道﹕你既已另投他處﹐快滾罷。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("thief");
		me->set("sect", "瑯夷派");
		me->set("rank", "黑龍左使");
		me->set("title", "瑯夷派黑龍左使");

		me->set_skill("dagger", 0);
		me->set_skill("blood dagger", 0);
		me->map_skill("dagger", "blood dagger");

		// 同時授予瑯夷派內功﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("longyeforce", 0);
		me->map_skill("force", "longyeforce");

		message_vision(
			"$N反手抽出一柄匕首﹐將血魂匕法的入門殺招一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"瑯夷堂主說道﹕從今日起﹐你便是我瑯夷派黑龍左使門下的人了。\n",
			"瑯夷堂主沉聲道﹕到演武場對著草人勤練匕法﹐出手要快、要狠、要無聲。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 盜賊(thief)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的瑯夷派弟子轉入
// 三大進階分支之一。比照武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀 d/hudao)、
// 道士天師(d/tianshi)、和尚白象(d/baixiang)的授技模型(門檻更高、以 sect_branch
// 標記分支、升階 rank/title)﹐惟本門為「盜賊(thief)」職業﹐入門武功為匕法(dagger)﹐
// 故所授為匕法/針法/劍法/槍法/盜門內功——以此驗證通用「進階」指令 + do_advance
// 模型可第四度跨職業(武者/道士/和尚之外)套用。
//
// 與前五門的關鍵差異(職業特性)：
//   * 入門武功為匕法(dagger)﹐入門時 map_skill("dagger","blood dagger")(血魂匕法)﹐
//     入門火候門檻即以 "blood dagger" 計(對應武者的 lunmay/fonxansword/bawang
//     blade、道士的 taoism-fire、和尚的 rid-evil)。
//   * 進階各分支的 "base" 視招式而異：黑龍左使/右使以 dagger(匕法)為主﹐金蛇門人
//     捨匕習劍改以 sword(劍法)證道﹔黑龍左使另授 needle(驚異二針)、金蛇門人另授
//     pike(金蛇槍法)等副技。
//   * 屬性主門檻為 "dex"(身手機敏﹐盜賊暗算/閃躲根本)﹐非 str/spi/wis﹔金蛇門人
//     另設第二道 cor(膽識)門檻(戰鬥賊搶攻所需)。
//
// 三大分支(見 docs/03-門派與武功/05-盜賊-瑯夷隱教.md §進階分支(兩派共通))：
//   黑龍左使  ── docs 明列之暗殺型分支。內功 黑龍真氣 heilong-force + 匕法 奪命血魂匕
//                shadow dagger(主) + 針法 驚異二針 amazing-needle(副)。docs 載其
//                「攻擊狀態脫離有機會一擊必殺、偷襲/暗算/殺手本能、消除疲勞內功」。
//                最早開放、門檻最低。
//   黑龍右使  ── docs 明列之用毒型分支。內功 龍涎毒功 venom-force + 毒匕 噬魂毒匕
//                venom dagger(主)。docs 載其「將身上的毒傳遞給敵人(不進戰鬥即毒殺)、
//                適合暗殺掌門級 NPC」。門檻居中。
//   金蛇門人  ── docs 明列之戰鬥賊分支。內功 金蛇罡氣 serpent-force + 劍法 金蛇劍法
//                serpent sword(主﹐base 改 sword) + 槍法 金蛇槍法 serpent pike(副)。
//                docs 載其「右手持劍、左手搭配槍法、快速背刺驚人破壞力、蛇感提升
//                警覺」﹐攻評 S。門檻最高、另設第二道 cor 屬性門檻。
//
// 轉職門檻(條件)為本次設計值(docs 只給定位/評分非確切數字)﹐供日後平衡微調﹐並與
// 冷梅/封山/虎刀/天師/白象同階(lv20/25/30、入門武功火候 60/80/100)對齊﹕
//   key        level  blood dagger  attr 門檻              授內功         授武功(base)
//   ────────── ─────  ────────────  ────────────────────  ────────────  ──────────────────────────────
//   黑龍左使   20     60            dex >= 18             黑龍真氣       奪命血魂匕 (dagger)+驚異二針(needle)
//   黑龍右使   25     80            dex >= 20             龍涎毒功       噬魂毒匕 (dagger)
//   金蛇門人   30     100           dex >= 22, cor >= 20  金蛇罡氣       金蛇劍法 (sword)+金蛇槍法(pike)
//
// 註(docs 未明定數字之門檻)：docs 黑龍左使典型玩家為夜叉 70/3、殺業 25688 等成品線﹐
//   無確切轉職數字﹔本驗證線取與他派同階之偏低值﹐殺業/警覺等業力門檻標記為待接的
//   故事門檻 TODO(同冷梅虎督「拜入天邪」、虎刀鬼才「5000 殺業」、天師太乙「青邪戰勳
//   3000」)。docs「攻擊脫離必殺、隔空遞毒、快速背刺暴擊、蛇感警覺」屬 perform/poison/
//   backstab 系統(非招式表/力道係數)﹐已於各招式 daemon 開頭標記為待辦。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(黑龍左使/右使為 dagger﹔金蛇門人捨匕習劍故為 sword)。
// "extra" 為另授的副技﹕({ ({中文,英文,基礎技能}), ... })﹐授技後 map_skill(基礎,英文)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"黑龍左使" : ([
			"rank"    : "黑龍左使",
			"title"   : "瑯夷派黑龍左使",
			"level"   : 20,
			"blood dagger" : 60,
			"attr"    : "dex",
			"attr_min": 18,
			"base"    : "dagger",
			"force"   : ({ "黑龍真氣", "heilong-force" }),
			"skills"  : ({ ({ "奪命血魂匕", "shadow dagger" }) }),
			"extra"   : ({
				({ "驚異二針", "amazing-needle", "needle" }),
			}),
			"desc"    : "黑龍左使一脈以匕暗算、見血追命﹐有黑龍真氣護體﹐偷襲、殺手本能"
			            "與閃躲俱增。奪命血魂匕走 dagger(匕法)﹐另授驚異二針走 needle(針法)﹐"
			            "你可自行 map_skill 在匕、針之間切換。",
		]),
		"黑龍右使" : ([
			"rank"    : "黑龍右使",
			"title"   : "瑯夷派黑龍右使",
			"level"   : 25,
			"blood dagger" : 80,
			"attr"    : "dex",
			"attr_min": 20,
			"base"    : "dagger",
			"force"   : ({ "龍涎毒功", "venom-force" }),
			"skills"  : ({ ({ "噬魂毒匕", "venom dagger" }) }),
			"desc"    : "黑龍右使一脈以毒證道﹐有龍涎毒功以毒養功﹐刃淬奇毒、見血封喉﹐"
			            "最擅暗殺神級 NPC。噬魂毒匕走 dagger(匕法)﹐專走死角下毒索命。",
		]),
		"金蛇門人" : ([
			"rank"    : "金蛇門人",
			"title"   : "瑯夷派金蛇門人",
			"level"   : 30,
			"blood dagger" : 100,
			"attr"    : "dex",
			"attr_min": 22,
			"attr2"   : "cor",
			"attr2_min": 20,
			"base"    : "sword",
			"force"   : ({ "金蛇罡氣", "serpent-force" }),
			"skills"  : ({ ({ "金蛇劍法", "serpent sword" }) }),
			"extra"   : ({
				({ "金蛇槍法", "serpent pike", "pike" }),
			}),
			"desc"    : "金蛇門人俗稱戰鬥賊﹐捨匕習劍、右手金蛇劍法走 sword、左手金蛇槍法"
			            "走 pike﹐有金蛇罡氣剛猛護體﹐快攻搶攻、背刺暴擊﹐攻勢驚人。你可"
			            "自行 map_skill 在劍、槍之間切換。",
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
		do_chat("瑯夷堂主把玩著匕首冷笑道﹕我瑯夷派進階只有「黑龍左使」、「黑龍右使」、"
		        "「金蛇門人」三路﹐你要走哪一門﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為瑯夷派入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "瑯夷派" ) {
		do_chat("瑯夷堂主斜睨道﹕你又非我瑯夷派的人﹐進階之事從何談起﹖且先拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("瑯夷堂主冷笑道﹕你既已選定「" + me->query("sect_branch") +
		        "」一路﹐黑道規矩貴在專一﹐豈可朝三暮四﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("瑯夷堂主斜睨了你一眼﹐搖頭道﹕你火候尚淺﹐且再到江湖上滾過些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門匕法(血魂匕法 blood dagger)火候門檻。
	if( me->query_skill("blood dagger", 1) < b["blood dagger"] ) {
		do_chat("瑯夷堂主冷哼道﹕你連我血魂匕法的根基都未練透﹐如何學得這上乘殺著﹖"
		        "且回演武場對草人勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（盜賊以身手機敏為本﹐金蛇門人另重膽識）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("瑯夷堂主上下打量了你一番﹐搖頭道﹕你手腳還不夠機敏﹐撐不起這一路殺手的"
		        "本事﹐勉強習之徒送了性命。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("瑯夷堂主嗤笑道﹕你膽氣還嫩﹐當不了刀頭舔血的戰鬥賊﹐且去再磨磨膽子。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔瑯夷諸進階皆另授高階內功）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階主招式﹐並把主招式對應到該分支的基礎技能（base﹔多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的匕/劍火候)﹔僅當該基礎技能尚未習得時
	// (如金蛇門人改習 sword﹐入門時未授)補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "dagger";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 授副技（針法/槍法等﹐各自掛回其基礎技能﹔如驚異二針→needle、金蛇槍法→pike）。
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
		"$N反手抽出一柄匕首﹐刃光內斂殺機暗藏﹐而後將一身「" + branch +
		"」的上乘殺手本事傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"瑯夷堂主嘿嘿一笑﹕好﹗從今日起﹐你便是我瑯夷派的「" + b["rank"] + "」了。\n",
		"瑯夷堂主沉聲道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
