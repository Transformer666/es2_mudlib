// haidafu.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("陰沉男子", ({"haidafu", "man"}));
    set_attr("str", 22);
    set_attr("con", 20);
    set_attr("dex", 20);
    set_attr("int", 18);
    set_attr("wis", 18);
    set_race("human");
    set_class("fighter");
    set_level(40);

    set_skill("sword", 90);
    set_skill("dodge", 80);
    set_skill("parry", 70);
    set_skill("unarmed", 60);

    set("age", 45);
    set("attitude", "peaceful");
    set("long",
	"一個面色陰沉的中年男子﹐穿著一件灰色長袍﹐坐在角落裡默默\n"
	"地喝著茶﹐看起來不像是普通人。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 500);
}
