// peddler.c -- 五味鋪的貨郎（F_VENDOR 販售乾糧吃食﹐純氣氛閒談）。
//             水嵐武陵的尋常小鋪﹐不接任務、不動任何旗標。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("貨郎", ({ "peddler", "shopman", "wuling_peddler" }) );
	set("nickname", "貨郎");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 45);
	set("gender", "male");
	set("long",
		"守著五味鋪的是個和氣的本地貨郎﹐生得敦厚﹐一張圓臉終\n"
		"日帶笑。鋪子雖小﹐油鹽醬醋、針線草鞋、乾糧吃食倒也一應俱\n"
		"全﹐都是武陵人家過日子離不得的零碎。他成日坐在櫃後搖著蒲\n"
		"扇﹐生意清淡也不著急。你可以用 list 看他賣些什麼﹐用 buy\n"
		"向他買東西。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"貨郎搖著蒲扇﹐懶洋洋地打量著進門的客人﹐笑呵呵地招呼。\n",
		"貨郎理了理櫃上的針線草鞋﹐口中哼著一支不成調的鄉間小曲。\n",
		"貨郎笑道﹕客官要往山外去﹖路上耐放的乾糧﹐可得在小老兒這兒備足了。\n",
	}));
	// 五味鋪賣的是過日子的零碎與趕路的乾糧﹐沿用既有食物物件。
	set("merchandise", ([
		"/obj/food/manto" : 50,
		"/obj/food/ricedough" : 40,
		"/obj/food/pork" : 30,
		"/obj/food/fish" : 40,
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
		return notify_fail("你想問這貨郎些甚麼﹖（試試 ask peddler about 武陵）\n");

	if( arg == "peddler about 武陵"
	||  arg == "peddler about 水嵐"
	||  arg == "peddler about 五味鋪"
	||  arg == "peddler about 鋪子"
	||  arg == "peddler about wuling" ) {
		do_chat(({
			(: command, "say 客官別看咱五味鋪寒酸﹐這武陵鎮上﹐就數小老兒這兒貨色最全了。鎮子小﹐人也少﹐巴掌大的地方﹐東到醉月茶寮﹐西到五陵客棧﹐抬腳就到。" :),
			(: command, "say 客官若是要進山訪那冷梅莊﹐打渡口過了溪﹐順著北邊那條石徑走便是。那一路梅花開得好﹐只是莊裡的規矩大﹐客官好生著些。" :),
		}));
		return 1;
	}

	return notify_fail("貨郎搖著蒲扇﹐衝你憨憨一笑﹕客官要買些甚麼﹐只管挑罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲喲﹗客官這是做甚﹖小老兒一個守鋪子的﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
