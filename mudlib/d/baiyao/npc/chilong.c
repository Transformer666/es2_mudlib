// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("赤龍", ({"chilong", "red dragon", "dragon"}));
	set_attr("str", 38);
	set_attr("con", 35);
	set_attr("dex", 22);
	set_attr("int", 18);
	set_attr("spi", 28);
	set_attr("wis", 16);
	set_race("dragon");
	set_class("commoner");
	set_level(70);
	advance_stat("gin", 300);
	advance_stat("kee", 300);
	advance_stat("sen", 300);

	set_skill("unarmed", 130);
	set_skill("dodge", 75);
	set_skill("parry", 65);
	set_skill("force", 100);

	set("attitude", "aggressive");
	set("age", 3000);
	set("gender", "male");
	set("long",
		"一條通體赤紅的巨龍蟠踞在血潭之中﹐龍鱗如烈焰般灼灼生輝﹐\n"
		"一雙金黃色的龍眼透著遠古的威嚴。牠的身軀龐大無比﹐每一片龍鱗\n"
		"都散發著灼人的熱氣﹐令四周的岩壁都隱隱泛紅。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"赤龍發出低沉的龍吟﹐洞穴中迴盪著震耳的回聲。\n",
		"赤龍緩緩睜開金瞳﹐灼熱的龍息從鼻孔中噴出。\n",
		"赤龍不耐煩地擺動著尾巴﹐掀起一陣滾燙的氣浪。\n",
	}));

	setup();

	add_temp("apply/attack", 90);
	add_temp("apply/defense", 90);
	add_temp("apply/damage", 70);
	add_temp("apply/armor", 90);
	set_temp("apply/vision_of_ghost", 1);
}
