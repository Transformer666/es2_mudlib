// shopkeeper.c -- 平陽山腳小店店主「一笑老兒」（F_VENDOR 供應既有的食物補給）
//
// 結構鏡 d/zhaoyin/npc/laowang.c（F_VILLAGER + F_VENDOR、merchandise 沿用既有食物物件、
// init() 掛 list、accept_fight 回 0 不應戰）。賣的是這山腳人家的酒食補給(沿用 obj/food
// 既有物件：烤肉、饅頭、餃子、月餅)，供上山打獵的玩家補給。店中所在房間 store.c 設
// no_fight，本人亦不應戰。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("一笑老兒", ({ "shopkeeper", "old man", "laoer", "vendor" }) );
	set("nickname", "一笑老兒");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 67);
	set("gender", "male");
	set("long",
		"這便是平陽山腳這間孤店的掌店老兒了。他生得白髮蒼蒼、腰背\n"
		"微僂﹐一張臉笑得滿是溝壑般的褶子﹐人都喚他一聲「一笑老兒」。\n"
		"他在這山腳開店數十年﹐替過往的獵戶行旅張羅酒食﹐見慣了上山\n"
		"的好漢一去不回﹐口裡總壓著嗓子念叨﹕山上那夥山賊兇得很﹐客\n"
		"官可千萬留神。你可以用 list 看他賣些什麼﹐用 buy 向他買來。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"一笑老兒擦著桌子﹐壓低了嗓子道﹕客官﹐這平陽山上的山賊近年愈發猖獗了﹐上山可千萬留神哪。\n",
		"一笑老兒嘆了口氣﹕那寨主公孫一笑兇名在外﹐手底下嘍囉成群﹐多少好漢上了山就再沒下來……\n",
		"一笑老兒笑呵呵地招呼﹕客官先沽壺酒、吃點東西暖暖身子﹐上山的路﹐可有得熬哩。\n",
	}));
	// 山腳小店﹐沿用既有的食物物件販售（烤肉、饅頭、餃子、月餅之屬，皆 obj/food 既有）。
	set("merchandise", ([
		"/obj/food/pork" : 35,
		"/obj/food/manto" : 25,
		"/obj/food/dumpling" : 30,
		"/obj/food/mooncake" : 40,
	]));

	setup();
	carry_money("coin", 80);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

// 店中不應戰（店所在房間 store.c 已設 no_fight，此處再以言語回絕）。
int accept_fight(object ob)
{
	do_chat("一笑老兒慌忙擺手﹐陪笑道﹕哎喲客官﹐小老兒一把年紀、與世無爭﹐你莫要尋我晦氣哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
