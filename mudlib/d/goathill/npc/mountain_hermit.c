// vim: syntax=lpc
// Quest: 隱士的棋局 (hermit_chess)
// Flow: talk about chess/past -> he asks for lost chess piece in ravine
//       -> search ravine -> return piece -> reward

#include <npc.h>

inherit F_VILLAGER;

void give_reward(object player);

void create()
{
    set_name("山中隱士", ({"mountain_hermit", "hermit"}));
    set_attr("str", 16);
    set_attr("dex", 16);
    set_attr("con", 18);
    set_attr("int", 24);
    set_attr("spi", 26);
    set_race("human");
    set_class("commoner");
    set_level(35);
    set("age", 65);
    set("gender", "male");
    set("long",
        "一位隱居在羊山山洞中的老者﹐蓬頭垢面﹐衣衫破舊﹐但談吐間\n"
        "卻流露出非凡的見識。據說他曾是朝廷中的高官﹐厭倦了官場的爾\n"
        "虞我詐才隱居山林。洞壁上掛著一個殘缺的棋盤﹐似乎少了幾枚\n"
        "棋子。\n");
    set("chat_chance", 3);
    set("chat_msg", ({
        "隱士嘆了口氣﹐說道﹕世事如棋﹐不過一場空。\n",
        "隱士望著遠方的群山﹐若有所思。\n",
        "隱士看了一眼洞壁上的棋盤﹐若有所失。\n",
    }));
    setup();
    carry_object(STOCK_ARMOR("cloth"))->wear();
}

int accept_fight()
{
    do_chat("隱士擺了擺手﹐說道﹕老夫早已不問世事﹐動手的日子已經過去了。\n");
    return 0;
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( ob->query("quest/hermit_chess_done") ) {
        if( strsrch(msg, "棋") >= 0 || strsrch(msg, "chess") >= 0 ) {
            do_chat("隱士微微一笑﹐說道﹕多虧你幫忙﹐這副棋終於完整了。哪天有空﹐來跟老夫下一局。\n");
        }
        return;
    }

    // Player has the chess piece and returned
    if( ob->query_temp("pending/hermit_chess") == 2 ) {
        if( strsrch(msg, "棋") >= 0 || strsrch(msg, "找到") >= 0
        ||  strsrch(msg, "chess") >= 0 ) {
            object piece;
            piece = present("jade_chess_piece", ob);
            if( !piece ) {
                do_chat("隱士說道﹕找到了﹖棋子在哪裡﹖\n");
                return;
            }
            destruct(piece);
            do_chat(({
                "隱士接過棋子﹐在手中細細端詳﹐眼中閃過一絲光彩。\n",
                "隱士說道﹕就是這枚 ... 三十年了﹐沒想到還能找回來。\n",
                "隱士將棋子放回棋盤上﹐長長地舒了一口氣。\n",
                "隱士說道﹕當年在朝中﹐每逢煩悶便與故友對弈﹐如今故友已去﹐只剩這副棋陪著老夫。\n",
                "隱士說道﹕年輕人﹐多謝你了。老夫雖無金銀﹐但有一點心得可以傳授給你。\n",
                (: give_reward, ob :),
            }));
            return;
        }
    }

    // Player has accepted quest, remind about ravine
    if( ob->query_temp("pending/hermit_chess") == 1 ) {
        if( strsrch(msg, "谷") >= 0 || strsrch(msg, "哪") >= 0
        ||  strsrch(msg, "棋") >= 0 || strsrch(msg, "ravine") >= 0 ) {
            do_chat("隱士說道﹕從洞口出去往西走到懸崖﹐再往下便是谷底了。那棋子大概就在谷底的水窪附近。\n");
            return;
        }
    }

    // Initial quest trigger
    if( strsrch(msg, "棋") >= 0 || strsrch(msg, "chess") >= 0
    ||  strsrch(msg, "棋盤") >= 0 ) {
        if( ob->query_temp("pending/hermit_chess") ) return;
        do_chat(({
            "隱士看了你一眼﹐緩緩說道﹕你對棋有興趣﹖\n",
            "隱士說道﹕這副棋是我從官場帶出來的唯一物事﹐用羊山的山玉親手雕的。\n",
            "隱士說道﹕可惜前些日子刮大風﹐一枚棋子被吹落懸崖﹐掉進了谷底。\n",
            "隱士說道﹕老夫腿腳不便﹐下不去那谷底。你若願意幫我找回來﹐老夫感激不盡。\n",
        }));
        ob->set_temp("pending/hermit_chess", 1);
        return;
    }

    if( strsrch(msg, "官") >= 0 || strsrch(msg, "朝廷") >= 0
    ||  strsrch(msg, "過去") >= 0 ) {
        do_chat(({
            "隱士沉默了片刻﹐說道﹕往事不堪回首。\n",
            "隱士說道﹕朝堂之上勾心鬥角﹐老夫厭倦了﹐便來此處終老。\n",
        }));
        return;
    }
}

void give_reward(object player)
{
    object money;

    if( !player || environment(player) != environment() ) return;

    player->set("quest/hermit_chess_done", 1);
    player->gain_score("quest", 80);
    player->delete_temp("pending/hermit_chess");

    // Teach a bit of force skill as wisdom reward
    player->improve_skill("force", random(5) + 3);

    money = new("/obj/money/silver");
    money->set_amount(1);
    if( money->move(player) )
        money->move(environment());

    do_chat("隱士閉目運氣﹐伸手在你肩頭輕輕一拍﹐一股暖流流遍全身。\n");
}
