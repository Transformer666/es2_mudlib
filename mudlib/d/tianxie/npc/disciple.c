#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("天邪弟子", ({"disciple", "tianxie_disciple"}));
    set_attr("str", 14);
    set_attr("con", 12);
    set_attr("dex", 18);
    set_race("human");
    set_class("warrior");
    set_level(25);

    set_skill("sword", 50);
    set_skill("dodge", 45);
    set_skill("parry", 40);

    set("age", 25);
    set("long",
        "一名身穿黑衣的天邪派弟子﹐面無表情﹐目光冰冷。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 100);
}
