// NPC: /d/fengcheng/npc/vendor.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("雜貨掌櫃", ({"vendor", "shopkeeper"}));
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 50);
    set("gender", "male");
    set("long",
        "一個精明的中年漢子﹐滿臉堆笑地招呼著客人。他的貨架上\n"
        "擺滿了各種日用品和北地特產。你可以用 list 看看﹐用 buy 來買。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "雜貨掌櫃說道﹕客倌﹐看看有什麼需要的﹖都是好東西﹗\n",
        "雜貨掌櫃整理著貨架上的貨物。\n",
    }));
    set("merchandise", ([
        STOCK_WEAPON("shortblade") : 120,
        STOCK_ARMOR("cloth") : 80,
    ]));

    setup();
    carry_money("coin", 500);
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
    do_chat("雜貨掌櫃嚇得連連後退﹐大喊救命。\n");
    return 0;
}
