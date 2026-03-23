// NPC: /d/fengbai/npc/villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("採藥村民", ({"villager", "farmer"}));
    set_race("human");
    set_class("commoner");
    set_level(2);

    set("age", 38);
    set("long", "一個樸實的村民﹐背著一個竹簍﹐裡面裝著一些採來的草藥。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "採藥村民說道﹕往北邊可別走太遠﹐黑風山上盜匪多得很。\n",
        "採藥村民整理著竹簍裡的草藥﹐自言自語道﹕今天收成還不錯。\n",
    }));
    setup();
    carry_money("coin", 10);
}
