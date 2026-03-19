// ferryman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("渡船夫", ({"ferryman"}));
    set_attr("str", 16);
    set_attr("con", 18);
    set_race("human");
    set_class("commoner");
    set_level(10);

    set("age", 50);
    set("long",
	"一個皮膚黝黑的老船夫﹐雙手滿是老繭﹐正坐在碼頭邊抽著旱\n"
	"煙。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
	"渡船夫吐了一口煙﹐說道﹕河水最近漲了﹐渡船怕是要再等等了。\n",
	"渡船夫說道﹕以前這渡口可熱鬧了﹐每天都有商旅往來。\n",
	"渡船夫望著河面﹐似乎在想什麼心事。\n",
    }));
    setup();
    carry_money("coin", 50);
}
