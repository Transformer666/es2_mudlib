// master.c -- 封山派掌門 柳東蘆

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

void create()
{
	set_name("柳東蘆", ({ "fonxan master", "master", "sword sage" }));
	set("nickname", "青嶂劍翁");
	set_attr("str", 24);
	set_attr("dex", 25);
	set_attr("int", 22);
	set_attr("wis", 24);
	set_attr("spi", 23);
	set_attr("cps", 24);
	set_attr("con", 23);
	set_attr("cor", 24);
	set_race("human");
	set_level(40);
	set_class("fighter");
	set("sect", "封山派");
	set("rank", "掌門");

	set_skill("unarmed", 80);
	set_skill("sword", 150);
	set_skill("parry", 120);
	set_skill("dodge", 110);
	set_skill("force", 120);
	set_skill("fonxansword", 150);
	set_skill("fonxanforce", 120);
	map_skill("sword", "fonxansword");
	map_skill("force", "fonxanforce");

	advance_stat("gin", 220);
	advance_stat("kee", 220);
	advance_stat("sen", 220);

	set("age", 54);
	set("long",
		"這位便是封山派掌門柳東蘆﹐一襲洗得發白的青布長衫﹐身形清\n"
		"癯而挺拔﹐腰間懸著一柄不起眼的長劍﹐然舉手投足之間自有一股淵\n"
		"渟嶽峙的氣度。封山派是喬陰城東青嶂峰上聲名素著的劍派﹐掌門自\n"
		"幼苦修封山劍法﹐劍勢如山嶽巍然﹐守若磐石﹐攻似奔雷﹐講究以靜\n"
		"制動、以正禦邪﹐江湖人尊稱一聲「青嶂劍翁」。他平日深居山中﹐\n"
		"潛心劍道﹐唯有心性端方、根骨堪造的後輩﹐方有機會拜入門下﹐習\n"
		"得這一身守正不阿的劍法。\n");
	// 結仇標記：殺封山派 NPC 會在玩家身上累積 vendetta/fonxan﹐其後封山派
	// NPC 一見此玩家便主動圍攻（機制見 chard.c 累積、attack.c init() 觸發）。
	set("vendetta_mark", "fonxan");
	setup();
	carry_object("/d/snow/npc/obj/silversword")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("柳東蘆搖了搖頭﹐說道﹕你既已入別派﹐何苦再來攪擾﹖\n");
		return 0;
	}

	// 須年滿一定等級﹐心性沉穩方可習劍
	if( me->query_level() < 1 ) {
		do_chat("柳東蘆說道﹕你根基未穩﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 封山劍法守正剛猛﹐膽魄不足者持劍不穩﹐難承這一脈的劍意
	if( me->query_attr("cor") < 14 ) {
		do_chat("柳東蘆端詳了你一會﹐說道﹕你心性怯懦﹐握不住這一柄守山的劍。\n");
		return 0;
	}

	do_chat(({
		"柳東蘆上下打量了你一番﹐微微頷首。\n",
		"柳東蘆說道﹕我封山派的劍法﹐講究一個「守」字﹐守山、守正、守心﹐你可受得了這份清苦﹖\n",
		"柳東蘆說道﹕也罷﹐我便收你做個記名弟子﹐傳你封山劍法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("柳東蘆揮了揮手﹐說道﹕你既已另投他師﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("fighter");
		me->set("sect", "封山派");
		me->set("rank", "劍客");
		me->set("title", "封山派劍客");

		me->set_skill("sword", 0);
		me->set_skill("fonxansword", 0);
		me->map_skill("sword", "fonxansword");

		// 同時授予封山派內功﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("fonxanforce", 0);
		me->map_skill("force", "fonxanforce");

		message_vision(
			"$N取過一柄長劍﹐將封山劍法的入門劍訣一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"柳東蘆說道﹕從今日起﹐你便是我封山派的劍客了。\n",
			"柳東蘆說道﹕劍道如山﹐你且到演武場勤加練習﹐守得住劍﹐方守得住心。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的封山派弟子
// 轉入三大進階分支之一。比照冷梅莊主 d/hanmei/npc/master.c 的授技模型(門檻
// 更高、以 sect_branch 標記分支、升階 rank/title)﹐使通用「進階」指令可不改
// 動地驅動本門。
//
// 三大分支(見 docs/03-門派與武功/01-武者-五大門派.md §1 封山派)：
//   劍靈    ── 內功 劍靈心法 jianling_force + 武功 凰翔三疊劍 jianling-sword
//              舊版封山強化(九天鳳翔那版)﹐無視防禦三連擊、以劍招提升攻勢/
//              守勢/護甲。最早開放﹐門檻最低。
//   山人    ── 內功 山人心法 shanren_force + 拳法 封山伏虎拳 shanren-fist
//              ES2 唯二使用拳法的武者門派之一﹐可定人/打擊精氣、穿移動力裝、
//              極靈活。捨劍習拳﹐故主招式對應基礎技能 unarmed(非 sword)。
//   劍客    ── 劍法 神芒劍 shenmang-sword + 心氣劍 xinqi-sword(不另授內功﹐
//              沿用入門封山派內功)。神芒、心氣四劍系 4 選 2 切換﹐神芒系強攻
//              (上弦月定人/搗亂七星步精傷)、心氣系守勢續戰(上弦月帶下弦月)。
//              門檻最高。
//
// 轉職門檻(條件)為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   key      level  fonxansword  attr 門檻        授內功         授武功(基礎技能)
//   ──────── ─────  ───────────  ─────────────  ────────────  ───────────────────────────
//   劍靈     20     60           cor >= 18      劍靈心法       凰翔三疊劍 (sword)
//   山人     25     80           dex >= 20      山人心法       封山伏虎拳 (unarmed)
//   劍客     30     100          dex >= 22      (不另授內功)   神芒劍 + 心氣劍 (sword)
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(預設 sword﹔山人捨劍習拳故為 unarmed)。
mapping query_advance_branches()
{
	return ([
		"劍靈" : ([
			"rank"    : "封山劍靈",
			"title"   : "封山劍靈",
			"level"   : 20,
			"fonxansword" : 60,
			"attr"    : "cor",
			"attr_min": 18,
			"base"    : "sword",
			"force"   : ({ "劍靈心法", "jianling_force" }),
			"skills"  : ({ ({ "凰翔三疊劍", "jianling-sword" }) }),
			"desc"    : "劍靈承九天鳳翔一脈﹐無視防禦三連擊﹐以劍招提升攻勢、守勢、護甲﹐"
			            "可彌補不足的根骨。",
		]),
		"山人" : ([
			"rank"    : "封山山人",
			"title"   : "封山山人",
			"level"   : 25,
			"fonxansword" : 80,
			"attr"    : "dex",
			"attr_min": 20,
			"base"    : "unarmed",     // 山人捨劍習拳﹐主招式對應 unarmed
			"force"   : ({ "山人心法", "shanren_force" }),
			"skills"  : ({ ({ "封山伏虎拳", "shanren-fist" }) }),
			"desc"    : "山人捨劍習拳﹐是本派唯二的拳法一脈﹐可定人、打擊精氣﹐身法極"
			            "靈活﹐宜穿移動力裝。自此你的拳腳(unarmed)便是殺敵的本錢。",
		]),
		"劍客" : ([
			"rank"    : "封山劍客",
			"title"   : "封山劍客",
			"level"   : 30,
			"fonxansword" : 100,
			"attr"    : "dex",
			"attr_min": 22,
			"base"    : "sword",
			"force"   : 0,    // 劍客不另授內功﹐沿用入門封山派內功
			"skills"  : ({ ({ "神芒劍", "shenmang-sword" }), ({ "心氣劍", "xinqi-sword" }) }),
			"desc"    : "劍客一脈神芒、心氣兩系並傳﹐神芒強攻、心氣綿守﹐你可自行"
			            "map_skill 在二者間切換。神芒系上弦月定人、搗亂七星步傷精﹔"
			            "心氣系上弦月帶下弦月﹐長於續戰削敵。",
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
		do_chat("柳東蘆撫須道﹕本派進階只有「劍靈」、「山人」、「劍客」三路﹐"
		        "你說的是哪一門﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為封山派入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "封山派" ) {
		do_chat("柳東蘆搖頭道﹕你又非我封山派弟子﹐進階之事從何談起﹖且先拜入本門再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("柳東蘆道﹕你既已選定「" + me->query("sect_branch") +
		        "」一路﹐劍道貴在守一﹐豈可見異思遷﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("柳東蘆端詳了你一會﹐搖頭道﹕你火候尚淺﹐且再歷練些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門劍法(封山劍法 fonxansword)火候門檻。
	if( me->query_skill("fonxansword", 1) < b["fonxansword"] ) {
		do_chat("柳東蘆道﹕你連我封山劍法的根基都未練透﹐如何學得這上乘武功﹖"
		        "且回演武場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（各分支重不同根骨）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("柳東蘆搖頭道﹕你的根骨還撐不起這一路功夫﹐勉強習之徒傷己身。\n");
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

	// 授高階武功﹐並把主招式對應到該分支的基礎技能（多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換﹐如劍客的神芒/心氣 4 選 2）。
	// 不重置既有基礎技能等級(保留弟子累積的兵刃/拳腳火候)﹔僅當該基礎技能
	// 尚未習得時(如山人改練 unarmed﹐入門時未授)補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "sword";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 傳藝氣象。
	message_vision(
		"$N橫劍於膝﹐閉目凝神片刻﹐而後將一身「" + branch +
		"」的上乘功夫傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"柳東蘆朗聲道﹕好﹗從今日起﹐你便是我封山派的「" + b["rank"] + "」了。\n",
		"柳東蘆道﹕" + b["desc"] + "\n",
	}));
	return 1;
}

// ─────────────────────────────────────────────────────────────────────────
// 全服唯一掉落：柳東蘆(封山掌門)伏誅後，其畢生佩劍自屍身遺落——全服任何時刻至多一柄。
//   走 LOOT_D("/daemon/misc/loot.c")->unique_drop(藍本, 屍體)：盤點世界現存該神兵 clone
//   數，已有任一柄(含其他屍體/房間/玩家身上者)則不再掉(回 0)，故同一件神兵全服唯一。
//   下手者須為真實玩家(userp)。結構鏡 d/langwo/npc/wolfking.c::die()：先 ::die()(屍體於此
//   生成並登錄 temp("corpse"))，再於屍體內置入掉落物(唯一掉落須在屍體生成「後」入屍)。
//   docs/02-遊戲系統與機制/05-裝備與強化.md L151：柳東蘆→玄蘇劍。**第二位以後**的殺者
//   (神兵已被先前殺者取走、全服唯一) 改得對應的普通劍「青嶂劍」(非 unique)，使每次擊殺
//   仍有像樣兵刃可得、不致空手。神兵起手即頂 enchant_cap、不破壞強化平衡，契合劍派掌門。
//   (玄霜劍 xuanshuang_sword 屬天靈山獸王摩雲一系，故柳東蘆另立其 docs 本名玄蘇劍，互不衝突。)
//   (LOOT_D 巨集需 globals.h，npc.h 未含，故逕用字面路徑——等義 call_other。)
// ─────────────────────────────────────────────────────────────────────────
#define FONXAN_UNIQUE_LOOT  "/obj/topgear/xuansu_sword"            // 神兵 玄蘇劍(全服唯一)
#define FONXAN_NORMAL_LOOT  "/d/fonxan/npc/obj/qingzhang_sword"    // 普通 青嶂劍(神兵已現世時替代)

void die();
private void drop_signature(object who);

// 簽名掉落：下手者須為真實玩家；於 ::die() 之後呼叫，corpse 已生成於 temp("corpse")。
//   先試掉全服唯一神兵「玄蘇劍」(LOOT_D->unique_drop)；世界已有一柄則回 0，改掉普通的
//   「青嶂劍」(new)，使第二位以後的殺者仍得一柄對應的封山劍、不致空手。
private void drop_signature(object who)
{
	object corpse, loot;

	if( !objectp(who) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) ) return;

	// 全服唯一神兵：LOOT_D 盤點世界現存玄蘇劍 clone 數，無則 new 一柄入屍、回該物件。
	loot = "/daemon/misc/loot.c"->unique_drop(FONXAN_UNIQUE_LOOT, corpse);
	if( objectp(loot) ) {
		message_vision(HIY
			"柳東蘆頹然倒地之際﹐腰間那柄不起眼的長劍「噹」地脫鞘墜地——劍身青鋼幽碧、"
			"氣勢沉沉如負山嶽﹐赫然便是封山一脈代代相承、唯掌門一人佩之的鎮派神兵"
			"「玄蘇劍」﹗\n" NOR);
		return;
	}

	// 神兵已現世於他處(全服唯一) → 改掉落普通的青嶂劍(非 unique)，使本次擊殺仍有兵刃可得。
	loot = new(FONXAN_NORMAL_LOOT);
	if( !objectp(loot) ) return;
	if( !loot->move(corpse) ) loot->move(environment());

	message_vision(HIR
		"柳東蘆頹然倒地﹐腰間佩劍「噹」地墜落——是一柄封山派門人慣用的青嶂劍。\n" NOR);
}

// 死亡：先 ::die()(屍體/bounty/善後悉依 std/char/npc.c::die()﹐恒呼不可略﹐屍體於此生成
//   並登錄 temp("corpse"))﹐再於下手者為真實玩家時﹐自屍身遺落全服唯一的神兵。
void die()
{
	object killer;

	killer = last_damage_giver();

	::die();

	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_signature(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
