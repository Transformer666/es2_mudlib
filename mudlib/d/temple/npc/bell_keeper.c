// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("撞鐘僧", ({"bell keeper", "bell_keeper", "keeper"}));
    set_attr("str", 16);
    set_attr("dex", 12);
    set_attr("con", 16);
    set_attr("int", 16);
    set_attr("spi", 20);
    set_race("human");
    set_class("commoner");
    set_level(15);

    set("age", 45);
    set("gender", "male");
    set("long",
        "一位負責每日撞鐘的老僧，他身形消瘦，卻自有一股安詳寧靜的氣\n"
        "質。每當他撞響銅鐘，悠揚的鐘聲便迴盪在山谷之間。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "撞鐘僧說道：晨鐘暮鼓，警醒世人。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
