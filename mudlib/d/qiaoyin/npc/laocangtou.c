// laocangtou.c -- 桐城老蒼頭：桐城派最後一位執事的老僕，桐城派支線之「終點」
//                 交付人。枯守於喬陰聚仙酒樓，懷藏掌門信物「桐城玉牌」，
//                 待有心人循信使密信尋來。
//
// 【canon】docs 01-世界觀與劇情/05-主線任務與NPC.md L102
//   「桐城派信使 (Mail man) @ 喬陰縣城大街 → 桐城派任務起點，
//    可解到武林至寶『真正的桐城派信物』」。
//   信使(d/qiaoyin/npc/mailman.c)為「起點」，本檔為「終點」交付人。
//
// 【桐城派支線 全鏈（旗標皆存玩家身上）】
//   quest/tongcheng_start  : 信使給密信時開（起點）。
//   quest/sq_tongchengxinshi : 信使「給密信」防重旗標。
//   quest/tongcheng_step1  : 書商(d/qiaoyin/npc/bookseller.c)驗火漆舊印、指引玩家
//                            往聚仙酒樓尋桐城老蒼頭時設 1（中繼線索一步）。
//   quest/tongcheng_done   : 本檔交付「真正的桐城派信物」(桐城玉牌)時設 1（終點）。
//
// 【本檔職責】桐城這條線的「終點」交付人：
//   - 驗信物：須玩家身上持有桐城密信(tongcheng letter)、且 step1>=1。
//   - 發終獎：桐城玉牌(d/qiaoyin/npc/obj/tongcheng_relic) ＝「真正的桐城派信物」。
//   - 開旗標：quest/tongcheng_done = 1（防重領）。
//   - 收回密信：交付玉牌時把桐城密信消耗掉（差使已了、密信功成身退）。
//
// 【ask-path 為主，繞過中文 give 障礙】（runtime 鐵則 #6：driver give 只認英文 id）
//   推進全程 `ask laocangtou about 桐城`（或 玉牌/信物/密信/桐城派 …），持密信時
//   ask 即可驗信+交獎，無須中文「給」。另留 accept_object(收 tongcheng letter)為替代
//   交付路徑，亦同步發獎、不吞物。
//
// 【同步交付】（本專案頭號 bug class 之防範）：發玉牌、設旗標、消耗密信一律在
//   do_ask / accept_object handler 內直接 new()+move()/destruct() 做、且在設完成
//   旗標之前——絕不放進延遲的 do_chat/closure（玩家中途離場會「物沒了、旗標卻記
//   完成」soft-lock）。do_chat 只擺氣氛對白。
//
// 【runtime 鐵則】本 NPC 有 do_ask / init，**不** replace_program（#11）。
//   do_ask 入口以 is_fighting()/is_chatting() 守衛；旗標/給物/消耗寫在 do_chat 之前（#10）。
//   init() 招呼有 interactive(this_player()) 護衛（#14），只對真人招呼。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIY "桐城老蒼頭" NOR,
		({ "laocangtou", "lao cangtou", "old retainer", "桐城老蒼頭", "老蒼頭", "蒼頭" }) );
	set("nickname", HIY "桐城老蒼頭" NOR);
	set_race("human");
	set_class("commoner");
	set_level(10);
	set_attr("con", 20);
	set_attr("dex", 16);
	set_skill("unarmed", 20);
	set_skill("dodge", 22);
	set_skill("literate", 20);

	set("gender", "male");
	set("age", 63);
	set("long",
		"一個獨坐在酒樓角落的老蒼頭﹐穿一身漿洗得發白的灰布長衫﹐\n"
		"花白的頭髮在腦後挽成一個鬆鬆的髻﹐臉上的皺紋裡盛著掩不住的\n"
		"落寞。他面前擺著一壺濁酒、一碟茴香豆﹐卻多半時候只是怔怔地\n"
		"望著杯中酒影出神。聽鄰座的人說﹐這老兒原是桐城派最後一位執\n"
		"事的老僕﹐桐城零落之後便流落到了喬陰﹐枯守在這聚仙酒樓裡﹐\n"
		"一守便是許多年。他渾濁的眼裡偶爾掠過一絲執拗的微光﹐像是還\n"
		"在等著甚麼人、守著甚麼放不下的舊物。\n"
		"你或許可以問問他﹕ask laocangtou about 桐城。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"桐城老蒼頭呷了一口濁酒﹐長長嘆了口氣﹕桐城一派數百年的香火﹐如今竟只剩老朽一個守著了。\n",
		"桐城老蒼頭望著杯中的酒影出神﹐喃喃道﹕老主人臨終託付的那樁事﹐老朽這把年紀﹐怕是等不到了……\n",
		"桐城老蒼頭摩挲著腰間一個鼓鼓的舊布囊﹐神色慎重﹐似是那裡頭藏著甚麼要緊的東西。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		object me = this_player();
		// 持密信、過了書商那一關、又未領終獎者，招呼點題往本檔交付。
		if( me->query("quest/tongcheng_step1")
		&&  !me->query("quest/tongcheng_done")
		&&  present("tongcheng letter", me) )
			do_chat((: command,
				"say 這位客官且坐——老朽瞧你像是循著桐城的舊事尋來的？可帶著桐城派信使那封密信麼？(ask laocangtou about 桐城)" :));
	}
}

