#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("雜貨掌櫃", ({"vendor", "shopkeeper"}));
    set_race("human");
    set_class("commoner");
    set_level(6);

    set("age", 38);
    set("gender", "female");
    set("attitude", "peaceful");
    set("long",
        "一個精明能幹的婦人﹐將店鋪打理得井井有條。她的貨源大\n"
        "多來自雪亭鎮的商隊﹐價錢也算公道。你可以用 list 看看﹐\n"
        "用 buy 來買。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "掌櫃娘子招呼道﹕客倌﹐進來看看﹐都是好貨。\n",
        "掌櫃娘子整理了一下貨架上的商品。\n",
    }));
    set("merchandise", ([
        STOCK_WEAPON("shortblade") : 110,
        STOCK_WEAPON("longsword") : 190,
        STOCK_ARMOR("cloth") : 75,
        STOCK_ARMOR("leather") : 140,
    ]));

    setup();
    carry_money("coin", 600);
}

int accept_fight(object ob)
{
    do_chat("掌櫃娘子叫道﹕客倌﹐這裡是做生意的地方﹐別動手啊﹗\n");
    return 0;
}
