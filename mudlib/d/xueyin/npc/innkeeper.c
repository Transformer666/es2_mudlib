#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("客棧掌櫃", ({"innkeeper", "shopkeeper"}));
    set_attr("str", 12);
    set_attr("con", 14);
    set_attr("dex", 10);
    set_attr("int", 14);
    set_race("human");
    set_class("commoner");
    set_level(8);

    set("age", 45);
    set("gender", "male");
    set("attitude", "peaceful");
    set("long",
        "掌櫃是個敦厚的中年漢子﹐臉上總是掛著笑容。聽說他原\n"
        "本也是雪吟莊的弟子﹐後來受了傷才退下來開客棧。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "掌櫃笑道﹕客倌﹐來碗熱湯麵吧﹐暖暖身子。\n",
        "掌櫃擦著酒杯﹐招呼著客人。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_money("coin", 100);
}