// 同步交付終獎：直接 new()+move() 把桐城玉牌交給玩家。先試 move 到玩家身上，
// 不成（負重等）則落在環境地上——絕不靜默丟失。並消耗掉那封桐城密信。
private void give_relic(object who)
{
	object relic, letter;

	if( !who || environment(who) != environment() ) return;

	// 差使已了：消耗那封功成身退的桐城密信（若還在玩家身上）。
	letter = present("tongcheng letter", who);
	if( letter ) destruct(letter);

	relic = new(__DIR__"obj/tongcheng_relic");
	if( !relic->move(who) ) relic->move(environment());

	message_vision(
		"桐城老蒼頭顫巍巍地解開腰間那個鼓鼓的舊布囊﹐自囊底鄭重地捧出一枚青瑩的玉牌﹐"
		"雙手奉著﹐慎重地交到$N手中。\n",
		who);

	who->gain_score("emprise", 200);
	who->gain_score("reputation", 80);
	who->gain_score("explorer fame", 60);
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg || (arg != "laocangtou about 桐城"
		&&   arg != "laocangtou about 桐城派"
		&&   arg != "laocangtou about 信物"
		&&   arg != "laocangtou about 玉牌"
		&&   arg != "laocangtou about 密信"
		&&   arg != "laocangtou about 信使"
		&&   arg != "laocangtou about 至寶"
		&&   arg != "laocangtou about tongcheng"
		&&   arg != "laocangtou about relic"
		&&   arg != "laocangtou about letter"
		&&   arg != "lao cangtou about 桐城"
		&&   arg != "old retainer about 桐城") )
		return notify_fail("你想問這位老蒼頭甚麼？（試試 ask laocangtou about 桐城）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("桐城老蒼頭正怔怔地對著杯中酒影出神，沒理會你。\n");

	// 已領過終獎：純劇情對白，不重發（防重領）。
	if( me->query("quest/tongcheng_done") >= 1 ) {
		do_chat(({
			(: command, "say 客官便是當年替桐城跑完這趟長路、領了那枚玉牌的有心人罷？老朽這把老骨頭，總算把老主人臨終的託付交代清楚了。" :),
			(: command, "say 那玉牌客官須得好生收著——它承的不是甚麼傷人的利器，是桐城一派數百年守正持中的念想。佩著它，便當記著：桐城的道，從不在爭強鬥狠。去罷，老朽在這酒樓裡，敬客官一杯。" :),
		}));
		return 1;
	}

	// 尚未經書商驗印那一步（step1 未開）：點撥玩家先尋書商。
	if( !me->query("quest/tongcheng_step1") ) {
		// 連密信都沒有：八竿子打不著，純氣氛。
		if( !present("tongcheng letter", me) ) {
			do_chat((: command,
				"say 桐城？嘿，那是樁早沒人提起的舊事了……客官若當真有心，城西書局那位老書商見多識廣，去問問他，許能指條明路。" :));
			return 1;
		}
		// 持密信但還沒給書商看過：指引去書局驗那枚火漆舊印。
		do_chat(({
			(: command, "say 哦？客官手裡這封火漆密緘的書信……老朽眼花，瞧不真切那印鑑。客官且先到城西喬陰書局走一趟，那位老書商最識得這些舊年的印鑑款識。(ask bookseller about 火漆)" :),
			(: command, "say 待書商替客官認準了那印鑑、指明了門路，客官再回老朽這兒來——老朽自有話對客官說。" :),
		}));
		return 1;
	}

	// step1 已開、卻把密信弄丟了：點撥回信使補領，不在此處發獎。
	if( !present("tongcheng letter", me) ) {
		do_chat((: command,
			"say 客官手裡那封桐城密信怎不見了？無憑無據，老朽怎敢把這等要緊的舊物託付出去？快回大街上尋那桐城派信使，討一封密信補上，再來尋老朽。" :));
		return 1;
	}

	// 通關條件齊備：持密信 + step1 已開 + 未領終獎。
	// 同步交付終獎、即記旗標（give_relic 為直接 new+move，玩家此刻必在場）。
	// 先發物、後記旗標——免於回呼前離場致玉牌沒領、旗標卻記完成而卡關（鐵則 #10）。
	do_chat(({
		(: command, "say 是了……是這封信，是信使那老腳力的密緘，錯不了。客官循著這封信、一路訪到老朽這兒來，足見是真有心為桐城奔走的人了。" :),
		(: command, "say 不瞞客官，老朽原是桐城派最後一位執事的老僕。桐城零落那年，老主人把這門中世代相傳、執掌門戶的掌門信物——桐城玉牌——託付給了老朽，要老朽守著它，待一個肯為桐城舊事奔走的有心人尋來，便將它交付出去。老朽枯守在這酒樓裡，這一守，便守了許多年了。" :),
	}));
	give_relic(me);
	me->set("quest/tongcheng_done", 1);
	do_chat(({
		(: command, "say 客官﹐這便是世人傳說的『真正的桐城派信物』了。它承的不是甚麼神兵利器，是桐城一派數百年守正持中、不爭強鬥狠的念想。望客官佩著它，記著桐城的道。" :),
		(: command, "say 老朽這樁差使了了，這把老骨頭，總算對得起九泉下的老主人了。客官那封密信，老朽便收下作個念想罷——去罷，桐城的香火，往後便看客官的造化了。" :),
	}));
	return 1;
}

