// luoyi.c - 駱易 Luo Yi, Boss NPC

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("駱易", ({"luoyi", "luo_yi"}));
    set_attr("str", 20);
    set_attr("con", 20);
    set_attr("dex", 22);
    set_attr("int", 22);
    set_attr("wis", 20);
    set_race("human");
    set_class("scholar");
    set_level(55);

    set_skill("sword", 85);
    set_skill("three rotations", 80);
    set_skill("dodge", 80);
    set_skill("parry", 75);
    set_skill("unarmed", 60);

    set("age", 35);
    set("long",
	"一個書生打扮的年輕人﹐面如冠玉﹐手持一把摺扇﹐看起來文質\n"
	"彬彬﹐但眼中偶爾閃過一絲精光﹐顯然並非手無縛雞之力。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 35);
}
