// NPC: /d/shuilan/npc/merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("魚販", ({"merchant", "fish merchant"}));
    set_race("human");
    set_class("commoner");
    set_level(4);

    set("age", 35);
    set("gender", "male");
    set("long",
        "一個穿著粗布圍裙的漢子﹐雙手沾滿了魚鱗﹐正扯著嗓子吆喝\n"
        "叫賣。他面前的攤位上擺著各種新鮮的魚蝦﹐看起來都是今天早\n"
        "上剛從河裡撈上來的。你可以用 list 看看﹐用 buy 來買。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "魚販大聲吆喝道﹕新鮮的羿水大鯉魚嘍﹐走過路過別錯過﹗\n",
        "魚販說道﹕今天的魚可新鮮了﹐都是一大早打的﹗\n",
    }));
    set("merchandise", ([
        STOCK_WEAPON("shortblade") : 100,
        STOCK_ARMOR("cloth") : 70,
    ]));

    setup();
    carry_money("coin", 200);
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
    do_chat("魚販連連擺手說道﹕別動手﹐別動手﹗有話好好說﹗\n");
    return 0;
}
