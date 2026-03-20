// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("大蜈蚣", ({"centipede", "giant centipede"}));
    set_attr("str", 30);
    set_attr("dex", 20);
    set_attr("con", 32);
    set_attr("int", 12);
    set_attr("spi", 18);
    set_attr("wis", 10);
    set_race("human");
    set_class("commoner");
    set_level(60);
    set_skill("unarmed", 100);
    set_skill("dodge", 70);
    set_skill("parry", 50);
    set("age", 500);
    set("gender", "male");
    set("long", "一條巨大的蜈蚣盤踞在霧林深處，身長數丈，通體漆黑，無數節足如利刃般閃著寒光。牠會主動攻擊入侵者，而且懂得自行療傷。\n");
    set("chat_chance", 5);
    set("chat_msg", ({"大蜈蚣發出嘶嘶的聲響。\n", "大蜈蚣的觸鬚不安地擺動著。\n"}));
    setup();
}
