#include <npc.h>

inherit F_FIGHTER;

void create()
{
    set_name("銀蛟弟子", ({"disciple", "yinjiao_disciple"}));
    set_attr("str", 15);
    set_attr("con", 14);
    set_attr("dex", 16);
    set_race("human");
    set_class("warrior");
    set_level(12);

    set_skill("claw", 30);
    set_skill("dodge", 25);
    set_skill("parry", 20);

    set("age", 24);
    set("gender", "male");
    set("long",
        "一名銀蛟幫的弟子﹐身穿黑色勁裝﹐雙手如鷹爪般鋒利﹐目光銳利地盯著前方。\n");
    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 35);
}
