// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("天道主祭", ({"high priest", "high_priest", "priest"}));
    set_attr("str", 14);
    set_attr("dex", 14);
    set_attr("con", 16);
    set_attr("int", 26);
    set_attr("spi", 30);
    set_attr("wis", 28);
    set_race("human");
    set_class("commoner");
    set_level(45);

    set("age", 65);
    set("gender", "male");
    set("no_fight", 1);
    set("long",
        "天道主祭是天道神殿中地位最高的祭司，身穿金絲鑲邊的白色法袍，\n"
        "手持一柄玉如意。他面容莊嚴肅穆，眼神深邃而慈悲。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "天道主祭雙手合十，低聲誦念經文。\n",
        "天道主祭說道：天道無常，唯善是從。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
