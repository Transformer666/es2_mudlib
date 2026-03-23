// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("鸂鷘", ({"charming bird", "charming_bird", "bird"}));
    set_attr("str", 18);
    set_attr("dex", 28);
    set_attr("con", 18);
    set_attr("int", 18);
    set_attr("spi", 24);
    set_race("human");
    set_class("commoner");
    set_level(35);
    set_skill("unarmed", 70);
    set_skill("dodge", 75);
    set("age", 500);
    set("gender", "male");
    set("attitude", "aggressive");
    set("long", "一隻身形端莊高雅的風鳥，漂亮的羽毛在陽光下折射出七彩光芒，優雅地棲息在古松枝頭。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "鸂鷘展開華麗的羽翼，發出清脆的鳴叫。\n",
        "鸂鷘高傲地昂起頭，俯視著地面。\n",
    }));
    setup();
}
