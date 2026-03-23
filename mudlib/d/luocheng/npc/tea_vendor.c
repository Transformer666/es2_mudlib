// NPC: /d/luocheng/npc/tea_vendor.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("茶博士", ({"tea_vendor", "tea master"}));
    set_race("human");
    set_class("commoner");
    set_level(4);

    set("age", 50);
    set("gender", "male");
    set("long",
        "聚賢茶樓的茶博士﹐穿著一件藏青色的短褂﹐肩上搭著一條白\n"
        "毛巾。他手腳麻利﹐一把銅壺提得穩穩當當﹐從三尺高處往下沖\n"
        "茶﹐居然一滴不灑﹐功夫了得。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "茶博士吆喝道﹕龍井、碧螺春、鐵觀音﹐各位客倌要喝點什麼﹖\n",
        "茶博士一邊沏茶一邊說道﹕這壺明前龍井可是今年的新茶﹐香得很。\n",
    }));
    setup();
    carry_money("coin", 60);
}

void init()
{
    ::init();
    if( !is_fighting() )
        do_chat((: command, "say 客倌請坐﹐茶馬上就來﹗" :));
}

int accept_fight(object ob)
{
    do_chat((: command, "say 客倌息怒﹐茶樓裡不興動武的﹗" :));
    return 0;
}
