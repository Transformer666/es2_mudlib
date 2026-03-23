// NPC: /d/luocheng/npc/merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("皮貨商人", ({"merchant", "fur merchant"}));
    set_race("human");
    set_class("commoner");
    set_level(6);

    set("age", 42);
    set("gender", "male");
    set("long",
        "一個身材魁梧的商人﹐穿著一件貂皮大氅﹐腰間掛著一個鼓鼓\n"
        "囊囊的錢袋。他是做皮貨生意的﹐常年往來於羅城和北方各地之\n"
        "間。你可以用 list 看看﹐用 buy 來買。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "皮貨商人說道﹕上好的狐皮、貂皮﹐都是北邊山裡獵來的﹗\n",
        "皮貨商人搓著手說道﹕今年的皮貨行情不錯﹐賺了不少。\n",
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

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
    do_chat("皮貨商人驚慌地叫道﹕救命啊﹗有人搶劫﹗\n");
    return 0;
}
