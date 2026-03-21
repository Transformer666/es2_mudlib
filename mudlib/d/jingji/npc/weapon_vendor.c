// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("兵器商", ({"weapon vendor", "vendor"}));
    set_attr("str", 14);
    set_attr("dex", 14);
    set_attr("con", 14);
    set_attr("int", 14);
    set_attr("spi", 12);
    set_attr("wis", 12);
    set_race("human");
    set_class("commoner");
    set_level(15);
    set("age", 42);
    set("gender", "male");
    set("long", "一位精明的兵器商人，身後擺滿了各式各樣的兵器。\n");
    set("merchandise", ([
        "/obj/area/obj/blade" : 30,
        "/obj/area/obj/longsword" : 20,
        "/obj/area/obj/dagger" : 50,
    ]));
    setup();
    carry_money("silver", 100);
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}
