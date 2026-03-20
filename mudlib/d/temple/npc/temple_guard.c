// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("護殿武僧", ({"temple guard", "temple_guard", "guard"}));
    set_attr("str", 22);
    set_attr("dex", 20);
    set_attr("con", 22);
    set_attr("int", 14);
    set_attr("spi", 18);
    set_race("human");
    set_class("commoner");
    set_level(35);

    set_skill("staff", 70);
    set_skill("dodge", 55);
    set_skill("parry", 60);
    set_skill("unarmed", 60);

    set("age", 30);
    set("gender", "male");
    set("long",
        "一名身穿僧袍的武僧，身材高大健壯，雙手合十站在殿門兩側。他的\n"
        "目光銳利，時刻警惕著任何可疑的動靜。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "護殿武僧警覺地掃視四周。\n",
    }));
    setup();
    carry_object(STOCK_WEAPON("staff"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
