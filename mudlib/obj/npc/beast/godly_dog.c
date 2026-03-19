// godly_dog.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("天獒", ({"godly_dog", "mastiff"}));

    set_attr("str", 26);
    set_attr("con", 26);
    set_attr("dex", 24);
    set_race("human");
    set_class("fighter");
    set_level(60);
    advance_stat("gin", 500);
    advance_stat("kee", 500);

    set_skill("unarmed", 100);
    set_skill("dodge", 85);

    set("age", 900);
    set("long",
        "一頭身軀龐大無比的天獒，渾身電光閃爍，每踏出一步都在地面\n"
        "留下焦黑的痕跡，低沉的咆哮聲中夾雜著雷鳴。\n");

    setup();

    add_temp("apply/attack", 85);
    add_temp("apply/defense", 75);
    add_temp("apply/damage", 45);
    add_temp("apply/armor", 60);

    carry_money("silver", 50);
}
