// master.c -- 天師派掌教真人 郭布（號朱衣真人）

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("郭布", ({ "guo bu", "taoist master", "master", "priest" }));
	set("nickname", "朱衣真人");
	set_attr("str", 20);
	set_attr("dex", 22);
	set_attr("int", 26);
	set_attr("wis", 25);
	set_attr("spi", 28);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("taoist");
	set("sect", "天師派");
	set("rank", "掌教");
	set("title", "天師派掌教真人");

	set_skill("unarmed", 60);
	set_skill("dodge", 100);
	set_skill("parry", 90);
	set_skill("force", 120);
	set_skill("magic", 150);
	set_skill("taoism-fire", 150);
	map_skill("magic", "taoism-fire");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 56);
	set("long",
		"這位便是天師派的掌教真人郭布﹐一身朱紅道袍﹐頭戴蓮花冠﹐手執一\n"
		"柄拂塵﹐面色紅潤﹐雙目炯炯有神﹐周身隱隱透著一股溫煦的火氣。天\n"
		"師派朱衣一脈以火證道﹐郭布浸淫火術數十年﹐一身道法已臻化境\n"
		"﹐江湖人稱「朱衣真人」。他久居三清殿中潛修大道﹐唯有靈性不俗、\n"
		"與火有緣的後輩﹐方有機會拜入朱衣門下﹐習得這一身焚天煉地的道法\n"
		"。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("郭布輕拂拂塵﹐說道﹕你既已入別派﹐道緣已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入道
	if( me->query_level() < 1 ) {
		do_chat("郭布說道﹕你塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 火術全憑靈性引動﹐靈性過低者難窺門徑（門檻甚低﹐尋常人皆可入）
	if( me->query_attr("spi") < 14 ) {
		do_chat("郭布端詳了你一會﹐搖頭道﹕你靈性閉塞﹐與火無緣﹐難學我這路道法。\n");
		return 0;
	}

	do_chat(({
		"郭布上下打量了你一番﹐微微頷首。\n",
		"郭布說道﹕我天師派朱衣一脈﹐以火證道﹐你可有這份道心﹖\n",
		"郭布說道﹕也罷﹐你既與火有緣﹐我便收你入朱衣門下﹐傳你天師道法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("郭布揮了揮拂塵﹐說道﹕你既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("taoist");
		me->set("sect", "天師派");
		me->set("rank", "朱衣弟子");
		me->set("title", "天師派朱衣弟子");

		me->set_skill("magic", 0);
		me->set_skill("taoism-fire", 0);
		me->map_skill("magic", "taoism-fire");

		// 同時授予丹陽神功（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("sun force", 0);
		me->map_skill("force", "sun force");

		message_vision(
			"$N取過一道朱符﹐將天師道法【火術】的入門口訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"郭布說道﹕從今日起﹐你便是我天師派朱衣門下的弟子了。\n",
			"郭布說道﹕道法無涯﹐你且到演法場對火參修﹐莫負了這身道法。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 非武者(法系/道士)門派的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的天師派朱衣弟子
// 轉入三大進階分支之一。比照武者三門(冷梅 d/hanmei、封山 d/fonxan、虎刀 d/hudao)
// 的授技模型(門檻更高、以 sect_branch 標記分支、升階 rank/title)﹐惟本門為「道士
// (taoist)」職業﹐故所授為「法術(magic)/內功(force)」而非劍刀招式——以此驗證通用
// 「進階」指令 + do_advance 模型可跨職業套用。
//
// 與武者門派的關鍵差異：
//   * "base" 一律為 "magic"(法術)﹐非 sword/blade﹔授技後 map_skill("magic", <咒>)。
//     (入門時即 map_skill("magic","taoism-fire")﹐進階沿此模型把 magic 改映到更
//      上乘的咒術 daemon。)
//   * 入門火候門檻以入門火術 "taoism-fire" 計(對應武者的 lunmay/fonxansword/
//     bawang blade)。
//   * 屬性主門檻為 "spi"(靈性，道士施法根本)﹐非 str/dex/cor。
//
// 三大分支(見 docs/03-門派與武功/02-道士-天師與茅山.md 天師派四元素 / 四系雙修)：
//   朱衣真傳  ── 法術 桃山密籙 taoism of conviction(炎殺咒一系﹐上乘火咒﹔沿用入門
//                丹陽神功)。最早開放、門檻最低。docs 桃山密籙原條件為「紫薇心經
//                100 + 桃仙任務」﹐此處以入門火術火候 + 靈性門檻替代驗證(見下注)。
//   素雲道人  ── 內功 紫府雷經 violet-thunder force + 法術 素雲書 taoism-cloud(駕雲
//                傳送)。兼修雷系吐納、得駕雲之能﹐重在游走馳援。門檻居中。
//   太乙真人  ── 內功 冰蠶奇功 polar-silkworm force + 法術 冰咒 taoism-freeze(四系
//                雙修第二系)。docs「天師四系雙修」之承襲(lv40、青邪戰勳3000、pray
//                太乙金身習第二系咒﹐lv50 攜元素 seal 於藏經閣五樓習對應內功)。
//                門檻最高、另設第二道屬性(int)門檻。
//
// 轉職門檻(條件)為本次設計值﹐供日後平衡微調﹕
//   key          level  taoism-fire  attr 門檻              授內功             授法術(base=magic)
//   ──────────── ─────  ───────────  ────────────────────  ────────────────  ─────────────────────────
//   朱衣真傳     20     60           spi >= 18             (沿用丹陽神功)     桃山密籙 taoism of conviction
//   素雲道人     25     80           spi >= 20             紫府雷經           素雲書 taoism-cloud
//   太乙真人     30     100          spi >= 22, int >= 20  冰蠶奇功           冰咒 taoism-freeze
//
// 註(朱衣真傳 docs 原值)：docs 桃山密籙條件為「紫薇心經 100 + 桃仙任務」。紫薇心經
//   (chivi sutra)與桃仙任務屬尚未接的法術/任務門檻﹔為與本批進階一致(只 gate
//   level/skill/attr)﹐此處先以入門火術火候 60 + 靈性 18 替代﹐並標記紫薇心經/桃仙
//   任務為待接的故事門檻 TODO(同冷梅虎督「拜入天邪」、虎刀鬼才「5000 殺業」)。
// 註(太乙真人 docs 原值)：docs 四系雙修為「lv40、青邪戰勳 3000、pray 太乙金身」並於
//   lv50 攜元素 seal 習第二系內功。本驗證線取 lv30 / taoism-fire 100 / spi22 / int20
//   (與封山劍客、冷梅虎督、虎刀太守同階)﹐青邪戰勳 3000 標記為待接的戰勳門檻 TODO。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主咒對應的基礎技能(天師諸進階皆以 magic 法術為主)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"朱衣真傳" : ([
			"rank"    : "朱衣真傳",
			"title"   : "天師派朱衣真傳",
			"level"   : 20,
			"taoism-fire" : 60,
			"attr"    : "spi",
			"attr_min": 18,
			"base"    : "magic",
			"force"   : 0,    // 朱衣真傳沿用入門丹陽神功(sun force)﹐不另授內功
			"skills"  : ({ ({ "桃山密籙", "taoism of conviction" }) }),
			"desc"    : "桃山密籙乃朱衣一脈的上乘火咒﹐炎殺咒幽赤煞焰可短時削敵火抗、"
			            "灼骨焚心﹐然耗神甚鉅﹐施法務必留意神識。",
		]),
		"素雲道人" : ([
			"rank"    : "素雲道人",
			"title"   : "天師派素雲道人",
			"level"   : 25,
			"taoism-fire" : 80,
			"attr"    : "spi",
			"attr_min": 20,
			"base"    : "magic",
			"force"   : ({ "紫府雷經", "violet-thunder force" }),
			"skills"  : ({ ({ "素雲書", "taoism-cloud" }) }),
			"desc"    : "素雲道人兼修紫府雷經吐納、又得素雲書駕雲之能﹐可御雲遨遊、"
			            "千里馳援。素雲書走 magic 槽駕雲趕路(enable magic with 素雲書)﹐"
			            "與攻擊咒術(enable spells)兩不相礙。",
		]),
		"太乙真人" : ([
			"rank"    : "太乙真人",
			"title"   : "天師派太乙真人",
			"level"   : 30,
			"taoism-fire" : 100,
			"attr"    : "spi",
			"attr_min": 22,
			"attr2"   : "int",
			"attr2_min": 20,
			"base"    : "magic",
			"force"   : ({ "冰蠶奇功", "polar-silkworm force" }),
			"skills"  : ({ ({ "冰咒", "taoism-freeze" }) }),
			"desc"    : "太乙真人乃天師四系雙修之始﹐於朱衣火道之外兼修冰蠶奇功與冰咒﹐"
			            "水火相濟、攻守俱備。你可自行 map_skill 在火咒、冰咒之間切換。",
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
		do_chat("郭布輕拂拂塵道﹕我天師派進階只有「朱衣真傳」、「素雲道人」、"
		        "「太乙真人」三路﹐你欲修哪一脈道法﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為天師派入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "天師派" ) {
		do_chat("郭布搖頭道﹕你又非我天師派門下﹐進階之事從何談起﹖且先拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("郭布道﹕你既已選定「" + me->query("sect_branch") +
		        "」一脈﹐道貴專一﹐豈可見異思遷﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("郭布端詳了你一會﹐搖頭道﹕你道行尚淺﹐且再潛修些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門火術(天師道法【火術】 taoism-fire)火候門檻。
	if( me->query_skill("taoism-fire", 1) < b["taoism-fire"] ) {
		do_chat("郭布道﹕你連我天師火術的根基都未練透﹐如何駕馭這上乘道法﹖"
		        "且回演法場對火參修去。\n");
		return notify_fail("");
	}

	// 屬性門檻（道士以靈性為本﹐部分分支另有第二道屬性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("郭布搖頭道﹕你的靈性還引動不了這一脈道法﹐勉強修之徒耗心神。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("郭布搖頭道﹕你悟性未足﹐尚參不透四系雙修的玄奧﹐"
		        "且去再參修參修。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳道 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔朱衣真傳沿用入門丹陽神功﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授上乘法術﹐並把主咒對應到該分支的基礎技能（base=magic﹔多咒者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換，如太乙真人的火咒/冰咒）。
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
		"$N拂塵一揚﹐口誦真言﹐將一身「" + branch +
		"」的上乘道法傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"郭布含笑道﹕善哉﹗從今日起﹐你便是我天師派的「" + b["rank"] + "」了。\n",
		"郭布道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
