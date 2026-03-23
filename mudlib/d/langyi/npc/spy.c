// vim: syntax=lpc
// spy.c - 瑯夷暗探
// Quest: 金蛇密函 (jinse_letter)
// Flow: talk about assassin/golden snake -> defeat assassin in passage
//       -> get jinse_letter -> give letter to spy -> reward

#include <npc.h>

inherit F_FIGHTER;

void do_reward(object player);

void create()
{
    set_name("瑯夷暗探", ({"spy", "langyi_spy"}));
    set_attr("str", 12);
    set_attr("con", 12);
    set_attr("dex", 18);
    set_race("human");
    set_class("thief");
    set_level(20);

    set_skill("dagger", 45);
    set_skill("dodge", 50);
    set_skill("parry", 35);

    set("age", 28);
    set("long",
        "一名身穿灰衣的瑯夷暗探﹐面容普通﹐放在人群中毫不起眼。\n"
        "他的眼神卻十分銳利﹐時刻警覺著周圍的動靜。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
        "暗探壓低聲音說道﹕最近通道裡來了個不速之客﹐得小心。\n",
        "暗探警惕地四處張望了一下。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_money("coin", 80);
}

int accept_object(object who, object ob)
{
    if( !ob->id("jinse letter") && !ob->id("jinse_letter") ) return 0;

    if( who->query("quest/jinse_letter_done") ) {
        do_chat("暗探搖搖頭﹐說道﹕這封信我已經看過了﹐你留著吧。\n");
        return 0;
    }
    if( !who->query_temp("pending/jinse_letter") ) {
        do_chat("暗探瞟了一眼﹐說道﹕這是什麼﹖看起來是金蛇門的東西。\n");
        return 0;
    }
    do_chat(({
        "暗探接過密函﹐小心地拆開蠟封﹐展開信紙細讀。\n",
        "暗探的臉色越來越凝重﹐最後深吸了一口氣。\n",
        "暗探說道﹕果然不出所料﹐金蛇門打算趁我們不備發動突襲。\n",
        "暗探鄭重道﹕多虧了你﹐我們才能及早防備。請收下這點薄禮。\n",
        (: do_reward, who :),
    }));
    return 1;
}

void do_reward(object player)
{
    object dagger;

    if( !player || !present(player, environment()) ) return;
    if( player->query("quest/jinse_letter_done") ) return;

    player->set("quest/jinse_letter_done", 1);
    player->delete_temp("pending/jinse_letter");
    player->gain_score("quest", 100);
    player->carry_money("silver", 3);

    message_vision(
        "暗探從懷中取出幾錠碎銀﹐遞給$N。\n",
        player);
    tell_object(player, "( 你獲得了 3 兩銀子 )\n");
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "金蛇") >= 0 || strsrch(msg, "殺手") >= 0
    ||  strsrch(msg, "assassin") >= 0 || strsrch(msg, "不速之客") >= 0
    ||  strsrch(msg, "通道") >= 0 || strsrch(msg, "可疑") >= 0 ) {
        if( ob->query("quest/jinse_letter_done") ) {
            do_chat("暗探微微頷首﹐說道﹕金蛇門的陰謀已經被你揭穿了﹐我們已做好防備。\n");
            return;
        }
        if( ob->query_temp("pending/jinse_letter") ) {
            do_chat(({
                "暗探壓低聲音說道﹕那殺手就在南邊的幽暗通道裡。\n",
                "暗探說道﹕殺了他﹐搜搜身上有沒有什麼線索。\n",
            }));
            return;
        }
        do_chat(({
            "暗探警覺地左右張望﹐確認無人偷聽﹐才壓低聲音說道﹕\n",
            "暗探說道﹕最近有個金蛇門的殺手潛入了我們的地道。\n",
            "暗探說道﹕此人武藝不弱﹐我們的人不敢輕舉妄動。\n",
            "暗探說道﹕但據我所知﹐金蛇門的殺手出任務時都會帶著密函。\n",
            "暗探說道﹕那密函裡記載著他們的行動計畫和聯絡暗號。\n",
            "暗探看了你一眼﹐說道﹕你若能解決那殺手﹐從他身上搜出密函﹐\n"
            "    拿來給我﹐我重重有賞。\n",
        }));
        ob->set_temp("pending/jinse_letter", 1);
        return;
    }

    if( strsrch(msg, "密函") >= 0 || strsrch(msg, "信") >= 0 ) {
        if( ob->query_temp("pending/jinse_letter") )
            do_chat("暗探說道﹕找到密函了﹖快拿來給我看看。\n");
        else
            do_chat("暗探淡淡地說道﹕什麼信﹖我不知道你在說什麼。\n");
        return;
    }
}
