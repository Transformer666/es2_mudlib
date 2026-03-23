// NPC: /d/lengmei/npc/servant.c
// Quest: 梅園夜影 — servant reports suspicious footprints in plum garden
// Flow: talk to servant -> search footprints in plum_garden -> return to report

#include <npc.h>

inherit F_VILLAGER;

void give_reward(object player);

void create()
{
    set_name("莊丁", ({"servant", "zhuangding"}));
    set_attr("str", 12);
    set_attr("con", 12);
    set_attr("dex", 10);
    set_race("human");
    set_class("commoner");
    set_level(8);

    set("age", 30);
    set("attitude", "peaceful");
    set("long",
        "一名冷梅莊的莊丁﹐正在打掃院落。他不時朝梅園的方向張望﹐\n"
        "似乎心裡藏著什麼事。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "莊丁一邊掃地一邊朝梅園方向張望。\n",
        "莊丁低聲嘟囔道﹕那些腳印到底是誰留下的 ...\n",
    }));

    setup();
    carry_object( STOCK_ARMOR("cloth") )->wear();
    carry_money("coin", 15);
}

void init()
{
    ::init();
    if( is_fighting() || is_chatting() ) return;
    if( !userp(this_player()) ) return;

    if( this_player()->query("quest/lengmei_garden_done") ) return;

    if( this_player()->query_temp("pending/lengmei_garden") == 2 ) {
        do_chat("莊丁見到你﹐連忙迎上前來﹐問道﹕你在梅園有什麼發現嗎﹖\n");
        return;
    }

    if( this_player()->query_temp("pending/lengmei_garden") == 1 ) {
        do_chat("莊丁對你說道﹕快去梅園看看吧﹐search 那些奇怪的腳印。\n");
        return;
    }

    do_chat("莊丁焦急地朝你招了招手﹐似乎有話要說。\n");
}

private void give_reward(object player)
{
    object money;

    if( !player || environment(player) != environment() ) return;

    player->set("quest/lengmei_garden_done", 1);
    player->gain_score("quest", 80);

    money = new("/obj/money/silver");
    money->set_amount(2);
    if( !money->move(player) )
        money->move(environment());
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;
    if( ob->query("quest/lengmei_garden_done") ) return;

    // Stage 2: player found the letter and returned
    if( ob->query_temp("pending/lengmei_garden") == 2 ) {
        if( strsrch(msg, "信") >= 0 || strsrch(msg, "弟子") >= 0
        ||  strsrch(msg, "找到") >= 0 || strsrch(msg, "發現") >= 0
        ||  strsrch(msg, "偷") >= 0 || strsrch(msg, "寒梅劍") >= 0 ) {
            do_chat(({
                "莊丁驚道﹕什麼﹖有人想偷寒梅劍﹖\n",
                "莊丁說道﹕難怪這幾天梅園裡總有動靜﹐原來是被逐出門牆的弟子想回來偷東西﹗\n",
                "莊丁說道﹕多虧你發現了這件事﹐我得趕緊稟報莊主。這是我的一點心意﹐你收下吧。\n",
                (: give_reward, ob :),
            }));
            return;
        }
    }

    // Stage 0: initial conversation about the footprints
    if( !ob->query_temp("pending/lengmei_garden") ) {
        if( strsrch(msg, "什麼事") >= 0 || strsrch(msg, "怎麼") >= 0
        ||  strsrch(msg, "腳印") >= 0 || strsrch(msg, "梅園") >= 0
        ||  strsrch(msg, "你好") >= 0 || strsrch(msg, "招手") >= 0 ) {
            do_chat(({
                "莊丁壓低聲音說道﹕這位客官﹐我這幾天在梅園發現了一些奇怪的腳印。\n",
                "莊丁說道﹕那些腳印不像是莊裡弟子的﹐倒像是有外人趁夜潛入。\n",
                "莊丁說道﹕我不敢驚動莊主﹐怕是虛驚一場 ... 你能不能幫我去梅園看看﹖\n",
                "莊丁說道﹕進了院子往東走就是梅園﹐仔細 search 地上的腳印看看。\n",
            }));
            ob->set_temp("pending/lengmei_garden", 1);
            return;
        }
    }
}
