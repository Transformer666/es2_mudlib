// fieldrat.c -- 田鼠，康平村外荒塘窪地草根下成群打洞的肥鼠，數量眾多、皮糙耐打。
//
// 結構沿用 /d/heifeng/npc/greywolf.c（承 /d/hudao/wild/npc/madwolf.c）：可 kill、
// 會還手、不主動攻擊路人(無 attitude)，殺後只給 score(無錢)。戰力定在 level 12
// 一線——是康平獵場的入門對手，新手練手用。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("田鼠", ({ "field rat", "fieldrat", "rat", "tianshu" }) );
	set_attr("con", 18);
	set_attr("str", 14);
	set_attr("dex", 22);
	set_race("human");
	set_class("commoner");
	set_level(12);

	// 撕咬、亂竄、閃躲俱靈，內力低微。
	set_skill("unarmed", 18);
	set_skill("dodge", 22);
	set_skill("parry", 12);
	set_skill("force", 8);

	set("age", 1);
	set("gender", "male");
	set("long",
		"一隻養得溜圓的塘窪田鼠﹐通體灰褐﹐拖著一條肥短的尾巴﹐一雙\n"
		"豆大的黑眼睛滴溜溜地亂轉。牠成日在草根底下掏洞做窠﹐啃食村\n"
		"裡的穀子﹐吃得膘肥體壯﹐是莊稼人恨極了的害物。見了生人也不\n"
		"甚怕﹐齜著兩排黃牙吱吱怪叫﹐逼急了竟會回身撲咬。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 90,
		"unarmed mastery" : 26,
		"martial art"     : 18,
		"martial mastery" : 10,
		"combat"          : 12,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；起手凶悍回身。
int accept_fight(object ob)
{
	do_chat((: command, "say 田鼠吱吱怪叫一聲﹐弓起背脊﹐齜著黃牙回身撲咬﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
