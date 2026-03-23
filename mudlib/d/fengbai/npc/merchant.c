// NPC: /d/fengbai/npc/merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("雜貨掌櫃", ({"merchant", "shopkeeper"}));
    set_race("human");
    set_class("commoner");
    set_level(3);

    set("age", 50);
    set("gender", "male");
    set("long",
        "一個瘦小的老頭子﹐滿臉皺紋但眼睛很亮﹐一看就是個精明人。\n"
        "他一邊整理著貨架上的東西﹐一邊招呼著客人。你可以用 list 看看他賣些什麼。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "雜貨掌櫃說道﹕山裡新採的藥材﹐便宜賣了。\n",
        "雜貨掌櫃整理著貨架上的東西﹐嘴裡嘟嘟囔囔的。\n",
    }));

    set("merchandise", ([
        STOCK_MEDICATION("black_pill") : 50,
        STOCK_MEDICATION("boar_berry") : 40,
        STOCK_MEDICATION("wild_ginseng") : 30,
    ]));

    setup();
    carry_object("/obj/area/obj/cloth")->wear();
    carry_money("coin", 120);
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}
