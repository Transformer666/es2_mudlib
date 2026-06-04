// instructor.c -- 雪吟莊教頭 屠九 (Tu jiu)
//
// 設定（依 docs/03-門派與武功/01-武者-五大門派.md §4 雪吟莊）：
//   雪吟莊莊主魚鐵山(yu_tieshan.c)是主線反派﹐城府極深、不收徒。莊主底下
//   另設一名「教頭」屠九﹐專司操演莊丁、為莊主廣納門人——浪人一脈即由他
//   傳授。雪吟莊本門武功並無獨到﹐然源自外邦天邪國的天邪神功(tianxie-force)
//   強悍﹔浪人強化「數字刀」(deepblade)﹐攻勢凌厲﹐是新手推薦的入門武者門派。
//   適合種族﹕夜叉、阿修羅、焦僥、刑天、人類。
//
//   * 拜師 NPC（浪人入門）﹕accept_apprentice 僅要求 commoner + level>=1﹐
//     保持新手可入﹔對膽識另有一句帶氣勢的話﹐但不硬性擋人。
//   * init_apprentice 授予 fighter / 雪吟莊 / 浪人 / 數字刀 / 天邪神功。
//   * 切勿與莊主魚鐵山混淆——魚鐵山不收徒﹐拜師一律找這位教頭屠九。
//
// 本 NPC 比照封山派掌門 d/fonxan/npc/master.c 撰寫（fighter 拜師樣板）﹐
// 基礎兵器由 sword 改為 blade（雪吟莊慣用單刀﹐見 retainer.c / yu_tieshan.c﹐
// 皆 wield /obj/area/obj/blade）﹐簽名武學改為數字刀(deepblade)＋天邪神功
// (tianxie-force)。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("屠九", ({ "tu jiu", "tu", "instructor", "manor instructor" }));
	set("nickname", "雪吟莊教頭");
	set_attr("str", 26);
	set_attr("dex", 23);
	set_attr("int", 20);
	set_attr("wis", 20);
	set_attr("spi", 22);
	set_attr("cps", 22);
	set_attr("con", 24);
	set_attr("cor", 23);
	set_race("human");
	set_level(33);
	set_class("fighter");
	set("sect", "雪吟莊");
	set("rank", "教頭");

	set_skill("unarmed", 90);
	set_skill("blade", 140);
	set_skill("parry", 110);
	set_skill("dodge", 100);
	set_skill("force", 120);
	set_skill("deepblade", 140);
	set_skill("tianxie-force", 120);
	map_skill("blade", "deepblade");
	map_skill("force", "tianxie-force");

	advance_stat("gin", 200);
	advance_stat("kee", 210);
	advance_stat("sen", 200);

	set("gender", "male");
	set("age", 46);
	set("long",
		"這位是雪吟莊的教頭屠九﹐一身藏青勁裝緊束在精悍的身板上﹐臂膀\n"
		"虯結﹐太陽穴高高鼓起﹐一望便知是個外家功夫練到了家的狠角色。他\n"
		"按著一柄寒光隱隱的單刀﹐神情冷峻﹐目光如刀﹐在你身上一掃便似已\n"
		"將你的斤兩掂量了個透。雪吟莊本門武功並無甚獨到﹐然莊主魚鐵山自\n"
		"外邦天邪國得來的天邪神功端的雄渾詭譎﹐這位教頭便奉莊主之命﹐日\n"
		"日在演武場督練莊丁、廣納浪人﹐將那一脈剛猛綿密的數字刀傳授下去。\n"
		"他治下極嚴﹐出手狠辣﹐莊中無人不畏他三分。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"屠九按著腰間單刀﹐冷冷地將你上下打量了一番。\n",
		"屠九沉聲道﹕想學雪吟莊的數字刀﹖先掂量掂量自己的膽子。\n",
		"屠九淡淡道﹕莊主的天邪神功﹐豈是人人練得起的。\n",
	}));
	setup();
	carry_object("/obj/area/obj/blade")->wield();
}

