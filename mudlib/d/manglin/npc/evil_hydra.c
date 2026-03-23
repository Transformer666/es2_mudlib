// vim: syntax=lpc
// NPC: evil_hydra.c - 鮫蛟 (quest boss for manglin_hydra)
// Spawned by pond.c when player searches the water

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
    set("long",
        "一條身長數十丈的巨蛟﹐生有一十二爪﹐鱗甲如同精鋼般堅硬。\n"
        "牠盤踞在莽林深處﹐渾身散發著令人窒息的妖氣。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "鮫蛟吐出長長的蛇信﹐發出嘶嘶的聲響。\n",
        "鮫蛟巨大的身軀緩緩移動﹐碾碎了周圍的灌木。\n",
    }));
    set("chat_chance_combat", 6);
    set("chat_msg_combat", ({
        "鮫蛟猛甩巨尾﹐掀起一陣狂風！\n",
        "鮫蛟張開血盆大口﹐噴出一口腥臭的毒霧！\n",
        "鮫蛟的十二爪同時揮出﹐如同暴雨般襲來！\n",
    }));
    set("attitude", "aggressive");
    setup();
    set_temp("apply/vision_of_ghost", 1);
}

void die(object killer)
{
    if( killer && userp(killer) ) {
        tell_object(killer,
            "鮫蛟發出一聲悲鳴﹐龐大的身軀轟然倒下﹐濺起漫天水花。\n"
            "牠的鱗甲在死後依然閃爍著幽幽的光芒。\n"
            "( 你可以回去找杞庸報告此事 )\n");
        killer->set_temp("pending/manglin_hydra", 2);
    }
    ::die(killer);
}
