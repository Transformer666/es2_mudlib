// NPC: /d/babao/npc/mansion_guard.c

#include <npc.h>

inherit F_SOLDIER;

void create()
{
    set_name("府衛", ({"mansion guard", "guard"}));
    set_attr("str", 22);
    set_attr("dex", 18);
    set_attr("con", 20);
    set_attr("int", 12);
    set_attr("spi", 10);
    set_race("human");
    set_class("warrior");
    set_level(25);

    set_skill("sword", 80);
    set_skill("parry", 60);
    set_skill("dodge", 50);
    set_skill("unarmed", 40);

    set("age", 30);
    set("gender", "male");
    set("long",
        "一名身披鎧甲的將軍府護衛，腰懸長劍，目光如鷹隼般銳利。\n"
        "他筆挺地站在府門前，渾身散發著一股久經沙場的肅殺之氣。\n");

    setup();
    carry_object(STOCK_WEAPON("longsword"))->wield();
    carry_object(STOCK_ARMOR("armor"))->wear();
}
