// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("孫漪", ({"sunyi"}));
    set_attr("str", 24);
    set_attr("dex", 28);
    set_attr("con", 22);
    set_attr("int", 20);
    set_attr("spi", 22);
    set_attr("wis", 18);
    set_race("asura");
    set_class("commoner");
    set_level(55);
    set_skill("blade", 100);
    set_skill("dodge", 90);
    set_skill("parry", 80);
    set_skill("force", 70);
    set("age", 15);
    set("gender", "female");
    set("long", "孫漪是韓笑十年前在山下遇到的一個修羅族女孩，後來韓笑成為虎刀門掌門便收她為義女。別被她嬌滴滴的樣子迷惑了，她在十三歲時就力克群雄成為虎刀門比武大會的武狀元。\n");
    setup();
    carry_object(STOCK_WEAPON("blade"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    set_temp("apply/vision_of_ghost", 1);
}
