// NPC: /d/shuilan/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("客棧掌櫃", ({"innkeeper", "keeper"}));
    set_race("human");
    set_class("commoner");
    set_level(4);

    set("age", 38);
    set("gender", "female");
    set("long", "一個精明幹練的婦人﹐操著一口南方口音﹐手腳十分麻利。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "客棧掌櫃說道﹕客人要住店還是吃飯﹖都有都有﹗\n",
        "客棧掌櫃擦著桌子﹐嘴裡哼著一首南方小調。\n",
    }));
    setup();
    carry_money("coin", 150);
}

void init()
{
    ::init();
    if( !is_fighting() )
        do_chat( (: command, "say 客人請進﹐請進﹗" :) );
}

int accept_fight(object ob)
{
    do_chat((: command, "say 哎喲﹐客人莫要動手啊﹗來人哪﹗" :));
    return 0;
}
