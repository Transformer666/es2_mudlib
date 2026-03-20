// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("錢莊護衛", ({"bank guard", "guard"}));
    set_attr("str", 20);
    set_attr("dex", 18);
    set_attr("con", 18);
    set_attr("int", 12);
    set_attr("spi", 12);
    set_attr("wis", 10);
    set_race("human");
    set_class("soldier");
    set_level(20);
    set_skill("blade", 55);
    set_skill("parry", 40);
    set_skill("dodge", 35);
    set("age", 35);
    set("gender", "male");
    set("long", "錢莊的護衛，身材魁梧，目光銳利，讓人不敢輕易造次。\n");
    setup();
    carry_object("/obj/area/obj/blade")->wield();
    carry_object("/obj/area/obj/armor")->wear();
}
