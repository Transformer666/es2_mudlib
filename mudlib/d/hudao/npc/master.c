// master.c -- 虎刀門門主 高慎

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("高慎", ({ "hudao master", "master", "gaoshen" }));
	set("nickname", "嘯林刀王");
	set_attr("str", 26);
	set_attr("dex", 24);
	set_attr("int", 21);
	set_attr("wis", 22);
	set_attr("spi", 23);
	set_attr("cps", 24);
	set_attr("con", 25);
	set_attr("cor", 25);
	set_race("human");
	set_level(40);
	set_class("fighter");
	set("sect", "虎刀門");
	set("rank", "門主");

	set_skill("unarmed", 80);
	set_skill("blade", 150);
	set_skill("parry", 120);
	set_skill("dodge", 110);
	set_skill("force", 120);
	set_skill("bawang blade", 150);
	set_skill("hudao force", 120);
	map_skill("blade", "bawang blade");
	map_skill("force", "hudao force");

	advance_stat("gin", 220);
	advance_stat("kee", 220);
	advance_stat("sen", 220);

	set("age", 49);
	set("long",
		"這位便是虎刀門門主高慎﹐身形魁梧如鐵塔﹐一身洗得發白的玄\n"
		"色勁裝裹著虬結的筋肉﹐左頰一道斜貫眉梢的舊刀疤﹐使那張本就剽\n"
		"悍的臉愈顯兇煞。他背負一口烏沉沉的厚背快刀﹐按刀而立﹐眉宇間\n"
		"自有一股嘯傲山林的霸烈之氣。虎刀門深藏老松林中﹐以一脈剛猛無\n"
		"匹的霸王刀招威震一方﹐高慎自幼在這林裡與猛虎搏命﹐悟出刀如虎\n"
		"撲、快狠決絕的刀道﹐江湖中人敬畏地喚他一聲「嘯林刀王」。他收\n"
		"徒不問出身﹐只重一個「膽」字﹐唯有心性剽悍、敢於亮刀的後生﹐\n"
		"方有機緣入他門下﹐習得這一身殺伐果決的快刀。\n");
	// 結仇標記：殺虎刀門 NPC 會在玩家身上累積 vendetta/tiger﹐其後虎刀門
	// NPC 一見此玩家便主動圍攻（機制見 chard.c 累積、attack.c init() 觸發）。
	set("vendetta_mark", "tiger");
	setup();
	carry_object("/obj/area/obj/blade")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("高慎冷笑一聲﹐說道﹕你既已入了別派﹐還來我虎刀門攪甚麼局﹖\n");
		return 0;
	}

	// 須略有歷練方可習刀
	if( me->query_level() < 1 ) {
		do_chat("高慎瞥了你一眼﹐說道﹕乳臭未乾的雛兒﹐且去江湖上滾過幾遭再來罷。\n");
		return 0;
	}

	// 虎刀門的刀剛猛霸烈﹐膽魄與筋力不足者﹐握不住這一口快刀。
	if( me->query_attr("str") < 14 && me->query_attr("cor") < 14 ) {
		do_chat("高慎按刀打量了你半晌﹐搖頭道﹕你筋骨綿軟、膽氣不足﹐提不動我虎刀門這口快刀。\n");
		return 0;
	}

	do_chat(({
		"高慎按著刀柄上下打量了你一番﹐眼中精光一閃。\n",
		"高慎喝道﹕我虎刀門的刀﹐講究一個「快」、一個「狠」﹐亮刀便要見血﹐你可有這份膽氣﹖\n",
		"高慎放聲大笑﹕好﹗我便收你做個記名弟子﹐傳你霸王刀招。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("高慎把手一揮﹐喝道﹕你既已另投他師﹐滾罷。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("fighter");
		me->set("sect", "虎刀門");
		me->set("rank", "護衛");
		me->set("title", "虎刀門護衛");

		me->set_skill("blade", 0);
		me->set_skill("bawang blade", 0);
		me->map_skill("blade", "bawang blade");

		// 同時授予虎刀門內功﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("hudao force", 0);
		me->map_skill("force", "hudao force");

		message_vision(
			"$N抄起一口快刀﹐將霸王刀招的入門刀訣一招一式地劈砍給$n看。\n",
			this_object(), me);
		do_chat(({
			"高慎喝道﹕從今日起﹐你便是我虎刀門的護衛了。\n",
			"高慎說道﹕刀道無他﹐唯快不破、唯狠制敵﹐你且到演武場去把這口刀劈到出神入化﹗\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的虎刀門弟子
// 轉入三大進階分支之一。比照封山派掌門 d/fonxan/npc/master.c 與冷梅莊主
// d/hanmei/npc/master.c 的授技模型(門檻更高、以 sect_branch 標記分支、升階
// rank/title)﹐使通用「進階」指令可不改動地驅動本門。
//
// 三大分支(見 docs/03-門派與武功/01-武者-五大門派.md §5 虎刀門)：
//   護衛  ── 刀法 猛虎護身刀 guardtiger blade(不另授內功﹐沿用入門虎刀心法)
//            虎刀門最早開放的二轉﹐攻守兼備、續戰持久﹐有定技/powerup/deathwish。
//            門檻最低。
//   鬼才  ── 刀法 瘋虎刀法 tiger blade(不另授內功)﹐兩手持刀皆可施展。江湖中
//            最具爆發力(攻擊 S)﹐有 overpower / 第一追保證第二追與反手拔刀(無視
//            防禦)/兩手 10 刀連擊。門檻居中(docs 載另需 5000 殺業﹐見下注)。
//   太守  ── 刀法 重擊術 powerblow + 格擋 強力格擋技巧 heavy_parry(不另授內功)。
//            最新開的二轉﹐多 sr 系列﹐重擊術可直接爆 hp。門檻最高﹐且 docs 明載
//            「轉職條件：等級 50、臂力 40、膽識 30 的**男性**虎刀門弟子」。
//
// 轉職門檻(條件)﹕太守的「男性」為 docs 明定的硬條件(故照實設 gender gate)﹔
// 其餘等級/入門刀法火候/屬性數字為本次設計值(docs 太守給的 lv50/str40/cor30
// 偏成品線﹐此處取與冷梅/封山同階的偏低驗證線﹐並以註解保留 docs 原值)﹐供
// 日後平衡微調﹕
//   key    level  bawang blade  attr 門檻              其它           授內功         授武功(基礎技能)
//   ────── ─────  ────────────  ────────────────────  ─────────────  ────────────  ──────────────────────────────
//   護衛   20     60            str >= 18             ─              (沿用虎刀心法) 猛虎護身刀 (blade)
//   鬼才   25     80            str >= 20, cor >= 20  (docs:5000殺業) (沿用虎刀心法) 瘋虎刀法 (blade)
//   太守   30     100           str >= 22, cor >= 20  男性(gender)   (沿用虎刀心法) 重擊術 + 強力格擋技巧 (blade/parry)
//
// 註(鬼才 5000 殺業)：docs 載鬼才「轉職條件最嚴苛 — 5000 殺業」。殺業屬聲望/
//   業力計分系統(score of kills)﹐其達標查驗理想上由業力系統提供﹔為與本批進階
//   一致(只 gate level/skill/attr)﹐此處先以更高的 blade 火候 + 雙屬性門檻替代﹐
//   並標記 5000 殺業為待接的業力門檻(同冷梅虎督「拜入天邪」、封山素衣衛「結盟」
//   等故事門檻之 TODO)。
// 註(太守 docs 原值)：docs 太守為 lv50 / str40 / cor30 / 男性。本驗證線取
//   lv30 / str22 / cor20 / 男性(與封山劍客、冷梅虎督同階)﹐待平衡時可逐步上修
//   回 docs 成品值。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(虎刀諸進階皆以 blade 刀法為主)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)﹔"male" 為 docs 明定的性別門檻。
mapping query_advance_branches()
{
	return ([
		"護衛" : ([
			"rank"    : "虎刀護衛",
			"title"   : "虎刀護衛",
			"level"   : 20,
			"bawang blade" : 60,
			"attr"    : "str",
			"attr_min": 18,
			"base"    : "blade",
			"force"   : 0,    // 護衛不另授內功﹐沿用入門虎刀心法
			"skills"  : ({ ({ "猛虎護身刀", "guardtiger blade" }) }),
			"desc"    : "護衛攻守兼備、續戰持久﹐是虎刀門最早開放的二轉﹐有定技、第一"
			            "追與 powerup 狀態下的 deathwish﹐宜久戰纏鬥。",
		]),
		"鬼才" : ([
			"rank"    : "虎刀鬼才",
			"title"   : "虎刀鬼才",
			"level"   : 25,
			"bawang blade" : 80,
			"attr"    : "str",
			"attr_min": 20,
			"attr2"   : "cor",
			"attr2_min": 20,
			"base"    : "blade",
			"force"   : 0,    // 鬼才不另授內功﹐沿用入門虎刀心法
			"skills"  : ({ ({ "瘋虎刀法", "tiger blade" }) }),
			"desc"    : "鬼才是江湖中最具爆發力的一脈﹐兩手持刀皆可施展瘋虎刀法﹐有"
			            "overpower 與第一追保證第二追、反手拔刀(無視防禦)﹐兩手最多可"
			            "打出十刀連擊。重在搶攻爆發﹐防禦極弱﹐須速戰速決。",
		]),
		"太守" : ([
			"rank"    : "虎刀太守",
			"title"   : "虎刀太守",
			"level"   : 30,
			"bawang blade" : 100,
			"attr"    : "str",
			"attr_min": 22,
			"attr2"   : "cor",
			"attr2_min": 20,
			"male"    : 1,    // docs 明定太守須為男性弟子
			"base"    : "blade",
			"force"   : 0,    // 太守不另授內功﹐沿用入門虎刀心法
			"skills"  : ({ ({ "重擊術", "powerblow" }), ({ "強力格擋技巧", "heavy_parry" }) }),
			"desc"    : "太守是最新開的二轉﹐多 sr 系列重擊絕學﹐重擊術依火候高低可直接"
			            "爆 hp﹐另有強力格擋技巧硬擋來襲。重擊術對應刀法(blade)﹐強力格"
			            "擋技巧可自行 map_skill 對應招架(parry)以強化減傷。",
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
		do_chat("高慎按刀喝道﹕我虎刀門進階只有「護衛」、「鬼才」、「太守」三路﹐"
		        "你說的是哪一門﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為虎刀門入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "虎刀門" ) {
		do_chat("高慎冷笑道﹕你又非我虎刀門弟子﹐進階之事從何談起﹖且先拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("高慎搖頭道﹕你既已選定「" + me->query("sect_branch") +
		        "」一路﹐刀道貴在專一﹐豈可朝三暮四﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("高慎瞥了你一眼﹐搖頭道﹕你火候尚淺﹐且再歷練些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門刀法(霸王刀招 bawang blade)火候門檻。
	if( me->query_skill("bawang blade", 1) < b["bawang blade"] ) {
		do_chat("高慎喝道﹕你連我霸王刀招的根基都未練透﹐如何學得這上乘刀法﹖"
		        "且回演武場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（各分支重不同根骨﹐部分分支另有第二道屬性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("高慎按刀打量了你半晌﹐搖頭道﹕你的筋骨膽氣還撐不起這一路刀法﹐"
		        "勉強習之徒傷己身。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("高慎搖頭道﹕你的根骨膽魄仍有所偏廢﹐撐不起這一路刀法﹐"
		        "且去再磨練磨練。\n");
		return notify_fail("");
	}

	// docs 明定之性別門檻（如太守須為男性）。
	if( b["male"] && me->query("gender") != "male" ) {
		do_chat("高慎搖頭道﹕太守一脈的功夫剛猛霸烈、傷身耗元﹐自古只傳男子﹐"
		        "你這身子骨承受不住﹐另擇一路罷。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔虎刀諸進階皆沿用入門虎刀心法﹐故多為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階武功﹐並把主招式對應到該分支的基礎技能（多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換﹐如太守的重擊術/強力格擋技巧）。
	// 不重置既有基礎技能等級(保留弟子累積的刀法/招架火候)﹔僅當該基礎技能
	// 尚未習得時補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "blade";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 傳藝氣象。
	message_vision(
		"$N橫刀於膝﹐閉目凝神片刻﹐而後一聲虎吼﹐將一身「" + branch +
		"」的上乘刀法傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"高慎放聲大笑﹕好﹗從今日起﹐你便是我虎刀門的「" + b["rank"] + "」了。\n",
		"高慎喝道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
