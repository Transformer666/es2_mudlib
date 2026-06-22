// stele.c -- 碧幽古墓石板：嵌於碧幽古墓石室正壁、刻滿失傳頂級丹方訣文的青石板。
//
// 來源(doc)：
//   docs/01-世界觀與劇情/04-地圖與場景.md L123「碧幽古墓石板｜抄寫煉丹配方」。
//   docs/02-遊戲系統與機制/06-煉丹與書本系統.md L83「其他配方需到碧幽古墓石板抄寫」、
//     L185「多層配方深度：基礎丹方 → 頂級丹方 → 古墓抄方」。
//
// === 機制定位（已讀既有 refine/煉丹系統原碼後的審慎決定） ===
//   經查 obj/alchemy/reactor.c、obj/alchemy/mixture.c、d/longtu/npc/jisheng.c
//   （藥鋪掌櫃）與 cmds/std/refine.c﹕現行煉丹「丹方知識」全部編碼在【藥鋪的
//   recipe_book() 表】裡——玩家 buy mixture for <丹方> 即可向藥鋪買到對應藥引﹐
//   【並無「玩家身上習得了哪些配方」的旗標/清單機制】﹐refine/結丹也不以任何
//   「已習得配方」為前置。亦即：目前【不存在】可供石板「真正授予一個頂級丹方」
//   的系統掛鉤(content-alchemy.md 亦載 v1 為單一固定配方、未掛完整 produce 系統)。
//
//   依建置任務指示：機制不明確時﹐把石板做成【可 look/read 抄寫的 lore 物件】﹐
//   抄寫後僅在玩家身上記一個 quest 旗標 quest/biyou_stele（呼應 docs「抄寫」之說）﹐
//   【實際授方留作 caveat 待後續】﹐不臆造任何煉丹數值/配方門檻/技能需求。
//   ⇒ 日後若於藥鋪/refine 補上「習得配方」機制(如以 query("quest/biyou_stele")
//      或 query("recipe/<丹名>") 解鎖某頂級丹方藥引)﹐本石板的旗標即為現成掛鉤。
//
// === 寫玩家 dbase 的 euid 安全（runtime-gotchas #15） ===
//   本物件路徑在 /d/biyou/obj/ 下——【Domain 物件﹐euid 本就在 USER_PROTECT 允許
//   名單內】(#15 明載「/d/(Domain) 下物件…quest NPC 設 flag 正常」)﹐故 me->set(
//   "quest/biyou_stele",…) 與一般 quest NPC 設旗標同理﹐不致撞 USER_PROTECT。
//   （對照 lesson #15 之金契是 /obj/ 物件方需 seteuid(MUDLIB_UID)﹔本物件非 /obj/。）
//
// === runtime 鐵則 ===
//   * 嵌於壁上的死物﹕set("no_get",…) 不可拾取(get.c:118 讀 no_get﹐回字串即擋)。
//   * 有自訂 init()/do_read﹐【不可 replace_program】(#11)——本為 ITEM﹐無此呼叫。
//   * 不涉 living die/destruct(#10)﹔非 NPC﹐不 include <weapon.h>。
//   * 前置宣告自訂函式(#12)。認物以英文 id 為準(#6)：read stele / look stele。

#include <ansi.h>

inherit ITEM;

// 前置宣告(lesson #12)。
int do_read(string arg);

