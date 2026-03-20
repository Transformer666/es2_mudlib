// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("遊蕩鬼魂", ({"wandering_ghost", "ghost"}));
    set_attr("str", 16);
    set_attr("con", 18);
    set_attr("dex", 20);
    set_attr("wis", 10);
    set_attr("spi", 22);
    set_race("human");
    set_class("commoner");
    set_level(25);

    set_skill("unarmed", 50);
    set_skill("dodge", 45);

    set("age", 0);
    set("long",
        "一個模糊的半透明人影在霧氣中飄蕩﹐面目模糊不清﹐只能隱\n"
        "約辨認出人形的輪廓。它似乎已經失去了生前的記憶﹐只是本能\n"
        "地在黃泉路上遊蕩。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "遊蕩鬼魂發出一聲淒厲的哀嚎。\n",
        "遊蕩鬼魂的身影忽明忽暗﹐似乎隨時會消散。\n",
    }));
    setup();
}
