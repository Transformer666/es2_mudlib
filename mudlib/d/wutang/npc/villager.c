// villager.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("村民", ({"villager", "wutang_villager"}));
    set_race("human");
    set_class("commoner");
    set_level(3);

    set("age", 30);
    set("long", "一個普普通通的五堂鎮村民。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
	"村民嘆了口氣﹐說道﹕最近山上好像不太平靜啊。\n",
	"村民看了看天色﹐自言自語道﹕不知道渡船什麼時候才能通航。\n",
	"村民說道﹕聽說武山洞窟裡有一座古老的神像﹐也不知道是真是假。\n",
    }));
    setup();
    carry_money("coin", 20);
}
