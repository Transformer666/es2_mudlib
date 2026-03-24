// vim: syntax=lpc
// NPC: /d/kangping/npc/farmer.c
// Quest: 田間野豬 (field_boar) - 幫農夫驅除禍害田地的野豬

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("農夫", ({"farmer"}));
    set_attr("str", 14);
    set_attr("dex", 10);
    set_attr("con", 14);
    set_attr("int", 8);
    set_attr("spi", 10);
    set_attr("wis", 10);
    set_race("human");
    set_class("commoner");
    set_level(5);
    set("age", 40);
    set("gender", "male");
    set("long", "一個皮膚黝黑的農夫，正扛著農具沿路走著。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "農夫擦了擦汗說道：今年的收成應該不錯。\n",
        "農夫抬頭看看天色：這天要是下場雨就好了。\n",
        "農夫嘟囔著：地裡的莊稼該施肥了。\n",
    }));
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}

private void spawn_boar(object player)
{
    object boar, env;

    if( !player || !environment(player) ) return;
    env = environment();

    // 在農夫所在房間生成野豬
    boar = new(__DIR__"wild_boar");
    if( !boar ) return;
    boar->move(env);
    tell_room(env, "忽然間﹐田邊的草叢一陣騷動﹐一頭碩大的野豬從草叢中衝了出來﹗\n");
}

private void give_reward(object player)
{
    object money;

    if( !player || environment(player) != environment() ) return;

    money = new("/obj/money/coin");
    money->set_amount(200);
    if( !money->move(player) )
        money->move(environment());

    player->set("quest/field_boar_done", 1);
    player->gain_score("quest", 80);
}

void init()
{
    ::init();
    if( is_fighting() || is_chatting() ) return;
    if( !userp(this_player()) ) return;

    if( this_player()->query("quest/field_boar_done") )
        return;

    if( this_player()->query_temp("pending/field_boar") == 2 ) {
        do_chat("農夫看了看你﹐驚喜地說道：你把那頭野豬收拾了﹖\n");
        return;
    }
}

int accept_object(object ob, object item)
{
    if( !userp(ob) ) return 0;
    if( is_chatting() ) return 0;
    if( ob->query("quest/field_boar_done") ) return 0;

    if( ob->query_temp("pending/field_boar") == 2
    &&  item->query("id") == "boar tusk" ) {
        do_chat(({
            "農夫接過獠牙﹐翻來覆去看了看﹐鬆了一口氣。\n",
            "農夫說道：好傢伙﹐這獠牙可真嚇人﹗難怪我的莊稼糟蹋得不成樣子。\n",
            "農夫感激地說道：太謝謝你了﹗這些日子我都快愁死了。\n",
            "農夫說道：這點錢不算什麼﹐你可幫了我大忙了﹗\n",
            (: give_reward, ob :),
        }));
        destruct(item);
        return 1;
    }
    return 0;
}

void relay_say(object ob, string msg)
{
    int stage;

    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( ob->query("quest/field_boar_done") ) {
        if( strsrch(msg, "野豬") >= 0 || strsrch(msg, "莊稼") >= 0 ) {
            do_chat("農夫笑著說道：自從你除了那頭野豬﹐莊稼長得可好了﹗\n");
        }
        return;
    }

    stage = ob->query_temp("pending/field_boar");

    if( !stage || stage == 0 ) {
        if( strsrch(msg, "幫") >= 0 || strsrch(msg, "忙") >= 0
        ||  strsrch(msg, "野豬") >= 0 || strsrch(msg, "豬") >= 0
        ||  strsrch(msg, "莊稼") >= 0 || strsrch(msg, "田") >= 0
        ||  strsrch(msg, "怎") >= 0 ) {
            do_chat(({
                "農夫愁眉苦臉地說道：唉﹐別提了 ...\n",
                "農夫說道：最近不知從哪來了一頭大野豬﹐天天來糟蹋我的莊稼。\n",
                "農夫說道：我一個莊稼漢﹐哪打得過那畜生﹖獠牙跟刀似的。\n",
                "農夫眼巴巴地看著你﹐說道：大俠﹐你要是能幫忙除了那禍害﹐我 ...\n",
                "農夫說道：你在這田邊等等﹐那畜生準會出現的。\n",
                (: call_out, "spawn_boar", 3, ob :),
            }));
            ob->set_temp("pending/field_boar", 1);
            return;
        }
    }

    if( stage == 1 ) {
        if( strsrch(msg, "豬") >= 0 || strsrch(msg, "哪") >= 0
        ||  strsrch(msg, "在") >= 0 ) {
            do_chat("農夫往田邊指了指﹐說道：就在附近﹐你等等看﹐那畜生肯定會出來的。\n");
            call_out("spawn_boar", 3, ob);
            return;
        }
    }

    if( stage == 2 ) {
        if( strsrch(msg, "豬") >= 0 || strsrch(msg, "殺") >= 0
        ||  strsrch(msg, "打") >= 0 || strsrch(msg, "獠") >= 0 ) {
            do_chat("農夫急切地說道：真的﹖快讓我看看證據﹗把那獠牙給我看看。\n");
            return;
        }
    }
}
