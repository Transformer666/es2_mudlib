// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("山中隱士", ({"mountain_hermit", "hermit"}));
    set_attr("str", 16);
    set_attr("dex", 16);
    set_attr("con", 18);
    set_attr("int", 24);
    set_attr("spi", 26);
    set_race("human");
    set_class("commoner");
    set_level(35);
    set("age", 65);
    set("gender", "male");
    set("long",
        "一位隱居在羊山山洞中的老者，蓬頭垢面，衣衫破舊，但談吐間\n"
        "卻流露出非凡的見識。據說他曾是朝廷中的高官，厭倦了官場的爾\n"
        "虞我詐才隱居山林。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "隱士嘆了口氣，說道：世事如棋，不過一場空。\n",
        "隱士望著遠方的群山，若有所思。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
