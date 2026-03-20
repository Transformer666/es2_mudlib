// vim: syntax=lpc

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("洗衣婦", ({"old woman", "woman"}));
    set_attr("str", 8);
    set_attr("dex", 10);
    set_attr("con", 10);
    set_attr("int", 10);
    set_attr("spi", 12);
    set_attr("wis", 12);
    set_race("human");
    set_class("commoner");
    set_level(3);
    set("age", 50);
    set("gender", "female");
    set("long", "一個在井邊洗衣的婦人，一邊搓洗著衣物一邊和人閒聊。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "洗衣婦低聲說道：你聽說了嗎？隔壁老王家的兒子考上武舉了！\n",
        "洗衣婦嘆了口氣：這天越來越冷了，衣服都不容易乾。\n",
        "洗衣婦抬頭張望了一下，又繼續搓洗衣物。\n",
    }));
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}
