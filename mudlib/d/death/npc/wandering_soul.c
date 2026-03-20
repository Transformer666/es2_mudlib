// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("遊魂", ({"wandering_soul", "soul"}));
    set_attr("str", 12);
    set_attr("dex", 18);
    set_attr("con", 10);
    set_attr("int", 8);
    set_attr("spi", 14);
    set_race("human");
    set_class("commoner");
    set_level(15);
    set_skill("unarmed", 30);
    set_skill("dodge", 50);
    set("age", 200);
    set("gender", "male");
    set("long",
        "一個飄忽不定的半透明身影，面容模糊不清。這是一個迷失在死\n"
        "域中的遊魂，不知已在此徘徊了多少年。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "遊魂發出微弱的嗚咽聲。\n",
        "遊魂伸出手，似乎想要抓住什麼。\n",
    }));
    setup();
}
