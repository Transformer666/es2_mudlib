// NPC: /d/fengbai/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("客棧老闆", ({"innkeeper", "keeper"}));
    set_race("human");
    set_class("commoner");
    set_level(3);

    set("age", 42);
    set("gender", "male");
    set("long", "一個老實巴交的莊稼漢﹐皮膚黝黑﹐雙手粗糙﹐兼著做些客棧的生意。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "客棧老闆說道﹕客人來了啊﹐坐坐﹐隨便吃點。\n",
        "客棧老闆擦了擦桌子﹐然後給自己倒了碗茶。\n",
    }));
    setup();
    carry_money("coin", 80);
}

void init()
{
    ::init();
    if( !is_fighting() )
        do_chat( (: command, "say 客人快請坐﹗" :) );
}

int accept_fight(object ob)
{
    do_chat((: command, "say 客人莫要動手﹐咱們這小地方可經不起折騰。" :));
    return 0;
}
