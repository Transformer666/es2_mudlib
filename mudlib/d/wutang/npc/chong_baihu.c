// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("崇白虎", ({"chong_baihu", "chong"}));
    set_attr("str", 28);
    set_attr("dex", 24);
    set_attr("con", 26);
    set_attr("int", 20);
    set_attr("spi", 18);
    set_attr("wis", 18);
    set_race("yaksha");
    set_class("commoner");
    set_level(55);

    set_skill("blade", 100);
    set_skill("parry", 75);
    set_skill("dodge", 65);
    set_skill("force", 70);

    set("age", 50);
    set("gender", "male");
    set("long", "崇白虎是「大漠八魔」之一，一生都在追求完美的鑄刀技巧，"
        "為了能鑄出一把寶刀，不惜千里跋涉到奐族境內偷學手藝。"
        "他看起來約五十多歲。\n");
    setup();
    carry_object(STOCK_WEAPON("blade"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
