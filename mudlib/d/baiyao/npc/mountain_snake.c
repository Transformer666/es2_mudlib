// mountain_snake.c

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("山蛇", ({"mountain_snake", "snake"}));
    set_attr("str", 14);
    set_attr("con", 14);
    set_attr("dex", 22);
    set_race("animal");
    set_class("fighter");
    set_level(10);

    set_skill("unarmed", 40);
    set_skill("dodge", 50);

    set("age", 5);
    set("gender", "female");
    set("long",
        "一條青綠色的山蛇﹐身長約四尺﹐鱗片在光線下泛著幽幽的\n"
        "綠光。它盤踞在岩石之間﹐扁平的三角形頭部微微昂起﹐吐著\n"
        "細長的信子﹐警惕地注視著周圍的動靜。\n");
    set("attitude", "aggressive");
    setup();
    carry_money("coin", 20);
}
