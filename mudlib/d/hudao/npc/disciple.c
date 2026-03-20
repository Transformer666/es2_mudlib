// vim: syntax=lpc
#include <npc.h>
inherit F_FIGHTER;
void create()
{
    set_name("虎刀弟子", ({"disciple", "dizi"}));
    set_race("human");
    set_class("warrior");
    set_level(15);
    set_attr("str", 14);
    set_attr("con", 13);
    set_attr("dex", 15);
    set_skill("blade", 35);
    set_skill("dodge", 25);
    set_skill("parry", 20);
    set("age", 22);
    set("gender", "male");
    set("long",
	"一名虎刀門的年輕弟子﹐身穿簡樸的練功服。他的雙手因長年練\n"
	"習刀法而磨出了厚厚的繭子﹐眼神中透著一股堅毅不屈的神色。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"虎刀弟子活動了一下手腕﹐自言自語道﹕今天的刀法練得還不夠﹐明天得加倍。\n",
	"虎刀弟子靠在牆邊﹐說道﹕師父說了﹐刀要練到與手合一﹐才算入門。\n",
	"虎刀弟子擦拭著手中的刀﹐嘟囔道﹕什麼時候才能像長老那樣一刀劈開巨石。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_object(STOCK_WEAPON("blade"))->wield();
    carry_money("coin", 30);
}
