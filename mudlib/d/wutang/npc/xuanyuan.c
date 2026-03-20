// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("軒轅劍月", ({"xuanyuan", "xuanyuan_jianyue"}));
    set_attr("str", 28);
    set_attr("dex", 30);
    set_attr("con", 26);
    set_attr("int", 26);
    set_attr("spi", 28);
    set_attr("wis", 24);
    set_race("human");
    set_class("commoner");
    set_level(80);

    set_skill("sword", 130);
    set_skill("dodge", 100);
    set_skill("parry", 100);
    set_skill("force", 100);

    set("age", 60);
    set("gender", "male");
    set("long", "劍皇軒轅劍月是「大漠八魔」中最強的存在。此人長得英俊瀟灑，"
        "氣度雍容華貴，渾身上下透著一種讓人無法抗拒的魅力。"
        "與他的七位結義兄弟不同的是，軒轅劍月很少殺人。\n");
    setup();
    carry_object(STOCK_WEAPON("longsword"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    set_temp("apply/vision_of_ghost", 1);
}
