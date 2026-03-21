// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("狻猊", ({"devilish tiger", "devilish_tiger", "tiger"}));
    set_attr("str", 30);
    set_attr("dex", 24);
    set_attr("con", 28);
    set_attr("int", 14);
    set_attr("spi", 20);
    set_race("human");
    set_class("commoner");
    set_level(45);
    set_skill("unarmed", 90);
    set_skill("dodge", 65);
    set("age", 800);
    set("gender", "male");
    set("long", "一頭週身陰氣纏繞的巨虎，漆黑的皮毛上隱約可見詭異的紋路，一雙血紅的眼睛散發著攝人的光芒。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "狻猊發出震耳欲聾的咆哮。\n",
        "狻猊的身上陰氣翻湧，令人不寒而慄。\n",
    }));
    set("attitude", "aggressive");
    setup();
}
