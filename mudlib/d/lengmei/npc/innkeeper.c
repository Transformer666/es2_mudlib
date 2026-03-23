#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("客棧掌櫃", ({"innkeeper", "shopkeeper"}));
    set_attr("str", 10);
    set_attr("con", 12);
    set_attr("dex", 12);
    set_attr("int", 14);
    set_race("human");
    set_class("commoner");
    set_level(8);

    set("age", 40);
    set("gender", "male");
    set("attitude", "peaceful");
    set("long",
        "客棧掌櫃是個四十來歲的中年人﹐面容和善﹐總是笑呵呵地\n"
        "招呼著客人。聽說他釀的梅花酒遠近聞名。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "掌櫃笑道﹕客倌﹐來杯梅花酒吧﹐自家釀的﹐味道不錯。\n",
        "掌櫃擦了擦桌子﹐哼著小曲。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_money("coin", 80);
}
