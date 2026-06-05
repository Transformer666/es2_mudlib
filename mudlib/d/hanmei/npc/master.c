// master.c -- 冷梅莊主 梅影風

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("梅影風", ({ "may yin fong", "lunmay master", "master", "lunmay" }));
	set("nickname", "傲梅劍客");
	set_attr("str", 24);
	set_attr("dex", 26);
	set_attr("int", 22);
	set_attr("wis", 23);
	set_attr("spi", 22);
	set_attr("cps", 24);
	set_attr("con", 22);
	set_attr("cor", 24);
	set_race("human");
	set_level(40);
	set_class("fighter");
	set("sect", "冷梅莊");
	set("rank", "莊主");

	set_skill("unarmed", 80);
	set_skill("sword", 150);
	set_skill("parry", 120);
	set_skill("dodge", 110);
	set_skill("force", 120);
	set_skill("lunmay", 150);
	set_skill("hainmay force", 120);
	map_skill("sword", "lunmay");
	map_skill("force", "hainmay force");

	advance_stat("gin", 220);
	advance_stat("kee", 220);
	advance_stat("sen", 220);

	set("age", 48);
	set("long",
		"這位便是冷梅莊主梅影風﹐一身月白長袍﹐腰懸長劍﹐眉宇間透著一\n"
		"股清冷孤傲之氣。冷梅莊是雪亭鎮一帶聲名卓著的劍派﹐他自幼苦練家\n"
		"傳的冷梅劍法﹐劍勢如寒梅綻放﹐冷冽中暗藏凌厲殺機﹐江湖人稱「傲\n"
		"梅劍客」。他平日深居莊中﹐潛心劍道﹐唯有資質清正的年輕人才有機\n"
		"會拜入他的門下﹐習得這一身傲視群雄的劍法。\n");
	setup();
	carry_object("/d/snow/npc/obj/silversword")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("梅影風搖了搖頭﹐說道﹕你既已入別派﹐何苦再來攪擾﹖\n");
		return 0;
	}

	// 須年滿一定等級﹐心性沉穩方可習劍
	if( me->query_level() < 1 ) {
		do_chat("梅影風說道﹕你根基未穩﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 冷梅劍法講究靈動﹐機敏不足者難窺堂奧
	if( me->query_attr("dex") < 18 ) {
		do_chat("梅影風端詳了你一會﹐說道﹕你筋骨太過遲鈍﹐學不得我這路劍法。\n");
		return 0;
	}

	do_chat(({
		"梅影風上下打量了你一番﹐微微頷首。\n",
		"梅影風說道﹕我冷梅莊的劍法﹐講究一個「傲」字﹐你可受得了這份清苦﹖\n",
		"梅影風說道﹕也罷﹐我便收你做個記名弟子﹐傳你冷梅劍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("梅影風揮了揮手﹐說道﹕你既已另投他師﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("fighter");
		me->set("sect", "冷梅莊");
		me->set("rank", "劍士");
		me->set("title", "冷梅莊劍士");

		me->set_skill("sword", 0);
		me->set_skill("lunmay", 0);
		me->map_skill("sword", "lunmay");

		// 同時授予寒梅心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("hainmay force", 0);
		me->map_skill("force", "hainmay force");

		message_vision(
			"$N取過一柄長劍﹐將冷梅劍法的入門劍訣緩緩傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"梅影風說道﹕從今日起﹐你便是我冷梅莊的劍士了。\n",
			"梅影風說道﹕劍道無窮﹐你且到演武場勤加練習﹐莫負了這身劍法。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的冷梅莊弟子
// 轉入三大進階分支之一。比照 init_apprentice 的授技模型﹐但門檻更高、且以
// sect_branch 標記分支、升階 rank/title(避免與入門 rank="劍士" 撞名)。
//
// 三大分支(見 docs/03-門派與武功/01-武者-五大門派.md §2 冷梅莊)：
//   劍士        ── 內功 明鏡止水 mingjing + 武功 傲梅暗劍訣 aomei-sword
//                  攻防一體、爆發力強、精耗極大。最早開放﹐門檻最低。
//   古劍門傳人  ── 武功 傲劍絕 aojian-jue(右) + 傲梅劍 aomei-jian(左)
//                  打不死的蟑螂、parry 回 kee、不能補 hp。門檻居中。
//   虎督        ── 內功 天邪神功 tianxie-force(沿用既有) + 武功 寒霜三千
//                  hanshuang + 天邪虎嘯 tianxie-roar。超高 kee、控場(定人)。
//                  最新開、拜入天邪﹐門檻最高。
//
// 轉職門檻(條件)為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   key            level  lunmay  attr 門檻        授內功         授武功
//   ────────────── ─────  ──────  ─────────────  ────────────  ─────────────────────
//   劍士           20     60      dex >= 18      明鏡止水       傲梅暗劍訣
//   古劍門傳人     25     80      con >= 20      (不另授內功)   傲劍絕 + 傲梅劍
//   虎督           30     100     str >= 22      天邪神功       寒霜三千 + 天邪虎嘯
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
mapping query_advance_branches()
{
	return ([
		"劍士" : ([
			"rank"    : "冷梅劍士",
			"title"   : "冷梅劍士",
			"level"   : 20,
			"lunmay"  : 60,
			"attr"    : "dex",
			"attr_min": 18,
			"force"   : ({ "明鏡止水", "mingjing" }),
			"swords"  : ({ ({ "傲梅暗劍訣", "aomei-sword" }) }),
			"desc"    : "傲梅暗劍訣攻防一體﹐爆發力極強﹐然精力消耗甚鉅﹐切記留意精力。",
		]),
		"古劍門傳人" : ([
			"rank"    : "古劍傳人",
			"title"   : "古劍傳人",
			"level"   : 25,
			"lunmay"  : 80,
			"attr"    : "con",
			"attr_min": 20,
			"force"   : 0,    // 古劍門不另授內功﹐沿用入門寒梅心法
			"swords"  : ({ ({ "傲劍絕", "aojian-jue" }), ({ "傲梅劍", "aomei-jian" }) }),
			"desc"    : "古劍一脈劍招華麗、守勢綿密﹐是打不死的蟑螂﹐重在續戰纏鬥。",
		]),
		"虎督" : ([
			"rank"    : "冷梅虎督",
			"title"   : "冷梅虎督",
			"level"   : 30,
			"lunmay"  : 100,
			"attr"    : "str",
			"attr_min": 22,
			"force"   : ({ "天邪神功", "tianxie-force" }),
			"swords"  : ({ ({ "寒霜三千", "hanshuang" }), ({ "天邪虎嘯", "tianxie-roar" }) }),
			"desc"    : "虎督拜入天邪﹐有天邪神功輔助﹐超高內力﹐長於控場(定人)與持久續戰。"
			            "寒霜三千與天邪虎嘯只能交替施展﹐善用之。",
		]),
	]);
}

int do_advance(object me, string branch)
{
	mapping branches, b;
	int i;

	if( is_chatting() ) return 0;
	if( !objectp(me) ) return 0;

	branches = query_advance_branches();

	// 分支名無效（含未指定）。
	if( !branch || undefinedp(branches[branch]) ) {
		do_chat("梅影風搖頭道﹕本莊進階只有「劍士」、「古劍門傳人」、「虎督」三路﹐"
		        "你說的是哪一門﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為冷梅莊入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "冷梅莊" ) {
		do_chat("梅影風冷冷道﹕你又非我冷梅莊弟子﹐進階之事從何談起﹖且先拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("梅影風道﹕你既已選定「" + me->query("sect_branch") +
		        "」一路﹐劍道貴在專一﹐豈可朝三暮四﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("梅影風端詳了你一會﹐搖頭道﹕你火候尚淺﹐且再歷練些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門劍法(冷梅劍法 lunmay)火候門檻。
	if( me->query_skill("lunmay", 1) < b["lunmay"] ) {
		do_chat("梅影風道﹕你連我冷梅劍法的根基都未練透﹐如何學得這上乘劍訣﹖"
		        "且回演武場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（各分支重不同根骨）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("梅影風搖頭道﹕你的根骨還撐不起這一路劍法﹐勉強習之徒傷己身。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階武功﹐並把 sword 對應到該分支的主招式（多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	for( i = 0; i < sizeof(b["swords"]); i++ )
		me->set_skill(b["swords"][i][1], 0);
	me->map_skill("sword", b["swords"][0][1]);

	// 傳藝氣象。
	message_vision(
		"$N橫劍於膝﹐閉目凝神片刻﹐而後將一身「" + branch +
		"」的上乘劍訣傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"梅影風朗聲道﹕好﹗從今日起﹐你便是我冷梅莊的「" + b["rank"] + "」了。\n",
		"梅影風道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
