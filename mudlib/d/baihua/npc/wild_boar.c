// wild_boar.c - 偷吃西瓜的野豬 (quest: melon_pest)

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("野豬", ({"wild_boar", "boar", "wild boar"}));
	set_attr("str", 18);
	set_attr("con", 16);
	set_attr("dex", 12);
	set_race("animal");
	set_class("fighter");
	set_level(12);

	set_skill("unarmed", 50);
	set_skill("dodge", 30);

	set("age", 5);
	set("gender", "male");
	set("long",
		"一頭毛色灰黑的野豬﹐體型碩大﹐尖銳的獠牙從嘴邊伸出﹐鼻\n"
		"子上沾滿了泥土。牠正用蹄子刨著地面﹐發出粗重的鼻息聲﹐看\n"
		"起來脾氣暴躁得很。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"野豬用鼻子拱了拱地面﹐哼哼叫著。\n",
		"野豬警覺地豎起耳朵﹐四處張望。\n",
	}));
	set("attitude", "aggressive");
	setup();
}
