#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("知客僧", ({"greeter", "zhike"}));
    set_attr("str", 14);
    set_attr("con", 14);
    set_attr("dex", 12);
    set_attr("wis", 16);
    set_race("human");
    set_class("monk");
    set_level(15);

    set_skill("staff", 30);
    set_skill("dodge", 25);

    set("age", 35);
    set("attitude", "peaceful");
    set("long",
        "一名知客僧﹐身穿灰色僧袍﹐面帶微笑﹐正在迎接來往的香\n"
        "客。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 30);
    set_temp("apply/vision_of_ghost", 1);
}
