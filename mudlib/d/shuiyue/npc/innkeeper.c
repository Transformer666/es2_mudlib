// NPC: /d/shuiyue/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("客棧老闆娘", ({"innkeeper", "keeper"}));
    set_race("human");
    set_class("commoner");
    set_level(3);

    set("age", 55);
    set("gender", "female");
    set("long", "一個和藹慈祥的老婦人﹐頭髮已經花白﹐臉上總是帶著溫暖的笑容。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "客棧老闆娘說道﹕客人難得來﹐坐下喝杯茶吧。\n",
        "客棧老闆娘端出一碟小菜﹐放在桌上。\n",
    }));
    setup();
    carry_money("coin", 100);
}

void init()
{
    ::init();
    if( !is_fighting() )
        do_chat( (: command, "say 歡迎歡迎﹐請裡邊坐。" :) );
}

int accept_fight(object ob)
{
    do_chat((: command, "say 哎呀﹐客人莫要動粗啊﹗" :));
    return 0;
}
