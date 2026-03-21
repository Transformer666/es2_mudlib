#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("雪吟弟子", ({"disciple", "xueyin_disciple"}));
    set_attr("str", 11);
    set_attr("con", 12);
    set_attr("dex", 14);
    set_attr("int", 13);
    set_race("human");
    set_class("scholar");
    set_level(10);

    set_skill("sword", 20);
    set_skill("dodge", 18);

    set("age", 23);
    set("gender", "female");
    set("attitude", "peaceful");
    set("long",
        "一名雪吟莊的弟子﹐身穿素白長裙﹐舉止優雅﹐正在安靜地練劍。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 30);
}
