// vim: syntax=lpc
// NPC: fog_hermit.c - 霧中隱者
// Quest: 霧林蜈蚣 (fog_centipede)
// Flow: talk about centipede/danger -> sets pending -> player kills centipede
//       -> give venom_sac to hermit -> reward

#include <npc.h>

inherit F_VILLAGER;

void do_reward(object player);

void create()
{
    set_name("霧中隱者", ({"fog hermit", "fog_hermit", "hermit"}));
    set_attr("str", 14);
    set_attr("dex", 16);
    set_attr("con", 16);
    set_attr("int", 24);
    set_attr("spi", 28);
    set_race("human");
    set_class("commoner");
    set_level(35);

    set("age", 80);
    set("gender", "male");
    set("long",
        "一位隱居在霧林小島上的白髮老者，身穿灰色麻袍，似乎已經習慣\n"
        "了這片迷霧。他身旁放著幾本泛黃的古籍，正在靜靜地品茶。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "霧中隱者說道：迷霧之中，方見真心。\n",
        "霧中隱者抿了口茶，意味深長地看著你。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}

int accept_object(object who, object ob)
{
    if( !ob->id("venom sac") && !ob->id("venom_sac") ) return 0;

    if( who->query("quest/fog_centipede_done") ) {
        do_chat("霧中隱者搖搖頭﹐說道﹕這個你留著吧﹐老夫已經有了。\n");
        return 0;
    }
    if( !who->query_temp("pending/fog_centipede") ) {
        do_chat("霧中隱者說道﹕這是什麼東西﹖腥臭得很。\n");
        return 0;
    }
    do_chat(({
        "霧中隱者接過毒囊﹐仔細端詳了一番。\n",
        "霧中隱者驚道﹕果然是那條大蜈蚣的毒囊﹗你竟然殺了牠﹖\n",
        "霧中隱者讚許道﹕好﹗好﹗有了這毒囊﹐老夫便能煉製解毒的藥物了。\n",
        "霧中隱者說道﹕收下這些東西﹐算是老夫的一點心意。\n",
        (: do_reward, who :),
    }));
    return 1;
}

void do_reward(object player)
{
    if( !player || !present(player, environment()) ) return;
    if( player->query("quest/fog_centipede_done") ) return;

    player->set("quest/fog_centipede_done", 1);
    player->delete_temp("pending/fog_centipede");
    player->gain_score("quest", 100);
    player->carry_money("silver", 3);

    message_vision(
        "霧中隱者從懷中取出幾錠碎銀﹐遞給$N。\n",
        player);
    tell_object(player, "( 你獲得了 3 兩銀子 )\n");
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "蜈蚣") >= 0 || strsrch(msg, "centipede") >= 0
    ||  strsrch(msg, "危險") >= 0 || strsrch(msg, "蟲") >= 0
    ||  strsrch(msg, "毒") >= 0 || strsrch(msg, "幫忙") >= 0 ) {
        if( ob->query("quest/fog_centipede_done") ) {
            do_chat("霧中隱者微笑道﹕多虧了你﹐那條蜈蚣已經不會再禍害人了。\n");
            return;
        }
        if( ob->query_temp("pending/fog_centipede") ) {
            do_chat(({
                "霧中隱者壓低聲音說道﹕那條大蜈蚣就在東邊迷霧深處出沒﹐\n",
                "霧中隱者說道﹕你到那裡仔細搜尋蹤跡﹐也許能引出牠。\n",
            }));
            return;
        }
        do_chat(({
            "霧中隱者放下茶杯﹐嘆了口氣。\n",
            "霧中隱者說道﹕老夫隱居此處多年﹐本來清靜得很。\n",
            "霧中隱者說道﹕可近來東邊的迷霧深處來了一條大蜈蚣﹐兇猛異常。\n",
            "霧中隱者說道﹕那蜈蚣身長數丈﹐渾身劇毒﹐已經傷了好幾個誤入的旅人。\n",
            "霧中隱者打量了你一番﹐說道﹕看你武藝不弱﹐能否幫老夫除了這禍害﹖\n",
            "霧中隱者說道﹕你到東邊深處去﹐搜尋蜈蚣的蹤跡便能引出牠。\n",
            "霧中隱者說道﹕若能取回牠的毒囊﹐老夫可以用來煉製解毒藥物﹐也算造福後人。\n",
        }));
        ob->set_temp("pending/fog_centipede", 1);
        return;
    }
}
