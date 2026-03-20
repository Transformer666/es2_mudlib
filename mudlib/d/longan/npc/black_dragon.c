// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("黑龍", ({"black dragon", "dragon"}));
    set_attr("str", 35);
    set_attr("con", 38);
    set_attr("dex", 25);
    set_attr("int", 20);
    set_attr("spi", 25);
    set_attr("wis", 18);
    set_race("human");
    set_class("commoner");
    set_level(65);
    advance_stat("gin", 250);
    advance_stat("kee", 250);
    advance_stat("sen", 250);

    set_skill("unarmed", 120);
    set_skill("dodge", 80);
    set_skill("parry", 70);
    set_skill("force", 90);

    set("age", 2000);
    set("gender", "male");
    set("long", "一條漆黑如墨的巨龍盤踞在湖底洞穴之中，龍鱗閃爍著幽暗的光芒，一雙血紅的眼睛死死盯著你。\n");
    set("chat_chance", 5);
    set("chat_msg", ({"黑龍發出震耳欲聾的咆哮，洞穴為之震動。\n", "黑龍緩緩蜷動著龐大的身軀，漆黑的龍鱗發出嘎嘎聲響。\n"}));

    setup();

    add_temp("apply/attack", 80);
    add_temp("apply/defense", 80);
    add_temp("apply/damage", 60);
    add_temp("apply/armor", 80);
}
