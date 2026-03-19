// liudonglu.c - 柳東蘆 Liu Donglu, Fengshan Sword School Leader

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("柳東蘆", ({"liudonglu", "liu_donglu"}));
    set_attr("str", 20);
    set_attr("con", 20);
    set_attr("dex", 24);
    set_attr("wis", 22);
    set_attr("spi", 20);
    set_race("human");
    set_class("warrior");
    set_level(60);

    set_skill("sword", 100);
    set_skill("fengshan sword", 95);
    set_skill("dodge", 90);
    set_skill("parry", 85);
    set_skill("unarmed", 50);

    set("age", 50);
    set("attitude", "peaceful");
    set("long",
	"封山派掌門人柳東蘆﹐身穿一襲灰袍﹐鬢髮斑白﹐面容清瘦﹐\n"
	"但一雙眼睛精光閃閃。腰間懸著一柄古劍﹐劍鞘上刻著封山二字。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 50);
}
