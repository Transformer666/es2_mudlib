// NPC: /d/shuiyue/npc/villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("村民", ({"villager"}));
    set_race("human");
    set_class("commoner");
    set_level(2);

    set("age", 40);
    set("long", "一個樸實的村民﹐穿著粗布衣裳﹐正在忙著手中的活計。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "村民說道﹕我們這水月村啊﹐雖然小﹐可風景好著呢。\n",
        "村民哼著小曲﹐悠閒地做著農活。\n",
    }));
    setup();
    carry_money("coin", 15);
}
