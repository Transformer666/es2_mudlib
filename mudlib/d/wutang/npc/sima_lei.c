// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("司馬雷", ({"sima_lei", "sima"}));
    set_attr("str", 26);
    set_attr("dex", 20);
    set_attr("con", 26);
    set_attr("int", 18);
    set_attr("spi", 18);
    set_attr("wis", 16);
    set_race("asura");
    set_class("commoner");
    set_level(50);

    set_skill("pike", 90);
    set_skill("parry", 70);
    set_skill("dodge", 60);
    set_skill("force", 60);

    set("age", 50);
    set("gender", "male");
    set("long", "司馬雷是「大漠八魔」中排行老七，原本是天朝的一名參將。"
        "他虎背熊腰，看起來約五十多歲，相當孔武有力。\n");
    setup();
    carry_object(STOCK_WEAPON("pike"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
