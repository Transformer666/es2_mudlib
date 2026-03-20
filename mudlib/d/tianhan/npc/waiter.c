// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("店小二", ({"waiter", "xiaoer"}));
    set_attr("str", 10);
    set_attr("dex", 14);
    set_attr("con", 12);
    set_attr("int", 13);
    set_attr("spi", 11);
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 20);
    set("gender", "male");
    set("long",
        "一個手腳麻利的年輕人，肩上搭著一條白毛巾，笑嘻嘻地招\n"
        "呼著來往的客人。你可以用 list 看看菜單，用 buy 來點菜。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "店小二吆喝道：客官裡面請！本店白切肉天下一絕！\n",
        "店小二擦了擦桌子，招呼道：客官要來點什麼？\n",
    }));

    setup();
    carry_money("coin", 50);
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
