// wild_boar.c - 田間野豬（任務觸發生成）

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("野豬", ({"wild boar", "boar", "wild_boar"}));
	set_attr("str", 18);
	set_attr("con", 20);
	set_attr("dex", 12);
	set_race("animal");
	set_class("fighter");
	set_level(10);

	set_skill("unarmed", 50);
	set_skill("dodge", 30);

	set("age", 5);
	set("gender", "male");
	set("long",
		"一頭碩大的野豬﹐渾身灰黑色的粗毛﹐嘴裡長著兩根鋒利的獠\n"
		"牙。它的眼睛泛著紅光﹐鼻子不斷噴著粗氣﹐正在拱翻田裡的莊\n"
		"稼。看到有人靠近﹐它立刻露出凶狠的神色。\n");
	set("attitude", "aggressive");
	setup();
	carry_money("coin", 30);
}

void die(object killer)
{
	object tusk;

	if( killer && userp(killer)
	&&  killer->query_temp("pending/field_boar") == 1 ) {
		tusk = new(__DIR__"obj/boar_tusk");
		if( tusk ) {
			if( tusk->move(killer) )
				tell_object(killer, "你從野豬屍體上取下了一根獠牙。\n");
			else {
				tusk->move(environment());
				tell_object(killer, "一根野豬獠牙掉落在地上。\n");
			}
		}
		killer->set_temp("pending/field_boar", 2);
	}

	::die(killer);
}
