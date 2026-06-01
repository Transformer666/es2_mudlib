// direwolf.c -- 獨眼惡狼，盤踞武陵古道旁血徑的孤狼，近月來屢屢撲噬過往的
//              行旅客商，是水嵐武陵自成一套的戰鬥支線「武陵狼患」的剿除目標。
//
// 結構沿用 /d/hudao/wild/npc/madwolf.c（承 /d/snow/npc/rabbit.c）：可 kill、
// 會還手、不主動攻擊路人（無 attitude，由玩家 kill 起釁）﹐殺後給 score(bounty)。
// 戰力定在 level 12 一線——較瘋狼(16)、黑熊(20)為弱﹐是「備妥兵刃、稍有火候」
// 的玩家堂堂正正打得過的公平對手（combat 修復後可勝）。
//
// 任務鉤子（die()）：惡狼伏誅時﹐由 last_damage_giver()(下手者)取得殺手﹐
//   若為真實玩家(userp)﹐便在其身上記 quest/wuling_menace_slain = 1（剿除憑證﹐
//   給貨郎驗看領賞用）。本鉤子只設這一面自成一套的旗標﹐不碰 main_omen 等他線。
//   末了恒呼 ::die()（屍體/bounty/善後悉依 std/char/npc.c::die()﹐bounty 一併
//   結算給下手者）。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("獨眼惡狼", ({ "dire wolf", "direwolf", "wolf", "duyan elang" }) );
	set("nickname", "獨眼");
	// 根骨 18 → 形體上限約 90 點，又快又凶，卻不及瘋狼(con24)、黑熊(con30)
	// 那般難纏——備妥兵刃、稍有火候的玩家可堂堂正正勝之。
	set_attr("con", 18);
	set_attr("str", 17);
	set_attr("dex", 18);
	set_race("human");
	set_class("commoner");
	set_level(12);

	// 撕咬迅捷、略諳閃拆，內力中平：是一場公平而有來有往的惡鬥。
	set_skill("unarmed", 20);
	set_skill("dodge", 18);
	set_skill("parry", 14);
	set_skill("force", 16);

	set("age", 4);
	set("gender", "male");
	set("long",
		"一頭脊毛賁張的青灰巨狼﹐左眼是一道猙獰的舊疤﹐空陷著早\n"
		"瞎了的眼眶﹐只剩右眼幽幽地泛著凶光。牠瘦長精悍﹐筋健如\n"
		"鐵﹐口角垂著涎沫﹐齒間還沾著暗褐的舊血。近月來牠盤踞在這\n"
		"血徑上﹐專一撲噬落單的行旅客商﹐攪得武陵古道人心惶惶﹐連\n"
		"鎮上趕路的客人都不敢輕易出山了。牠喉間滾出一聲低沉的威\n"
		"嗥﹐那僅剩的一隻獨眼﹐死死地盯住了你。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、實戰經驗。無錢幣(carry_money)。
	set("bounty", ([
		"survive"         : 110,
		"unarmed mastery" : 30,
		"martial art"     : 22,
		"combat"          : 14,
	]));
	setup();
}

// 死亡：記剿除憑證旗標於下手者身上（防無下手者 / 自戕誤記）﹐末了恒呼 ::die()。
void die()
{
	object killer;

	killer = last_damage_giver();

	// 下手者須為真實玩家（userp），方記剿除憑證。重複記 1 無妨（領賞那端防重複）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer) )
		killer->set("quest/wuling_menace_slain", 1);

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼﹐不可略）。
	::die();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 獨眼惡狼喉間滾出一聲淒厲的長嗥﹐弓背豎毛﹐獠牙森森地撲了上來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
