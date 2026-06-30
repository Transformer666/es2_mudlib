// storekeeper.c -- 霧中野店的老店家。
//   F_VENDOR 賣乾糧清水給入林獵殺的客人補給（list / buy）。
//   兼氛圍/lore NPC：ask keeper about 幻霧/古樹/鬼魅，講這霧林的來歷與傳說，
//   為日後「霧牆之後 / 霧靈古樹之謎」鋪陳伏筆（docs 未給此地完整設定，僅作
//   lore 探索與劇情鋪墊，不臆造完整解謎/獎勵）。不接任務、不交物、不動旗標。
//
// init() 招呼依 lesson #14 加 interactive(this_player()) 護衛，只招呼真人，
// 避免 NPC 互觸成 say-storm。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("老店家", ({ "storekeeper", "keeper", "old man", "dianjia" }) );
	set("nickname", "老店家");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 67);
	set("gender", "male");
	set("long",
		"一個鬚髮花白、佝僂著背的老店家﹐在這迷路吃人的霧林裡守了\n"
		"大半輩子的店。他生得一張刀刻似的皺臉﹐渾濁的老眼卻透著股\n"
		"看透世情的精明﹐時不時要望向門外那團化不開的濃霧。他見慣\n"
		"了形形色色的入林客——有滿載而歸的、有狼狽逃命的、也有進去\n"
		"了便再沒出來的。你可以用 list 看店裡有些甚麼乾糧吃食﹐用\n"
		"buy 跟他補些﹔得空也問問他這林子的來歷（ask keeper about 幻霧）。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老店家就著昏黃的燈火﹐一針一線地補著那張破網﹐不時抬眼望一望門外的濃霧。\n",
		"老店家往火塘裡添了根松柴﹐火光一跳﹐映得他刀刻似的皺臉明明滅滅。\n",
		"老店家壓低了嗓子咕噥道﹕入了林﹐切記莫貪深、莫戀戰﹐霧一濃就趁早往回走 ... 不聽老朽勸的﹐墳頭草都幾尺高嘍。\n",
	}));
	// 野店供應入林獵殺者的乾糧補給，沿用既有 COMBINED_ITEM 食物物件販售
	// （皆 set base_value→value，list/buy 計價正常）。清水(/obj/water)為
	// LIQUID_ITEM、未設 value，混入會以 0 計價、list 顯示「零文錢」，故不售；
	// 補水留待後續以設了 value 的飲品物件補上。
	set("merchandise", ([
		"/obj/food/manto" : 50,
		"/obj/food/pork" : 40,
		"/obj/food/dumpling" : 50,
		"/obj/food/mooncake" : 30,
	]));

	setup();
	carry_money("coin", 80);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
	add_action("do_ask", "ask");
	// 只對真人玩家招呼（lesson #14：缺 interactive 護衛＝say-storm）。
	if( this_player() && interactive(this_player()) && !is_fighting() )
		do_chat((: command,
			"say 客官打林子裡來﹖快進來烤烤火、歇歇腳﹗要補些乾糧清水﹐只管同老朽說。" :));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這老店家些甚麼﹖（試試 ask keeper about 幻霧）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老店家正忙著﹐沒空理你。\n");

	// 幻霧森林的來歷與傳說（lore 伏筆）
	if( arg == "keeper about 幻霧"
	||  arg == "keeper about 森林"
	||  arg == "keeper about 幻霧森林"
	||  arg == "keeper about 霧"
	||  arg == "keeper about 林子"
	||  arg == "keeper about huanwu" ) {
		do_chat(({
			(: command, "say 這幻霧森林啊﹐打老朽爺爺的爺爺那輩起﹐就是這麼終年罩著一片化不開的白霧。霧裡多獸、多岔路﹐進去的人十有八九要迷了道﹐轉著轉著就再尋不著歸途嘍。" :),
			(: command, "say 客官若只在林緣淺處打打野豬、霧狼練練手﹐倒還使得——霧薄﹐認得清來路。可越往林深﹐霧越濃、獸越兇﹐那古木林、林心裡頭的東西 ... 唉﹐不是老朽嚇唬客官﹐沒幾分本事﹐千萬別往深裡闖。" :),
		}));
		return 1;
	}

	// 霧靈古樹 / 林心之謎（lore 伏筆，不給解答）
	if( arg == "keeper about 古樹"
	||  arg == "keeper about 霧靈古樹"
	||  arg == "keeper about 林心"
	||  arg == "keeper about 枯樹"
	||  arg == "keeper about tree" ) {
		do_chat(({
			(: command, "say 林子最深處的林心﹐立著一株灰白如骨的枯樹﹐村裡老人都喚作『霧靈古樹』。傳說這滿林的霧、那些幽幽的磷火鬼影﹐全是打那株枯樹底下生出來的。" :),
			(: command, "say 那樹底下埋著甚麼、那滿身的古怪刻痕又是誰刻的——老朽守了一輩子店﹐也沒人說得清。進去過林心、又活著回來的人﹐一隻手都數得過來﹐個個回來都魂不守舍的﹐問甚麼都不肯說。客官﹐有些事﹐不知道反倒太平。" :),
		}));
		return 1;
	}

	// 鬼魅 / 迷失者傳說（lore 伏筆）
	if( arg == "keeper about 鬼魅"
	||  arg == "keeper about 鬼"
	||  arg == "keeper about 迷霧鬼魅"
	||  arg == "keeper about 磷火"
	||  arg == "keeper about ghost" ) {
		do_chat(({
			(: command, "say 客官在林裡﹐怕是見著那些飄飄忽忽、半透不透的影子了罷﹖老朽們都說﹐那是當年迷死在這林子裡、走不出去的人﹐魂魄教霧氣纏住了﹐困在林子裡頭出不來嘍。" :),
			(: command, "say 林心那株古樹底下的﹐怨念最深、最厲﹐連別的鬼魅都怕它三分。客官武藝若真到了家﹐去會牠一會、替那些孤魂了結了這口怨氣﹐倒是樁積德的事——只是﹐那是要拿命去拚的﹐量力﹐量力。" :),
		}));
		return 1;
	}

	return notify_fail("老店家眯著渾濁的老眼﹐慢吞吞道﹕客官要補乾糧清水﹐只管 list、buy﹔旁的﹐問這林子的來歷便是（ask keeper about 幻霧）。\n");
}

int accept_fight(object ob)
{
	do_chat("老店家連連擺手﹐佝僂著背賠笑﹕使不得使不得﹗老朽一把年紀﹐守爿小店餬口﹐怎敢與客官動手﹖\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
