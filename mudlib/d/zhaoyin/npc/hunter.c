// hunter.c -- 兆隱城門邊歇腳的進山獵戶。
//             非戰鬥調查支線「渾沌獸的蹤跡」三位線索人之一（親歷目擊者視角）。
//
// 任務銜接（旗標皆存在玩家身上，支線由 /d/zhaoyin/npc/farmer.c 開啟）：
//   須先接任務 (quest/zhaoyin_chaos==1) ﹐ask hunter about 渾沌獸 ->
//     獵戶道出他親眼撞見那大物的情形：黑霧裹身、沒眉沒眼、見人不撲反逃。
//     若這條線索未記過﹐則：
//       設 quest/zhaoyin_chaos_clue_hunter = 1﹐並把 quest/zhaoyin_chaos_clues 計數 +1。
//   未接任務 / 已記過此線索 / 已完成支線：只作對應的閒談﹐不重複計數。
//
// 注意：本 NPC 不開啟任務、不領賞﹔開啟與領賞皆在 farmer.c。
//       線索純以對話交付（不交付任何物件）﹐計數只在確認未記過後才 +1﹐防重複。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("獵戶", ({ "hunter", "shanke", "huntsman" }) );
	set("nickname", "獵戶");
	set_race("human");
	set_class("commoner");
	set_level(7);

	set("age", 35);
	set("gender", "male");
	set("long",
		"一個精壯黝黑的進山獵戶﹐麻衣草鞋﹐背上斜挎一張舊獵弓﹐腰\n"
		"間別著柄解腕的尖刀。他剛打山裡出來﹐正蹲在城門邊歇腳飲水﹐\n"
		"褲腳沾著草汁泥點。瞧他眉頭緊鎖、時不時回頭望一眼那莽莽群\n"
		"山的神色﹐山裡頭像是有甚麼東西教他犯了怵。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"獵戶就著竹筒灌了口涼水﹐抹了把汗﹐眉頭卻一直沒鬆開。\n",
		"獵戶回頭望了一眼黑沉沉的山影﹐低聲嘟囔﹕這陣子的山﹐邪性 ...\n",
		"獵戶檢視著弓弦﹐悶聲道﹕近來進山﹐總覺著背後有甚麼在瞧著我。\n",
	}));
	setup();
	carry_money("coin", 25);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player())
		&& this_player()->query("quest/zhaoyin_chaos") == 1
		&& !this_player()->query("quest/zhaoyin_chaos_clue_hunter") )
		do_chat((: command,
			"say 這位客官也是來打聽山裡那樁邪事的﹖" :));
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "hunter about 渾沌獸"
		&&   arg != "huntsman about 渾沌獸"
		&&   arg != "hunter about 渾沌"
		&&   arg != "hunter about 怪獸"
		&&   arg != "hunter about 異獸"
		&&   arg != "hunter about 線索"
		&&   arg != "hunter about chaos beast"
		&&   arg != "hunter about beast"
		&&   arg != "huntsman about beast") )
		return notify_fail("你想問這位獵戶甚麼﹖（試試 ask hunter about 渾沌獸）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("獵戶正悶頭歇著腳﹐沒空理你。\n");

	q = me->query("quest/zhaoyin_chaos");

	// 未接任務：含糊帶過，順道把人引向井邊的老農
	if( q < 1 ) {
		do_chat((: command,
			"say 山裡的怪事﹖客官要聽古﹐去井邊尋那幾個老農﹐他們比我會說。我這趟還急著進城換些鹽米哩。" :));
		return 1;
	}

	// 已記過此線索（或支線已完成）：只重述，不再計數
	if( q >= 2 || me->query("quest/zhaoyin_chaos_clue_hunter") ) {
		do_chat((: command,
			"say 我撞見那物事的情形﹐方才不都對你說了麼﹖那黑霧裹身、見人就逃的怪模樣﹐我這輩子也忘不了。" :));
		return 1;
	}

	// 任務進行中、此線索未記過：道出親歷目擊，記下線索並計數 +1
	do_chat(({
		(: command, "say 你問著正主了——那物事﹐我前些日子在後山親眼撞見的﹗當時天剛擦黑﹐林子裡平白起了一團化不開的黑霧﹐裹著個比熊還大的影子﹐緩緩地挪。" :),
		(: command, "say 我嚇得連弓都忘了搭﹐定睛一瞧——那大物渾身上下竟沒眉沒眼﹐看不出個臉面來﹗我心一橫﹐想著拚了﹐誰知它一發覺我﹐非但不撲過來﹐反倒像受了驚似的﹐忽地化進黑霧裡﹐一陣風也似的竄沒了。" :),
		(: command, "say 你說怪不怪﹖那麼大個物事﹐見了我這獨個兒的獵戶﹐怕的倒像是它。我打了半輩子獵﹐山裡的虎豹豺狼見得多了﹐就沒見過這麼個——不傷人、只一個勁兒躲人的怪東西。" :),
	}));
	// 線索確實道出後才記旗標、計數（先確認上面未記過，故此處不會重複加）
	me->set("quest/zhaoyin_chaos_clue_hunter", 1);
	me->set("quest/zhaoyin_chaos_clues",
		me->query("quest/zhaoyin_chaos_clues") + 1);
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 客官這是做甚﹖我一個進山討生活的獵戶﹐與你無冤無仇﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
