// NPC: /d/fengcheng/npc/old_man.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("白髮老者", ({"old man", "oldman"}));
    set_race("human");
    set_class("commoner");
    set_level(3);

    set("age", 72);
    set("gender", "male");
    set("long", "一位白髮蒼蒼的老者﹐身穿厚實的羊皮襖﹐坐在井邊的石墩上瞇著眼睛曬太陽。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "白髮老者捋了捋鬍子﹐瞇著眼說道﹕老頭子在風城住了一輩子嘍。\n",
        "白髮老者指了指北邊﹐說道﹕年輕的時候﹐我也上過天山呢。\n",
        "白髮老者嘆了口氣﹐說道﹕這口井啊﹐我小時候就有了﹐比我歲數還大。\n",
    }));
    setup();
    carry_money("coin", 10);
}
