// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("混沌獸", ({"chaos beast", "beast"}));
    set_attr("str", 32);
    set_attr("con", 35);
    set_attr("dex", 28);
    set_attr("int", 15);
    set_attr("spi", 20);
    set_attr("wis", 12);
    set_attr("cor", 25);
    set_attr("cps", 20);
    set_race("human");
    set_class("commoner");
    set_level(60);
    advance_stat("gin", 220);
    advance_stat("kee", 220);
    advance_stat("sen", 220);

    set_skill("unarmed", 110);
    set_skill("dodge", 85);
    set_skill("parry", 60);
    set_skill("force", 80);

    set("age", 3000);
    set("gender", "male");
    set("long", "混沌獸形如巨犬，全身籠罩在一團不斷變幻的黑霧之中，肢體時而扭曲變形，散發著令人不安的混沌氣息。\n");
    set("chat_chance", 5);
    set("chat_msg", ({"混沌獸發出低沉的咆哮，身形在黑霧中不斷扭曲變化。\n", "混沌獸的軀體忽然膨脹又縮小，彷彿隨時要化為另一種形態。\n"}));

    setup();

    add_temp("apply/attack", 70);
    add_temp("apply/defense", 70);
    add_temp("apply/damage", 50);
    add_temp("apply/armor", 60);
}
