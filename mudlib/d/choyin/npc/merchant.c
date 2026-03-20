// npc/merchant.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("雜貨鋪掌櫃", ({"merchant", "shopkeeper"}));
    set_race("human");
    set_class("commoner");
    set_level(10);

    set("age", 38);
    set("gender", "male");
    set("long",
        "雜貨鋪的掌櫃﹐是個精明能幹的中年人﹐正忙著擺弄櫃台上的\n"
        "各色貨物。你可以用 list 查看貨品﹐用 buy 購買。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "掌櫃笑道﹕客倌隨便看﹐本店貨真價實。\n",
        "掌櫃用抹布擦了擦櫃台﹐把幾件貨品擺得更整齊了些。\n",
    }));
    set("merchandise", ([
        "/obj/area/obj/ration" : 50,
        "/obj/area/obj/torch" : 50,
    ]));

    setup();
    carry_money("coin", 150);
}
