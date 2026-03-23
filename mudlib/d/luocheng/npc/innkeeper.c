// NPC: /d/luocheng/npc/innkeeper.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("通寶掌櫃", ({"innkeeper", "keeper"}));
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 48);
    set("gender", "male");
    set("long", "一個圓臉的胖掌櫃﹐笑起來眼睛瞇成一條縫﹐看起來十分精明。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "通寶掌櫃說道﹕客倌要吃點什麼﹖本店的滷牛肉可是一絕﹗\n",
        "通寶掌櫃對著夥計喊道﹕快點﹐三號桌的酒上了沒有﹗\n",
    }));
    setup();
    carry_money("coin", 300);
}

void init()
{
    ::init();
    if( !is_fighting() )
        do_chat( (: command, "say 客倌裡邊請﹗" :) );
}

int accept_fight(object ob)
{
    do_chat((: command, "say 客倌息怒﹐有話好說﹗" :));
    return 0;
}
