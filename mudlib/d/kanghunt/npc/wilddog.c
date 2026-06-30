// wilddog.c -- 野狗，康平村外荒塘窪地裡無人看管、結伙覓食的瘦野狗。
//
// 結構沿用 /d/heifeng/npc/greywolf.c：可 kill、會還手、不主動攻擊路人(無 attitude)，
// 殺後只給 score(無錢)。戰力定在 level 16 一線——較田鼠(12)硬，是康平獵場的中段對手。

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("野狗", ({ "wild dog", "wilddog", "dog", "yegou" }) );
	set_attr("con", 24);
	set_attr("str", 24);
	set_attr("dex", 20);
	set_race("human");
	set_class("commoner");
	set_level(16);

	// 撲咬有力、閃竄迅捷、略諳拆招，內力低平。
	set_skill("unarmed", 28);
	set_skill("dodge", 20);
	set_skill("parry", 18);
	set_skill("force", 14);

	set("age", 3);
	set("gender", "male");
	set("long",
		"一條無人看管的瘦野狗﹐黃毛糾結著塘泥﹐肋骨根根可數﹐眼裡卻\n"
		"閃著餓綠的凶光。牠在這片荒塘窪地裡覓食討活﹐慣與同類結伙﹐\n"
		"逮著田鼠蛤蟆便撕咬分食﹐見了落單的生人﹐也未必不敢上前。牠\n"
		"低伏著身子﹐喉間滾出一串嗚嗚的低吼﹐齜出一口尖利的犬牙。\n");
	// 純 score：江湖歷練(升級)、拳腳精熟、武術造詣、武學之道、實戰經驗。無錢幣。
	set("bounty", ([
		"survive"         : 160,
		"unarmed mastery" : 44,
		"martial art"     : 30,
		"martial mastery" : 16,
		"combat"          : 20,
	]));
	setup();
}

// 不主動撲路人﹐由玩家 kill 起釁；凶悍反撲。
int accept_fight(object ob)
{
	do_chat((: command, "say 野狗喉間滾出一串嗚嗚低吼﹐低伏身子﹐齜牙疾撲而上﹗" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
