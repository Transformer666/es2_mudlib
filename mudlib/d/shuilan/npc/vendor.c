// NPC: /d/shuilan/npc/vendor.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("南貨掌櫃", ({"vendor", "shopkeeper"}));
    set_race("human");
    set_class("commoner");
    set_level(4);

    set("age", 60);
    set("gender", "male");
    set("long",
        "一個瘦小的老頭﹐說話慢條斯理﹐但眼神精明。他的店裡\n"
        "擺滿了南方的特產。你可以用 list 看看﹐用 buy 來買。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "南貨掌櫃慢悠悠地說道﹕慢慢看﹐不急不急。\n",
        "南貨掌櫃整理著貨架上的貨物﹐動作不緊不慢。\n",
    }));
    set("merchandise", ([
        STOCK_WEAPON("shortblade") : 100,
        STOCK_ARMOR("cloth") : 70,
    ]));

    setup();
    carry_money("coin", 400);
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
    do_chat("南貨掌櫃嚇得往後退了幾步﹐嘴裡連聲說道﹕別別別﹐老朽不會武功啊。\n");
    return 0;
}
