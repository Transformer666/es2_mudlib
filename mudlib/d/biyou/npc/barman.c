// barman.c -- 碧幽亭客棧的酒保（F_VILLAGER + F_VENDOR 供應山貨乾糧水酒）。
//             兼作守墓部落的「指路人」：玩家可 ask barman about 石板/古墓﹐
//             問出碧幽古墓石板的所在(墓道南下→石室)。僅作 lore 引路﹐不給賞、
//             不記旗標、不動任何任務旗標。
//
// 售賣機制：F_VENDOR(feature/npc/vendor.c)﹐merchandise 列既有食物物件﹐玩家以
//   標準 /cmds/std/buy.c「buy X from barman」購買﹔本 NPC 只需 add_action(
//   "do_vendor_list","list")(buy 由玩家指令處理﹐見 feixian/npc/barman.c 範式)。
//   沿用既有食物路徑(obj/food/*)﹐不另建食物物件﹐免擴大改動面。
//
// 與既有 NPC 不撞：id 取 biyou_barman/barman/waiter﹐顯示名「酒保」於碧幽部落
//   獨有的碧幽亭客棧內﹐玩家不會與斐縣錢記酒樓的酒保混指(各在其房﹐present 各認各)。
//
// 認物以英文 id 為準(feature/name.c::id() 只比對 set_name 第二參數﹐runtime
//   -gotchas #6)。NPC init 招呼一律加 interactive(this_player()) 護衛(#14)。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("酒保", ({ "biyou barman", "barman", "waiter" }) );
	set("nickname", "酒保");
	set_race("human");
	set_class("commoner");
	set_level(4);
	set_skill("unarmed", 6);
	set_skill("dodge", 6);
	set_skill("parry", 6);

	set("age", 38);
	set("gender", "male");
	set("long",
		"這是碧幽亭客棧的酒保﹐一個裹著青灰麻衣的精瘦寨民﹐生得面\n"
		"色幽沉、顴骨高聳﹐一雙手卻麻利得很。守墓部落世代久居這幽碧\n"
		"深山﹐難得見著外鄉客﹐他算是寨裡少數還肯與生人搭話的了。見\n"
		"了客人﹐他擱下手裡的茶壺﹐拿生硬的官話招呼一聲﹐問可要打尖\n"
		"住店。你可以用 list 看櫃上有些什麼山貨酒食﹐用 buy 向他買來\n"
		"充飢﹔得閒也可問問他這碧幽部落的來歷﹕ask barman about 石板。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"酒保替火塘上的黑陶大壺添了把松柴﹐拿生硬的官話招呼﹕客官山路勞頓﹐先喝碗驅寒的苦茶罷。\n",
		"酒保壓低了嗓子道﹕客官是衝著東邊那古墓場來的罷﹖這碧幽部落﹐世代守的便是墓底那座碧幽古墓哩。\n",
		"酒保篩著一碗幽紫的山果酒道﹕咱這山裡的果子酒﹐後勁足﹐喝上一碗﹐連古墓裡的陰寒都熬得住。\n",
	}));
	// 山寨補給：沿用既有食物物件﹐供入古墓前充飢解渴。守墓山寨﹐量不多。
	set("merchandise", ([
		"/obj/food/manto" : 30,
		"/obj/food/pork" : 20,
		"/obj/food/dumpling" : 20,
		"/obj/food/mooncake" : 15,
		"/obj/food/ricedough" : 20,
	]));

	setup();
	carry_money("coin", 150);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
	add_action("do_ask", "ask");
	// NPC 招呼一律加 interactive 護衛(runtime-gotchas #14)﹐只招呼真人﹐免 NPC 互觸洗版。
	if( this_player() && interactive(this_player()) && !is_fighting() )
		do_chat((: command,
			"say 客官山裡來、墓邊歇﹐先喝碗苦茶暖暖身子罷。" :));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問酒保些甚麼﹖（試試 ask barman about 石板）\n");

	// 碧幽部落來歷
	if( arg == "barman about 碧幽"
	||  arg == "barman about 部落"
	||  arg == "barman about 碧幽部落"
	||  arg == "barman about biyou" ) {
		do_chat(({
			(: command, "say 客官問起咱碧幽部落﹖這名兒﹐是打那滿山化不開的碧色山靄來的。咱寨子小﹐人也不多﹐祖祖輩輩就守在這兒﹐替東邊古墓場裡的亡者看墳。" :),
			(: command, "say 外鄉人難得來咱這荒山野嶺。客官若是趕路累了﹐就在這碧幽亭歇上一宿﹐補些乾糧水酒﹐明兒個再走不遲。" :),
		}));
		return 1;
	}

	// 碧幽古墓石板（lore 引路，指向 chamber 的 stele）
	if( arg == "barman about 石板"
	||  arg == "barman about 古墓"
	||  arg == "barman about 碧幽古墓"
	||  arg == "barman about 丹方"
	||  arg == "barman about 配方"
	||  arg == "barman about stele" ) {
		do_chat(({
			(: command, "say 客官打聽那石板﹖嘿﹐看來客官是個懂煉丹的方士罷。墓底石室正壁上那方青石板﹐刻的是咱寨子守的那位墓主畢生嘔心刻下的丹方訣文——傳說盡是當世失傳的頂級丹方哩。" :),
			(: command, "say 要去看那石板﹐須自部落街南面那道石階下到墓道﹐再往下一進﹐便是墓心的石室了。墓裡陰寒森森﹐客官膽子若夠﹐自去看罷——只是莫要驚擾了那位墓主的清修。" :),
			(: command, "say 石板上的丹方訣文古奧難辨﹐聽寨裡老人說﹐須得 read 石板 細細抄寫﹐方能參透其中一二。客官造化如何﹐就看自個兒的本事了。" :),
		}));
		return 1;
	}

	return notify_fail("酒保憨憨一笑﹕客官問的這個﹐小的山裡人﹐可答不上來。先喝碗苦茶罷。\n");
}

int accept_fight(object ob)
{
	do_chat("酒保嚇得縮起脖子賠笑﹕客官息怒﹗小的這就給您篩碗熱酒賠罪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
