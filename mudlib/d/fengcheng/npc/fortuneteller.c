// fortuneteller.c -- 神算子﹐風城廣場的算命先生（目前純風味互動）
//
// 設定來源（docs/01-世界觀與劇情/04-地圖與場景.md）：
//   風城地標「神算子」﹐算命師收 1 兩銀子﹐算「練是否滿」（天賦根器是否練到頂）。
//
// 目前狀態：純風味。`算命` 指令只給氣氛化的批命﹐不收錢、不真的判讀天賦。
// TODO: 接上真正的天賦/練滿判讀機制——
//   1. 先確認玩家身上有 1 兩銀子（/obj/money/silver﹐100 文 = 1 兩）並扣除。
//   2. 以 query_skill() 逐項比對玩家各項技能是否已達該天賦/根器的上限，
//      回報「某某技藝已臻化境」或「尚有精進餘地」。
//   （需先重建 daemon/skill 與天賦上限定義後方能實作﹐見 CLAUDE.md 鐵則 5。）

#include <npc.h>

inherit F_VILLAGER;

int do_divine(string arg);

void create()
{
	set_name("神算子", ({ "fortuneteller", "fortune teller", "shensuanzi" }) );
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 63);
	set("gender", "male");
	set("long",
		"這位便是風城遠近聞名的算命先生「神算子」。他生得仙風道\n"
		"骨﹐一部花白的長鬚垂在胸前﹐頭戴一頂舊葛巾﹐身著洗得發白\n"
		"的青布道袍﹐一雙眼睛半開半闔﹐卻彷彿能看透人的窮通禍福。\n"
		"據說他鐵口直斷﹐連你天賦根器練到了幾分﹐他都算得出來。\n"
		"你或許可以請他算上一卦﹕算命 (或 divine)。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"神算子閉目掐指﹐口中念念有詞﹐似在推演甚麼玄機。\n",
		"神算子捻著長鬚﹐淡淡道﹕施主印堂發亮﹐近日想必有番際遇。\n",
		"神算子睜眼一笑道﹕窮通禍福皆有定數﹐施主若有疑惑﹐不妨請老朽算上一卦。\n",
		"神算子悠悠道﹕天賦根器各有高下﹐練到幾分火候﹐老朽一算便知﹐只取紋銀一兩。\n",
	}));
	setup();
	carry_money("coin", 100);
}

void init()
{
	::init();
	// 中文動詞「算命」為設定上的主指令；但全 mudlib 僅此一處用中文 verb﹐
	// driver parser 對多位元組 verb 的支援未驗證﹐故另加 ASCII 別名 divine 作後備。
	add_action("do_divine", "算命");
	add_action("do_divine", "divine");
}

int do_divine(string arg)
{
	object me = this_player();

	if( !me || !interactive(me) ) return 0;

	if( is_fighting() || is_chatting() )
		return notify_fail("神算子正忙著﹐你且稍候片刻。\n");

	// TODO: 真正的機制應在此收取 1 兩銀子並以 query_skill() 判讀天賦/練滿狀況。
	//       目前僅作風味批命﹐不收費、不判讀。
	do_chat(({
		"神算子拈起三枚銅錢﹐拋擲在青布上﹐俯身細看了片刻。\n",
		(: command, "say 施主且聽老朽一言——你天賦根器尚有可塑之機﹐勤加磨練﹐他日必成大器。" :),
		(: command, "say 只是這真正的玄機﹐須得老朽掐算良久方能道破﹐施主來日再來罷。" :),
	}));
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹐天機不可洩漏﹐動手更是大大的不該﹗施主息怒、息怒﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
