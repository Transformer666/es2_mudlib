#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("商鋪掌櫃", ({"vendor", "shopkeeper"}));
    set_race("human");
    set_class("commoner");
    set_level(6);

    set("age", 50);
    set("gender", "male");
    set("attitude", "peaceful");
    set("long",
        "商鋪掌櫃是個精明的中年人﹐眼睛不大卻十分有神﹐正在撥\n"
        "弄著算盤盤算今天的帳目。你可以用 list 看看﹐用 buy 來買。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "掌櫃吆喝道﹕上好的兵器防具﹐價錢公道﹐快來看看﹗\n",
        "掌櫃撥了撥算盤﹐滿意地點了點頭。\n",
    }));
    set("merchandise", ([
        STOCK_WEAPON("shortblade") : 100,
        STOCK_WEAPON("longsword") : 180,
        STOCK_ARMOR("cloth") : 70,
        STOCK_ARMOR("leather") : 130,
    ]));

    setup();
    carry_money("coin", 500);
}

int accept_fight(object ob)
{
    do_chat("掌櫃連忙擺手道﹕大俠饒命﹐小的只是個做買賣的﹗\n");
    return 0;
}
