// NPC: /d/luocheng/npc/old_woman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("賣花老嫗", ({"old woman", "old_woman", "flower seller"}));
    set_race("human");
    set_class("commoner");
    set_level(2);

    set("age", 65);
    set("gender", "female");
    set("long",
        "一個頭髮花白的老婦人﹐提著一個竹籃﹐籃中插著幾枝鮮花。\n"
        "她弓著腰在集市中慢慢穿行﹐用沙啞的聲音叫賣著花朵。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "賣花老嫗叫賣道﹕買花嘍﹐新鮮的山茶花﹐好看又好聞。\n",
        "賣花老嫗微笑道﹕年輕人﹐買枝花送給心上人吧。\n",
    }));
    setup();
    carry_money("coin", 10);
}
