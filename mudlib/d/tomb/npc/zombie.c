// zombie.c -- 殭屍，古墓墓道/地宮間久殮不腐、受陰煞所役的亡靈，古墓亡靈獵場的
//             中堅對手。
//
// 結構沿用 /d/heifeng/npc/greywolf.c（承 /d/snow/npc/rabbit.c）：可 kill、會還
// 手、不主動攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給 score(無錢)。戰力
// 定在 level 145 一線，與古墳墓(taoism-cloud lv150 落點)的高階獵場相稱。
//
// 亡靈標記（呼應 docs 茅山幽冥三箭「對殭屍鬼魂傷害更高」）：
//   * set("life_form","undead")：mudlib 既有的「僵屍」生命型態。combat.c 的傷害
//     switch 中 "undead" 落入 default(==living) 分支，故【照常可被一般玩家獵殺】、
//     不臆造任何傷害公式（life_form "ghost" 才會在 absorb() 吸收一切攻擊而打不死，
//     故【不】用於可獵的亡靈，見 std/feature/char/combat.c::absorb）。
//   * set("undead",1)：純標記旗標，供日後茅山幽冥三箭(youmin/mao-shan-sword)等
//     daemon 偵測「殭屍鬼魂」以加成克制之用。本檔【不】實作傷害加成（無現成機制，
//     依任務鐵則不臆造公式）。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("殭屍", ({ "zombie", "jiangshi", "corpse" }) );
	// 根骨深厚、皮肉如鐵：con 高、形體上限厚，耐戰耐打；身手卻僵直遲緩(dex 低)。
	set_attr("con", 62);
	set_attr("str", 55);
	set_attr("dex", 18);
	set_race("human");
	set_class("commoner");
	set_level(145);

	// 久殮不腐之屍：枯爪奇硬如鐵(unarmed 高)、皮糙肉厚耐打(parry 高)；然動作僵
	// 直遲緩、不諳閃躲(dodge 極低)，陰煞所役、內力中平。
	set_skill("unarmed", 165);
	set_skill("dodge", 40);
	set_skill("parry", 150);
	set_skill("force", 130);

	// 厚其氣血，使之耐打、有來有往（鏡 greywolf advance_stat 之法，量加重）。
	advance_stat("kee", 220);

	// 亡靈生命型態 + 標記（見檔頭）：照常可被一般玩家獵殺，僅供幽冥三箭日後克制。
	set("life_form", "undead");
	set("undead", 1);

	set("age", 0);
	set("gender", "none");
	set("long",
		"一具久殮不腐的殭屍。牠皮肉青黑乾癟﹐緊緊貼著嶙峋的枯骨﹐\n"
		"殮衣早已朽爛成縷縷敗絮。空洞的眼眶裡沒有半點神光﹐口角卻\n"
		"汩汩滲著黑黃的屍水﹐渾身透出一股化不開的陰腐屍氣。牠受著\n"
		"這墓中陰煞所役﹐動作雖僵直遲緩﹐一雙枯爪卻奇硬如鐵﹐正循\n"
		"著生人的氣息﹐踉踉蹌蹌地朝你直撲過來。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 2400,
		"unarmed mastery" : 360,
		"martial art"     : 240,
		"martial mastery" : 120,
		"combat"          : 110,
	]));
	setup();
}

// 奉陪到底、凶悍反擊（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 殭屍喉間滾出一聲嘶啞的低吼﹐雙臂僵直地探出﹐枯爪如鐵﹐踉蹌撲來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
