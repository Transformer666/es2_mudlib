// vim: syntax=lpc
#include <npc.h>
inherit F_FIGHTER;
void create()
{
    set_name("長老", ({"elder", "zhang_lao"}));
    set_race("human");
    set_class("warrior");
    set_level(35);
    set_attr("str", 18);
    set_attr("con", 17);
    set_attr("dex", 16);
    set_skill("blade", 70);
    set_skill("dodge", 55);
    set_skill("parry", 50);
    set_skill("unarmed", 40);
    set("age", 55);
    set("gender", "male");
    set("long",
	"一位飽經風霜的長老坐在老榕樹下﹐悠然地品著茶。他的雙手厚\n"
	"實粗糙﹐掌心佈滿了數十年練刀磨出的老繭。雖然看似閒適﹐但眼\n"
	"神中卻透著一股銳利的警覺。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"長老端起茶杯輕啜一口﹐緩緩說道﹕刀法之道﹐重在一個「勢」字。\n",
	"長老望著遠處﹐感慨道﹕想當年我跟老掌門學刀﹐一把木刀劈了三千下才算入門。\n",
	"長老放下茶杯﹐說道﹕如今的年輕人﹐少了幾分吃苦的勁頭啊。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_object(STOCK_WEAPON("blade"))->wield();
    carry_money("coin", 100);
}
