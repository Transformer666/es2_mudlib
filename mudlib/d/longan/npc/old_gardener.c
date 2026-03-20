// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("老園丁", ({"gardener"}));
    set_attr("str", 10);
    set_attr("dex", 10);
    set_attr("con", 11);
    set_attr("int", 12);
    set_attr("spi", 12);
    set_attr("wis", 14);
    set_race("human");
    set_class("commoner");
    set_level(8);
    set("age", 60);
    set("gender", "male");
    set("long", "一位白髮蒼蒼的老園丁，正彎著腰在花園中侍弄花草。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "老園丁嘟囔道：今年的雨水不錯，花兒長得好。\n",
        "老園丁仔細端詳著一株草藥，若有所思。\n",
        "老園丁抬頭看看天色，自言自語道：看這天氣，明天該是個晴天。\n",
    }));
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}
