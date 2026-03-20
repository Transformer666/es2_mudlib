// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("知客尼", ({"greeter", "zhike"}));
    set_attr("str", 12);
    set_attr("con", 14);
    set_attr("dex", 13);
    set_attr("wis", 16);
    set_race("human");
    set_class("monk");
    set_level(15);

    set_skill("staff", 28);
    set_skill("dodge", 25);

    set("age", 30);
    set("gender", "female");
    set("attitude", "peaceful");
    set("long",
        "一名知客尼﹐身穿灰色僧袍﹐面帶微笑﹐正在庭中迎接來往的\n"
        "香客。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 20);
}
