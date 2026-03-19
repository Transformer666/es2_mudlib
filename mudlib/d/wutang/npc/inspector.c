// inspector.c

#include <npc.h>

inherit F_SCHOLAR;

void create()
{
    set_name("御史大人", ({"inspector", "yushi"}));
    set_attr("int", 20);
    set_attr("wis", 22);
    set_race("human");
    set_class("scholar");
    set_level(30);

    set("age", 40);
    set("attitude", "peaceful");
    set("long",
	"一個身穿官服的中年文官﹐眉頭深鎖﹐似乎正在為什麼事情煩\n"
	"惱。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
	"御史大人皺著眉頭看著案上的公文﹐喃喃自語道﹕這件案子果然蹊蹺。\n",
	"御史大人嘆了口氣﹐說道﹕五堂鎮最近不太太平啊。\n",
    }));
    setup();
    carry_money("coin", 1000);
}
