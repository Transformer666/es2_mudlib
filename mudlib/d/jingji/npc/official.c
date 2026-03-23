// NPC: /d/jingji/npc/official.c
// Quest: 師爺的懸案 — help find missing tax ledger page
// Flow: talk to official -> search pavilion in garden -> return to report

#include <npc.h>

inherit F_SCHOLAR;

void give_reward(object player);

void create()
{
    set_name("師爺", ({"official", "shiye"}));
    set_attr("int", 22);
    set_attr("wis", 20);
    set_race("human");
    set_class("commoner");
    set_level(18);

    set_skill("unarmed", 30);
    set_skill("dodge", 40);

    set("age", 48);
    set("gender", "male");
    set("long",
        "一位身穿青色長袍的中年文士，面容清瘦，目光精明。他是衙門\n"
        "裡的師爺，專門替大人處理文書案牘。他手中拿著一卷公文，似乎\n"
        "正在核對什麼。\n");
    set("chat_chance", 1);
    set("chat_msg", ({
        "師爺翻閱著手中的公文，不時皺眉搖頭。\n",
        "師爺提筆在公文上批註了幾個字。\n",
        "師爺低聲嘟囔道：這案子可不好辦啊……\n",
    }));

    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
    carry_money("coin", 200);
}

int accept_fight(object ob)
{
    do_chat("師爺驚道：你、你要做什麼？來人啊！\n");
    return 0;
}

void init()
{
    ::init();
    if( is_fighting() || is_chatting() ) return;
    if( !userp(this_player()) ) return;

    if( this_player()->query("quest/jingji_ledger_done") ) return;

    if( this_player()->query_temp("pending/jingji_ledger") == 2 ) {
        do_chat("師爺見到你﹐連忙問道﹕御花園裡可有發現什麼線索﹖\n");
        return;
    }

    if( this_player()->query_temp("pending/jingji_ledger") == 1 ) {
        do_chat("師爺催促道﹕快去衙門東面的御花園找找吧。\n");
        return;
    }

    do_chat("師爺見到你﹐似乎欲言又止。\n");
}

private void give_reward(object player)
{
    object money;

    if( !player || environment(player) != environment() ) return;

    player->set("quest/jingji_ledger_done", 1);
    player->gain_score("quest", 100);

    money = new("/obj/money/silver");
    money->set_amount(5);
    if( !money->move(player) )
        money->move(environment());
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;
    if( ob->query("quest/jingji_ledger_done") ) return;

    // Stage 2: player found the evidence and returned
    if( ob->query_temp("pending/jingji_ledger") == 2 ) {
        if( strsrch(msg, "帳冊") >= 0 || strsrch(msg, "找到") >= 0
        ||  strsrch(msg, "發現") >= 0 || strsrch(msg, "涼亭") >= 0
        ||  strsrch(msg, "證據") >= 0 || strsrch(msg, "殘頁") >= 0 ) {
            do_chat(({
                "師爺接過殘頁﹐仔細端詳﹐面色大變。\n",
                "師爺說道﹕果然﹗這上面記載的數目和報上來的對不上﹐有人動了手腳﹗\n",
                "師爺說道﹕有了這份證據﹐就能查出是誰中飽私囊了。\n",
                "師爺拱手道﹕多謝義士相助﹐此案若能告破﹐你可是立了大功。這些銀子請收下。\n",
                (: give_reward, ob :),
            }));
            return;
        }
    }

    // Stage 0: initial conversation about the case
    if( !ob->query_temp("pending/jingji_ledger") ) {
        if( strsrch(msg, "案子") >= 0 || strsrch(msg, "什麼事") >= 0
        ||  strsrch(msg, "怎麼") >= 0 || strsrch(msg, "幫忙") >= 0
        ||  strsrch(msg, "公文") >= 0 || strsrch(msg, "你好") >= 0 ) {
            do_chat(({
                "師爺左右看了看﹐壓低聲音說道﹕你是外地來的吧﹖倒是可以幫個忙。\n",
                "師爺說道﹕上個月的稅銀帳冊少了一頁﹐記載著一筆大額收支。\n",
                "師爺說道﹕我懷疑是有人故意撕走了那一頁﹐好掩蓋貪墨的證據。\n",
                "師爺說道﹕前幾天有人看到一個可疑的身影在衙門後面的御花園出沒。\n",
                "師爺說道﹕你能不能去御花園找找看﹖從衙門往東走就到了﹐仔細 search 涼亭附近。\n",
            }));
            ob->set_temp("pending/jingji_ledger", 1);
            return;
        }
    }
}
