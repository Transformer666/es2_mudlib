// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("採藥人", ({"herbalist"}));
    set_attr("str", 12);
    set_attr("dex", 12);
    set_attr("con", 12);
    set_attr("int", 14);
    set_attr("spi", 14);
    set_attr("wis", 14);
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("age", 50);
    set("gender", "male");
    set("long", "一個採藥人正在藥圃中仔細查看各種藥材。\n");
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}
