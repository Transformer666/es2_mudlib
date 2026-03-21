// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("天獒", ({"godly dog", "godly_dog", "dog"}));
    set_attr("str", 28);
    set_attr("dex", 22);
    set_attr("con", 26);
    set_attr("int", 14);
    set_attr("spi", 22);
    set_race("human");
    set_class("commoner");
    set_level(50);
    set_skill("unarmed", 95);
    set_skill("dodge", 60);
    set("age", 1000);
    set("gender", "male");
    set("long", "一隻身大如象的巨犬，全身覆蓋著金色長毛，如同一座移動的金色山丘。牠渾身散發著雷電之力，令人不敢輕視。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "天獒仰天長嘯，空中劈過一道閃電。\n",
        "天獒抖了抖金色的皮毛，四周響起噼啪的電光。\n",
    }));
    setup();
    set_temp("apply/vision_of_ghost", 1);
}
