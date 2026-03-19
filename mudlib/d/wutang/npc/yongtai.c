// yongtai.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("雍泰", ({"yongtai"}));
    set_race("human");
    set_class("commoner");
    set_level(15);

    set("age", 35);
    set("long",
	"一個中等身材的男子﹐穿著一件藏青色的長衫﹐正靠在櫃臺邊悠\n"
	"閒地翻看著帳簿。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"雍泰說道﹕醇雨樓開業這麼多年﹐在五堂鎮也算是老字號了。\n",
	"雍泰翻了翻帳簿﹐嘀咕道﹕最近生意還不錯嘛。\n",
    }));
    setup();
    carry_money("coin", 300);
}
