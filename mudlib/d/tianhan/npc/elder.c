// NPC: /d/tianhan/npc/elder.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("村長", ({"elder", "village elder"}));
    set_attr("str", 12);
    set_attr("dex", 10);
    set_attr("con", 14);
    set_attr("int", 16);
    set_attr("spi", 14);
    set_race("human");
    set_class("commoner");
    set_level(15);

    set_skill("staff", 40);
    set_skill("parry", 30);

    set("age", 68);
    set("gender", "male");
    set("long",
        "一位鬚髮皆白的老者，身穿一件洗得發白的棉襖，腰間繫著\n"
        "一條粗布腰帶。他雖然年邁，但精神矍鑠，一雙眼睛透著睿智\n"
        "的光芒。他是天寒村的村長，村裡大小事務都由他做主。\n");

    setup();
    carry_object(STOCK_WEAPON("staff"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
