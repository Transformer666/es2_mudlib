// temple_master.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("神殿住持", ({"temple_master", "master"}));
    set_attr("int", 20);
    set_attr("wis", 25);
    set_attr("spi", 22);
    set_race("human");
    set_class("commoner");
    set_level(45);

    set("age", 70);
    set("attitude", "peaceful");
    set("long",
	"一個鬚髮皆白的老者﹐身穿一件素白的道袍﹐盤坐在神像前的蒲\n"
	"團上﹐雙目微閉﹐似乎正在入定。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"住持微微睜開雙目﹐淡淡地說道﹕萬物有靈﹐善惡有報。\n",
    }));
    setup();
}
