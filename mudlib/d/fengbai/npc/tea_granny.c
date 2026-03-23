// NPC: /d/fengbai/npc/tea_granny.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("茶棚老婆婆", ({"granny", "tea_granny"}));
    set_race("human");
    set_class("commoner");
    set_level(2);

    set("age", 65);
    set("gender", "female");
    set("long",
        "一位滿頭白髮的老婆婆﹐臉上佈滿了皺紋﹐但笑起來十分慈祥。\n"
        "她一邊燒水煮茶﹐一邊和過路的客人閒話家常。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "茶棚老婆婆笑呵呵地說道﹕來﹐喝碗茶再走﹐不收你錢。\n",
        "茶棚老婆婆往爐子裡添了幾塊柴﹐嘴裡哼著小調。\n",
        "茶棚老婆婆嘆了口氣道﹕唉﹐現在走這條路的人越來越少了。\n",
    }));
    setup();
    carry_money("coin", 5);
}
