// NPC: /d/luocheng/npc/storyteller.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("說書人", ({"storyteller", "narrator"}));
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 55);
    set("gender", "male");
    set("long",
        "一個穿著青布長衫的中年人﹐手持一把摺扇﹐說起話來抑揚頓\n"
        "挫﹐聲音洪亮。他是茶樓裡的說書先生﹐每天午後都會在這裡說\n"
        "上幾段江湖故事﹐引得茶客們聽得如痴如醉。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "說書人一拍驚堂木﹐朗聲說道﹕話說當年天山論劍﹐各路英雄齊聚一堂...\n",
        "說書人搖著摺扇說道﹕欲知後事如何﹐且聽下回分解﹗\n",
        "說書人壓低聲音說道﹕列位看官﹐這一段可是驚心動魄...\n",
        "說書人喝了口茶﹐清了清嗓子﹐又接著講了下去。\n",
    }));
    setup();
    carry_money("coin", 50);
}

int accept_fight(object ob)
{
    do_chat((: command, "say 好漢饒命﹐小人只是個說書的﹗" :));
    return 0;
}
