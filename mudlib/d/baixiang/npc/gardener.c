// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("園頭僧", ({"gardener", "monk", "yuantou"}));
	set_race("human");
	set_class("commoner");
	set_level(10);
	set_skill("unarmed", 20);

	set("age", 50);
	set("gender", "male");
	set("attitude", "peaceful");
	set("long",
		"一位年邁的僧人﹐皮膚被日曬得黝黑﹐雙手佈滿老繭。他正\n"
		"彎著腰仔細地修剪菩提樹的枝葉﹐動作輕柔而嫻熟﹐彷彿對\n"
		"待自己的孩子一般。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"園頭僧輕輕撫摸著一棵菩提樹的樹幹﹐喃喃自語。\n",
		"園頭僧說道﹕「這棵菩提樹已有百年﹐見證了多少僧人的悟道。」\n",
		"園頭僧蹲下身﹐小心翼翼地拔去花叢中的雜草。\n",
		"園頭僧說道﹕「草木有情﹐用心照料﹐它們自會回報你。」\n",
	}));
	set("refuse_fight", 1);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 15);
}
