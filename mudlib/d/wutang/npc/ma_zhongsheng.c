// vim: syntax=lpc

#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("馬鍾聖", ({"ma_zhongsheng", "ma"}));
    set_attr("str", 30);
    set_attr("dex", 26);
    set_attr("con", 28);
    set_attr("int", 16);
    set_attr("spi", 16);
    set_attr("wis", 18);
    set_race("blackteeth");
    set_class("commoner");
    set_level(60);

    set_skill("unarmed", 110);
    set_skill("parry", 80);
    set_skill("dodge", 75);
    set_skill("force", 80);

    set("age", 50);
    set("gender", "male");
    set("long", "馬鍾聖是「大漠八魔」中排行老五，拳法造詣極深，"
        "為人沈默寡言，很少說話，殺起人來卻也是異常殘忍。"
        "他虎背熊腰，看起來約五十多歲。\n");
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    set_temp("apply/vision_of_ghost", 1);
}
