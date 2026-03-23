// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
	set_name("混沌獸", ({"hundunshou", "chaos beast", "hundun"}));
	set_attr("str", 40);
	set_attr("con", 40);
	set_attr("dex", 20);
	set_attr("int", 15);
	set_attr("spi", 30);
	set_attr("wis", 10);
	set_race("human");
	set_class("commoner");
	set_level(80);
	advance_stat("gin", 350);
	advance_stat("kee", 350);
	advance_stat("sen", 350);

	set_skill("unarmed", 150);
	set_skill("dodge", 70);
	set_skill("parry", 60);
	set_skill("force", 120);

	set("age", 10000);
	set("gender", "male");
	set("long",
		"一頭形如巨犬的混沌之獸﹐渾身覆蓋著灰黑色的硬甲﹐似金非金\n"
		"﹐似石非石。牠沒有五官﹐卻能感知一切氣息。四隻粗壯的利爪深深\n"
		"嵌入地面﹐口中不斷噴出灰色的迷霧﹐令四周天地混沌一片。據說牠\n"
		"是太古時代的神獸﹐因觸犯天條而被封印於此。\n");
	set("attitude", "aggressive");
	set("chat_chance", 3);
	set("chat_msg", ({
		"混沌獸發出一聲低沉的嘶吼﹐大地為之震動。\n",
		"混沌獸周身散發的灰霧越來越濃﹐幾乎遮蔽了一切。\n",
		"混沌獸躁動不安﹐粗壯的利爪在地面上留下了深深的爪痕。\n",
	}));

	setup();

	add_temp("apply/attack", 120);
	add_temp("apply/defense", 100);
	add_temp("apply/damage", 90);
	add_temp("apply/armor", 120);
	set_temp("apply/vision_of_ghost", 1);
}