void create()
{
	set_name(GRN "碧幽古墓石板" NOR,
		({ "biyou stele", "stele", "stone tablet", "tablet",
		   "石板", "古墓石板", "碧幽古墓石板" }) );
	// 巨石嵌壁﹐重逾萬鈞﹐取之不動。
	set_weight(50000000);

	if( !clonep() ) {
		set("unit", "方");
		set("value", 1);
		// 嵌於墓壁的死物﹐不可拾取（get.c 讀此字串即擋下並回此訊息）。
		set("no_get", "那石板足有丈許見方、嵌在墓壁之內﹐重逾萬鈞﹐莫說搬動﹐便是撼它一撼也不能夠。\n");
		// 死物不賣。
		set("no_sell", 1);
		set("long",
			"這便是傳說中的碧幽古墓石板了。一方丈許見方的青石板嚴絲合\n"
			"縫地嵌在石室的正壁之內﹐石面青黑斑駁﹐歷千百年而不朽。通\n"
			"體刻滿了密密麻麻、古奧難辨的篆文與配伍圖訣——一行行列鼎布\n"
			"爐的圖樣旁﹐密註著辰砂、雄黃、鉛汞的配伍分兩﹐間以文武火\n"
			"候的口訣﹐字裡行間隱隱透出一股辛烈的丹砂氣息。這顯是當年\n"
			"長眠於此的墓主——一位精擅爐火丹道的古之方士——畢生嘔心瀝\n"
			"血、刻石以傳的一身丹方絕學﹐傳說盡是當世早已失傳的頂級丹\n"
			"方。只是這訣文古奧繁奧﹐縱是方士﹐也須得凝神細細抄錄參詳﹐\n"
			"方能參透其中一二。\n"
			"可用 read 石板（或 read stele）試著抄寫其上的丹方訣文。\n");
		// 供日後煉丹系統辨識「這是碧幽古墓石板」用的 identity 旗標。
		set("stele", 1);
	}

	setup();
}

void init()
{
	// read / 抄寫 石板：抄錄石板丹方訣文。掛在石板上﹐玩家在石室即可用。
	add_action("do_read", "read");
	add_action("do_read", "抄寫");
}

// do_read -- read 石板 / 抄寫 石板：抄錄石板上的頂級丹方訣文。
//   * 須指認本石板(arg 比對 id)﹐否則放行給別的 read（如 read map）。
//   * 抄寫後在玩家身上記 quest/biyou_stele 旗標（lore 信物﹐呼應 docs「抄寫」）。
//   * 重複抄寫只給氣氛訊息、不重複「初次抄成」之敘事(旗標冪等)。
//   * 【caveat】本旗標目前【不】真正授予可煉的頂級丹方——現行 refine/藥鋪系統無
//     「習得配方」掛鉤(見檔首長註)。實際授方待後續煉丹系統補機制時再接此旗標。
int do_read(string arg)
{
	object me = this_player();

	if( !objectp(me) ) return 0;
	// 未指認本石板 -> 放行給別的 read（return 0﹐讓 read map 等照舊）。
	if( !arg || !id(arg) ) return 0;

	// 已抄寫過：純氣氛收尾，不重複初次敘事。
	if( me->query("quest/biyou_stele") ) {
		message_vision(
			"$N再次凝立石板之前﹐就著那盞幽碧的鬼火﹐逐字逐句地溫覆\n"
			"先前抄錄下的丹方訣文﹐石上古奧的篆文﹐已不似初見時那般\n"
			"難解了。\n", me);
		return 1;
	}

	// 初次抄寫：給 lore 敘事 + 記旗標。
	message_vision(HIG
		"$N整衣斂容﹐凝立於碧幽古墓石板之前﹐就著那盞忽明忽暗的幽\n"
		"碧鬼火﹐屏息凝神﹐逐字逐句地辨認、抄錄石上那一行行古奧的\n"
		"丹方訣文。列鼎布爐的圖樣、辰砂雄黃的配伍、文武火候的口訣\n"
		"……隨著筆下一字字落定﹐$N但覺一股辛烈的丹砂氣息直透心\n"
		"脾﹐胸中那煉丹的丘壑﹐竟似豁然開朗了幾分。\n" NOR, me);
	message_vision(
		"$N將這碧幽古墓石板上的頂級丹方訣文﹐盡數抄錄在懷。\n", me);

	// lore 信物旗標（Domain 物件設玩家 quest 旗標﹐euid 安全﹐見檔首 #15 說明）。
	me->set("quest/biyou_stele", 1);

	// 提示：此為 lore 信物，實際授方機制待後續（不臆造煉丹數值）。
	tell_object(me,
		"（你抄下了石板上的頂級丹方訣文。這些失傳的丹方深奧無比﹐\n"
		"　如何依方煉成那一爐爐頂級丹藥﹐還待你日後慢慢參詳。）\n");
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
