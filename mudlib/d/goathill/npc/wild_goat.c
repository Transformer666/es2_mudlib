// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("野山羊", ({"wild_goat", "goat"}));
    set_attr("str", 14);
    set_attr("dex", 16);
    set_attr("con", 14);
    set_attr("int", 4);
    set_attr("spi", 8);
    set_race("human");
    set_class("commoner");
    set_level(10);
    set_skill("unarmed", 25);
    set_skill("dodge", 35);
    set("age", 5);
    set("gender", "male");
    set("long",
        "一隻毛色灰白的野山羊，長著一對彎曲的大角，正悠閒地在山坡\n"
        "上啃著青草。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "野山羊咩咩叫了兩聲。\n",
    }));
    set("attitude", "aggressive");
    setup();
}
