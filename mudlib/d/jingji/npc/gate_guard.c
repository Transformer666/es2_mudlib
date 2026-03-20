// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("城門守衛", ({"gate guard", "guard"}));
    set_attr("str", 20);
    set_attr("dex", 18);
    set_attr("con", 18);
    set_attr("int", 12);
    set_attr("spi", 12);
    set_attr("wis", 10);
    set_race("human");
    set_class("soldier");
    set_level(18);
    set_skill("blade", 50);
    set_skill("parry", 35);
    set_skill("dodge", 30);
    set("age", 32);
    set("gender", "male");
    set("long", "京畿重地，守衛格外嚴格，這名城門守衛目光如炬地盯著每一個過往行人。\n");
    setup();
    carry_object("/obj/area/obj/blade")->wield();
    carry_object("/obj/area/obj/armor")->wear();
}
