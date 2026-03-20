// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("客棧老闆娘", ({"village innkeeper", "village_innkeeper", "innkeeper"}));
    set_attr("str", 12);
    set_attr("dex", 14);
    set_attr("con", 14);
    set_attr("int", 16);
    set_attr("spi", 14);
    set_race("human");
    set_class("commoner");
    set_level(10);

    set("age", 35);
    set("gender", "female");
    set("long",
        "客棧老闆娘是個三十多歲的婦人，身材微胖，臉上總是掛著熱情的笑\n"
        "容。她做的飯菜在附近幾個村子都小有名氣。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "老闆娘笑道：客官，要吃點什麼？\n",
        "老闆娘麻利地擦著桌子。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
