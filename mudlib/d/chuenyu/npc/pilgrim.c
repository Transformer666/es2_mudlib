// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("朝聖者", ({"pilgrim"}));
    set_attr("str", 10);
    set_attr("dex", 12);
    set_attr("con", 12);
    set_attr("int", 16);
    set_attr("spi", 20);
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("age", 35);
    set("gender", "female");
    set("long",
        "一位虔誠的朝聖者，她千里迢迢來到泉域祈福，臉上滿是風塵僕\n"
        "僕的疲憊，但眼中卻帶著希望。\n");
    set("chat_chance", 4);
    set("chat_msg", ({
        "朝聖者雙手合十，低聲祈禱著。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
