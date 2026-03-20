// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("乞丐", ({"beggar"}));
    set_attr("str", 8);
    set_attr("dex", 10);
    set_attr("con", 8);
    set_attr("int", 10);
    set_attr("spi", 10);
    set_attr("wis", 10);
    set_race("human");
    set_class("commoner");
    set_level(3);
    set("age", 55);
    set("gender", "male");
    set("long", "一個衣衫襤褸的乞丐，蜷縮在暗巷的角落裡。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "乞丐伸出手：行行好，賞口飯吃吧。\n",
        "乞丐咳嗽了幾聲，縮了縮身子。\n",
        "乞丐低聲嘟囔著什麼，聽不太清楚。\n",
    }));
    setup();
}
