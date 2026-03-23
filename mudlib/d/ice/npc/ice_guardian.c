// vim: syntax=lpc
// NPC: ice_guardian.c - 冰域守衛 (quest boss for ice_guardian_challenge)
// Drops frost_crystal on death

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("冰域守衛", ({"ice guardian", "ice_guardian", "guardian"}));
    set_attr("str", 26);
    set_attr("dex", 22);
    set_attr("con", 28);
    set_attr("int", 20);
    set_attr("spi", 26);
    set_race("human");
    set_class("commoner");
    set_level(50);

    set_skill("staff", 90);
    set_skill("dodge", 65);
    set_skill("parry", 70);
    set_skill("force", 80);

    set("age", 500);
    set("gender", "male");
    set("long",
        "一個渾身覆蓋著一層淡藍色冰晶的守衛，他似乎已經在這片冰域中\n"
        "守護了數百年。每一次呼吸都帶出一團白霧，週身寒氣逼人。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "冰域守衛冷冷地注視著你，寒氣更加濃郁了。\n",
    }));
    set("attitude", "aggressive");
    setup();
    carry_object(STOCK_WEAPON("staff"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    set_temp("apply/vision_of_ghost", 1);
}

void die(object killer)
{
    object crystal;

    if( killer && userp(killer) ) {
        crystal = new(__DIR__"obj/frost_crystal");
        if( crystal ) crystal->move(environment());
        tell_object(killer,
            "冰域守衛的身軀轟然碎裂﹐化作無數冰晶散落一地。\n"
            "在碎冰之中﹐一塊散發著幽藍光芒的寒冰結晶靜靜地躺在那裡。\n");
        if( !killer->query("quest/ice_guardian_challenge_done") ) {
            killer->set("quest/ice_guardian_challenge_done", 1);
            killer->gain_score("quest", 150);
            killer->delete_temp("pending/ice_guardian");
        }
    }
    ::die(killer);
}
