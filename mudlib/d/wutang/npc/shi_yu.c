// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("施鈺", ({"shi_yu", "shi"}));
    set_attr("str", 20);
    set_attr("dex", 26);
    set_attr("con", 22);
    set_attr("int", 28);
    set_attr("spi", 24);
    set_attr("wis", 26);
    set_race("human");
    set_class("commoner");
    set_level(75);

    set_skill("sword", 90);
    set_skill("dodge", 85);
    set_skill("parry", 70);
    set_skill("force", 80);

    set("age", 40);
    set("gender", "male");
    set("long", "「鬼見愁」施鈺是「大漠八魔」之一。施鈺武功並不高，"
        "但不知從何處學到了極為高深的下毒之術，不論對手有多麼高強的武功"
        "都會莫名其妙的中了他下的毒。\n");
    setup();
    carry_object(STOCK_WEAPON("longsword"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    set_temp("apply/vision_of_ghost", 1);
}
