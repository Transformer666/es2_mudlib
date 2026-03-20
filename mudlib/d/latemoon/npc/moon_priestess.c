// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("月神祭司", ({"moon priestess", "moon_priestess", "priestess"}));
    set_attr("str", 14);
    set_attr("dex", 18);
    set_attr("con", 16);
    set_attr("int", 26);
    set_attr("spi", 30);
    set_attr("wis", 28);
    set_race("human");
    set_class("commoner");
    set_level(40);

    set("age", 200);
    set("gender", "female");
    set("no_fight", 1);
    set("long",
        "一位身著銀白長袍的女子，面容清冷如月，長髮如瀑，週身散發著柔\n"
        "和的銀色光芒。她是月神祭壇的守護者，已在此地守候了兩百年。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "月神祭司輕聲道：月光所照之處，萬物皆得安寧。\n",
        "月神祭司閉目凝神，祭壇上的月光似乎更亮了。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
