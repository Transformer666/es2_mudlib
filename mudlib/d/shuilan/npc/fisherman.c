// NPC: /d/shuilan/npc/fisherman.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("老漁夫", ({"fisherman", "old fisherman"}));
    set_race("human");
    set_class("commoner");
    set_level(5);

    set("age", 58);
    set("gender", "male");
    set("long",
        "一個飽經風霜的老漁夫﹐皮膚被烈日曬得黝黑﹐滿臉皺紋像是\n"
        "被風乾的橘皮。他穿著一件打了補丁的短褂﹐赤著腳坐在碼頭邊\n"
        "修補漁網﹐動作嫻熟而專注。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "老漁夫嘆了口氣說道﹕今天的收成不好﹐魚都跑到深水去了。\n",
        "老漁夫抬頭看了看天色﹐喃喃說道﹕怕是要變天了。\n",
        "老漁夫哼著一首不知名的漁歌﹐手上的活計卻一刻也沒停。\n",
    }));
    setup();
    carry_money("coin", 15);
}
