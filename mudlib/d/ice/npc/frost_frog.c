// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("寒蟾", ({"frost frog", "frost_frog", "frog"}));
    set_attr("str", 14);
    set_attr("dex", 22);
    set_attr("con", 20);
    set_attr("int", 26);
    set_attr("spi", 28);
    set_race("human");
    set_class("commoner");
    set_level(40);
    set_skill("unarmed", 70);
    set_skill("dodge", 70);
    set("age", 600);
    set("gender", "male");
    set("long", "一隻翠綠色的小青蛙，看似不起眼，卻散發著令人窒息的寒氣。牠的法力強悍，據說是上古時代留存至今的妖獸。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "寒蟾呱呱叫了兩聲，四周的溫度驟降。\n",
        "寒蟾吐出一口寒霧，地面立刻結了一層薄冰。\n",
    }));
    set("attitude", "aggressive");
    setup();
}
