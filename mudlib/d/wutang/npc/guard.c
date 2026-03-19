// guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("守衛", ({"guard", "wutang_guard"}));
    set_attr("str", 18);
    set_attr("con", 18);
    set_attr("dex", 16);
    set_race("human");
    set_class("fighter");
    set_level(15);

    set_skill("sword", 60);
    set_skill("dodge", 50);
    set_skill("parry", 40);

    set("age", 28);
    set("long", "一個身穿甲冑的守衛﹐手持長槍﹐警惕地注視著來往的行人。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 100);
}
