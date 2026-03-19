// guobu.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("郭布", ({"guobu"}));
    set_attr("str", 20);
    set_attr("dex", 18);
    set_attr("wis", 16);
    set_race("human");
    set_class("fighter");
    set_level(35);

    set_skill("sword", 80);
    set_skill("dodge", 60);

    set("age", 55);
    set("long",
	"一個身材高大的老者﹐雖然年紀不小了﹐但雙目依然炯炯有神﹐\n"
	"身上散發著一股久經沙場的氣息。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
	"郭布嘆了口氣﹐自言自語道﹕唉﹐何時才能找到一個合適的傳人呢。\n",
	"郭布似乎在回憶什麼﹐眼神變得悠遠。\n",
    }));
    setup();
    carry_money("coin", 200);
}
