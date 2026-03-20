// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("囚犯", ({"prisoner"}));
    set_attr("str", 10);
    set_attr("dex", 10);
    set_attr("con", 10);
    set_attr("int", 10);
    set_attr("spi", 8);
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 30);
    set("gender", "male");
    set("long",
        "一個面容憔悴的囚犯，衣衫襤褸，手腳都戴著沉重的鐵鏈。他蜷縮\n"
        "在牢房的角落，目光呆滯。\n");
    set("chat_chance", 4);
    set("chat_msg", ({
        "囚犯低聲呻吟著。\n",
        "囚犯喃喃自語道：我是冤枉的 ...\n",
    }));
    setup();
}
