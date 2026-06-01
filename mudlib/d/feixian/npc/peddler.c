// peddler.c -- 斐縣雜貨鋪的雜貨郎（F_VENDOR 販售既有的乾糧吃食與傷藥）。
//             兼斐縣非戰鬥支線「悅客來的散帳」的一處核帳點：玩家持悅客來
//             客棧掌櫃的收帳冊來核雜貨鋪代記的賒帳（ask peddler about 賒帳）。
//             僅推進該支線旗標（quest/feixian_tab_shop / _count）﹐不給賞、
//             不動別的任務旗標﹐核帳一次即記﹐重問不重複計數。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("雜貨郎", ({ "peddler", "vendor", "shopkeeper", "feixian_peddler" }) );
	set("nickname", "雜貨郎");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一個和氣的本地生意人﹐生得圓臉福相﹐裹著件漿洗得發白\n"
		"的短褐﹐成日價坐在櫃後搖著蒲扇。他守著這城裡貨色最齊的雜\n"
		"貨鋪﹐見了客人便笑呵呵地招呼。你可以用 list 看他賣些什麼﹐\n"
		"用 buy 向他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"雜貨郎搖著蒲扇﹐笑呵呵地招呼道﹕客官要點什麼﹖過日子的零碎物事﹐小店大半尋得著哩。\n",
		"雜貨郎一面理著貨架﹐一面道﹕進山趕路的客官﹐多帶些乾糧傷藥﹐這山裡頭可不比城裡方便。\n",
		"雜貨郎嘆道﹕咱這縣前街﹐就指著趕集的日子熱鬧那麼一陣﹐平日裡慢生意﹐圖個自在罷了。\n",
	}));
	// 斐縣雜貨鋪﹐沿用既有的乾糧吃食與傷藥物件販售。
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
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這雜貨郎些甚麼﹖（試試 ask peddler about 賒帳）\n");

	// 賒帳：非戰鬥支線「悅客來的散帳」的核帳點（須已接任務、且持收帳冊在身）
	if( arg == "peddler about 賒帳"
	||  arg == "peddler about 散帳"
	||  arg == "peddler about 收帳冊"
	||  arg == "peddler about 帳"
	||  arg == "vendor about 賒帳"
	||  arg == "shopkeeper about 賒帳"
	||  arg == "peddler about tab" ) {
		object me = this_player();

		// 未接任務 / 已交差：只當尋常打聽，不核帳、不記旗標
		if( me->query("quest/feixian_tab") != 1 ) {
			do_chat((: command,
				"say 賒帳﹖客官問這個做甚﹖小店是替悅客來代記過幾位過路客商的零碎賒帳﹐都是相與的舊例﹐客官若不是掌櫃打發來核帳的﹐這帳本子可不便隨意給人瞧。" :));
			return 1;
		}

		// 接了任務卻沒帶收帳冊：提示先去掌櫃處領冊
		if( !present("tab ledger", me) ) {
			do_chat((: command,
				"say 客官是悅客來掌櫃打發來核帳的﹖那得先問掌櫃討了那本收帳冊來﹐小老兒纔好對著謄錄。空著手﹐這帳沒法核哪。" :));
			return 1;
		}

		// 已核過本家：純氣氛，不重複計數
		if( me->query("quest/feixian_tab_shop") ) {
			do_chat((: command,
				"say 小店這幾筆零碎賒帳﹐方纔已替客官核對謄錄在收帳冊上了。客官且往錢記酒樓、清風茶行那兩處﹐把另兩家的也核齊了罷。" :));
			return 1;
		}

		// 首次核帳：記本家旗標、總數 +1
		me->set("quest/feixian_tab_shop", 1);
		me->add("quest/feixian_tab_count", 1);
		do_chat(({
			(: command, "say 哦﹐掌櫃打發客官來核散帳的﹖難為他想得周全。客官把收帳冊攤開﹐小老兒這就把雜貨鋪代記的賒帳與客官對。" :),
			(: command, "say 有趕路的客商賒過乾糧傷藥、火石蠟燭﹐零零碎碎也記了幾筆在悅客來帳上。小老兒替客官一筆筆對著謄錄清楚了﹐客官收好冊子﹐三家核齊了﹐便回客棧尋掌櫃對帳罷。" :),
		}));
		return 1;
	}

	// 斐縣本地閒談（純氣氛﹐與街坊各 NPC 一致的指路口吻）
	if( arg == "peddler about 斐縣"
	||  arg == "peddler about 縣前街"
	||  arg == "peddler about 雜貨鋪"
	||  arg == "peddler about feixian" ) {
		do_chat(({
			(: command, "say 客官是頭一回逛咱這縣前街罷﹖小店是這街東頭貨色最齊的雜貨鋪了﹐過日子的零碎物事、趕路的乾糧傷藥﹐大半尋得著。" :),
			(: command, "say 街西那座土地祠香火旺﹐街南頭便是縣衙﹐往北回了五向路口﹐東西南北的鋪子茶樓都齊全。客官慢慢逛便是。" :),
		}));
		return 1;
	}

	return notify_fail("雜貨郎搖著蒲扇憨憨一笑﹕客官要買些甚麼﹐只管 list 來瞧。\n");
}

int accept_fight(object ob)
{
	do_chat("雜貨郎連忙縮手陪笑﹕客官有話好說﹗縣衙就在街那頭哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
