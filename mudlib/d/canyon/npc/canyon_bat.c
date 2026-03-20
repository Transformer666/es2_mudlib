// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("峽谷蝠", ({"canyon_bat", "bat"}));
    set_attr("str", 18);
    set_attr("dex", 26);
    set_attr("con", 16);
    set_attr("int", 6);
    set_attr("spi", 10);
    set_race("human");
    set_class("commoner");
    set_level(20);
    set_skill("unarmed", 50);
    set_skill("dodge", 60);
    set("age", 100);
    set("gender", "male");
    set("long",
        "一隻巨大的蝙蝠棲息在峽谷洞穴的天花板上，翼展超過一丈，\n"
        "渾身散發著腥臭的氣味。\n");
    set("chat_chance", 4);
    set("chat_msg", ({
        "峽谷蝠發出尖銳的叫聲，在洞穴中迴盪。\n",
    }));
    setup();
}
