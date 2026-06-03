// herbalist.c -- 百藥谷藥廬的采藥老人（F_VENDOR）。
//
// 本區的核心可玩點﹕以 list / buy 販售煉丹藥材﹐為一般玩家補上「煉丹藥材
// 何處得」的缺口。在此之前﹐refine（煉丹）所需的靈芝、當歸只能靠巫師 clone
// （見 memory/patterns/content-alchemy.md「藥材取得」）﹐玩家無正規來源。
//
// 販售的是 refine 配方真正讀取的物件路徑﹕
//   /obj/reagent/lingzhi（靈芝）、/obj/reagent/danggui（當歸）
// ——即 cmds/std/refine.c 之 HERB_LINGZHI / HERB_DANGGUI。另搭售山豬果(傷藥)增色。
//
// 機制比照 d/feixian/npc/peddler.c﹕
//   * inherit F_VILLAGER + F_VENDOR（非戰鬥商販）。
//   * set("merchandise", ([ "物件路徑" : 庫存數 ]))﹔買賣由 /cmds/std/buy.c 經
//     vendor.c 的 affirm_merchandise/deliver_merchandise 處理。售價取物件自身
//     query("value")（COMBINED_ITEM = base_value*amount = base_value）﹐
//     mapping 的整數值僅作初始庫存計數。
//   * add_action("do_vendor_list", "list")﹔add_action("do_ask", "ask")。
//   * carry_money 給找零﹔accept_fight 回 0（非戰鬥）。
//
// 認物以英文 id 為準（feature/name.c::id() 只比對 set_name 第二參數）﹐
// 故買藥語法為﹕buy lingzhi from laoren / buy danggui from laoren。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("采藥老人", ({ "herbalist", "laoren", "old man", "baiyao_herbalist" }) );
	set("nickname", "采藥老人");
	set_race("human");
	set_class("commoner");
	set_level(15);

	set("age", 68);
	set("gender", "male");
	set("long",
		"一位在百藥谷裡采了大半輩子藥的老人﹐鬚眉皆白卻面色紅潤﹐\n"
		"一雙眼睛清亮有神﹐想是常年服食谷中靈藥之故。他枯瘦而靈巧\n"
		"的手指不住地分揀著竹榻上的草藥﹐谷裡百草的脾性、煉丹的門\n"
		"道﹐他無一不曉。你可以用 list 看他賣些什麼藥材﹐用 buy 向\n"
		"他買﹐也可 ask 他些採藥煉丹的事（試試 ask laoren about 煉丹）。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"采藥老人捻著一株草藥湊到鼻端聞了聞﹐含笑道﹕客官是來尋丹材的罷﹖這谷裡的藥﹐錯不了。\n",
		"采藥老人一面分揀草藥﹐一面道﹕煉丹講究藥材地道﹐我這谷裡的靈芝、當歸﹐都是溪水養、地氣足的﹐入爐最是出效。\n",
		"采藥老人慢悠悠地道﹕老朽在這百藥谷裡采了五十年藥﹐哪一味該幾時採、怎麼炮製﹐閉著眼也錯不了哩。\n",
	}));

	// 核心﹕販售 refine（煉丹）配方表 (cmds/std/refine.c) 真正讀取的全部藥材﹐
	// 讓玩家備齊任一爐丹方。整數為初始庫存份數﹔售價取自物件 query("value")：
	//   COMBINED_ITEM 取 base_value（靈芝 200、當歸 120 文）﹔
	//   REAGENT_ITEM  取 unit_value×weight（辰砂 300、枸杞 500、番木鱉 1050、鶴頂紅 3000 文）。
	// 認物以英文 id 為準﹐買法如 buy cinnabar from laoren、buy crane dye from laoren。
	set("merchandise", ([
		"/obj/reagent/lingzhi"          : 50,   // 靈芝（COMBINED_ITEM）
		"/obj/reagent/danggui"          : 50,   // 當歸（COMBINED_ITEM）
		"/obj/reagent/cinnabar"         : 30,   // 辰砂（汞護爐，金液丹/小還丹等）
		"/obj/reagent/medlar"           : 40,   // 枸杞（清毒/醒神/養心等）
		"/obj/reagent/strychin"         : 10,   // 番木鱉（劇毒罕材，大還丹）
		"/obj/reagent/crane_dye"        : 10,   // 鶴頂紅（劇毒罕材，甘靈清毒丹）
		"/obj/medication/boar_berry"    : 20,   // 山豬果（傷藥，增色）
	]));

	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這采藥老人些什麼﹖（試試 ask laoren about 煉丹）\n");

	// 煉丹／藥材﹕點出本谷藥材與龍圖丹派 refine 的關聯（純氣氛指路）
	if( arg == "laoren about 煉丹"
	||  arg == "laoren about 丹"
	||  arg == "laoren about 藥材"
	||  arg == "laoren about 丹材"
	||  arg == "herbalist about 煉丹"
	||  arg == "herbalist about 藥材"
	||  arg == "old man about 煉丹"
	||  arg == "laoren about refine"
	||  arg == "laoren about alchemy" ) {
		do_chat(({
			(: command, "say 客官也曉得煉丹﹖那便是同道了。煉丹最要緊的是藥材地道——靈芝平補、當歸活血﹐一爐養氣丹少了哪一味都不成。" :),
			(: command, "say 老朽這藥廬裡﹐靈芝、當歸、辰砂、枸杞﹐連那劇毒的番木鱉、鶴頂紅都備著﹐客官 list 一看便知。買齊了藥材﹐尋一處架著丹爐的丹房﹐方士便可起火煉丹了。" :),
			(: command, "say 聽聞雪亭鎮、龍圖丹派那邊都有丹房丹爐。客官若拜在丹派門下做了方士﹐備齊我這兒的靈芝當歸﹐refine（煉丹）一試便知好歹。" :),
		}));
		return 1;
	}

	// 靈芝
	if( arg == "laoren about 靈芝"
	||  arg == "herbalist about 靈芝"
	||  arg == "laoren about lingzhi" ) {
		do_chat((: command,
			"say 靈芝啊﹐谷底幽谷的朽木上長得最好﹐傘蓋赤褐如漆﹐藥性溫和平補﹐是煉丹的上好藥材。老朽這兒曬乾的現貨儘有﹐買賣語法是 buy lingzhi from laoren。" :));
		return 1;
	}

	// 當歸
	if( arg == "laoren about 當歸"
	||  arg == "herbalist about 當歸"
	||  arg == "laoren about danggui" ) {
		do_chat((: command,
			"say 當歸補血活血﹐藥圃裡栽著一畦﹐根莖肥碩、氣味芳香﹐也是入爐煉丹的常用藥材。要買便道一聲 buy danggui from laoren。" :));
		return 1;
	}

	// 辰砂（汞）
	if( arg == "laoren about 辰砂"
	||  arg == "herbalist about 辰砂"
	||  arg == "laoren about 汞"
	||  arg == "laoren about cinnabar" ) {
		do_chat((: command,
			"say 辰砂是一種紅色礦砂﹐加熱便得水銀（汞）﹐煉小還丹、金液丹這等療傷靈丹﹐須以汞護住丹爐才壓得住火候。買法是 buy cinnabar from laoren。" :));
		return 1;
	}

	// 枸杞
	if( arg == "laoren about 枸杞"
	||  arg == "herbalist about 枸杞"
	||  arg == "laoren about medlar" ) {
		do_chat((: command,
			"say 枸杞性平味甘﹐谷中藥圃多的是﹐清毒、醒神、養心的丹方都少不了它。要買道一聲 buy medlar from laoren。" :));
		return 1;
	}

	// 番木鱉
	if( arg == "laoren about 番木鱉"
	||  arg == "herbalist about 番木鱉"
	||  arg == "laoren about strychin" ) {
		do_chat((: command,
			"say 番木鱉含著劇毒﹐尋常人碰不得﹐唯有煉大還丹這等內外俱癒的極品仙丹方用得上一味﹐價也不菲。要買道一聲 buy strychin from laoren。" :));
		return 1;
	}

	// 鶴頂紅
	if( arg == "laoren about 鶴頂紅"
	||  arg == "herbalist about 鶴頂紅"
	||  arg == "laoren about crane dye"
	||  arg == "laoren about crane_dye" ) {
		do_chat((: command,
			"say 鶴頂紅也是一味劇毒﹐偏偏甘靈清毒丹要以毒攻毒﹐少不得它。客官買時道一聲 buy crane dye from laoren﹐留神莫要誤食。" :));
		return 1;
	}

	// 百藥谷本身（純氣氛）
	if( arg == "laoren about 百藥谷"
	||  arg == "herbalist about 百藥谷"
	||  arg == "laoren about baiyao"
	||  arg == "laoren about 谷" ) {
		do_chat(({
			(: command, "say 這百藥谷藏在老松林裡頭﹐一道石隙隔開了外頭的兵戈獸患﹐谷裡溪水甘冽、地氣豐厚﹐百草俱備﹐尋常難尋的丹材﹐這兒長得跟野草似的。" :),
			(: command, "say 客官沿溪走走﹐藥圃、采藥小徑、谷底幽谷都去瞧瞧。只是谷底那些稀世靈藥﹐可遇而不可求﹐老朽采了五十年﹐也未必撞上一回哩。" :),
		}));
		return 1;
	}

	return notify_fail("采藥老人捻著鬍鬚笑道﹕客官要買什麼藥材﹐只管 list 來瞧﹔煉丹尋藥的事﹐也問得（ask laoren about 煉丹）。\n");
}

int accept_fight(object ob)
{
	do_chat("采藥老人連忙擺手﹕客官有話好說﹗老朽一個采藥的﹐哪會什麼武功﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
