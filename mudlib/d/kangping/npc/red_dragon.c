// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("赤龍", ({"red dragon", "dragon"}));
    set_attr("str", 36);
    set_attr("con", 35);
    set_attr("dex", 22);
    set_attr("int", 18);
    set_attr("spi", 22);
    set_attr("wis", 15);
    set_race("dragon");
    set_class("commoner");
    set_level(65);
    advance_stat("gin", 250);
    advance_stat("kee", 250);
    advance_stat("sen", 250);

    set_skill("unarmed", 120);
    set_skill("dodge", 75);
    set_skill("parry", 65);
    set_skill("force", 85);

    set("attitude", "aggressive");
    set("age", 1500);
    set("gender", "male");
    set("long", "一條通體赤紅的巨龍蟄伏在石洞深處，鱗片如燃燒的烈焰般灼目，灼熱的氣息從巨口中噴湧而出。\n");
    set("chat_chance", 5);
    set("chat_msg", ({"赤龍張口噴出一團灼熱的火焰，空氣中瀰漫著焦灼的氣味。\n", "赤龍抖動著赤紅的鱗片，發出金屬碰撞般的鏗鏘聲。\n"}));

    setup();

    add_temp("apply/attack", 80);
    add_temp("apply/defense", 70);
    add_temp("apply/damage", 70);
    add_temp("apply/armor", 70);
    set_temp("apply/vision_of_ghost", 1);
}
