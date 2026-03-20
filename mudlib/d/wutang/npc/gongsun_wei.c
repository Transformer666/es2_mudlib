// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("公孫微", ({"gongsun_wei", "gongsun"}));
    set_attr("str", 22);
    set_attr("dex", 32);
    set_attr("con", 20);
    set_attr("int", 22);
    set_attr("spi", 20);
    set_attr("wis", 20);
    set_race("jiaojao");
    set_class("commoner");
    set_level(65);

    set_skill("dagger", 110);
    set_skill("dodge", 100);
    set_skill("parry", 60);
    set_skill("force", 70);

    set("age", 50);
    set("gender", "male");
    set("long", "「神行無蹤」公孫微是「大漠八魔」之一。此人長得又高又瘦，"
        "皮包著骨頭，好象僵屍一樣。一雙小眼睛炯炯有神，猿臂狼腰，"
        "鬼鬼祟祟地躲在暗處。\n");
    setup();
    carry_object(STOCK_WEAPON("dagger"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
