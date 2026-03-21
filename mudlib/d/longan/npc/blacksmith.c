// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("鐵匠", ({"blacksmith"}));
    set_attr("str", 16);
    set_attr("dex", 14);
    set_attr("con", 15);
    set_attr("int", 10);
    set_attr("spi", 10);
    set_attr("wis", 10);
    set_race("human");
    set_class("commoner");
    set_level(12);
    set("age", 45);
    set("gender", "male");
    set("long", "一個壯碩的鐵匠，手臂上滿是燙傷的疤痕，正在鍛造兵器。\n");
    set("merchandise", ([
        "/obj/area/obj/blade" : 30,
        "/obj/area/obj/longsword" : 20,
    ]));
    setup();
    carry_money("silver", 50);
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}
