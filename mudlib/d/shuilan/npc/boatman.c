// NPC: /d/shuilan/npc/boatman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("船夫", ({"boatman", "ferryman"}));
    set_race("human");
    set_class("commoner");
    set_level(8);

    set("age", 40);
    set("gender", "male");
    set("long",
        "一個身材壯碩的漢子﹐臂膀上的肌肉隆起﹐一看就是常年划船\n"
        "練出來的。他蹲在碼頭邊抽著旱煙﹐不時瞇著眼睛望向遠處的河\n"
        "面﹐似乎在等什麼人。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "船夫說道﹕要過河的話﹐往北門外走﹐那邊有渡船。\n",
        "船夫吐了一口煙圈﹐說道﹕這羿水可不好渡﹐水下暗流多著呢。\n",
    }));
    setup();
    carry_money("coin", 30);
}
