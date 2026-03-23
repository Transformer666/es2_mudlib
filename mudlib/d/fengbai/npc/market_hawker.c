// NPC: /d/fengbai/npc/market_hawker.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("山貨小販", ({"hawker", "vendor"}));
    set_race("human");
    set_class("commoner");
    set_level(3);

    set("age", 35);
    set("gender", "male");
    set("long",
        "一個皮膚黝黑的漢子﹐一看就是常年在山裡討生活的人。\n"
        "他面前的草蓆上擺著各式山貨﹐正大聲吆喝著招攬生意。\n"
        "你可以用 list 看看他賣些什麼。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "山貨小販吆喝道﹕新鮮的山菌﹐剛從山裡採的﹐便宜賣了！\n",
        "山貨小販整理著草蓆上的貨物﹐嘴裡嘟嘟囔囔的。\n",
    }));

    set("merchandise", ([
        STOCK_MEDICATION("wild_ginseng") : 20,
        STOCK_MEDICATION("boar_berry") : 30,
    ]));

    setup();
    carry_object("/obj/area/obj/cloth")->wear();
    carry_money("coin", 80);
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}
