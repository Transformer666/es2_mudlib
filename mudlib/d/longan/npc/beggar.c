// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("乞丐", ({"beggar", "qigai"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 50);
	set("gender", "male");
	set("long",
		"一個衣衫襤褸的乞丐蜷縮在小巷的角落裡，骯髒的衣衫勉強遮\n"
		"蔽著他瘦骨嶙峋的身軀。儘管外表潦倒，他的雙眼卻銳利而警覺，\n"
		"彷彿這座城中發生的每一件秘密他都瞭若指掌。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"乞丐伸出枯瘦的手：行行好，賞口飯吃吧。\n",
		"乞丐壓低聲音自言自語：昨晚碼頭那邊可不太平啊……\n",
		"乞丐神秘兮兮地說：江湖上最近可有不少大事發生呢。\n",
	}));

	set_skill("unarmed", 10);
	set_skill("dodge", 15);

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 5);
}
