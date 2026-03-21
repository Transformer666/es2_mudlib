// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("兵器鋪老闆", ({"weapon vendor", "vendor"}));
    set_attr("str", 14);
    set_attr("dex", 12);
    set_attr("con", 13);
    set_attr("int", 12);
    set_attr("spi", 10);
    set_attr("wis", 10);
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("age", 48);
    set("gender", "male");
    set("long", "兵器鋪的老闆，一臉精明的樣子，正在擦拭著兵器架上的刀劍。\n");
    set("merchandise", ([
        "/obj/area/obj/blade" : 30,
        "/obj/area/obj/dagger" : 40,
    ]));
    setup();
    carry_money("silver", 50);
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}
