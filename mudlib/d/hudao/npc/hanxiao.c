// hanxiao.c - 韓笑 Han Xiao, Tiger Blade School Leader

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("韓笑", ({"hanxiao", "han_xiao"}));
    set_attr("str", 25);
    set_attr("con", 22);
    set_attr("dex", 22);
    set_attr("cor", 20);
    set_race("human");
    set_class("warrior");
    set_level(60);

    set_skill("blade", 100);
    set_skill("tiger blade", 95);
    set_skill("dodge", 85);
    set_skill("parry", 80);
    set_skill("unarmed", 60);

    set("age", 42);
    set("attitude", "peaceful");
    set("long",
	"虎刀門掌門人韓笑﹐身材魁梧﹐面帶微笑﹐但笑容中透著一股\n"
	"凜然不可犯的殺氣。腰間佩著一把虎紋大刀﹐刀柄上纏著虎皮。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("silver", 50);
}
