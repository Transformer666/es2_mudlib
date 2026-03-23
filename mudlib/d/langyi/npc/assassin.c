// vim: syntax=lpc
// assassin.c - 金蛇殺手
// Quest: 金蛇密函 (jinse_letter) - carries secret letter, drops on death

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("金蛇殺手", ({"assassin", "jinse_killer"}));
    set_attr("str", 16);
    set_attr("con", 14);
    set_attr("dex", 22);
    set_race("human");
    set_class("thief");
    set_level(30);

    set_skill("dagger", 60);
    set_skill("dodge", 65);
    set_skill("parry", 50);

    set("age", 32);
    set("attitude", "aggressive");
    set("long",
        "一名金蛇門的殺手﹐身穿緊身黑衣﹐腰間掛著數把短匕﹐\n"
        "眼神陰冷﹐渾身散發著危險的氣息。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "金蛇殺手冷冷地盯著你﹐手已經摸上了匕首。\n",
        "金蛇殺手陰沉地說道﹕既然被你撞見﹐那就別想活著離開。\n",
    }));
    setup();
    carry_object(__DIR__"obj/viper_dagger")->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_object(__DIR__"obj/jinse_letter");
    carry_money("silver", 15);
}
