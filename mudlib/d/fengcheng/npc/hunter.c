// NPC: /d/fengcheng/npc/hunter.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("山中獵戶", ({"hunter", "mountain hunter"}));
    set_race("human");
    set_class("commoner");
    set_level(10);

    set("age", 38);
    set("gender", "male");
    set("long",
        "一個身材精悍的獵戶﹐穿著一件狼皮大氅﹐背上背著一張硬弓。\n"
        "他的臉被寒風吹得通紅﹐但一雙眼睛卻炯炯有神﹐透著一股子機\n"
        "警和警覺﹐一看就是常年在山中打獵的老手。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "山中獵戶說道﹕天山裡的野獸可不好對付﹐我上次差點被一頭黑熊撕了。\n",
        "山中獵戶壓低聲音說道﹕聽說天山深處有雪狐出沒﹐那皮毛可值錢了。\n",
        "山中獵戶搓著手說道﹕今天冷得很﹐山裡更冷﹐明天怕是出不了門了。\n",
    }));
    setup();
    carry_object(STOCK_WEAPON("shortblade"))->wield();
    carry_object(STOCK_ARMOR("leather"))->wear();
    carry_money("coin", 80);
}
