// zhangtian.c -- 小霸王 張天：茅山遺址(鳳盈盈墓地)的茅山劍士轉職入口 NPC
//
// 來歷(承 docs/01-世界觀與劇情/05-主線任務與NPC.md「小霸王 張天 / 鳳盈盈 @ 茅山
//   遺址 → 茅山劍士轉職入口」一列﹐及 docs/03-門派與武功/02-道士-天師與茅山.md
//   「茅山劍士」段)：
//   茅山遺址即鳳盈盈墓地。三百年前祖師林正英憑《幽冥三箭》與《茅山劍法》創派﹐
//   後總壇大火﹐藏書閣(藏茅山劍譜、茅山心經)被焚﹐暫任掌門的鳳盈盈內疚而死﹐葬
//   於此地。其墓前有三層茅山石陣﹐石壁間刻著殘存的茅山劍法、心經口訣。小霸王張
//   天是個遊蕩於遺址的江湖人(docs 轉職程序：找張天 → say 古董/戒指 → 二爺 → 10g
//   → 鳳盈盈 → 附近石壁 → 三層茅山石陣)﹐他熟知這石陣的門徑﹐肯為與茅山有淵源、
//   修為到家的後輩指點﹐使其於石壁石陣間悟成「茅山劍士」一脈。
//
// 轉職機制(比照本專案已驗證的「進階(二轉)」範式)：
//   * 比照 cmds/std/進階.c(及 english alias advance.c)＋各掌門 do_advance(me,branch)
//     /query_advance_branches() 模型。直接套冷梅莊主(d/hanmei/npc/master.c)的劍系
//     授技模型(set_skill sword/force + map_skill + set sect_branch/rank/title)﹐
//     惟所授為茅山劍法 mao-shan sword(劍)＋茅山心經 mao-shan force(內功)。
//   * 玩家於本室面對張天﹐輸入「進階 茅山劍士」(或 advance 茅山劍士)即觸發
//     do_advance(me,"茅山劍士")驗條件、授技。
//   * 對白(do_ask 的 古董/戒指/二爺/鳳盈盈/石陣 諸 alias)只擺 docs 劇情風味與指路
//     (引玩家用「進階 茅山劍士」)﹐不另設硬性 gate﹐授技一律走 do_advance 一處驗證。
//     (docs 程序原作 say 古董/戒指 觸發﹔本實作改以 ask...about 古董/戒指 等 alias
//      承接──不 hook 全域 say 動詞﹐免攔截玩家的標準 say 指令﹐照 gongsunzhi/laodao
//      已驗證的 ask-path 範式辦。)
//
// gate(轉職門檻﹐本次設計值﹐docs 載「三觀弟子 lv50 + 二級門派級能後可轉」)：
//   * 須為茅山派(sect=="茅山派")。
//   * 須已在三觀中轉過階(已有 sect_branch﹐即 docs「二級門派級能」)──未二轉者不收。
//   * level >= 50(docs 明載)。
//   * 入門咒術幽冥三箭 youmin 火候 >= 100(承三觀弟子之根基﹐比照三觀進階上限門檻)。
//   * 屬性主門檻 dex >= 22(劍士重靈動﹐比照冷梅虎督 str22 一階)﹐另設 spi >= 22
//     (茅山心經以靈力御劍﹐道緣未足者御不動)。
//
// rehash 註：本 NPC 不 replace_program(需保有 init 之 add_action 與 do_advance/
//   do_ask 諸鉤子)。授技走同步(do_advance 內直接 set_skill/map_skill/set 旗標)﹐
//   不丟進 do_chat 延遲 closure(遵本專案同步交付鐵則)。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);
mapping query_advance_branches();
int do_advance(object me, string branch);

