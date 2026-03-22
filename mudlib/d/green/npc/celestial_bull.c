// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("饕餮", ({"celestial bull", "celestial_bull", "bull"}));
    set_attr("str", 32);
    set_attr("dex", 16);
    set_attr("con", 30);
    set_attr("int", 12);
    set_attr("spi", 18);
    set_race("human");
    set_class("commoner");
    set_level(45);
    set_skill("unarmed", 85);
    set_skill("dodge", 50);
    set("age", 800);
    set("gender", "male");
    set("long", "一頭狀若牛的巨獸，渾身無毛，赤紅色的硬皮堅如磐石。牠低著碩大的頭顱，四隻蹄子深深陷入泥土之中。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "饕餮發出低沉的哞聲，大地為之震動。\n",
        "饕餮用蹄子刨著地面，揚起一陣塵土。\n",
    }));
    set("attitude", "aggressive");
    setup();
}
