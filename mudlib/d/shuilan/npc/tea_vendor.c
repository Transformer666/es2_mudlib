// NPC: /d/shuilan/npc/tea_vendor.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("茶寮老闆", ({"tea_vendor", "tea seller", "boss"}));
    set_race("human");
    set_class("commoner");
    set_level(4);

    set("age", 62);
    set("gender", "male");
    set("long",
        "一個精瘦的老頭﹐臉上的皺紋像是河水沖刷出來的溝壑。他穿\n"
        "著一件洗得發白的長衫﹐一邊慢悠悠地沏著茶﹐一邊跟客人閒聊。\n"
        "別看他年紀大了﹐耳朵卻靈得很﹐什麼消息都瞞不過他。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "茶寮老闆一邊沏茶一邊說道﹕聽說北邊雪亭鎮最近不太平靜啊。\n",
        "茶寮老闆壓低聲音說道﹕前幾天有人在河上看到一條大魚﹐有船那麼大﹗\n",
        "茶寮老闆搖頭嘆道﹕如今世道不太平﹐出門在外可得多加小心。\n",
    }));
    setup();
    carry_money("coin", 40);
}

void init()
{
    ::init();
    if( !is_fighting() )
        do_chat((: command, "say 客倌喝杯茶歇歇腳吧。" :));
}

int accept_fight(object ob)
{
    do_chat((: command, "say 哎哎﹐別動手﹐有話好說﹗" :));
    return 0;
}
