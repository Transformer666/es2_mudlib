// liuyi.c - 劉乙忘玄 Liu Yi, Kuxiao School Leader

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("劉乙忘玄", ({"liuyi", "liu_yi"}));
    set_attr("str", 22);
    set_attr("con", 20);
    set_attr("dex", 22);
    set_attr("int", 20);
    set_attr("cps", 22);
    set_race("human");
    set_class("warrior");
    set_level(60);

    set_skill("sword", 95);
    set_skill("dodge", 85);
    set_skill("parry", 90);
    set_skill("unarmed", 65);

    set("age", 48);
    set("attitude", "peaceful");
    set("long",
	"哭笑門掌門劉乙忘玄﹐面容半喜半悲﹐令人捉摸不透。身穿一\n"
	"件素白長袍﹐手中提著一柄無鞘的長劍﹐劍身寒光閃閃。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 40);
}
