// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("龍安守衛", ({"guard"}));
    set_attr("str", 18);
    set_attr("dex", 16);
    set_attr("con", 17);
    set_attr("int", 12);
    set_attr("spi", 12);
    set_attr("wis", 10);
    set_race("human");
    set_class("soldier");
    set_level(15);
    set_skill("blade", 40);
    set_skill("parry", 30);
    set_skill("dodge", 25);
    set("age", 30);
    set("gender", "male");
    set("long", "一名龍安城的守衛，負責在入口處巡邏。\n");
    setup();
    carry_object("/obj/area/obj/blade")->wield();
    carry_object("/obj/area/obj/armor")->wear();
}
