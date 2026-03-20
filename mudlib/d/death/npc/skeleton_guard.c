// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("骨衛", ({"skeleton_guard", "skeleton", "guard"}));
    set_attr("str", 22);
    set_attr("dex", 18);
    set_attr("con", 24);
    set_attr("int", 6);
    set_attr("spi", 12);
    set_race("human");
    set_class("commoner");
    set_level(30);
    set_skill("blade", 60);
    set_skill("dodge", 40);
    set_skill("parry", 50);
    set("age", 500);
    set("gender", "male");
    set("long",
        "一具散發著幽綠磷火的骷髏，手持一把鏽跡斑斑的大刀，機械\n"
        "般地守護著白骨荒原。它的眼眶中閃爍著詭異的光芒。\n");
    set("chat_chance", 4);
    set("chat_msg", ({
        "骨衛的骨骼喀喀作響，它似乎在巡邏。\n",
    }));
    setup();
    carry_object(STOCK_WEAPON("blade"))->wield();
    set_temp("apply/vision_of_ghost", 1);
}
