// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("香客", ({"pilgrim"}));
    set_attr("str", 10);
    set_attr("dex", 10);
    set_attr("con", 10);
    set_attr("int", 12);
    set_attr("spi", 14);
    set_attr("wis", 12);
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("age", 45);
    set("gender", "female");
    set("long", "一位虔誠的香客，手持香燭，正準備前往廟中上香祈福。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "香客雙手合十，口中唸唸有詞。\n",
        "香客輕聲說道：願神明保佑家人平安。\n",
        "香客小心翼翼地點燃了一炷香。\n",
    }));
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}
