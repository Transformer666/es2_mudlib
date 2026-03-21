#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("武陀弟子", ({"disciple", "wutuo_disciple"}));
    set_attr("str", 11);
    set_attr("con", 13);
    set_attr("dex", 14);
    set_attr("int", 15);
    set_attr("wis", 14);
    set_race("human");
    set_class("healer");
    set_level(10);

    set_skill("staff", 20);
    set_skill("dodge", 15);

    set("age", 20);
    set("gender", "male");
    set("attitude", "peaceful");
    set("long",
        "一名武陀門的弟子﹐身穿灰色布衣﹐正在認真研讀醫書﹐神情專注。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("staff") )->wield();
    carry_money("coin", 25);
}
