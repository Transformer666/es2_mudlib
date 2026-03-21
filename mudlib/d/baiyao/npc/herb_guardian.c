// herb_guardian.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("草藥守衛", ({"herb_guardian", "guardian"}));
    set_attr("str", 22);
    set_attr("con", 20);
    set_attr("dex", 20);
    set_race("monster");
    set_class("fighter");
    set_level(14);

    set_skill("unarmed", 55);
    set_skill("dodge", 45);
    set_skill("parry", 35);

    set("age", 100);
    set("gender", "male");
    set("long",
        "一個由藤蔓和草藥纏繞而成的人形生物﹐渾身散發著濃烈的藥\n"
        "草氣息。它的雙臂是粗壯的藤條﹐頭部由一朵碩大的靈芝構成﹐\n"
        "正忠實地守護著這片藥圃。\n");
    set("attitude", "aggressive");
    setup();
    carry_money("coin", 45);
}
