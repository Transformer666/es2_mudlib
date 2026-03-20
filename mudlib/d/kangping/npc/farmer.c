// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("農夫", ({"farmer"}));
    set_attr("str", 14);
    set_attr("dex", 10);
    set_attr("con", 14);
    set_attr("int", 8);
    set_attr("spi", 10);
    set_attr("wis", 10);
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("age", 40);
    set("gender", "male");
    set("long", "一個皮膚黝黑的農夫，正扛著農具沿路走著。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "農夫擦了擦汗說道：今年的收成應該不錯。\n",
        "農夫抬頭看看天色：這天要是下場雨就好了。\n",
        "農夫嘟囔著：地裡的莊稼該施肥了。\n",
    }));
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}
