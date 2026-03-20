// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("大邪道人", ({"daxiedaoren", "daxie", "daoren"}));
	set_attr("str", 30);
	set_attr("dex", 28);
	set_attr("con", 28);
	set_attr("int", 26);
	set_attr("spi", 30);
	set_attr("wis", 24);
	set_race("human");
	set_class("commoner");
	set_level(75);
	advance_stat("gin", 280);
	advance_stat("kee", 280);
	advance_stat("sen", 280);

	set_skill("phantom sword", 140);
	set_skill("sword", 120);
	set_skill("dodge", 100);
	set_skill("parry", 90);
	set_skill("force", 110);

	set("age", 60);
	set("gender", "male");
	set("long",
		"大邪道人身穿一襲墨紫色的道袍﹐面容陰鬱而銳利﹐雙眼閃爍\n"
		"著令人不寒而慄的寒光。他是天邪派的前任掌門﹐因修煉禁術而\n"
		"走火入魔﹐如今行蹤飄忽﹐圖謀不軌﹐是武林中人人忌憚的大魔頭。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"大邪道人冷笑道：天下英雄﹐不過如此。\n",
		"大邪道人閉目運功﹐周身散發著一股陰寒的氣息。\n",
		"大邪道人緩緩睜開雙眼﹐目光如刀。\n",
	}));

	setup();

	add_temp("apply/attack", 100);
	add_temp("apply/defense", 80);
	add_temp("apply/damage", 80);
	add_temp("apply/armor", 60);

	carry_object(STOCK_WEAPON("longsword"))->wield();
	carry_object(STOCK_ARMOR("cloth"))->wear();
}
