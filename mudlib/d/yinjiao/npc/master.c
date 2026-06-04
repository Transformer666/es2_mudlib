// master.c -- 隱教聖女 利丰華

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("利丰華", ({ "yinjiao master", "master", "saint", "lifenghua" }));
	set("nickname", "隱教聖女");
	set("gender", "女性");
	set_attr("str", 18);
	set_attr("dex", 32);
	set_attr("int", 26);
	set_attr("wis", 24);
	set_attr("spi", 24);
	set_attr("cps", 24);
	set_attr("con", 20);
	set_attr("cor", 16);
	set_race("human");
	set_level(40);
	set_class("thief");
	set("sect", "隱教");
	set("rank", "聖女");
	set("title", "隱教聖女");

	set_skill("unarmed", 60);
	set_skill("dodge", 130);
	set_skill("parry", 90);
	set_skill("force", 120);
	set_skill("yinjiao force", 120);
	set_skill("dagger", 150);
	set_skill("serpent dagger", 150);
	map_skill("force", "yinjiao force");
	map_skill("dagger", "serpent dagger");

	advance_stat("gin", 220);
	advance_stat("kee", 200);
	advance_stat("sen", 200);

	set("age", 36);
	set("long",
		"這位便是隱教的聖女利丰華。她一身緊束的玄色勁裝﹐外罩一襲輕\n"
		"薄如煙的黑紗﹐面容清冷絕美﹐唯獨一雙眼睛深不見底﹐顧盼之間\n"
		"透著一股看慣了生死的漠然殺氣。她腰間斜束軟帶﹐帶上暗藏著數\n"
		"柄淬毒的薄刃匕首。隱教隱於野羊山深處﹐自金蛇門一脈分出﹐專\n"
		"事潛行暗殺、見血封喉的勾當﹐聖女浸淫金蛇匕法多年﹐出手如毒\n"
		"蛇噬人﹐無聲無息。她端坐壇上﹐冷眼旁觀來人﹐唯有身手機敏、\n"
		"心性夠狠的後輩﹐方有機會叩拜金蛇﹐拜入她門下﹐學得這一身殺\n"
		"人的本事。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("利丰華指尖撫過匕首薄刃﹐冷冷說道﹕你既已入別派﹐道兒已定﹐何苦再來自尋死路﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入夥
	if( me->query_level() < 1 ) {
		do_chat("利丰華淡淡瞥了你一眼﹐說道﹕乳臭未乾的雛兒﹐且去江湖上滾過一遭再來罷。\n");
		return 0;
	}

	// 匕法暗算全憑一身機敏﹐手腳遲鈍者難成氣候（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("dex") < 14 ) {
		do_chat("利丰華上下打量了你一番﹐搖頭道﹕你手腳這般遲鈍﹐學不來我隱教見血封喉的手藝。\n");
		return 0;
	}

	do_chat(({
		"利丰華眯起那雙深不見底的眼睛﹐將你細細打量了一番。\n",
		"利丰華壓低聲音道﹕入了我隱教﹐刀頭舔血﹐見不得光﹐你可怕了﹖\n",
		"利丰華嘴角微微一揚﹕也罷﹐瞧你還算機靈﹐你便去叩拜金蛇﹐我收你入金蛇門人之列﹐傳你這套吃飯的本事。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("利丰華薄刃一收﹐冷聲道﹕你既已另投他處﹐快滾罷。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("thief");
		me->set("sect", "隱教");
		me->set("rank", "金蛇門人");
		me->set("title", "隱教金蛇門人");

		me->set_skill("dagger", 0);
		me->set_skill("serpent dagger", 0);
		me->map_skill("dagger", "serpent dagger");

		// 同時授予隱教心法﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("yinjiao force", 0);
		me->map_skill("force", "yinjiao force");

		message_vision(
			"$N自腰間反手抽出一柄薄刃匕首﹐將金蛇匕法的入門殺招一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"利丰華說道﹕從今日起﹐你便是我隱教金蛇門下的人了。\n",
			"利丰華沉聲道﹕到演武場對著草人勤練匕法﹐出手要快、要狠、要無聲﹐如金蛇噬人。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 盜賊(thief)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的隱教金蛇門人
// 弟子轉入三大進階分支之一。比照武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀
// d/hudao)、道士天師(d/tianshi)、和尚白象(d/baixiang)的授技模型(門檻更高、以
// sect_branch 標記分支、升階 rank/title)﹐惟本門為「盜賊(thief)」職業﹐入門武功
// 為匕法(dagger)、入門時 map_skill("dagger","serpent dagger")(金蛇匕法)、另授
// 隱教心法(yinjiao force)——以此驗證通用「進階」指令 + do_advance 模型可跨第四個
// 職業(武者/道士/和尚之外)套用。
//
// 三大分支(見 docs/03-門派與武功/05-盜賊-瑯夷隱教.md §進階分支(兩派共通))﹕
// docs 明載盜賊兩派(瑯夷派/隱教)共通三條進階路﹐故所授高階技能 daemon 與瑯夷
// 派共用(daemon/skill/ 下已先行建好﹐本檔只負責 map_skill 掛上、不重寫 daemon)﹕
//   金蛇門人  ── docs「俗稱戰鬥賊﹕右手持劍、左手搭配槍法、戰鬥中靠快速背刺有
//                驚人破壞力(攻評 S)」。捨匕習劍﹕內功 金蛇罡氣 serpent-force +
//                主武功 金蛇劍法 serpent sword(基礎技能由 dagger 改 sword) + 副武功
//                金蛇槍法 serpent pike(基礎技能 pike﹐左手所配)。最早開放、門檻最低。
//   黑龍左使  ── docs「攻擊狀態脫離有機會造成一擊必殺技(打 hp)、消除疲勞內功」。
//                沿匕法一路精進﹕內功 黑龍真氣 heilong-force + 高階匕法 奪命血魂匕
//                shadow dagger(基礎技能仍為 dagger)。門檻居中、另設第二道屬性(str)。
//   黑龍右使  ── docs「將身上的毒傳遞給敵人(不進入戰鬥狀態)、適合暗殺掌門級 NPC」。
//                轉走用毒一路﹕內功 龍涎毒功 venom-force + 毒匕 噬魂毒匕 venom dagger
//                (基礎技能仍為 dagger)。門檻最高、另設第二道屬性(int)。
//
// 轉職門檻(條件)為本次設計值(docs 只給評分/定位非確切數字)﹐供日後平衡微調﹕
//   key      level  serpent dagger  attr 門檻              授內功           授武功(base)
//   ──────── ─────  ──────────────  ────────────────────  ──────────────  ──────────────────────────
//   金蛇門人 20     60              dex >= 18             金蛇罡氣         金蛇劍法 serpent sword (sword)
//                                                                         +金蛇槍法 serpent pike (pike)
//   黑龍左使 25     80              dex >= 20, str >= 18  黑龍真氣         奪命血魂匕 shadow dagger (dagger)
//   黑龍右使 30     100             dex >= 22, int >= 20  龍涎毒功         噬魂毒匕 venom dagger (dagger)
//
// 註(屬性門檻)：盜賊三轉主屬性皆取 dex(機敏﹐呼應入門 accept_apprentice 的
//   dex 門檻與 docs「全憑一身機敏」)﹔黑龍左使另重 str(暗算搶攻之力)、黑龍右使
//   另重 int(煉毒/暗殺掌門級需算計)﹐為設計(docs未明定):各分支偏重的第二屬性。
// 註(門派故事門檻 TODO)：docs 黑龍右使「不戰即毒殺」、左使「脫戰必殺」、金蛇門人
//   「快速背刺暴擊 / 蛇感提升警覺」屬 perform/poison/警覺 系統(非招式表/非力道係數)﹐
//   各高階 daemon 內已標記為待辦﹔此處進階只 gate level/skill/attr﹐與其餘五門一致。
// 註(高階 daemon 共用)：本門進階所授 serpent sword/serpent pike/serpent-force/
//   shadow dagger/heilong-force/venom dagger/venom-force 等 daemon 為盜賊兩派共通
//   (docs §進階分支「兩派共通」)﹐已存在於 daemon/skill/ 下﹐本檔僅 map_skill 掛上﹐
//   不重複建立。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(金蛇門人捨匕習劍故為 sword﹔黑龍左右使沿匕法故為 dagger)。
// "extra" 為另授的副技﹕({ ({中文,英文,基礎技能}), ... })﹐授技後 map_skill(基礎,英文)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"金蛇門人" : ([
			"rank"    : "隱教金蛇使者",
			"title"   : "隱教金蛇使者",
			"level"   : 20,
			"serpent dagger" : 60,
			"attr"    : "dex",
			"attr_min": 18,
			"base"    : "sword",     // 金蛇門人捨匕習劍﹐主招式對應 sword
			"force"   : ({ "金蛇罡氣", "serpent-force" }),
			"skills"  : ({ ({ "金蛇劍法", "serpent sword" }) }),
			"extra"   : ({
				({ "金蛇槍法", "serpent pike", "pike" }),
			}),
			"desc"    : "金蛇門人俗稱「戰鬥賊」﹐捨匕習劍、右手金蛇劍法快攻、左手金蛇槍法"
			            "牽制﹐有金蛇罡氣護身﹐攻勢凌厲(攻評 S)。金蛇劍法走 sword、金蛇槍法"
			            "走 pike﹐你可自行 map_skill 在劍、槍之間切換﹐重在搶攻背刺。",
		]),
		"黑龍左使" : ([
			"rank"    : "隱教黑龍左使",
			"title"   : "隱教黑龍左使",
			"level"   : 25,
			"serpent dagger" : 80,
			"attr"    : "dex",
			"attr_min": 20,
			"attr2"   : "str",
			"attr2_min": 18,
			"base"    : "dagger",    // 黑龍左使沿匕法一路精進﹐主招式仍對應 dagger
			"force"   : ({ "黑龍真氣", "heilong-force" }),
			"skills"  : ({ ({ "奪命血魂匕", "shadow dagger" }) }),
			"desc"    : "黑龍左使一脈以奪命血魂匕走死角、見血追命﹐有黑龍真氣護身﹐殺氣"
			            "內斂如蟄龍蓄勢。脫戰必殺、清疲勞之能屬 perform 系統(待辦)﹐你"
			            "且先把這手暗算搶攻的匕法練至出神入化。",
		]),
		"黑龍右使" : ([
			"rank"    : "隱教黑龍右使",
			"title"   : "隱教黑龍右使",
			"level"   : 30,
			"serpent dagger" : 100,
			"attr"    : "dex",
			"attr_min": 22,
			"attr2"   : "int",
			"attr2_min": 20,
			"base"    : "dagger",    // 黑龍右使轉走用毒一路﹐主招式仍對應 dagger
			"force"   : ({ "龍涎毒功", "venom-force" }),
			"skills"  : ({ ({ "噬魂毒匕", "venom dagger" }) }),
			"desc"    : "黑龍右使以龍涎毒功煉毒養功、噬魂毒匕刃淬奇毒、見血封喉﹐專事暗殺"
			            "掌門級強敵。隔空遞毒、不戰而殺之能屬 poison 系統(待辦)﹐你且先把"
			            "這手淬毒的殺著磨利。",
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
		do_chat("利丰華指尖撫過匕首薄刃﹐冷冷道﹕我隱教進階只有「金蛇門人」、「黑龍左使」、"
		        "「黑龍右使」三路﹐你說的是哪一門﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為隱教入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "隱教" ) {
		do_chat("利丰華冷笑道﹕你又非我隱教門人﹐進階之事從何談起﹖且先叩拜金蛇、拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("利丰華搖頭道﹕你既已選定「" + me->query("sect_branch") +
		        "」一路﹐殺手之道貴在專精﹐豈可三心二意﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("利丰華淡淡瞥了你一眼﹐搖頭道﹕你火候尚淺﹐且再到江湖上歷練些時日﹐"
		        "待手藝熟了再來罷。\n");
		return notify_fail("");
	}

	// 入門匕法(金蛇匕法 serpent dagger)火候門檻。
	if( me->query_skill("serpent dagger", 1) < b["serpent dagger"] ) {
		do_chat("利丰華冷聲道﹕你連我金蛇匕法的根基都未練透﹐如何學得這上乘殺著﹖"
		        "且回演武場對著草人勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（盜賊三轉皆重機敏 dex﹐部分分支另有第二道屬性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("利丰華上下打量了你一番﹐搖頭道﹕你手腳還不夠機敏﹐撐不起這一路殺手的功夫﹐"
		        "勉強習之徒誤性命。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("利丰華薄刃輕轉﹐搖頭道﹕你的根骨心機仍有所偏廢﹐撐不起這一路殺手的勾當﹐"
		        "且去再磨練磨練。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（隱教三轉皆另授高階內功﹐取代入門隱教心法）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階主招式﹐並把主招式對應到該分支的基礎技能（base﹔金蛇門人改習 sword﹐
	// 黑龍左右使沿用 dagger）。不重置既有基礎技能等級(保留弟子累積的兵刃火候)﹔
	// 僅當該基礎技能尚未習得時(如金蛇門人改練 sword﹐入門時未授)補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "dagger";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 授副技（如金蛇門人左手所配的金蛇槍法﹐各自掛回其基礎技能 pike）。
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
		"$N自腰間反手抽出一柄薄刃匕首﹐閉目凝神片刻﹐而後將一身「" + branch +
		"」的上乘殺手功夫傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"利丰華冷冷一笑﹕也罷﹗從今日起﹐你便是我隱教的「" + b["rank"] + "」了。\n",
		"利丰華沉聲道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
