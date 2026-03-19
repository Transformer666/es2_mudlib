#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("哭無望", ({"lieutenant", "kuwuwang"}));
    set_attr("str", 18);
    set_attr("con", 16);
    set_attr("dex", 20);
    set_attr("cps", 18);
    set_race("human");
    set_class("warrior");
    set_level(35);

    set_skill("sword", 65);
    set_skill("dodge", 60);
    set_skill("parry", 55);

    set("age", 38);
    set("attitude", "peaceful");
    set("long",
        "哭笑門左使哭無望﹐面容悲苦﹐似乎永遠在哭泣﹐但據說他\n"
        "的劍法在哭泣中反而更加凌厲。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_object( STOCK_WEAPON("longsword") )->wield();
    carry_money("silver", 25);
}
