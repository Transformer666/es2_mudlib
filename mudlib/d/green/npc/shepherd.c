// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("牧羊人", ({"shepherd"}));
    set_attr("str", 14);
    set_attr("dex", 14);
    set_attr("con", 16);
    set_attr("int", 12);
    set_attr("spi", 14);
    set_race("human");
    set_class("commoner");
    set_level(8);

    set("age", 40);
    set("gender", "male");
    set("long",
        "一位臉龐黝黑的牧羊人，手持一根長鞭，正看顧著一群羊。他的皮\n"
        "膚被日曬得黝黑發亮，身上帶著草原特有的泥土氣息。\n");
    set("chat_chance", 4);
    set("chat_msg", ({
        "牧羊人吆喝了一聲，驅趕著走散的羊群。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
