// NPC: /d/fengcheng/npc/patrol.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("衙役", ({"patrol", "yamen guard"}));
    set_race("human");
    set_class("soldier");
    set_level(12);

    set("age", 28);
    set("gender", "male");
    set("long", "一個身穿皂衣的衙役﹐手持水火棍﹐站在衙門口值守。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "衙役喝道﹕閒雜人等﹐不得在衙門前逗留！\n",
        "衙役打了個哈欠﹐又趕緊挺直了腰桿。\n",
    }));
    setup();
    carry_object(STOCK_WEAPON("staff"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_money("coin", 60);
}
