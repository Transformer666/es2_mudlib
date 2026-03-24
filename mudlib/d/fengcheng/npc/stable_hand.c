// NPC: /d/fengcheng/npc/stable_hand.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("馬伕", ({"stable hand", "stablehand"}));
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 25);
    set("gender", "male");
    set("long", "一個皮膚黝黑的年輕漢子﹐穿著沾滿草屑的粗布衣裳﹐正在照料馬匹。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "馬伕拍了拍身旁的馬﹐笑著說道﹕這匹棗紅馬可是好馬啊﹐日行千里。\n",
        "馬伕叉著腰說道﹕風城的馬﹐那可都是吃天山上的青草長大的﹐耐寒著呢。\n",
    }));
    setup();
    carry_money("coin", 30);
}
