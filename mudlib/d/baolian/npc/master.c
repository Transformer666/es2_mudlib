// master.c -- 寶蓮寺方丈 善想上人
//
// 寶蓮寺是善想禪宗三大寺院之一﹐與白象寺同屬和尚(bonze)一脈﹐故本檔
// 結構完全比照 d/baixiang/npc/master.c﹐沿用既有的 bonze class﹐只是
// 兵器/招式由金剛伏魔杖法(staff/rid-evil)改為慈顏除障手(unarmed/
// buddha_zarn)、內功由蓮華心法(lotus force)改為寶蓮心法(baolian force)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("善想上人", ({ "baolian master", "master", "monk", "shanxiang" }));
	set("nickname", "寶蓮方丈");
	set_attr("str", 22);
	set_attr("dex", 24);
	set_attr("int", 26);
	set_attr("wis", 26);
	set_attr("spi", 26);
	set_attr("cps", 24);
	set_attr("con", 24);
	set_attr("cor", 22);
	set_race("human");
	set_level(40);
	set_class("bonze");
	set("sect", "寶蓮寺");
	set("rank", "方丈");
	set("title", "寶蓮寺方丈");

	set_skill("unarmed", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("force", 120);
	set_skill("buddha_zarn", 150);
	set_skill("buddhism", 120);
	map_skill("unarmed", "buddha_zarn");
	map_skill("force", "buddhism");

	advance_stat("gin", 200);
	advance_stat("kee", 200);
	advance_stat("sen", 260);

	set("age", 65);
	set("gender", "male");
	set("long",
		"這位便是寶蓮寺的方丈善想上人﹐一身漿洗得發白的灰色袈裟﹐\n"
		"身形清瞿﹐鬚眉如雪﹐面容慈和恬淡﹐一雙眼眸澄澈如水﹐顧盼之\n"
		"間流露出一股悲天憫人的祥和之氣。他垂手而立﹐神態淵默﹐周身\n"
		"卻隱隱有股深不可測的內力韻致﹐似已將一身武功盡數收斂於慈眉\n"
		"善目之中。寶蓮寺善想一脈以慈悲心濟世度人﹐上人浸淫慈顏除障\n"
		"手與寶蓮心法數十年﹐功參造化而不滯於物﹐人稱「寶蓮方丈」。\n"
		"他平日在大雄寶殿中誦經說法﹐唯有心存善念、根器不俗的後輩﹐\n"
		"方有機會拜入門下﹐習得這一身以慈化障的佛門掌法。\n");
	setup();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("善想上人雙手合十﹐宣了聲佛號﹕施主既已入別派﹐緣分已定﹐何苦再來﹖\n");
		return 0;
	}

	// 須先在江湖上歷練過方可入門
	if( me->query_level() < 1 ) {
		do_chat("善想上人微笑道﹕施主塵緣未了﹐且去歷練一番再來罷。\n");
		return 0;
	}

	// 慈顏除障手須以慧根參悟佛理（門檻甚低﹐尋常人皆可入）。
	// 註﹕int 為悟性﹐wis 為慧根。
	if( me->query_attr("wis") < 14 ) {
		do_chat("善想上人端詳了你一會﹐搖頭道﹕施主慧根閉塞﹐難參我這路佛法。\n");
		return 0;
	}

	if( me->query_attr("int") < 14 ) {
		do_chat("善想上人微微搖頭﹕施主悟性未開﹐這慈顏除障手的精微之處﹐只怕一時難以領會。\n");
		return 0;
	}

	do_chat(({
		"善想上人上下打量了你一番﹐微微頷首。\n",
		"善想上人道﹕我寶蓮寺善想一脈﹐以慈悲度世﹐施主可有這份向善之心﹖\n",
		"善想上人宣了聲佛號﹕善哉善哉﹐你既與我佛有緣﹐老衲便收你入門下﹐傳你慈顏除障手。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("善想上人雙手合十﹐道﹕施主既已另投他派﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("bonze");
		me->set("sect", "寶蓮寺");
		me->set("rank", "善想弟子");
		me->set("title", "寶蓮寺僧人");

		me->set_skill("unarmed", 0);
		me->set_skill("buddha_zarn", 0);
		me->map_skill("unarmed", "buddha_zarn");

		// 同時授予寶蓮心法（內功）﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("baolian force", 0);
		me->map_skill("force", "baolian force");

		message_vision(
			"$N合什誦了聲佛號﹐將慈顏除障手的入門掌訣一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"善想上人宣了聲佛號﹕從今日起﹐你便是我寶蓮寺善想門下的弟子了。\n",
			"善想上人道﹕武學乃濟世之具﹐你且到演武場勤加錘鍊﹐莫失了這份慈悲本心。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)  ── 和尚(bonze)「治療輔助」一脈的進階驗證
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的寶蓮寺善想弟子
// 轉入三大進階分支之一。比照同為和尚(bonze)的白象寺方丈 d/baixiang/npc/master.c
// 與道士天師掌教 d/tianshi/npc/master.c(非武者、授 magic 法術)的授技模型(門檻更
// 高、以 sect_branch 標記分支、升階 rank/title)。
//
// 與白象寺(武僧/羅漢一脈﹐授杖法/刀法)的關鍵差異(寺院定位)：
//   * docs 明定寶蓮寺定位為「治療輔助」(三大寺院定位表)﹐其核心技能皆為「法術
//     (magic)」——善想禪法 kindness magic、大悲咒 almsdeed magic、長生禪法
//     longevity magic(見 docs §寶蓮寺-核心技能)。故本門進階各分支的 "base" 一律
//     為 "magic"(法術)而非 staff/blade﹐授技後 map_skill("magic", <禪法/咒>)﹐
//     比照天師派把 magic 改映到更上乘咒術 daemon 的模型(惟入門時寶蓮弟子只授
//     unarmed→buddha_zarn / force→baolian force﹐未授 magic﹐故 base 'magic'
//     於進階時若尚未習得﹐do_advance 補初始 0﹐與白象降魔尊者改習 blade 同理)。
//   * 入門火候門檻以入門掌法 慈顏除障手 "buddha_zarn" 計(對應白象的 rid-evil、
//     道士的 taoism-fire)。
//   * 屬性主門檻為 "wis"(慧根/禪定﹐拜師即以 wis/int 為門檻)﹐高階分支另設第二道
//     "spi"(靈性﹐法術施法根本)門檻。
//
// 三大分支(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md §寶蓮寺-核心技能﹐三式
//   皆 docs 明列之寶蓮 magic 法術﹐由淺入深)：
//   善想禪師  ── 法術 善想禪法 kindness magic(docs 明列)。寶蓮入階禪法﹐沿用入門
//                寶蓮心法(baolian force)﹐不另授內功。最早開放、門檻最低、重慧根。
//   大悲行者  ── 內功 大悲心經 almsdeed force(設計:承 docs「善想禪要 almsdeed」一脈)
//                + 法術 大悲咒 almsdeed magic(docs 明列﹐寶蓮天月共通看家咒)+ 身法
//                達摩移身法 damo steps(docs 佛門共通身法﹐沿用白象/天月既有 daemon)。
//                門檻居中、另設靈性門檻。
//   長生上人  ── 內功 長生心法 longevity force(設計:承 docs「link/link2 長生」一脈)
//                + 法術 長生禪法 longevity magic(docs 明列﹐寶蓮成為團隊核心的關鍵
//                link 群補絕學)。寶蓮治療最高一階。門檻最高、另設更高靈性門檻。
//
// 轉職門檻(條件)為本次設計值(docs 只給寶蓮「治療輔助」定位與技能名﹐未給確切轉職
//   數字)﹐供日後平衡微調(與白象寺、天師派同階)﹕
//   key        level  buddha_zarn  attr 門檻              授內功         授法術(base=magic) + 副技
//   ────────── ─────  ───────────  ────────────────────  ────────────  ────────────────────────────────
//   善想禪師   20     60           wis >= 18             (沿用寶蓮心法) 善想禪法 kindness magic
//   大悲行者   25     80           wis >= 20, spi >= 18  大悲心經       大悲咒 almsdeed magic +達摩移身法
//   長生上人   30     100          wis >= 22, spi >= 20  長生心法       長生禪法 longevity magic
//
// 註(治療特殊功能 TODO)：docs 明載寶蓮主力為「link/link2 長生維持隊友、ena;#tick
//   自動群補、sarira 佛舍利、受 almsdeed 50% 影響」等治療/群補/增益機制﹐屬 heal/
//   perform/group/link 系統(非招式/咒文表)﹔為與本批進階一致(只 gate level/skill/
//   attr)﹐三式法術 daemon 先以攻擊咒(cast/auto-attack)交付戰鬥能力﹐link 群補/狀態
//   維持等核心治療功能標記為待接的系統門檻 TODO(同白象「18 銅人任務」、天師「青邪
//   戰勳 3000」)。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主咒/禪法對應的基礎技能(寶蓮諸進階皆以 magic 法術為主)。
// "extra" 為另授的副技﹕({ ({中文,英文,基礎技能}), ... })﹐授技後 map_skill(基礎,英文)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"善想禪師" : ([
			"rank"    : "善想禪師",
			"title"   : "寶蓮寺善想禪師",
			"level"   : 20,
			"buddha_zarn" : 60,
			"attr"    : "wis",
			"attr_min": 18,
			"base"    : "magic",
			"force"   : 0,    // 善想禪師沿用入門寶蓮心法(baolian force)﹐不另授內功
			"skills"  : ({ ({ "善想禪法", "kindness magic" }) }),
			"desc"    : "善想禪法乃寶蓮入階佛法﹐以慈悲心化作禪定法力﹐金剛梵音可"
			            "震懾邪魔、亦藏濟世度人之機。你可 enable spells with 善想禪法 "
			            "後 cast 慈心/金剛梵音/善想度世﹐或 map_skill 對應法術出手。",
		]),
		"大悲行者" : ([
			"rank"    : "大悲行者",
			"title"   : "寶蓮寺大悲行者",
			"level"   : 25,
			"buddha_zarn" : 80,
			"attr"    : "wis",
			"attr_min": 20,
			"attr2"   : "spi",
			"attr2_min": 18,
			"base"    : "magic",
			"force"   : ({ "大悲心經", "almsdeed force" }),
			"skills"  : ({ ({ "大悲咒", "almsdeed magic" }) }),
			"extra"   : ({
				({ "達摩移身法", "damo steps", "dodge" }),
			}),
			"desc"    : "大悲咒乃寶蓮、天月兩寺共通的善想禪要﹐以大悲願力濟世度人、降伏"
			            "邪魔﹐輔以大悲心經培養願力、達摩移身法移形換步。你可 enable "
			            "spells with 大悲咒 後 cast 大悲/大悲千手/大悲願海。",
		]),
		"長生上人" : ([
			"rank"    : "長生上人",
			"title"   : "寶蓮寺長生上人",
			"level"   : 30,
			"buddha_zarn" : 100,
			"attr"    : "wis",
			"attr_min": 22,
			"attr2"   : "spi",
			"attr2_min": 20,
			"base"    : "magic",
			"force"   : ({ "長生心法", "longevity force" }),
			"skills"  : ({ ({ "長生禪法", "longevity magic" }) }),
			"desc"    : "長生禪法乃寶蓮治療最高絕學﹐以無量壽佛之願力續命延壽、維持同袍"
			            "(link/link2 長生)﹐是隊中不可或缺的長生核心。輔以長生心法培元固"
			            "本。你可 enable spells with 長生禪法 後 cast 長生/無量壽佛/長生願海。",
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
		do_chat("善想上人雙手合十﹐宣了聲佛號﹕本寺進階只有「善想禪師」、「大悲行者」、"
		        "「長生上人」三路佛法﹐施主欲修哪一門﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為寶蓮寺入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "寶蓮寺" ) {
		do_chat("善想上人搖頭道﹕施主又非我寶蓮寺門下﹐進階之事從何談起﹖且先拜入本寺再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("善想上人宣了聲佛號﹕施主既已選定「" + me->query("sect_branch") +
		        "」一脈﹐佛法貴在精專﹐豈可見異思遷﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("善想上人端詳了你一會﹐搖頭道﹕施主火候尚淺﹐且再潛修些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門掌法(慈顏除障手 buddha_zarn)火候門檻。
	if( me->query_skill("buddha_zarn", 1) < b["buddha_zarn"] ) {
		do_chat("善想上人道﹕施主連我慈顏除障手的根基都未練透﹐如何參得這上乘佛法﹖"
		        "且回演武場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（寶蓮以慧根禪定為本﹐高階分支另設靈性門檻以承法術）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("善想上人搖頭道﹕施主的慧根還參不透這一路佛法﹐勉強習之徒亂心神。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("善想上人宣了聲佛號﹕施主靈性未足﹐尚引動不了這上乘禪法的願力﹐"
		        "且去再參修參修。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔善想禪師沿用入門寶蓮心法﹐故為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授上乘法術﹐並把主禪法對應到該分支的基礎技能（base=magic﹔多咒者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換）。
	// 不重置既有基礎技能等級(保留弟子累積的法術火候)﹔僅當該基礎技能尚未習得時
	// (入門時寶蓮弟子未授 magic)補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "magic";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 授副技（身法等﹐各自掛回其基礎技能﹔如達摩移身法→dodge）。
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
		"」的上乘佛門禪法傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"善想上人宣了聲佛號﹕善哉﹗從今日起﹐你便是我寶蓮寺的「" + b["rank"] + "」了。\n",
		"善想上人道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
