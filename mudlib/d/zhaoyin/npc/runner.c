// runner.c -- 兆隱縣衙前當值的老捕快。
//             亦是非戰鬥調查支線「渾沌獸的蹤跡」三位線索人之一（官府視角）。
//
// 任務銜接（旗標皆存在玩家身上，支線由 /d/zhaoyin/npc/farmer.c 開啟）：
//   須先接任務 (quest/zhaoyin_chaos==1) ﹐ask runner about 渾沌獸 ->
//     老捕快道出衙門檔冊裡記過的目擊：那大物現過幾回、衙役遍尋不著﹐
//     見人不傷、像在躲甚麼。若這條線索未記過﹐則：
//       設 quest/zhaoyin_chaos_clue_runner = 1﹐並把 quest/zhaoyin_chaos_clues 計數 +1。
//   未接任務 / 已記過此線索 / 已完成支線：只作對應的閒談﹐不重複計數。
//
// 注意：本 NPC 不開啟任務、不領賞﹔開啟與領賞皆在 farmer.c。
//       線索純以對話交付（不交付任何物件）﹐計數只在確認未記過後才 +1﹐防重複。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("捕快", ({ "runner", "constable", "bushou" }) );
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 41);
	set("gender", "male");
	set("long",
		"一名兆隱縣衙的捕快﹐穿著件半舊的青色號褂﹐腰間斜插一\n"
		"根烏木水火棍。他這差事在這太平小縣清閒得很﹐一年到頭也\n"
		"拿不著幾個賊﹐成日價背著手在衙門前踱來踱去﹐連腰桿都站\n"
		"得鬆鬆垮垮的。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"捕快打了個長長的呵欠﹐伸著懶腰嘟囔﹕這日子﹐閒得骨頭都要鏽了。\n",
		"捕快按著腰刀慢悠悠地踱步﹐沒精打采地掃視著街面。\n",
		"捕快瞇眼瞧了瞧你﹐懶懶地道﹕生面孔啊﹖在咱兆隱縣﹐安分守己便好﹐莫要惹事。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player())
		&& this_player()->query("quest/zhaoyin_chaos") == 1
		&& !this_player()->query("quest/zhaoyin_chaos_clue_runner") )
		do_chat((: command,
			"say 生面孔﹐有事﹖也罷﹐這太平地界悶得很﹐有話便問罷。" :));
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "runner about 渾沌獸"
		&&   arg != "constable about 渾沌獸"
		&&   arg != "runner about 渾沌"
		&&   arg != "runner about 怪獸"
		&&   arg != "runner about 異獸"
		&&   arg != "runner about 線索"
		&&   arg != "runner about chaos beast"
		&&   arg != "runner about beast"
		&&   arg != "constable about beast") )
		return notify_fail("你想問這位捕快甚麼﹖（試試 ask runner about 渾沌獸）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("捕快正按著腰刀打著呵欠﹐沒空理你。\n");

	q = me->query("quest/zhaoyin_chaos");

	// 未接任務：裝糊塗，順道把人引向井邊的老農
	if( q < 1 ) {
		do_chat((: command,
			"say 渾沌獸﹖那等山野怪談﹐你去井邊問那幾個說古的老農罷﹐衙門可不管這些。" :));
		return 1;
	}

	// 已記過此線索（或支線已完成）：只重述，不再計數
	if( q >= 2 || me->query("quest/zhaoyin_chaos_clue_runner") ) {
		do_chat((: command,
			"say 檔冊裡記的那幾筆﹐我方才不都說與你了麼﹖橫豎是遍尋不著、見人就躲的怪物罷了。" :));
		return 1;
	}

	// 任務進行中、此線索未記過：道出官府視角的目擊，記下線索並計數 +1
	do_chat(({
		(: command, "say 你也為那物事來的﹖唉﹐這兩年衙門檔冊裡﹐確是記過幾筆古怪的目擊——說山裡頭有頭黑霧裹身的大物﹐沒眉沒眼﹐忽隱忽現。" :),
		(: command, "say 縣太爺起初只當是刁民謠言﹐後來見報的人多了﹐才差我們進山查過幾回。怪就怪在——那物事見了衙役也不撲不咬﹐遠遠一瞧見人﹐反倒慌慌張張地竄沒了﹐尋它的蹤跡更是難如登天。" :),
		(: command, "say 依我這當差多年的眼光看哪﹐它不像是來尋釁的﹐倒像是自個兒在躲甚麼、避甚麼——你問我躲的是甚麼﹖嘿﹐這就不是咱這小縣衙查得明白的了。" :),
	}));
	// 線索確實道出後才記旗標、計數（先確認上面未記過，故此處不會重複加）
	me->set("quest/zhaoyin_chaos_clue_runner", 1);
	me->set("quest/zhaoyin_chaos_clues",
		me->query("quest/zhaoyin_chaos_clues") + 1);
	return 1;
}

int accept_fight(object ob)
{
	do_chat("捕快這才來了精神﹐抽出水火棍喝道﹕反了你了﹗光天化日竟敢在縣衙門前撒野﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
