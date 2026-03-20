// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("泉守", ({"spring_keeper", "keeper"}));
    set_attr("str", 14);
    set_attr("dex", 14);
    set_attr("con", 16);
    set_attr("int", 20);
    set_attr("spi", 22);
    set_race("human");
    set_class("commoner");
    set_level(20);
    set("age", 50);
    set("gender", "male");
    set("long",
        "泉守是一位守護泉域的中年道士，身穿青色道袍，面容和善。他\n"
        "負責維護溫泉的清潔和祠堂的香火。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "泉守說道：這溫泉有療傷之效，施主不妨泡泡。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
