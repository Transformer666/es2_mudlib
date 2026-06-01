// shopman.c -- 康平雜貨鋪的貨郎（F_VENDOR 販售既有的乾糧吃食與傷藥﹐
//              純買賣 + 本地閒談）。不接任務、不交物、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("貨郎", ({ "shopman", "vendor", "shopkeeper", "kangping_shopman" }) );
	set("nickname", "貨郎");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一個和氣的本村生意人﹐生得圓臉福相﹐裹著件漿洗得發白\n"
		"的短褐﹐成日價坐在櫃後搖著蒲扇﹐看曬場上翻穀趕集的村人來來\n"
		"往往。他守著這村心的小雜貨鋪﹐村人過日子的零碎、出村趕路的\n"
		"吃食傷藥﹐大半尋得著。你可以用 list 看他賣些什麼﹐用 buy 向\n"
		"他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"貨郎搖著蒲扇﹐笑呵呵地招呼道﹕客官要點什麼﹖過日子的零碎物事﹐小店大半尋得著哩。\n",
		"貨郎一面理著貨架﹐一面道﹕出村趕路的客官﹐多帶些乾糧傷藥﹐這村外頭的長路可不比村裡方便。\n",
		"貨郎嘆道﹕咱這康平村偏在斐縣城西﹐生意慢﹐圖個守著這一村安生﹐自在罷了。\n",
	}));
	// 康平雜貨鋪﹐沿用既有的乾糧吃食與傷藥物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 50,
		"/obj/food/ricedough" : 40,
		"/obj/food/mooncake" : 28,
		"/obj/food/dumpling" : 60,
		"/obj/medication/boar_berry" : 10,
	]));

	setup();
	carry_money("coin", 120);
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
		return notify_fail("你想問這貨郎些甚麼﹖（試試 ask shopman about 康平村）\n");

	if( arg == "shopman about 康平村"
	||  arg == "shopman about 雜貨鋪"
	||  arg == "shopman about 村"
	||  arg == "shopman about 康平"
	||  arg == "shopman about kangping" ) {
		do_chat(({
			(: command, "say 客官是頭一回逛咱這康平村罷﹖咱這小村偏在斐縣城西﹐合村人家靠著村外那一片田過活﹐日子過得安生平淡。小店過日子的零碎、趕路的乾糧傷藥﹐大半尋得著。客官慢慢逛便是。" :),
			(: command, "say 村心北邊是康平小店﹐西北窄巷進去是吃水的井臺﹐南面田埂下去便是村外的田壟。眼下新穀登場﹐村裡正忙著曬穀碾米﹐熱鬧得很。客官得空都去瞧瞧﹐出村在即﹐莫忘了帶足乾糧。" :),
		}));
		return 1;
	}

	return notify_fail("貨郎搖著蒲扇憨憨一笑﹕客官要買些甚麼﹐只管 list 來瞧。\n");
}

int accept_fight(object ob)
{
	do_chat("貨郎連忙縮手陪笑﹕客官有話好說﹗咱一個本分的生意人哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
