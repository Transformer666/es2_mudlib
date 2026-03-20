// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("小販", ({"peddler"}));
    set_attr("str", 12);
    set_attr("dex", 12);
    set_attr("con", 12);
    set_attr("int", 10);
    set_attr("spi", 10);
    set_attr("wis", 10);
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("age", 30);
    set("gender", "male");
    set("long", "一個在後街叫賣的小販，看起來精明幹練。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "小販吆喝道：便宜賣了！走過路過不要錯過！\n",
        "小販四處張望，尋找著可能的顧客。\n",
    }));
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}
