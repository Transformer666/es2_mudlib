// NPC: /d/luocheng/npc/vendor.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("百貨行掌櫃", ({"vendor", "shopkeeper"}));
    set_race("human");
    set_class("commoner");
    set_level(6);

    set("age", 55);
    set("gender", "male");
    set("long",
        "一個鬚髮皆白的老商人﹐雖然年紀大了﹐但目光精明﹐一看\n"
        "就是個老練的生意人。你可以用 list 看看﹐用 buy 來買。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "百貨行掌櫃說道﹕本店貨品齊全﹐價錢公道﹐童叟無欺。\n",
        "百貨行掌櫃撥弄著算盤﹐嘴裡念念有詞。\n",
    }));
    set("merchandise", ([
        STOCK_WEAPON("shortblade") : 120,
        STOCK_WEAPON("longsword") : 200,
        STOCK_ARMOR("cloth") : 80,
        STOCK_ARMOR("leather") : 150,
    ]));

    setup();
    carry_money("coin", 800);
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
    do_chat("百貨行掌櫃嚇了一跳﹐連連擺手說道﹕別別別﹐有話好說﹗\n");
    return 0;
}
