// vim: syntax=lpc
// Quest: bird_feather_done - 餵食鸂鷘獲得彩羽

#include <npc.h>

inherit F_VILLAGER;

private void give_feather(object player);

void create()
{
    set_name("鸂鷘", ({"charming bird", "charming_bird", "bird"}));
    set_attr("str", 18);
    set_attr("dex", 28);
    set_attr("con", 18);
    set_attr("int", 18);
    set_attr("spi", 24);
    set_race("human");
    set_class("commoner");
    set_level(35);
    set_skill("unarmed", 70);
    set_skill("dodge", 75);
    set("age", 500);
    set("gender", "male");
    set("long",
        "一隻身形端莊高雅的風鳥﹐漂亮的羽毛在陽光下折射出七彩光芒﹐\n"
        "優雅地棲息在崖邊的松枝上。牠高傲地昂著頭﹐偶爾展翅梳理自己\n"
        "的羽毛﹐似乎對來人毫不在意。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "鸂鷘展開華麗的羽翼﹐發出清脆的鳴叫。\n",
        "鸂鷘高傲地昂起頭﹐俯視著地面。\n",
        "鸂鷘用尖喙梳理著自己的羽毛﹐一根彩羽飄落又被牠叼回。\n",
    }));
    setup();
}

int accept_object(object player, object ob)
{
    if( !userp(player) ) return 0;

    if( player->query("quest/bird_feather_done") ) {
        do_chat("鸂鷘親暱地蹭了蹭你﹐似乎還記得你。\n");
        return 0;
    }

    // Accept food items (dried fish, rice cake, watermelon, etc.)
    if( !ob->id("dried_fish") && !ob->id("dried fish")
    &&  !ob->id("rice_cake") && !ob->id("rice cake")
    &&  !ob->id("watermelon") && !ob->id("melon")
    &&  !ob->id("wild_fruit") && !ob->id("wild fruit")
    &&  !ob->id("food") ) {
        do_chat("鸂鷘看了一眼﹐不屑地轉過頭去。\n");
        return 0;
    }

    do_chat(({
        "鸂鷘歪了歪頭﹐好奇地打量著你手中的食物。\n",
        "鸂鷘小心翼翼地從你手中啄走食物﹐開心地吞了下去。\n",
        "鸂鷘滿足地抖了抖羽毛﹐一根絢麗的彩羽隨風飄落。\n",
        (: give_feather, player :),
    }));
    return 1;
}

private void give_feather(object player)
{
    object feather;

    if( !player || environment(player) != environment() ) return;

    feather = new(__DIR__"obj/phoenix_feather");
    if( feather ) {
        if( feather->move(player) )
            feather->move(environment());
    }

    player->set("quest/bird_feather_done", 1);
    player->gain_score("quest", 100);
}

int accept_fight()
{
    do_chat("鸂鷘發出一聲尖銳的悲鳴﹐展翅飛走了。\n");
    return 0;
}