int accept_apprentice(object me)
{
	if( is_chatting() ) return 0;

	// 已有師門者不收
	if( me->query_class() != "commoner" ) {
		do_chat("屠九搖了搖頭﹐說道﹕你既已入別派﹐還來雪吟莊作甚﹖\n");
		return 0;
	}

	// 新手門派﹐只須略具根基便收——保持可入(newbie entry)。
	if( me->query_level() < 1 ) {
		do_chat("屠九瞥了你一眼﹐說道﹕乳臭未乾﹐且去歷練歷練再來。\n");
		return 0;
	}

	// 數字刀剛猛﹐膽小者使來不夠狠——只作一句激將﹐不硬性擋人(新手可入)。
	if( me->query_attr("cor") < 12 )
		do_chat("屠九哼了一聲﹕你這膽子﹐使起刀來怕是要自己先軟了手——也罷﹐進來罷。\n");

	do_chat(({
		"屠九上下打量了你一番﹐微微頷首。\n",
		"屠九沉聲道﹕雪吟莊收的是浪人﹐使的是數字刀﹐練的是天邪神功﹐你可吃得了這份苦﹖\n",
		"屠九說道﹕也罷﹐我便收你做個浪人﹐傳你莊上的刀法。\n",
	}));
	return 1;
}

int init_apprentice(object me)
{
	if( me->query_class() != "commoner" ) {
		do_chat("屠九揮了揮手﹐說道﹕你既已另投他師﹐去吧。\n");
		return 1;
	}

	if( ::init_apprentice(me) ) {
		seteuid(getuid());
		me->set_class("fighter");
		me->set("sect", "雪吟莊");
		me->set("rank", "浪人");
		me->set("title", "雪吟莊浪人");

		me->set_skill("blade", 0);
		me->set_skill("deepblade", 0);
		me->map_skill("blade", "deepblade");

		// 同時授予雪吟莊源自天邪國的內功﹐使弟子戰鬥時力道能隨內功成長。
		me->set_skill("force", 0);
		me->set_skill("tianxie-force", 0);
		me->map_skill("force", "tianxie-force");

		message_vision(
			"$N取過一柄單刀﹐將數字刀的入門刀訣一招一式地傳授給$n。\n",
			this_object(), me);
		do_chat(({
			"屠九沉聲道﹕從今日起﹐你便是我雪吟莊的浪人了。\n",
			"屠九說道﹕到演武場去勤練數字刀﹐運起天邪神功﹐莫墮了莊主的威名。\n",
		}));
	}
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(二轉)：do_advance(me, branch)
//
// 由 cmds/std/進階.c(及 english alias advance.c)呼叫﹐讓已入門的雪吟莊弟子
// 轉入三大進階分支之一。比照武者諸門(冷梅 d/hanmei、封山 d/fonxan、虎刀
// d/hudao)與白象寺(d/baixiang)的授技模型(門檻更高、以 sect_branch 標記分支、
// 升階 rank/title)﹐使通用「進階」指令可不改動地驅動本門。雪吟莊入門即授
// 數字刀(blade->deepblade)＋天邪神功(force->tianxie-force)﹐故進階以入門刀法
// 火候(deepblade)為門檻﹐天邪神功沿用不另授(各分支 force 多為 0)。
//
// 三大分支(見 docs/03-門派與武功/01-武者-五大門派.md §4 雪吟莊﹔三進階為
//   浪人、棄徒、天邪派弟子(神掌))：
//   浪人        ── 刀法 浪人刀法 langren-blade(強化數字刀﹐攻勢可破千)。沿用
//                  入門天邪神功。docs 評分 攻擊 A-/防禦 C+/續戰 C+/靈活 B﹐中
//                  規中矩﹐是最早開放、門檻最低的二轉(入門 rank 即「浪人」﹐
//                  進階後升為「雪吟莊浪人」﹐同虎刀門護衛之例)。
//   棄徒        ── 刀法 棄徒反擊刀 qitu-blade(靠反擊吃飯)。沿用入門天邪神功
//                  (docs 載「天邪神功 190+ 占決定性因素」)。docs 評分 攻擊 B+/
//                  防禦 B/續戰 A/靈活 B﹐重在卸力反擊、續戰纏鬥。門檻居中。
//   天邪派弟子  ── 掌法 天邪神掌 tianxie-palm(神掌不需武器﹐基礎技能改 unarmed)
//                  ＋牽制群攻 天邪虎嘯 tianxie-roar(既有 daemon﹐一併授予)。另
//                  授內功仍為天邪神功(沿用)。docs 評分 攻擊 B/防禦 C+/續戰 B+/
//                  靈活 B+﹐高規格血牛、群攻補血定人。最高一階﹐門檻最高。
//
// 轉職門檻(條件)為本次設計值(docs 只給評分非確切數字)﹐供日後平衡微調﹕
//   key          level  deepblade  attr 門檻              授內功         授武功(base)
//   ──────────── ─────  ─────────  ────────────────────  ────────────  ──────────────────────────
//   浪人         20     60         str >= 18             (沿用天邪神功) 浪人刀法 (blade)
//   棄徒         25     80         con >= 20             (沿用天邪神功) 棄徒反擊刀 (blade)
//   天邪派弟子   30     100        str >= 22, spi >= 20  (沿用天邪神功) 天邪神掌 (unarmed)
//                                                                       +天邪虎嘯
//
// 設計(docs未明定):分支名「天邪派弟子(神掌)」取 docs §4 標題﹐sect_branch 鍵
//   作「天邪派弟子」。神掌「陰陽眼/全體攻擊/補血/定人/無視防禦/血牛」屬 combat/
//   perform 系統(非招式表)﹐為待接的功能門檻 TODO(同封山素衣衛、冷梅虎督等故事/
//   系統門檻)﹔本驗證線僅 gate level/skill/attr。棄徒 docs「天邪神功 190+ 占
//   決定性因素」屬內功火候﹐沿用入門天邪神功﹐日後可上修為硬門檻。
// ─────────────────────────────────────────────────────────────────────────

// 分支設定表﹕branch -> 條件與授技。集中於此便於日後平衡微調。
// "base" 為主招式對應的基礎技能(浪人/棄徒為 blade 刀法﹔神掌捨刀習掌故為 unarmed)。
// "skills" 多招式者只 map 第一門(其餘已 set_skill﹐玩家可自行 map_skill 切換)。
// "attr2"/"attr2_min" 為第二道屬性門檻(無則省略)。
mapping query_advance_branches()
{
	return ([
		"浪人" : ([
			"rank"    : "雪吟莊浪人",
			"title"   : "雪吟莊浪人",
			"level"   : 20,
			"deepblade" : 60,
			"attr"    : "str",
			"attr_min": 18,
			"base"    : "blade",
			"force"   : 0,    // 浪人不另授內功﹐沿用入門天邪神功
			"skills"  : ({ ({ "浪人刀法", "langren-blade" }) }),
			"desc"    : "浪人一脈強化數字刀﹐攻勢凌厲、可破千﹐三不五時更有無視防禦"
			            "的必殺招﹐配合天邪神功力道愈發雄渾。中規中矩﹐是本莊最早"
			            "開放的二轉。",
		]),
		"棄徒" : ([
			"rank"    : "雪吟莊棄徒",
			"title"   : "雪吟莊棄徒",
			"level"   : 25,
			"deepblade" : 80,
			"attr"    : "con",
			"attr_min": 20,
			"base"    : "blade",
			"force"   : 0,    // 棄徒不另授內功﹐沿用入門天邪神功(190+ 占決定性因素)
			"skills"  : ({ ({ "棄徒反擊刀", "qitu-blade" }) }),
			"desc"    : "棄徒一脈靠反擊吃飯﹐卸力後發、借勢反撩﹐看的是移動力而非護甲﹐"
			            "不能補 hp 卻極耐久戰。天邪神功火候(190+)是這一路的命脈﹐切記"
			            "勤修內功。",
		]),
		"天邪派弟子" : ([
			"rank"    : "天邪派弟子",
			"title"   : "雪吟莊天邪派弟子",
			"level"   : 30,
			"deepblade" : 100,
			"attr"    : "str",
			"attr_min": 22,
			"attr2"   : "spi",
			"attr2_min": 20,
			"base"    : "unarmed",     // 神掌不需武器﹐主招式對應 unarmed
			"force"   : 0,    // 仍以天邪神功為本﹐沿用入門﹐不另授
			"skills"  : ({
				({ "天邪神掌", "tianxie-palm" }),    // 主招式﹐map_skill("unarmed",...)
				({ "天邪虎嘯", "tianxie-roar" }),    // 牽制群攻﹐一併授予(僅 set_skill)
			}),
			"desc"    : "天邪派弟子是本莊最高規格的二轉﹐神掌不需兵刃﹐以天邪神掌掌挾"
			            "煞風殺敵﹐另習天邪虎嘯牽制群攻、補血定人﹐血量超高如血牛。自此"
			            "你的掌法(unarmed)便是殺敵的本錢。",
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
		do_chat("屠九按刀沉聲道﹕我雪吟莊進階只有「浪人」、「棄徒」、「天邪派弟子」三路﹐"
		        "你說的是哪一門﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為雪吟莊入門弟子方可進階（非本派/平民一律不收）。
	if( me->query("sect") != "雪吟莊" ) {
		do_chat("屠九冷笑道﹕你又非我雪吟莊弟子﹐進階之事從何談起﹖且先拜入本莊再說。\n");
		return notify_fail("");
	}

	// 已轉過階者不得再轉。
	if( stringp(me->query("sect_branch")) ) {
		do_chat("屠九搖頭道﹕你既已選定「" + me->query("sect_branch") +
		        "」一路﹐刀道貴在專一﹐豈可朝三暮四﹖\n");
		return notify_fail("");
	}

	// 等級門檻。
	if( me->query_level() < b["level"] ) {
		do_chat("屠九瞥了你一眼﹐搖頭道﹕你火候尚淺﹐且再歷練些時日﹐"
		        "待修為到了再來罷。\n");
		return notify_fail("");
	}

	// 入門刀法(數字刀 deepblade)火候門檻。
	if( me->query_skill("deepblade", 1) < b["deepblade"] ) {
		do_chat("屠九喝道﹕你連我雪吟莊數字刀的根基都未練透﹐如何學得這上乘武功﹖"
		        "且回演武場勤練去。\n");
		return notify_fail("");
	}

	// 屬性門檻（各分支重不同根骨﹐部分分支另有第二道屬性門檻）。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("屠九按刀打量了你半晌﹐搖頭道﹕你的根骨還撐不起這一路功夫﹐"
		        "勉強習之徒傷己身。\n");
		return notify_fail("");
	}
	if( !undefinedp(b["attr2"]) && me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("屠九搖頭道﹕你的根骨心性仍有所偏廢﹐撐不起這一路天邪神掌﹐"
		        "且去再磨練磨練。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐正式傳藝 ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授內功心法（若該分支另有內功﹔雪吟莊諸進階皆沿用入門天邪神功﹐故多為 0）。
	if( arrayp(b["force"]) ) {
		me->set_skill("force", 0);
		me->set_skill(b["force"][1], 0);
		me->map_skill("force", b["force"][1]);
	}

	// 授高階武功﹐並把主招式對應到該分支的基礎技能（base﹔多招式者對應第一門﹐
	// 其餘已 set_skill﹐玩家可自行 map_skill 切換﹐如神掌另授的天邪虎嘯）。
	// 不重置既有基礎技能等級(保留弟子累積的刀法/拳腳火候)﹔僅當該基礎技能尚未
	// 習得時(如神掌改習 unarmed)補初始 0﹐以免映射落空。
	base = stringp(b["base"]) ? b["base"] : "blade";
	if( undefinedp(me->query_skill(base, 1)) )
		me->set_skill(base, 0);
	for( i = 0; i < sizeof(b["skills"]); i++ )
		me->set_skill(b["skills"][i][1], 0);
	me->map_skill(base, b["skills"][0][1]);

	// 傳藝氣象。
	message_vision(
		"$N橫刀於膝﹐閉目凝神片刻﹐而後一聲冷哼﹐將一身「" + branch +
		"」的上乘功夫傾囊傳授給$n。\n", this_object(), me);
	do_chat(({
		"屠九沉聲道﹕好﹗從今日起﹐你便是我雪吟莊的「" + b["rank"] + "」了。\n",
		"屠九說道﹕" + b["desc"] + "\n",
	}));
	return 1;
}
// vim: set ts=4 sw=4 syntax=lpc
