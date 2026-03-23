// NPC: /d/fengcheng/npc/merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("藥材商人", ({"merchant", "herb merchant"}));
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 48);
    set("gender", "male");
    set("long",
        "一個穿著厚棉袍的中年商人﹐面前的攤位上擺滿了各種藥材和\n"
        "山珍。他是從中原來的藥材商人﹐每年入冬前都會到風城收購天\n"
        "山的珍貴藥材。你可以用 list 看看﹐用 buy 來買。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "藥材商人說道﹕天山雪蓮﹐百年人參﹐都是難得的好東西啊。\n",
        "藥材商人搓著手說道﹕風城的冬天可真冷啊﹐比中原冷了不知多少倍。\n",
    }));
    set("merchandise", ([
        STOCK_WEAPON("shortblade") : 110,
        STOCK_ARMOR("cloth") : 75,
        STOCK_ARMOR("leather") : 140,
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
    do_chat("藥材商人嚇得連連後退﹐叫道﹕別打別打﹐有話好說﹗\n");
    return 0;
}
