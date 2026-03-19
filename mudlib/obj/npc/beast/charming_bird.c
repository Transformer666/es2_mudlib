// charming_bird.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("鸂鷘", ({"charming_bird", "bird"}));

    set_attr("str", 18);
    set_attr("dex", 30);
    set_attr("spi", 22);
    set_race("human");
    set_class("fighter");
    set_level(50);
    advance_stat("gin", 400);
    advance_stat("kee", 400);

    set_skill("unarmed", 80);
    set_skill("dodge", 110);

    set("age", 600);
    set("long",
        "一隻色彩斑斕的奇鳥，羽翼流轉著七彩光華，歌聲婉轉動人，\n"
        "凡聽聞者無不為之神魂顛倒，迷失心智。\n");

    setup();

    add_temp("apply/attack", 60);
    add_temp("apply/defense", 90);
    add_temp("apply/damage", 25);
    add_temp("apply/armor", 30);

    carry_money("silver", 35);
}
