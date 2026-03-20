// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("靈狙", ({"ritual monkey", "ritual_monkey", "monkey"}));
    set_attr("str", 16);
    set_attr("dex", 30);
    set_attr("con", 16);
    set_attr("int", 20);
    set_attr("spi", 22);
    set_race("human");
    set_class("commoner");
    set_level(30);
    set_skill("unarmed", 65);
    set_skill("dodge", 80);
    set("age", 400);
    set("gender", "male");
    set("long", "一隻天性聰穎但膽小害羞的神猴，通體金毛閃閃發光，靈動的雙眼充滿了智慧。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "靈狙好奇地歪著頭看著你。\n",
        "靈狙靈活地跳上樹梢，消失了一瞬又出現在你身後。\n",
    }));
    setup();
}
