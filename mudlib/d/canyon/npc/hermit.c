// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("隱居老人", ({"hermit"}));
    set_attr("str", 14);
    set_attr("dex", 14);
    set_attr("con", 16);
    set_attr("int", 22);
    set_attr("spi", 24);
    set_race("human");
    set_class("commoner");
    set_level(30);
    set("age", 75);
    set("gender", "male");
    set("long",
        "一位隱居在峽谷岩棚上的白髮老人，鬚髮皆白，面容清癯，似\n"
        "乎已在此修行多年。他面前擺著一盤殘棋，不知在和誰對弈。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "老人抬頭看了你一眼，又低頭繼續下棋。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
