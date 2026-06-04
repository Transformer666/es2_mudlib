// jiang.c -- 江述仁 (Jiang hsuren)﹕龍圖丹派物資商、二轉醫師。
//
// 角色出處﹕docs/01-世界觀與劇情/05-主線任務與NPC.md「重要任務 NPC」表
//   「江述仁 (Jiang hsuren) | 大屋正廳 | 龍圖丹派物資商；二轉醫師」。
//   本派(龍圖丹派 d/longtu)既有掌門神醫(npc/master)坐堂醫館施診/收徒/二轉﹐
//   惟玩家無正規購置現成丹藥、傷藥之處﹔江述仁即補上此缺──以醫館為「正廳」﹐
//   設一龍圖丹派的物資商兼醫師﹐list / buy 販售既有的丹藥、傷藥、補氣補神物資。
//
// 機制全盤比照已驗證的 F_VENDOR 範式﹕
//   * d/baiyao/npc/herbalist.c（龍圖丹派 refine 藥材商﹐同 sect 同題材的最近範式）
//   * d/wenguo/npc/shopman.c、d/feixian/npc/peddler.c（純買賣 + 本地閒談非戰鬥商販）
// 即﹕inherit F_VILLAGER + F_VENDOR﹔set("merchandise", ([ "物件路徑" : 初始庫存 ]))﹔
//   買賣由 /cmds/std/buy.c 經 feature/npc/vendor.c 的 affirm_merchandise /
//   query_trading_price / deliver_merchandise 處理﹐售價取物件自身 query("value")
//   (販品皆 COMBINED_ITEM﹐value = base_value*amount = base_value)﹐mapping 整數
//   值僅作初始庫存份數。add_action("do_vendor_list", "list")﹔add_action("do_ask","ask")。
//   carry_money 給找零﹔accept_fight 回 0（非戰鬥商販）。不接任務、不交物、不動旗標。
//
// 販品皆既有 /obj/medication 物件（無自造買賣 efun、無臆造路徑）﹕
//   /obj/medication/black_pill              烏心丹（恢復體力的民間藥﹐base_value 80）
//   /obj/medication/boar_berry              山豬果（傷藥﹐base_value 2000）
//   /obj/medication/alchemist/minor_heal_pill 小還丹（療傷靈丹﹐base_value 6000）
//   /obj/medication/alchemist/mana_pill     醒神丹（補神﹐base_value 260）
//   /obj/medication/alchemist/refresh_pill  金鎖固精丸（固精補氣﹐base_value 1000）
//
// 認物以英文 id 為準（feature/name.c::id() 只比對 set_name 第二參數）﹔多件共用 "pill"
// id 時﹐affirm_merchandise 支援 "buy pill 2 from hsuren" 以序號區分﹐list 亦逐項列出。
// 與同室掌門(npc/master)id 不撞﹕master 用 master/physician/doctor﹐此 NPC 用
//   jiang/hsuren/merchant/supplier/vendor。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("江述仁", ({ "jiang hsuren", "hsuren", "jiang", "merchant", "supplier", "vendor", "longtu_jiang" }) );
	set("nickname", "江述仁");
	set_race("human");
	set_class("alchemist");
	set("sect", "龍圖丹派");
	set("rank", "物資");
	set("title", "龍圖丹派物資商");
	set_level(20);

	set("age", 41);
	set("gender", "male");
	set("long",
		"龍圖丹派的物資商江述仁﹐人喚他一聲『江二爺』。生得方面闊\n"
		"口、兩道濃眉﹐穿一件半舊的藏青綢褂﹐袖口別著一支算盤﹐腰間\n"
		"懸著個盛藥的錦囊。他原也是本派二轉的醫師﹐辨穴施針的本事都\n"
		"還在﹐只是性子好張羅、會盤帳﹐索性替丹派打理起這醫館正廳的\n"
		"進出物資來——丹房煉出的丹藥、谷裡采來的傷藥﹐外頭來求醫問\n"
		"藥的客人﹐都經他的手過。他見了客人便拱手招呼﹐一面撥著算\n"
		"盤﹐一面笑問可要備些丹藥傷藥。你可以用 list 看他賣些什麼﹐\n"
		"用 buy 向他買﹐也可 ask 他些丹藥的事（試試 ask hsuren about 丹藥）。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"江述仁撥著算盤﹐含笑拱手﹕客官是來抓藥的罷﹖丹房新煉的丹、谷裡采的傷藥﹐小號都備著哩。\n",
		"江述仁一面清點藥囊﹐一面道﹕出門在外﹐傷藥、補神的丹丸總要備上幾粒﹐免得臨急抓瞎。\n",
		"江述仁慢條斯理地道﹕我龍圖丹派以丹針濟世﹐這正廳的物資﹐進進出出都經我的手﹐錯不了。\n",
	}));

	// 核心﹕list / buy 販售既有 /obj/medication 物件﹐補上玩家購置現成丹藥傷藥的缺口。
	// 整數為初始庫存份數﹔售價取自物件 query("value")（皆 COMBINED_ITEM﹐= base_value）。
	// 認物以英文 id 為準（exact token match﹐feature/name.c::id() = member_array）﹐
	// 買法如﹕buy black pill from hsuren、buy berry from hsuren﹔三味丹藥共用 "pill"
	// id﹐可 buy minor from hsuren / buy mana from hsuren（皆其專屬 id）取﹔金鎖固精丸
	// 無單字專屬 id﹐用全名 buy refresh pill from hsuren﹐或 buy pill 3 from hsuren 以序號取。
	set("merchandise", ([
		"/obj/medication/black_pill"                : 30,   // 烏心丹（恢復體力，民間藥）
		"/obj/medication/boar_berry"                : 20,   // 山豬果（傷藥）
		"/obj/medication/alchemist/minor_heal_pill" : 10,   // 小還丹（療傷靈丹）
		"/obj/medication/alchemist/mana_pill"       : 20,   // 醒神丹（補神）
		"/obj/medication/alchemist/refresh_pill"    : 15,   // 金鎖固精丸（固精補氣）
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
	// 戰鬥/談話中不應答（runtime 守衛﹕do_ask 類動作須 is_fighting()/is_chatting() 把關）。
	if( is_fighting() || is_chatting() ) return 0;

	if( !arg )
		return notify_fail("你想問這江述仁些什麼﹖（試試 ask hsuren about 丹藥）\n");

	// 丹藥／物資﹕點出本派 list/buy 與龍圖丹派丹房、藥圃的關聯（純氣氛指路）。
	if( arg == "hsuren about 丹藥"
	||  arg == "hsuren about 丹"
	||  arg == "hsuren about 藥"
	||  arg == "hsuren about 物資"
	||  arg == "jiang about 丹藥"
	||  arg == "jiang about 物資"
	||  arg == "merchant about 丹藥"
	||  arg == "hsuren about medication"
	||  arg == "hsuren about pill" ) {
		do_chat(({
			(: command, "say 客官要丹藥傷藥儘管 list 來瞧。小號這兒﹕烏心丹補體力、醒神丹補神、金鎖固精丸固精補氣﹐傷著了有山豬果﹐傷重便用那小還丹﹐外傷瞬癒﹐只是價也不菲。" :),
			(: command, "say 這些丹丸﹐多是後頭丹房裡本派方士起爐煉的﹐傷藥則是百藥谷采藥老人那邊運來的。客官買法是 buy <藥名> from hsuren﹐譬如 buy black pill from hsuren、buy minor from hsuren、buy berry from hsuren。" :),
		}));
		return 1;
	}

	// 龍圖丹派／煉丹／二轉（指掌門與丹房，自己只是物資商）
	if( arg == "hsuren about 龍圖丹派"
	||  arg == "hsuren about 龍圖"
	||  arg == "hsuren about 煉丹"
	||  arg == "hsuren about refine"
	||  arg == "hsuren about 拜師"
	||  arg == "hsuren about 二轉"
	||  arg == "jiang about 龍圖丹派"
	||  arg == "merchant about 龍圖丹派"
	||  arg == "hsuren about longtu" ) {
		do_chat(({
			(: command, "say 我龍圖丹派以煉丹施針、懸壺濟世立足江湖。這醫館正廳坐堂的便是本派掌門杏林神醫﹐求醫拜師、進階授技﹐都得尋他老人家——我不過替丹派打理物資﹐做不得主。" :),
			(: command, "say 客官若想學這一身丹道針法﹐ask master 便是﹔備齊了藥材﹐後頭丹房架著丹爐﹐方士便可 refine（煉丹）。藥材麼﹐百藥谷采藥老人那兒備得齊全。" :),
		}));
		return 1;
	}

	return notify_fail("江述仁撥著算盤笑道﹕客官要買什麼丹藥﹐只管 list 來瞧﹔丹道煉丹的事﹐也問得（ask hsuren about 丹藥）。\n");
}

int accept_fight(object ob)
{
	do_chat("江述仁連忙拱手陪笑﹕客官有話好說﹗江某一個盤帳抓藥的﹐哪會什麼真功夫﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
