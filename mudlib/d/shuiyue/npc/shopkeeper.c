// NPC: /d/shuiyue/npc/shopkeeper.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("雜貨掌櫃", ({"shopkeeper", "keeper"}));
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 42);
    set("gender", "male");
    set("long",
        "一個精明幹練的中年人﹐穿著一身洗得發白的布衣﹐手腳\n"
        "麻利地在貨架間忙碌著。你可以用 list 看看有什麼﹐用 buy 來買。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "雜貨掌櫃說道﹕水月村雖小﹐東西可不少﹐客倌看看吧。\n",
        "雜貨掌櫃擦了擦櫃台﹐把貨物擺得整整齊齊。\n",
    }));
    set("merchandise", ([
        STOCK_ITEM("ration") : 40,
        STOCK_ITEM("torch") : 20,
    ]));

    setup();
    carry_money("coin", 80);
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

int accept_fight(object ob)
{
    do_chat("雜貨掌櫃連忙擺手道﹕大俠饒命﹐小的只是個做小買賣的﹗\n");
    return 0;
}

void deliver_merchandise(object customer, mixed item)
{
    command("say " + item->name() + "﹐拿好嘍。");
    ::deliver_merchandise(customer, item);
}
