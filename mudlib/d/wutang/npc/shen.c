// shen.c

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void create()
{
    set_name("沈老闆", ({"shen", "boss_shen"}));
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 50);
    set("long",
	"一個白髮蒼蒼的老者﹐面前擺著一個小攤子﹐上面放滿了各種護\n"
	"身符和飾品。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
	"沈老闆笑咪咪地說道﹕客倌﹐來看看我的護身符吧﹐都是開過光的﹗\n",
	"沈老闆說道﹕這些護身符可以增強你的能力﹐戴上就知道好處了。\n",
    }));
    set("merchandise", ([
	__DIR__"obj/amulet" : 10,
    ]));

    setup();
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}
