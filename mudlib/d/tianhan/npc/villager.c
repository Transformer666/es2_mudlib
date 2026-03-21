// NPC: /d/tianhan/npc/villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("莊稼漢", ({"villager", "farmer"}));
    set_attr("str", 16);
    set_attr("dex", 12);
    set_attr("con", 18);
    set_attr("int", 8);
    set_attr("spi", 8);
    set_race("human");
    set_class("commoner");
    set_level(6);

    set_skill("unarmed", 20);

    set("age", 35);
    set("gender", "male");
    set("long",
        "一個皮膚黝黑、身材魁梧的莊稼漢，雙手滿是老繭，一看就\n"
        "是常年勞作的人。他正在空地上揮舞著木棍，笨拙地練著幾招\n"
        "防身的功夫。\n");

    setup();
    carry_object(STOCK_WEAPON("staff"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
