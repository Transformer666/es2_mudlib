// yutieshan.c - 魚鐵山 Yu Tieshan, Xueyin Manor Leader

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("魚鐵山", ({"yutieshan", "yu_tieshan"}));
    set_attr("str", 24);
    set_attr("con", 24);
    set_attr("dex", 20);
    set_attr("cor", 22);
    set_race("human");
    set_class("warrior");
    set_level(60);

    set_skill("sword", 95);
    set_skill("dodge", 80);
    set_skill("parry", 85);
    set_skill("unarmed", 70);

    set("age", 52);
    set("attitude", "peaceful");
    set("long",
	"雪吟莊莊主魚鐵山﹐身材高大壯碩﹐面如鐵鑄﹐濃眉大眼﹐一\n"
	"雙虎目透著精光。身穿一件黑色勁裝﹐腰間佩著一把闊劍。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 60);
}
