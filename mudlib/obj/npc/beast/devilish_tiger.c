// devilish_tiger.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("狻猊", ({"devilish_tiger", "tiger"}));

    set_attr("str", 30);
    set_attr("con", 28);
    set_attr("dex", 20);
    set_race("human");
    set_class("fighter");
    set_level(65);
    advance_stat("gin", 550);
    advance_stat("kee", 550);

    set_skill("unarmed", 110);
    set_skill("dodge", 70);

    set("age", 1200);
    set("long",
        "一頭巨大的黑虎，雙瞳閃爍著幽紫色的光芒，周身不斷滲出濃\n"
        "密的黑暗氣息，所到之處光線都為之黯淡。\n");

    setup();

    add_temp("apply/attack", 100);
    add_temp("apply/defense", 70);
    add_temp("apply/damage", 60);
    add_temp("apply/armor", 80);

    carry_money("silver", 60);
}
