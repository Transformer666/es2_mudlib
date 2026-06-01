// monger.c -- 走村串戶的賣貨郎，挑著貨擔在縣前街歇腳。
//             非戰鬥調查支線「渾沌獸的蹤跡」三位線索人之一（道聽途說、跨村比對視角）。
//
// 任務銜接（旗標皆存在玩家身上，支線由 /d/zhaoyin/npc/farmer.c 開啟）：
//   須先接任務 (quest/zhaoyin_chaos==1) ﹐ask monger about 渾沌獸 ->
//     賣貨郎道出他走遍鄰近村寨聽來的說法：那物事不只兆隱有﹐專往荒祠野廟、
//     斷壁殘垣這類沒人的荒處鑽﹐從沒聽說傷過誰。若這條線索未記過﹐則：
//       設 quest/zhaoyin_chaos_clue_monger = 1﹐並把 quest/zhaoyin_chaos_clues 計數 +1。
//   未接任務 / 已記過此線索 / 已完成支線：只作對應的閒談﹐不重複計數。
//
// 注意：本 NPC 不開啟任務、不領賞﹔開啟與領賞皆在 farmer.c。
//       線索純以對話交付（不交付任何物件）﹐計數只在確認未記過後才 +1﹐防重複。
//       本 NPC 不擺攤販售﹐ids 取「monger / huolang」﹐與市集那位 peddler 雜貨鋪老闆有別。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("賣貨郎", ({ "monger", "huolang", "pedlar" }) );
	set("nickname", "賣貨郎");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 48);
	set("gender", "male");
	set("long",
		"一個走村串戶的賣貨郎﹐挑著副吱呀作響的貨擔﹐擔上掛滿了\n"
		"針線、頂針、撥浪鼓、胭脂水粉之類的零碎雜貨﹐手裡還搖著\n"
		"個招客的撥浪鼓。他成年累月在這一帶的山村寨子間奔走﹐三\n"
		"教九流、東家長西家短、奇談異聞﹐肚裡裝得比誰都多。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"賣貨郎搖著撥浪鼓﹐扯著嗓子吆喝﹕針頭線腦﹐胭脂花粉﹐換糖換錢咧——\n",
		"賣貨郎放下貨擔捶了捶腰﹐笑道﹕走村串寨這許多年﹐甚麼新鮮事兒沒聽過。\n",
		"賣貨郎神祕兮兮地壓低嗓子﹕客官﹐這方圓百里的奇聞﹐問我可就問著啦。\n",
	}));
	setup();
	carry_money("coin", 60);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player())
		&& this_player()->query("quest/zhaoyin_chaos") == 1
		&& !this_player()->query("quest/zhaoyin_chaos_clue_monger") )
		do_chat((: command,
			"say 這位客官面生﹐想打聽點甚麼﹖儘管問﹐我這擔子走遍了四鄉八寨哩。" :));
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "monger about 渾沌獸"
		&&   arg != "pedlar about 渾沌獸"
		&&   arg != "monger about 渾沌"
		&&   arg != "monger about 怪獸"
		&&   arg != "monger about 異獸"
		&&   arg != "monger about 線索"
		&&   arg != "monger about chaos beast"
		&&   arg != "monger about beast"
		&&   arg != "pedlar about beast") )
		return notify_fail("你想問這位賣貨郎甚麼﹖（試試 ask monger about 渾沌獸）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("賣貨郎正搖著撥浪鼓招攬生意﹐沒空理你。\n");

	q = me->query("quest/zhaoyin_chaos");

	// 未接任務：含糊帶過，順道把人引向井邊的老農
	if( q < 1 ) {
		do_chat((: command,
			"say 渾沌獸﹖客官愛聽這些﹐去井邊尋那幾個閒著磕牙的老農罷。我還得趕著去下個寨子哩。" :));
		return 1;
	}

	// 已記過此線索（或支線已完成）：只重述，不再計數
	if( q >= 2 || me->query("quest/zhaoyin_chaos_clue_monger") ) {
		do_chat((: command,
			"say 我打各村聽來的那些﹐方才不都說與客官了麼﹖橫豎是個專愛往荒祠野廟鑽、卻從不傷人的怪物罷了。" :));
		return 1;
	}

	// 任務進行中、此線索未記過：道出跨村比對來的說法，記下線索並計數 +1
	do_chat(({
		(: command, "say 嘿﹐客官問著行家了﹗那物事可不單咱兆隱有。我這擔子走村串寨﹐打鄰縣好幾個寨子裡都聽人提過——黑霧裹身、沒眉沒眼的大物﹐東一處西一處地有人撞見。" :),
		(: command, "say 怪就怪在﹐各村的說法湊到一塊兒﹐倒像是一個調子﹕那物事專愛往沒人煙的去處鑽——斷了香火的荒祠、塌了半邊的野廟、人跡不到的亂石崗子﹐淨挑這些荒涼破敗的地界藏身。" :),
		(: command, "say 可走遍這許多村寨﹐我愣是沒聽說它傷過哪一個人、糟蹋過哪一畝田。客官你說﹐天底下哪有這樣的怪物﹖躲著人、揀著荒處待——倒像是它自個兒﹐也在沒命地躲著甚麼似的。" :),
	}));
	// 線索確實道出後才記旗標、計數（先確認上面未記過，故此處不會重複加）
	me->set("quest/zhaoyin_chaos_clue_monger", 1);
	me->set("quest/zhaoyin_chaos_clues",
		me->query("quest/zhaoyin_chaos_clues") + 1);
	return 1;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲客官﹗有話好說﹗我一個挑擔賣貨的﹐經不起這般唬嚇呀﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
