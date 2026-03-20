// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("景愈濤", ({"jing yutao", "jing", "yutao"}));
    set_attr("str", 28);
    set_attr("dex", 26);
    set_attr("con", 26);
    set_attr("int", 22);
    set_attr("spi", 20);
    set_attr("wis", 22);
    set_race("yaksha");
    set_class("commoner");
    set_level(65);
    set_skill("sword", 120);
    set_skill("parry", 90);
    set_skill("dodge", 80);
    set_skill("force", 85);
    set("age", 40);
    set("gender", "male");
    set("long", "景愈濤是古劍門掌門，虎背熊腰，看起來相當孔武有力，約四十多歲。他一生都在追尋劍道的至高境界，隱居在峽谷深處潛心修煉。\n");
    setup();
    carry_object(STOCK_WEAPON("longsword"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    set_temp("apply/vision_of_ghost", 1);
}
