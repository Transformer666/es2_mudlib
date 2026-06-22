// ghost.c -- 鬼魂，古墓地宮裡含怨不散、凝氣為形的亡魂，古墓亡靈獵場巔峰之敵。
//
// 結構沿用 /d/heifeng/npc/greywolf.c（承 /d/snow/npc/rabbit.c）：可 kill、會還
// 手、不主動攻擊路人(無 attitude，由玩家 kill 起釁)，殺後只給 score(無錢)。戰力
// 定在 level 152 一線——較同墓的殭屍(lv145)更厲，是地宮獵場的巔峰對手。
//
// 亡靈標記（呼應 docs 茅山幽冥三箭「對殭屍鬼魂傷害更高」）：
//   * 【刻意不設】set("life_form","ghost")：combat.c::absorb 對 life_form=="ghost"
//     者會吸收一切攻擊的力道(「從身上穿透過去」)，一般玩家根本打不死——故【不】用
//     於可獵的亡靈，否則整個獵場無法獵殺。本鬼魂維持預設 life_form "living"，照常
//     可被一般玩家獵殺、不臆造任何傷害公式。
//   * set("undead",1)：純標記旗標，供日後茅山幽冥三箭(youmin/mao-shan-sword)等
//     daemon 偵測「殭屍鬼魂」以加成克制之用。本檔【不】實作傷害加成（無現成機制，
//     依任務鐵則不臆造公式）。其飄忽縹緲、難以捉摸之質以高 dodge 表現之。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("鬼魂", ({ "ghost", "guihun", "spirit", "wraith" }) );
	// 凝氣為形、虛無縹緲：con/str 中平不靠血肉，dex 奇高——飄忽不定、極難捉摸。
	set_attr("con", 44);
	set_attr("str", 40);
	set_attr("dex", 60);
	set_race("human");
	set_class("commoner");
	set_level(152);

	// 含怨厲鬼：身形飄忽縹緲(dodge 極高、最難命中)、陰氣攫人(unarmed 高)、拆招了
	// 得(parry 高)；不靠血肉之軀，全憑一股不散的怨煞陰氣(force 厚)。
	set_skill("unarmed", 185);
	set_skill("dodge", 205);
	set_skill("parry", 160);
	set_skill("force", 175);

	// 厚其陰煞、使之耐戰有來有往（鏡 greywolf advance_stat 之法，量加重；偏 sen/gin）。
	advance_stat("gin", 180);
	advance_stat("sen", 200);
	advance_stat("kee", 120);

	// 亡靈標記（見檔頭）：純供幽冥三箭日後克制；【不】設 life_form "ghost"(否則打不死)。
	set("undead", 1);

	set("age", 0);
	set("gender", "none");
	set("long",
		"一縷含怨不散的鬼魂。牠周身蒼白而半透明﹐依稀還是個人形﹐\n"
		"卻沒了下半身﹐只一團幽幽的陰氣裊裊地懸在半空﹐隨著墓底的\n"
		"陰風飄忽聚散﹐忽濃忽淡。牠那雙慘綠的眼睛深陷在模糊的面孔\n"
		"裡﹐死死盯住了闖入幽宅的生人﹐口中發出絲絲縷縷淒厲的悲\n"
		"嗥﹐縹緲的身形倏地一斂﹐已無聲無息地欺到了你的近前。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 2900,
		"unarmed mastery" : 420,
		"martial art"     : 280,
		"martial mastery" : 150,
		"combat"          : 130,
	]));
	setup();
}

// 奉陪到底、淒厲反撲（牠並不主動撲路人﹐由玩家 kill 起釁）。
int accept_fight(object ob)
{
	do_chat((: command, "say 鬼魂發出一聲淒厲的悲嗥﹐縹緲的身形倏地一斂﹐挾著刺骨的陰氣撲了上來﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
