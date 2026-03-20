// zombie.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("殭屍", ({"zombie", "undead"}));
	set_attr("str", 24);
	set_attr("con", 26);
	set_attr("dex", 8);
	set_race("undead");
	set_class("fighter");
	set_level(20);

	set_skill("unarmed", 70);
	set_skill("parry", 40);

	set("age", 200);
	set("long",
		"一具從墳墓中爬出來的殭屍﹐全身皮膚呈暗灰色﹐已經開始腐\n"
		"爛﹐散發著令人作嘔的惡臭。它的雙眼空洞無神﹐嘴裡露出發黑的\n"
		"牙齒﹐四肢僵硬﹐行動遲緩但力量驚人。\n");
	set("attitude", "aggressive");
	setup();
	carry_money("coin", 80);
}
