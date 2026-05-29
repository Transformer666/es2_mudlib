// sunbird.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("太陽鳥", ({ "sunbird", "sun bird", "bird" }) );
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 0);
	set("gender", "無性");
	set("long",
		"這是棲在京畿神社神龕上的太陽鳥﹐相傳是日神的化身。牠生\n"
		"著三足金喙﹐一身火紅的羽翼上嵌著細碎的金芒﹐振翅之際彷彿\n"
		"有暖融融的日光自羽間流瀉而出﹐叫人望之而生敬畏之心。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"太陽鳥輕輕舒展火紅的羽翼﹐一層暖融融的金芒在殿中流轉。\n",
		"太陽鳥昂首發出一聲清越的長鳴﹐殿內的香煙竟隨之裊裊盤旋而上。\n",
		"太陽鳥金喙微啟﹐一雙眼睛靜靜地凝視著前來上香的香客﹐似有所悟。\n",
	}));
	set("no_get", 1);
	setup();
}

int accept_fight(object ob)
{
	do_chat("太陽鳥振翅騰起﹐周身金芒大盛﹐一股莊嚴之氣令人不敢造次。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
