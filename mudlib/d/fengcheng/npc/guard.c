// NPC: /d/fengcheng/npc/guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("城門守衛", ({"guard"}));
    set_race("human");
    set_class("soldier");
    set_level(15);

    set("age", 30);
    set("gender", "male");
    set("long", "一個身披皮甲的守衛﹐手持長槍﹐警惕地注視著來往的行人。\n");
    setup();
    carry_object(STOCK_WEAPON("longspear"))->wield();
    carry_object(STOCK_ARMOR("leather"))->wear();
    carry_money("coin", 80);
}
