// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("三掩守衛", ({"guard"}));
    set_attr("str", 17);
    set_attr("dex", 15);
    set_attr("con", 16);
    set_attr("int", 11);
    set_attr("spi", 11);
    set_attr("wis", 10);
    set_race("human");
    set_class("soldier");
    set_level(13);
    set_skill("blade", 38);
    set_skill("parry", 28);
    set_skill("dodge", 22);
    set("age", 29);
    set("gender", "male");
    set("long", "一名三掩鎮的守衛，正警惕地守在入口處。\n");
    setup();
    carry_object("/obj/area/obj/blade")->wield();
    carry_object("/obj/area/obj/armor")->wear();
}
