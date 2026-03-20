// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("路人", ({"passerby"}));
    set_attr("str", 12);
    set_attr("dex", 12);
    set_attr("con", 12);
    set_attr("int", 10);
    set_attr("spi", 10);
    set_attr("wis", 10);
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("age", 28);
    set("gender", "male");
    set("long", "一個匆匆趕路的路人，看起來正忙著自己的事。\n");
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}
