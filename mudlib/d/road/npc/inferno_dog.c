// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("鬼獫", ({"inferno dog", "inferno_dog", "dog"}));
    set_attr("str", 22);
    set_attr("dex", 24);
    set_attr("con", 22);
    set_attr("int", 10);
    set_attr("spi", 16);
    set_race("human");
    set_class("commoner");
    set_level(35);
    set_skill("unarmed", 70);
    set_skill("dodge", 60);
    set("age", 500);
    set("gender", "male");
    set("attitude", "aggressive");
    set("long", "一隻渾身散發著灼熱氣息的火犬，牠的毛髮如同燃燒的火焰，週身團團熱氣，令人難以靠近。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "鬼獫噴出一道火焰。\n",
        "鬼獫低吼著，渾身的火焰更加旺盛。\n",
    }));
    setup();
}
