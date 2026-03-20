// vim: syntax=lpc
#include <npc.h>
inherit F_VILLAGER;
void create()
{
    set_name("廚子", ({"cook", "chuzi"}));
    set_race("human");
    set_class("commoner");
    set_level(8);
    set_attr("str", 14);
    set_attr("con", 15);
    set("age", 38);
    set("gender", "male");
    set("long",
	"一個身材壯實的廚子﹐粗壯的臂膀上滿是油煙燻染的痕跡。他正\n"
	"在灶台前忙碌著﹐為虎刀門的弟子們烹煮大鍋大鍋的肉食。額頭上\n"
	"不斷滲出汗珠﹐卻絲毫不影響他手中的動作。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"廚子一邊翻炒著鍋中的菜﹐一邊嘟囔道﹕這幫練刀的小子﹐一個比一個能吃。\n",
	"廚子擦了擦額頭上的汗﹐說道﹕今天又得多燉兩鍋肉﹐不然不夠分。\n",
	"廚子朝灶台上吹了吹火﹐自言自語道﹕虎刀門的人﹐不吃肉哪來力氣揮刀。\n",
    }));
    set("attitude", "peaceful");
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_money("coin", 20);
}
