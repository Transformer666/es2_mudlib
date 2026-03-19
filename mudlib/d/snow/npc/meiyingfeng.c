// meiyingfeng.c - 梅影風 Mei Yingfeng, Boss NPC

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("梅影風", ({"meiyingfeng", "mei_yingfeng"}));
    set_attr("str", 22);
    set_attr("con", 20);
    set_attr("dex", 24);
    set_attr("spi", 20);
    set_race("human");
    set_class("warrior");
    set_level(60);

    set_skill("sword", 100);
    set_skill("dodge", 90);
    set_skill("parry", 85);
    set_skill("unarmed", 55);

    set("age", 38);
    set("long",
	"一個身穿白衣的女子﹐容貌清麗絕俗﹐如梅花般傲然獨立。手\n"
	"中握著一柄通體潔白的長劍﹐劍上似有寒霜凝結。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 45);
}
