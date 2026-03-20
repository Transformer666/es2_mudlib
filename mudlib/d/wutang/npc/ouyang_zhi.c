// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("歐陽芝", ({"ouyang_zhi", "ouyang"}));
    set_attr("str", 20);
    set_attr("dex", 22);
    set_attr("con", 18);
    set_attr("int", 26);
    set_attr("spi", 20);
    set_attr("wis", 24);
    set_race("human");
    set_class("commoner");
    set_level(45);

    set_skill("sword", 80);
    set_skill("dodge", 70);
    set_skill("parry", 60);
    set_skill("tactic", 90);

    set("age", 40);
    set("gender", "male");
    set("long", "歐陽芝是「大漠八魔」之一，號稱「神算無疑」。"
        "他的武功似乎是步玄派的，但為人心浮氣躁，自視極高，"
        "自認為風流倜儻，文采天下無雙。\n");
    setup();
    carry_object(STOCK_WEAPON("longsword"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
