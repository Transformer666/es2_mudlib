// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("村民", ({"villager", "guard"}));
    set_attr("str", 14);
    set_attr("dex", 12);
    set_attr("con", 16);
    set_attr("int", 10);
    set_attr("spi", 10);
    set_race("human");
    set_class("commoner");
    set_level(8);

    set_skill("staff", 30);

    set("age", 45);
    set("gender", "male");
    set("long",
        "一個面容憔悴的中年村民，手裡拄著一根木棍，警惕地守在\n"
        "村口。看來天寒村偶爾會有野獸出沒，需要有人看守。\n");

    setup();
    carry_object(STOCK_WEAPON("staff"))->wield();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}
