// vim: syntax=lpc

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("獄卒", ({"jailer"}));
    set_attr("str", 18);
    set_attr("dex", 14);
    set_attr("con", 18);
    set_attr("int", 12);
    set_attr("spi", 10);
    set_race("human");
    set_class("commoner");
    set_level(20);

    set_skill("blade", 40);
    set_skill("dodge", 30);
    set_skill("parry", 30);

    set("age", 35);
    set("gender", "male");
    set("long",
        "一名身材魁梧的獄卒，腰間掛著一大串鑰匙，手持一把鬼頭刀。他\n"
        "臉上帶著兇狠的神情，讓人不寒而慄。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "獄卒拍了拍手中的刀，冷笑道：老實點。\n",
    }));
    setup();
    carry_object(STOCK_WEAPON("blade"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
