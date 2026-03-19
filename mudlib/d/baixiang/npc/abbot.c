// abbot.c - Baixiang Temple Abbot

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("白象寺方丈", ({"abbot", "fangzhang"}));
    set_attr("str", 20);
    set_attr("con", 22);
    set_attr("wis", 25);
    set_attr("spi", 24);
    set_attr("cps", 22);
    set_race("human");
    set_class("monk");
    set_level(60);

    set_skill("staff", 90);
    set_skill("diamond hammer", 85);
    set_skill("dodge", 75);
    set_skill("parry", 80);
    set_skill("unarmed", 70);

    set("age", 65);
    set("attitude", "peaceful");
    set("long",
	"白象寺方丈﹐身穿一件洗得發白的灰色僧袍﹐面容慈祥﹐雙手\n"
	"合十﹐身形雖然消瘦﹐但自有一股不怒而威的氣勢。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"方丈微微一笑﹐說道﹕施主﹐萬法皆空﹐放下即是自在。\n",
    }));
    setup();
    carry_money("coin", 100);
}
