#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("冷梅弟子", ({"disciple", "lengmei_disciple"}));
    set_attr("str", 14);
    set_attr("con", 12);
    set_attr("dex", 18);
    set_race("human");
    set_class("warrior");
    set_level(20);

    set_skill("sword", 45);
    set_skill("dodge", 40);
    set_skill("parry", 35);

    set("age", 22);
    set("long",
        "一名身穿白衣的冷梅莊弟子﹐正在認真地練習劍法。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 50);
}
