// vim: syntax=lpc
#include <npc.h>
inherit F_SOLDIER;
void create()
{
    set_name("護閣弟子", ({"guard", "disciple", "hugedi"}));
    set_race("human");
    set_class("warrior");
    set_level(18);
    set_attr("str", 16);
    set_attr("con", 16);
    set_attr("dex", 14);
    set_skill("blade", 50);
    set_skill("dodge", 35);
    set_skill("parry", 40);
    set("age", 28);
    set("gender", "male");
    set("long",
	"一名肌肉結實的弟子筆直地站在藏刀閣門前﹐手中緊握著一把鋼\n"
	"刀﹐用警惕的目光打量著每一個經過的人。沒有掌門的許可﹐任何人\n"
	"都別想踏入此地半步。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"護閣弟子冷冷地掃視四周﹐沉聲道﹕藏刀閣重地﹐閒人勿近。\n",
	"護閣弟子握緊了手中的刀﹐低聲道﹕掌門交代的差事﹐不敢有半分懈怠。\n",
	"護閣弟子目不轉睛地盯著前方﹐說道﹕這裡的每一把刀都是門中至寶。\n",
    }));
    set("attitude", "peaceful");
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_object(STOCK_WEAPON("blade"))->wield();
    carry_money("coin", 60);
}
