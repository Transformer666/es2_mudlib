// elder.c - Maoshan Elder

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("茅山長老", ({"elder", "maoshan_elder"}));
    set_attr("str", 18);
    set_attr("con", 18);
    set_attr("dex", 20);
    set_attr("int", 24);
    set_attr("wis", 25);
    set_attr("spi", 26);
    set_race("human");
    set_class("taoist");
    set_level(60);

    set_skill("sword", 85);
    set_skill("maoshan sword", 90);
    set_skill("maoshan neigong", 80);
    set_skill("dodge", 75);
    set_skill("parry", 70);

    set("age", 70);
    set("attitude", "peaceful");
    set("long",
	"茅山派長老﹐身穿一件玄色道袍﹐頭戴混元巾﹐手持一柄拂塵﹐\n"
	"仙風道骨﹐飄飄然有出塵之姿。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"長老撫鬚說道﹕道法自然﹐萬物歸一。\n",
    }));
    setup();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("coin", 200);
}
