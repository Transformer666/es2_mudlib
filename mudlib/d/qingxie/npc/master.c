// master.c -- 哭笑門主 劉乙忘玄

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("劉乙忘玄", ({ "grimace master", "master", "kuxiao" }));
	set("nickname", "哭笑判官");
	set_attr("str", 25);
	set_attr("dex", 22);
	set_attr("int", 22);
	set_attr("wis", 23);
	set_attr("spi", 24);
	set_attr("cps", 25);
	set_attr("con", 26);
	set_attr("cor", 18);
	set_race("human");
	set_level(40);
	set_class("fighter");
	set("sect", "哭笑門");
	set("rank", "門主");

	set_skill("unarmed", 80);
	set_skill("staff", 150);
	set_skill("parry", 130);
	set_skill("dodge", 110);
	set_skill("force", 130);
	set_skill("chin_staff", 150);
	set_skill("huge force", 130);
	map_skill("staff", "chin_staff");
	map_skill("force", "huge force");

	advance_stat("gin", 220);
	advance_stat("kee", 240);
	advance_stat("sen", 220);

	set("age", 56);
	set("long",
		"這位便是哭笑門主劉乙忘玄﹐一襲玄黑長袍﹐手按一根烏沉沉的鐵\n"
		"杖﹐臉上一半在笑一半在哭﹐叫人捉摸不透。哭笑門是江湖上聞之色\n"
		"變的邪派﹐門主修得一身詭譎剛猛的青邪杖法與大邪心法﹐杖出如鬼\n"
		"嘯﹐守若銅牆﹐縱是成名高手亦難在他杖下討得便宜﹐人稱「哭笑判\n"
		"官」。他坐鎮青邪宮中﹐極少現身﹐唯有心志夠狠、根骨夠硬的人﹐\n"
		"方有機會拜入門下﹐習得這一身護法絕學。\n");
	setup();
	carry_object("/d/snow/npc/obj/cane")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("劉乙忘玄似笑非笑地瞥了你一眼﹕你既已入別派﹐還來我青邪宮作甚﹖\n");
		return 0;
	}

	// 須年滿一定等級﹐方有資格修習邪功
	if( me->query_level() < 1 ) {
		do_chat("劉乙忘玄冷哼一聲﹕你這身子骨還嫩得很﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 護法之學講究守得住、扛得起﹐筋骨孱弱者扛不住這份剛猛內勁
	if( me->query_attr("con") < 18 ) {
		do_chat("劉乙忘玄端詳了你半晌﹕你體魄太過孱弱﹐扛不住我這路邪功的反噬。\n");
		return 0;
	}

	do_chat(({
		"劉乙忘玄上上下下將你打量了一番﹐臉上的哭笑霎時凝住。\n",
		"劉乙忘玄陰惻惻地說道﹕我哭笑門的功夫﹐入門容易出門難﹐你可想清楚了﹖\n",
		"劉乙忘玄說道﹕也罷﹐我便收你做個護法弟子﹐傳你青邪杖法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("劉乙忘玄袍袖一拂﹕你既已另投他師﹐滾罷。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("fighter");
		me->set("sect", "哭笑門");
		me->set("rank", "護法");
		me->set("title", "哭笑門護法");

		me->set_skill("staff", 0);
		me->set_skill("chin_staff", 0);
		me->map_skill("staff", "chin_staff");

		// 同時授予大邪心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("huge force", 0);
		me->map_skill("force", "huge force");

		message_vision(
			"$N抄起一根烏沉沉的鐵杖﹐將青邪杖法的入門杖訣一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"劉乙忘玄陰陰一笑﹕從今日起﹐你便是我哭笑門的護法了。\n",
			"劉乙忘玄沉聲道﹕到演武場領根鐵杖勤加操演﹐杖要狠、樁要穩、心要冷﹐莫墮了我哭笑門的兇名。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 哭笑門(武者/fighter)的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的哭笑門弟子
// 轉入三大進階分支之一。比照冷梅莊 d/hanmei、封山派 d/fonxan、虎刀門 d/hudao
// 的授技模型(門檻更高、以 sect_branch 標記分支、升階 rank/title)﹐使通用
// 「進階」指令可不改動地驅動本門。
//
// 入門時(init_apprentice)即 map_skill("staff","chin_staff")(青邪杖法)、
// map_skill("force","huge force")(大邪心法)﹔故入門武功火候門檻以入門杖法
// "chin_staff" 計(對應冷梅 lunmay、封山 fonxansword、虎刀 bawang blade)。
//
// 三大分支(見 docs/03-門派與武功/01-武者-五大門派.md §3 哭笑門 三個進階)：
//   護法    ── docs 明列。ES2 最堅強的後盾、頂級完全防禦﹐唯一可在戰鬥中回 hp。
//              沿用入門大邪心法﹐授守勢杖法 青邪伏魔杖 chin-guard-staff(主招式
//              仍對應 staff 杖法)。評分 攻擊 D / 防禦 S / 續戰 S / 靈活 B﹐故
//              最早開放、門檻最低﹐重根骨(con)。
//   使者    ── docs 明列「使者(七損刀)」。難練自損(attr-2)﹐手動 perform、無視
//              防禦、外加定人。授內功 大邪心經 danei-sutra(戰鬥時補精氣)+ 刀法
//              大邪七損刀訣 seven_blade(基礎技能由 staff 改 blade)。重攻擊能力
//              值﹐故設 str + cor 雙屬性門檻。評分 攻擊 A。
//   素衣衛  ── docs 明列。太乙觀(天師)與青邪宮結盟之組合﹐既有天師法術 冰咒﹐又
//              有青邪杖法。沿用入門大邪心法﹐授法術 冰咒 taoism-freeze(基礎技能
//              magic﹐沿用天師既有 daemon)+ 副技 無相冰杖 wuxiang-staff(staff)。
//              docs 載「慧根 2x 裸體則法術很弱」﹐故設 wis + spi 雙屬性門檻。
//              門檻最高。
//
// 轉職門檻(條件)為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   key      level  chin_staff  attr 門檻              授內功         授武功(base)
//   ──────── ─────  ──────────  ────────────────────  ────────────  ─────────────────────────────
//   護法     20     60          con >= 18             (沿用大邪心法) 青邪伏魔杖 chin-guard-staff (staff)
//   使者     25     80          str >= 20, cor >= 20  大邪心經       大邪七損刀訣 seven_blade (blade)
//   素衣衛   30     100         wis >= 22, spi >= 20  (沿用大邪心法) 冰咒 taoism-freeze (magic)
//                                                                    +無相冰杖 wuxiang-staff (staff)
//
// 註(使者自損)：docs 載使者「難練自損(attr-2)」。屬性扣減屬轉職代價/perform 系統
//   (非授技表)﹐標記為待接的設計 TODO(同冷梅虎督「拜入天邪」、虎刀鬼才「5000 殺業」
//   等故事/系統門檻)。
// 註(素衣衛結盟)：docs 載素衣衛為太乙觀(天師派)與青邪宮結盟之組合﹐理應另有「結盟/
//   雙修」前置(同封山素衣衛、天師太乙真人之故事門檻)。為與本批進階一致(只 gate
//   level/skill/attr)﹐此處先以入門杖法火候 100 + wis/spi 雙屬性替代驗證﹐結盟前置
//   標記為待接的故事門檻 TODO。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(護法以 staff 杖法﹔使者改 blade 刀法﹔素衣衛
//   主修法術故為 magic)。
// "extra" 為另授的副技﹕({ ({中文,英文,基礎技能}), ... })﹐授技後 map_skill(基礎,英文)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"護法" : ([
			"rank"    : "哭笑護法",
			"title"   : "哭笑門護法",
			"level"   : 20,
			"chin_staff" : 60,
			"attr"    : "con",
			"attr_min": 18,
			"base"    : "staff",
			"force"   : 0,    // 護法沿用入門大邪心法(huge force)﹐不另授內功
			"skills"  : ({ ({ "青邪伏魔杖", "chin-guard-staff" }) }),
			"desc"    : "護法是 ES2 最堅強的後盾、頂級完全防禦﹐更是唯一能在戰鬥中"
			            "回 hp 的一脈。青邪伏魔杖沉穩綿密、長於格擋纏鬥與久戰﹐拿一"
			            "根杖逛大街幾可立於不敗之地﹐然遇上無視防禦的對手須當心。",
		]),
		"使者" : ([
			"rank"    : "哭笑使者",
			"title"   : "哭笑門使者",
			"level"   : 25,
			"chin_staff" : 80,
			"attr"    : "str",
			"attr_min": 20,
			"attr2"   : "cor",
			"attr2_min": 20,
			"base"    : "blade",    // 使者捨杖習刀﹐主招式對應 blade
			"force"   : ({ "大邪心經", "danei-sutra" }),
			"skills"  : ({ ({ "大邪七損刀訣", "seven_blade" }) }),
			"desc"    : "使者捨杖習七損刀﹐刀招無視防禦、外加定人﹐威力全看攻擊能力值﹐"
			            "宜穿攻擊能力裝。佐以大邪心經﹐戰鬥時可同時補回精氣﹐招架成功"
			            "更注入破體刀氣。唯刀法難練自損﹐單打獨鬥最能逞威。",
		]),
		"素衣衛" : ([
			"rank"    : "哭笑素衣衛",
			"title"   : "哭笑門素衣衛",
			"level"   : 30,
			"chin_staff" : 100,
			"attr"    : "wis",
			"attr_min": 22,
			"attr2"   : "spi",
			"attr2_min": 20,
			"base"    : "magic",    // 素衣衛主修天師冰咒﹐主招式對應 magic
			"force"   : 0,    // 素衣衛沿用入門大邪心法(huge force)﹐不另授內功
			"skills"  : ({ ({ "冰咒", "taoism-freeze" }) }),
			"extra"   : ({
				({ "無相冰杖", "wuxiang-staff", "staff" }),
			}),
			"desc"    : "素衣衛乃太乙觀與青邪宮結盟之絕學﹐既習天師冰咒(走 magic﹐以"
			            "無相冰、兆冰交替定人、削敵神識)﹐又承青邪杖法﹐授無相冰杖(走"
			            "staff)。你可自行 map_skill 在冰咒與杖法之間切換。慧根、靈性"
			            "為施法根本﹐裸體則法術大弱﹐務必披掛慧根裝。",
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
		do_chat("劉乙忘玄似笑非笑道﹕我哭笑門進階只有「護法」、「使者」、「素衣衛」三路﹐"
		        "你說的是哪一門﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為哭笑門入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "哭笑門" ) {
		do_chat("劉乙忘玄陰惻惻道﹕你又非我哭笑門弟子﹐進階之事從何談起﹖且先拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("劉乙忘玄冷笑道﹕你既已選定「" + me->query("sect_branch") +
		        "」一路﹐邪功貴在專一﹐豈可朝三暮四﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("劉乙忘玄瞥了你一眼﹐搖頭道﹕你火候尚淺﹐且再歷練些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門杖法(青邪杖法 chin_staff)火候門檻。
	if( me->query_skill("chin_staff", 1) < b["chin_staff"] ) {
		do_chat("劉乙忘玄陰陰道﹕你連我青邪杖法的根基都未練透﹐如何學得這上乘邪功﹖"
		        "且回演武場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（各分支重不同根骨﹐部分分支另有第二道屬性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("劉乙忘玄端詳了你半晌﹐搖頭道﹕你的根骨還撐不起這一路邪功﹐"
		        "勉強習之反噬己身。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("劉乙忘玄搖頭道﹕你的根骨悟性仍有所偏廢﹐撐不起這一路邪功﹐"
		        "且去再磨練磨練。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔護法/素衣衛沿用入門大邪心法﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階主招式﹐並把主招式對應到該分支的基礎技能（base﹔多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的杖/刀/法火候)﹔僅當該基礎技能尚未習得
	// 時(如使者改習 blade、素衣衛改習 magic﹐入門時未授)補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "staff";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 授副技（如素衣衛的無相冰杖→staff﹔各自掛回其基礎技能）。
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
		"$N抄起一根烏沉沉的鐵杖﹐臉上忽哭忽笑﹐將一身「" + branch +
		"」的上乘邪功傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"劉乙忘玄陰陰一笑﹕好﹗從今日起﹐你便是我哭笑門的「" + b["rank"] + "」了。\n",
		"劉乙忘玄沉聲道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
