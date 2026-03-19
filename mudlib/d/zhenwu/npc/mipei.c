// mipei.c - 米沛 Mi Pei, Zhenwu Military Camp Commander

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("米沛", ({"mipei", "mi_pei"}));
    set_attr("str", 22);
    set_attr("con", 22);
    set_attr("dex", 18);
    set_attr("wis", 20);
    set_attr("cor", 22);
    set_race("human");
    set_class("soldier");
    set_level(50);

    set_skill("pike", 90);
    set_skill("tactic", 85);
    set_skill("dodge", 70);
    set_skill("parry", 75);
    set_skill("unarmed", 50);

    set("age", 45);
    set("attitude", "peaceful");
    set("long",
	"振武軍營統領米沛﹐身披鐵甲﹐腰懸令旗﹐面容剛毅﹐目光如\n"
	"鷹隼般銳利。一手持著長槍﹐氣宇軒昂﹐頗具將帥之風。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("silver", 80);
}