// 收物路徑（中文 give 障礙之替代）：玩家把桐城密信 give 過來時，同步驗信、發獎、設旗標。
int accept_object(object who, object ob)
{
	if( !ob->id("tongcheng letter") ) {
		do_chat((: command,
			"say 老朽一個守著舊物的糟老頭子，受不起客官這個，還是自個兒留著罷。" :));
		return 0;
	}

	// 還沒經書商驗印那一步：不收信、不發獎，指引玩家先尋書商。
	if( !who->query("quest/tongcheng_step1") ) {
		do_chat((: command,
			"say 客官且慢——老朽眼花，認不得這印鑑。煩請客官先到城西喬陰書局，請那位老書商替你認認這枚火漆舊印，再回來尋老朽。(ask bookseller about 火漆)" :));
		return 0;	// 退還密信，不吞物
	}

	// 已領過終獎：婉拒收信、不重發（防重領），把密信退還玩家。
	if( who->query("quest/tongcheng_done") >= 1 ) {
		do_chat((: command,
			"say 玉牌老朽早交付給客官了，這密信客官留作個念想罷，老朽不收。" :));
		return 0;
	}

	// 通關條件齊備：同步發終獎、設旗標。give_relic 內會消耗這封密信（故此處回 0、不另由
	// driver 把信移入老蒼頭——避免重複；信已在 give_relic 裡 destruct）。
	do_chat((: command,
		"say 是這封信……錯不了。客官循信尋來，是真有心為桐城奔走的人了。老朽便把這守了多年的掌門信物，交付與客官。" :));
	give_relic(who);
	who->set("quest/tongcheng_done", 1);
	do_chat((: command,
		"say 這便是『真正的桐城派信物』桐城玉牌了。它承的是桐城數百年守正持中的念想，望客官佩著它，記著桐城的道。老朽這樁差使，總算了了。" :));
	return 0;	// 密信已在 give_relic 內 destruct，不勞 driver 再移；回 0 即可
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 客官息怒——老朽一把年紀的糟老頭子，手無縛雞之力，與客官無冤無仇，何苦動這刀兵？" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
