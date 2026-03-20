// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("白無常", ({"white_agent", "white", "baiwuchang"}));
	set_attr("str", 25);
	set_attr("dex", 28);
	set_attr("con", 24);
	set_attr("int", 24);
	set_attr("spi", 32);
	set_attr("wis", 26);
	set_race("malik");
	set_class("commoner");
	set_level(80);

	set_skill("sword", 120);
	set_skill("dodge", 100);
	set_skill("parry", 90);
	set_skill("force", 100);

	set("age", 5320);
	set("gender", "male");
	set("long",
		"白無常屬於巫首族﹐他負責將因戰亂和意外而喪生的人的靈魂\n"
		"引去接受閻王的審判。他看起來膽識過人﹐一副天不怕地不怕的\n"
		"模樣。\n");

	set("chat_chance", 3);
	set("chat_msg", ({
		"白無常輕聲道﹕迷途的亡魂﹐隨我來吧。\n",
		"白無常的白袍在無風中飄動﹐周圍的溫度驟然下降。\n",
		"白無常嘆息道﹕生死有命﹐莫要執著於塵世。\n",
	}));

	setup();
	carry_object(STOCK_WEAPON("sword"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
