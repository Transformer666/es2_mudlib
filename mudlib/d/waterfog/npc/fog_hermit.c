// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("霧中隱者", ({"fog hermit", "fog_hermit", "hermit"}));
    set_attr("str", 14);
    set_attr("dex", 16);
    set_attr("con", 16);
    set_attr("int", 24);
    set_attr("spi", 28);
    set_race("human");
    set_class("commoner");
    set_level(35);

    set("age", 80);
    set("gender", "male");
    set("long",
        "一位隱居在霧林小島上的白髮老者，身穿灰色麻袍，似乎已經習慣\n"
        "了這片迷霧。他身旁放著幾本泛黃的古籍，正在靜靜地品茶。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "霧中隱者說道：迷霧之中，方見真心。\n",
        "霧中隱者抿了口茶，意味深長地看著你。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
