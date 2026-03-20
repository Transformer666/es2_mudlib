// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("風神", ({"wind god", "wind", "god"}));
    set_attr("str", 30);
    set_attr("dex", 30);
    set_attr("con", 28);
    set_attr("int", 26);
    set_attr("spi", 32);
    set_attr("wis", 28);
    set_race("human");
    set_class("commoner");
    set_level(80);
    set_skill("sword", 130);
    set_skill("dodge", 110);
    set_skill("parry", 100);
    set_skill("force", 120);
    set("age", 7860);
    set("gender", "male");
    set("long", "墮落的風神，曾經是天界最強大的風之守護者。他約七千八百六十多歲，渾身散發著凜冽的風之力量，長年隱匿在晚月谷的廢墟之中。\n");
    set("chat_chance", 2);
    set("chat_msg", ({"一陣狂風呼嘯而過。\n", "風神冷冷地注視著四周。\n"}));
    setup();
    carry_object(STOCK_WEAPON("longsword"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    set_temp("apply/vision_of_ghost", 1);
}
