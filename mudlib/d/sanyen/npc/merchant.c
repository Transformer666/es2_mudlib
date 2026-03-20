// npc/merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("雜貨商人", ({"merchant", "trader"}));
    set_race("human");
    set_class("commoner");
    set_level(8);

    set("age", 40);
    set("gender", "male");
    set("long",
        "一個皮膚黝黑的中年漢子，身穿粗布短褂，腰間繫著一條布帶。\n"
        "他面前的攤位上擺著一些粗糧、獸皮和山貨，看起來都是從附近\n"
        "山裡收來的。你可以用 list 查看貨品，用 buy 購買。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "商人吆喝道：山貨便宜賣了，走過路過不要錯過！\n",
        "商人整理了一下攤位上的貨物，拍了拍身上的灰塵。\n",
    }));
    set("merchandise", ([
        "/obj/area/obj/ration" : 50,
        "/obj/area/obj/torch" : 50,
    ]));

    setup();
    carry_money("coin", 100);
}
