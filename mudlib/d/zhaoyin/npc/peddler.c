// peddler.c -- 兆隱縣雜貨鋪的老闆（F_VENDOR 販售既有的乾糧吃食與傷藥）

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
	set_name("雜貨鋪老闆", ({ "peddler", "vendor", "shopkeeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 51);
	set("gender", "male");
	set("long",
		"一個和氣的山城生意人﹐生得圓臉福相﹐裹著件漿洗得發白\n"
		"的短褐﹐成日價坐在櫃後搖著蒲扇。他守著這城裡貨色最齊的\n"
		"雜貨鋪﹐見了客人便笑呵呵地招呼。你可以用 list 看他賣些\n"
		"什麼﹐用 buy 向他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"雜貨鋪老闆搖著蒲扇﹐笑呵呵地招呼道﹕客官要點什麼﹖過日子的零碎物事﹐小店大半尋得著哩。\n",
		"雜貨鋪老闆一面理著貨架﹐一面道﹕進山趕路的客官﹐多帶些乾糧傷藥﹐這山裡頭可不比城裡方便。\n",
		"雜貨鋪老闆嘆道﹕咱這小縣城地僻人稀﹐一日也沒幾個主顧﹐慢生意﹐圖個自在罷了。\n",
	}));
	// 僻遠縣城雜貨鋪﹐沿用既有的乾糧吃食與傷藥物件販售。
	set("merchandise", ([
		"/obj/food/manto" : 55,
		"/obj/food/ricedough" : 45,
		"/obj/food/mooncake" : 28,
		"/obj/medication/boar_berry" : 10,
	]));

	setup();
	carry_money("coin", 120);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
	do_chat("雜貨鋪老闆連忙縮手陪笑﹕客官有話好說﹗縣衙就在街那頭哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
