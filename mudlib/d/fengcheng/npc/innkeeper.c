// NPC: /d/fengcheng/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("客棧掌櫃", ({"innkeeper", "keeper"}));
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 45);
    set("gender", "male");
    set("long", "一個壯實的中年漢子﹐滿臉紅光﹐看起來十分豪爽。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "客棧掌櫃說道﹕客倌﹐外頭冷﹐進來喝碗熱酒暖暖身子吧﹗\n",
        "客棧掌櫃往火盆裡添了幾塊炭﹐火光更旺了。\n",
    }));
    setup();
    carry_money("coin", 200);
}

void init()
{
    ::init();
    if( !is_fighting() )
        do_chat( (: command, "say 歡迎光臨朔風客棧﹗" :) );
}

int accept_fight(object ob)
{
    do_chat((: command, "say 客倌莫要動手﹐有話好好說嘛。" :));
    return 0;
}
