// NPC: /d/luocheng/npc/guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("守城兵士", ({"guard", "soldier"}));
    set_race("human");
    set_class("soldier");
    set_level(12);

    set("age", 28);
    set("gender", "male");
    set("long", "一個身穿鎧甲的守城兵士﹐手持長槍﹐警惕地注視著來往的行人。\n");
    setup();
    carry_object(STOCK_WEAPON("longspear"))->wield();
    carry_object(STOCK_ARMOR("leather"))->wear();
    carry_money("coin", 60);
}
