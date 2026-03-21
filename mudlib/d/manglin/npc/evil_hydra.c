// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("鮫蛟", ({"evil hydra", "evil_hydra", "hydra"}));
    set_attr("str", 30);
    set_attr("dex", 20);
    set_attr("con", 30);
    set_attr("int", 16);
    set_attr("spi", 22);
    set_race("human");
    set_class("commoner");
    set_level(55);
    set_skill("unarmed", 100);
    set_skill("dodge", 55);
    set("age", 1200);
    set("gender", "male");
    set("long", "一條身長數十丈的巨蛟，生有一十二爪，鱗甲如同精鋼般堅硬。牠盤踞在莽林深處，渾身散發著令人窒息的妖氣。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "鮫蛟吐出長長的蛇信，發出嘶嘶的聲響。\n",
        "鮫蛟巨大的身軀緩緩移動，碾碎了周圍的灌木。\n",
    }));
    set("attitude", "aggressive");
    setup();
    set_temp("apply/vision_of_ghost", 1);
}
