// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("大邪道人", ({"evil daoist", "evil_daoist", "daoist"}));
    set("nickname", "大邪道人");
    set_attr("str", 30);
    set_attr("dex", 28);
    set_attr("con", 28);
    set_attr("int", 30);
    set_attr("spi", 35);
    set_attr("wis", 30);
    set_attr("cor", 25);
    set_attr("cps", 28);
    set_race("human");
    set_class("taoist");
    set_level(75);
    advance_stat("gin", 280);
    advance_stat("kee", 280);
    advance_stat("sen", 280);

    set_skill("sword", 120);
    set_skill("dodge", 100);
    set_skill("parry", 90);
    set_skill("force", 110);
    set_skill("unarmed", 80);

    set("age", 70);
    set("gender", "male");
    set("long",
        "大邪道人身穿一襲黑色道袍，面容枯槁，雙目中卻閃爍著攝人的精\n"
        "光。他是天邪派的幕後黑手，武功深不可測，江湖中人聞之色變。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "大邪道人冷笑道﹕天地萬物﹐不過是力量的棋子罷了。\n",
        "大邪道人閉目養神﹐周身散發著一股令人窒息的陰暗氣息。\n",
        "大邪道人喃喃自語﹕光明？黑暗？不過是弱者的藉口。\n",
        "大邪道人緩緩睜開雙眼﹐目光如兩道寒電﹐令人不寒而慄。\n",
    }));

    setup();

    add_temp("apply/attack", 90);
    add_temp("apply/defense", 90);
    add_temp("apply/damage", 40);
    add_temp("apply/armor", 80);

    carry_object("/obj/area/obj/longsword")->wield();
    carry_object("/obj/area/obj/cloth")->wear();
    set_temp("apply/vision_of_ghost", 1);
}
