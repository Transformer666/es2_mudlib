// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("康平守衛", ({"guard"}));
    set_attr("str", 16);
    set_attr("dex", 14);
    set_attr("con", 15);
    set_attr("int", 10);
    set_attr("spi", 10);
    set_attr("wis", 10);
    set_race("human");
    set_class("soldier");
    set_level(12);
    set_skill("blade", 35);
    set_skill("parry", 25);
    set_skill("dodge", 20);
    set("age", 28);
    set("gender", "male");
    set("long", "一名康平鎮的守衛，正警覺地守在入口處。\n");
    setup();
    carry_object("/obj/area/obj/blade")->wield();
    carry_object("/obj/area/obj/armor")->wear();
}