void create()
{
	set_name(HIY "小霸王張天" NOR,
		({ "zhangtian", "zhang tian", "xiaobawang", "zhangda tian", "swordsman" }) );
	set("nickname", "小霸王");
	set_attr("str", 26);
	set_attr("dex", 28);
	set_attr("int", 22);
	set_attr("wis", 22);
	set_attr("spi", 24);
	set_attr("cps", 24);
	set_attr("con", 24);
	set_attr("cor", 24);
	set_race("human");
	set_level(45);
	set_class("fighter");
	set("sect", "茅山派");
	set("rank", "茅山劍士");
	set("title", "茅山劍士");
	set("sect_branch", "茅山劍士");

	set_skill("unarmed", 80);
	set_skill("sword", 150);
	set_skill("parry", 120);
	set_skill("dodge", 130);
	set_skill("force", 130);
	set_skill("mao-shan force", 150);
	set_skill("mao-shan sword", 150);
	map_skill("force", "mao-shan force");
	map_skill("sword", "mao-shan sword");

	advance_stat("gin", 220);
	advance_stat("kee", 220);
	advance_stat("sen", 240);

	set("age", 41);
	set("gender", "male");
	set("long",
		"這位江湖人自稱「小霸王」張天﹐一身洗得發白的勁裝﹐腰懸長劍\n"
		"﹐身形精悍﹐眉宇間透著一股桀驁不馴的江湖氣。他終日遊蕩在茅山\n"
		"遺址這片斷垣殘壁之間﹐對著鳳盈盈墓前那三層斑駁的茅山石陣指指\n"
		"點點﹐口中念念有詞。據說他早年偶然闖入石陣﹐在石壁的劍痕符文\n"
		"間悟得了失傳的茅山劍法﹐成了如今江湖上罕見的「茅山劍士」。他\n"
		"看似玩世不恭﹐卻獨敬重與茅山有淵源的後輩——若你是三觀出身、修\n"
		"為又到了家﹐不妨向他問問這石陣的門徑。\n"
		"(試試 ask zhangtian about 古董／戒指／石陣﹐或於他面前「進階 茅山劍士」)\n");
	set("chat_chance", 5);
	set("chat_msg", ({
		"小霸王張天負手立在石陣前﹐瞇眼端詳石壁上斑駁的劍痕﹐忽地伸指虛劃一式﹐又搖頭嘆息。\n",
		"小霸王張天拍了拍鳳盈盈的墓碑﹐自語道﹕鳳掌門﹐這茅山劍法的種子﹐總算沒在你手裡斷了根。\n",
		"小霸王張天抽出長劍﹐對著空無一人的石陣比劃了一式﹐劍尖竟隱隱浮起一層淡淡符光。\n",
		"小霸王張天斜睨著你﹐咧嘴一笑﹕怎麼﹖也想在這石陣裡碰碰運氣﹖先報報你的來歷罷。\n",
	}));
	setup();
	carry_object("/d/snow/npc/obj/silversword")->wield();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// ─────────────────────────────────────────────────────────────────────────
// 對白(風味 + 指路)：do_ask / do_say
//
// docs 轉職程序「找張天 → say 古董/戒指 → 二爺 → 10g → 鳳盈盈 → 附近石壁 →
// 三層茅山石陣」以對白風味重現﹐末了一律指向「進階 茅山劍士」這個唯一授技入口
// (授技與門檻驗證都在 do_advance 一處﹐對白不另發物、不另設硬 gate)。do_ask 以
// is_fighting()/is_chatting() 守衛(本專案鐵則)。
// ─────────────────────────────────────────────────────────────────────────

int do_ask(string arg)
{
	if( !arg ||
		(arg != "zhangtian about 古董"
		&& arg != "zhangtian about 戒指"
		&& arg != "zhangtian about 石陣"
		&& arg != "zhangtian about 石壁"
		&& arg != "zhangtian about 二爺"
		&& arg != "zhangtian about 鳳盈盈"
		&& arg != "zhangtian about 茅山劍士"
		&& arg != "zhangtian about 進階"
		&& arg != "zhangtian about 轉職"
		&& arg != "zhang tian about 古董"
		&& arg != "zhang tian about 戒指"
		&& arg != "xiaobawang about 古董"
		&& arg != "swordsman about 古董"
		&& arg != "zhangtian about ring"
		&& arg != "zhangtian about antique"
		&& arg != "zhangtian about maoshan swordsman") )
		return notify_fail("你想問小霸王張天甚麼﹖（試試 ask zhangtian about 古董／戒指／石陣）\n");

	return talk_zhangtian();
}

// docs 程序原作 say 古董/戒指 觸發﹐故 say 含關鍵字時亦走同一段對白指路。
int do_say(string arg)
{
	if( !arg ) return 0;

	if( strsrch(arg, "古董") >= 0 || strsrch(arg, "戒指") >= 0
	||  strsrch(arg, "石陣") >= 0 || strsrch(arg, "二爺") >= 0
	||  strsrch(arg, "鳳盈盈") >= 0 || strsrch(arg, "茅山劍士") >= 0 ) {
		// 先讓玩家那句 say 正常顯示(回 0 放行給 /cmds/std/say.c)﹐張天再答話。
		// 為使對白接在玩家發言之後﹐這裡直接觸發 talk﹐再回 0 讓 say 繼續走。
		talk_zhangtian();
		return 0;
	}
	return 0;
}

// ─────────────────────────────────────────────────────────────────────────
// 進階(轉職)：query_advance_branches() / do_advance(me, branch)
//
// 由 cmds/std/進階.c(及 alias advance.c)呼叫。比照冷梅莊主 d/hanmei/npc/master.c
// 的劍系 do_advance 結構(set sect_branch/rank/title + set_skill/map_skill 授劍法
// 與內功)﹐惟茅山劍士為「三觀弟子 lv50 + 已二轉」方可轉的側線分支﹐故 gate 另加
// 「須已有 sect_branch(已二轉)」一道。授技走同步﹐不入延遲 closure。
// ─────────────────────────────────────────────────────────────────────────

mapping query_advance_branches()
{
	return ([
		"茅山劍士" : ([
			"rank"     : "茅山劍士",
			"title"    : "茅山劍士",
			"level"    : 50,
			"youmin"   : 100,
			"attr"     : "dex",
			"attr_min" : 22,
			"attr2"    : "spi",
			"attr2_min": 22,
			"force"    : ({ "茅山心經", "mao-shan force" }),
			"swords"   : ({ ({ "茅山劍法", "mao-shan sword" }) }),
			"desc"     : "茅山劍法以符入劍、劍咒同流﹐茅山心經煉靈力為符文御劍﹐"
			             "是失傳於遺址石陣的一脈奇劍﹐攻防之間自有風火水雷之變。",
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
		do_chat("小霸王張天咧嘴一笑﹕這石陣裡頭﹐我能指點你的就只有「茅山劍士」一脈﹐"
		        "你說的是哪門子玩意兒﹖\n");
		return notify_fail("");
	}
	b = branches[branch];

	// 須為茅山派弟子(三觀出身)方可轉。
	if( me->query("sect") != "茅山派" ) {
		do_chat("小霸王張天斜睨著你﹐搖頭道﹕你又不是茅山三觀出身﹐這石陣認的是茅山的根﹐"
		        "輪不到你來碰運氣。\n");
		return notify_fail("");
	}

	// 須已在三觀中轉過階(已有 sect_branch﹐即 docs「二級門派級能」)。
	if( !stringp(me->query("sect_branch")) ) {
		do_chat("小霸王張天道﹕你連三觀的二轉都還沒成﹐根基浮淺﹐這三層石陣的劍意能把你"
		        "震個七葷八素﹐且回觀裡把本門道法練紮實了再來。\n");
		return notify_fail("");
	}

	// 已是茅山劍士者不必再轉。
	if( me->query("sect_branch") == branch ) {
		do_chat("小霸王張天哈哈一笑﹕你早已是茅山劍士了﹐還來這石陣前湊甚麼熱鬧﹖\n");
		return notify_fail("");
	}

	// 等級門檻(docs：lv50)。
	if( me->query_level() < b["level"] ) {
		do_chat("小霸王張天上下打量了你一番﹐搖頭道﹕你火候還差得遠﹐這石陣的劍意你接不住﹐"
		        "再去歷練個十年八載罷。\n");
		return notify_fail("");
	}

	// 入門咒術幽冥三箭 youmin 火候門檻(三觀弟子之根基)。
	if( me->query_skill("youmin", 1) < b["youmin"] ) {
		do_chat("小霸王張天道﹕你連幽冥三箭都沒練透﹐茅山的根都沒紮穩﹐這石壁劍痕你看一眼"
		        "便要走火﹐回去再練﹗\n");
		return notify_fail("");
	}

	// 屬性門檻：劍士重靈動(dex)﹐茅山心經以靈力御劍(spi)。
	if( me->query_attr(b["attr"]) < b["attr_min"] ) {
		do_chat("小霸王張天搖頭道﹕你身手太過遲滯﹐這以符入劍的劍法講究個快字﹐你使不來。\n");
		return notify_fail("");
	}
	if( me->query_attr(b["attr2"]) < b["attr2_min"] ) {
		do_chat("小霸王張天搖頭道﹕你靈性不足﹐茅山心經煉不出御劍的符文﹐勉強修之徒傷己身。\n");
		return notify_fail("");
	}

	// ── 門檻俱足﹐石陣傳劍(同步授技) ──
	seteuid(getuid());
	me->set("sect_branch", branch);
	me->set("rank", b["rank"]);
	me->set("title", b["title"]);

	// 授茅山心經(內功)。
	me->set_skill("force", 0);
	me->set_skill(b["force"][1], 0);
	me->map_skill("force", b["force"][1]);

	// 授茅山劍法(劍)﹐並把 sword 對應到茅山劍法。
	for( i = 0; i < sizeof(b["swords"]); i++ )
		me->set_skill(b["swords"][i][1], 0);
	me->map_skill("sword", b["swords"][0][1]);

	// 傳劍氣象。
	message_vision(
		"$N領著$n步入三層茅山石陣﹐指點$n細看石壁上斑駁的劍痕與符文。$n凝神參悟之間﹐"
		"周身忽地浮起一層淡淡符光——一脈失傳的「" + branch + "」劍法﹐就此入了$n的心。\n",
		this_object(), me);
	do_chat(({
		"小霸王張天朗聲笑道﹕好﹗石陣認你﹗從今日起﹐你便是這世上罕有的「茅山劍士」了﹗\n",
		"小霸王張天道﹕" + b["desc"] + "\n",
		(: command, "say 鳳掌門﹐又有一個茅山劍士成了——你在天有靈﹐也該瞑目了。" :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat("小霸王張天長劍一橫﹐冷笑道﹕在鳳掌門墓前動粗﹖你倒是有種——不過我勸你掂量掂量。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
