// yin_wuchang.c -- 黑風寨四頭目 殷無常（綽號「鬼影子」），黑風寨四頭目之一。
//
// 設定（依 docs/02-遊戲系統與機制/05-裝備與強化.md L184-186「黑風寨四頭目」掉裝副本）：
//   docs 僅具名大寨主閰狂風並列四件掉裝；本副本依「四頭目」之名補擬餘三位頭目並分屬其
//   餘三件。此「四頭目」殷無常乃黑風寨的智囊軍師﹐喜匿於後寨密室、運籌策劃﹐出手詭秘
//   如鬼影﹐慣使一柄淬毒匕首﹔他壓寨珍藏著一卷兵法奇書﹐故掉落 docs-named「杞庸兵書」
//   (/d/heifeng/npc/obj/qiyong_book.c，可 study 研讀)。
//
// 戰力定位（boss，lv 54，四頭目中身法詭秘、善暗算）：
//   * dex/int 偏高(軍師型)﹐技以 dagger/dodge 為主﹐advance_stat gin/sen 厚。
//   * accept_fight 回傳 1；「不」設 aggressive(由玩家 kill 起釁)。
//   * die() 鏡諸頭目慣式：::die() 後將簽名兵書(study book、非全服唯一)恒掉一件入屍。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

#define YIN_LOOT  "/d/heifeng/npc/obj/qiyong_book"   // 簽名掉落 杞庸兵書(study book、非 unique)

void die();
private void drop_signature(object who);

void create()
{
	set_name("殷無常", ({ "yin wuchang", "wuchang", "guiyingzi", "yin" }) );
	set("nickname", "鬼影子");
	set_attr("str", 24);
	set_attr("dex", 29);
	set_attr("int", 28);
	set_attr("wis", 26);
	set_attr("spi", 24);
	set_attr("cps", 25);
	set_attr("con", 24);
	set_attr("cor", 24);
	set_race("human");
	set_level(54);
	set_class("fighter");
	set("sect", "黑風寨");
	set("rank", "四頭目");

	// 軍師型：匕首詭秘、身法飄忽﹐善暗算偷襲。
	set_skill("unarmed", 120);
	set_skill("dagger", 160);
	set_skill("parry", 130);
	set_skill("dodge", 150);
	set_skill("force", 140);

	advance_stat("gin", 290);
	advance_stat("kee", 250);
	advance_stat("sen", 290);

	set("gender", "male");
	set("age", 41);
	set("long",
		"這便是黑風寨的四頭目、綽號「鬼影子」的殷無常。他生得清瘦\n"
		"陰沉﹐一襲玄色的緊身夜行衣裹著乾枯的身板﹐面如金紙﹐顴骨\n"
		"高聳﹐一雙三角眼半開半闔﹐眸底卻時時掠過一絲算計的精光。\n"
		"他是這黑風寨裡的智囊軍師﹐寨中大小劫案、設伏布局﹐多出自\n"
		"他的謀劃﹔平日深居後寨密室﹐青燈古卷﹐運籌帷幄。他出手詭\n"
		"秘如鬼影﹐一柄淬了毒的薄刃匕首藏在袖中﹐神出鬼沒﹐人未及\n"
		"防﹐冷刃已自背後而至——「鬼影子」三字﹐江湖上聞之無不齒\n"
		"冷。案頭那卷殘破的兵書﹐是他壓寨的珍藏。\n");
	set("chat_chance_combat", 3);
	set("chat_msg_combat", ({
		"殷無常身形一飄﹐如一縷鬼影般繞至側後﹐袖中淬毒匕首閃著幽幽的青芒﹗\n",
		"殷無常陰陰一笑﹕能尋到我這後寨密室﹐倒也算你有些本事——可惜，活不過今日了。\n",
		"殷無常匕首一抹﹐刃上的毒沫泛著詭異的青黑﹐專往要害刁鑽處招呼。\n",
	}));
	set("bounty", ([
		"survive"         : 1050,
		"dagger mastery"  : 200,
		"martial art"     : 150,
		"martial mastery" : 90,
		"combat"          : 90,
		"martial fame"    : 80,
		"reputation"      : 55,
	]));
	setup();
	carry_money("coin", 1800);
}

// boss：奉陪到底、兇悍反擊（不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 殷無常陰陰一笑﹕摸到我這後寨密室來的﹐還沒有一個能活著下山的。" :));
	return 1;
}

// 簽名掉落：下手者須為真實玩家；於 ::die() 之後呼叫，corpse 已生成於 temp("corpse")。
//   杞庸兵書屬 study book(可量產、非全服唯一)，故恒 new 一件入屍(不走 LOOT_D)。
private void drop_signature(object who)
{
	object corpse, loot;

	if( !objectp(who) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) ) return;

	loot = new(YIN_LOOT);
	if( !objectp(loot) ) return;
	if( !loot->move(corpse) ) loot->move(environment());

	message_vision(HIY
		"殷無常頹然倒地之際﹐懷中一卷以陳舊絹帛裝裱的書冊「啪」地滑落——封面蒼勁的篆字"
		"題著『杞庸兵書』四字﹐赫然便是這四頭目壓寨珍藏的兵法奇書﹗\n" NOR);
}

// 死亡：先 ::die()(屍體/bounty/善後悉依之﹐恒呼不可略﹐屍體於此生成並登錄 temp("corpse"))﹐
//   再於下手者為真實玩家時﹐自屍身遺落簽名兵書。
void die()
{
	object killer;

	killer = last_damage_giver();

	::die();

	if( objectp(killer) && killer != this_object() && userp(killer) )
		drop_signature(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
