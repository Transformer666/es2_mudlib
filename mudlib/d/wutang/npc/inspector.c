// inspector.c
// Quest: 別館內的欽差來五堂要做甚麼？
// Flow: ask inspector -> he asks you to investigate -> ask storyteller -> report back

#include <npc.h>

inherit F_SCHOLAR;

void give_quest_reward(object player);

void create()
{
    set_name("御史大人", ({"inspector", "yushi"}));
    set_attr("int", 20);
    set_attr("wis", 22);
    set_race("human");
    set_class("scholar");
    set_level(30);

    set("age", 40);
    set("attitude", "peaceful");
    set("long",
	"一個身穿官服的中年文官﹐眉頭深鎖﹐似乎正在為什麼事情煩\n"
	"惱。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
	"御史大人皺著眉頭看著案上的公文﹐喃喃自語道﹕這件案子果然蹊蹺。\n",
	"御史大人嘆了口氣﹐說道﹕五堂鎮最近不太太平啊。\n",
    }));
    setup();
    carry_money("coin", 1000);
}

void init()
{
    ::init();
    if( is_fighting() || is_chatting() ) return;
    if( !userp(this_player()) ) return;

    if( this_player()->query("quest/inspector_case_done") )
	return;

    if( this_player()->query_temp("pending/inspector_case") == 2 )
	do_chat("御史大人看見你回來了﹐連忙問道﹕可有打聽到什麼消息﹖\n");
}

private void give_quest_reward(object player)
{
    object money;

    if( !player || environment(player) != environment() ) return;

    player->set("quest/inspector_case_done", 1);
    player->gain_score("quest", 80);

    money = new("/obj/money/silver");
    money->set_amount(5);
    if( !money->move(player) )
	money->move(environment());
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "調查") >= 0 || strsrch(msg, "案件") >= 0
    ||  strsrch(msg, "甚麼事") >= 0 || strsrch(msg, "什麼事") >= 0
    ||  strsrch(msg, "來做") >= 0 ) {
	if( ob->query("quest/inspector_case_done") ) {
	    do_chat("御史大人說道﹕多虧你的線索﹐案子已經有了眉目。\n");
	    return;
	}
	if( ob->query_temp("pending/inspector_case") ) {
	    do_chat("御史大人說道﹕你去鎮上打聽打聽﹐客棧裡的說書先生消息最靈通。\n");
	    return;
	}
	do_chat(({
	    "御史大人放下公文﹐嘆了口氣。\n",
	    "御史大人說道﹕本官奉旨來五堂鎮調查一樁案子。\n",
	    "御史大人說道﹕近半年來﹐接連有數名旅人在武山附近失蹤﹐活不見人﹐死不見屍。\n",
	    "御史大人說道﹕本官到了這裡﹐卻發現鎮上的人都噤若寒蟬﹐無人敢多說一個字。\n",
	    "御史大人壓低聲音道﹕你若肯幫忙﹐去客棧裡打聽打聽﹐說書先生消息最靈通﹐也許他知道些什麼。\n",
	}));
	ob->set_temp("pending/inspector_case", 1);
	return;
    }

    if( strsrch(msg, "密道") >= 0 || strsrch(msg, "密室") >= 0
    ||  strsrch(msg, "巫山") >= 0 || strsrch(msg, "失蹤") >= 0
    ||  strsrch(msg, "線索") >= 0 || strsrch(msg, "雕像") >= 0 ) {
	if( ob->query("quest/inspector_case_done") ) {
	    do_chat("御史大人說道﹕多虧你的線索﹐案子已經有了眉目。\n");
	    return;
	}
	if( ob->query_temp("pending/inspector_case") == 2 ) {
	    do_chat(({
		"御史大人猛地站了起來﹐說道﹕什麼﹖巫山洞窟裡有密道﹖\n",
		"御史大人說道﹕難怪失蹤的人都是在武山附近消失的﹗\n",
		"御史大人說道﹕這條線索太重要了﹐本官會立刻上報朝廷﹐派人去查。\n",
		"御史大人拱手道﹕多謝你的幫助﹐這點銀兩是本官的一點心意。\n",
		(: give_quest_reward, ob :),
	    }));
	    return;
	}
	do_chat("御史大人說道﹕你說的這些﹐本官也有所耳聞﹐但苦於沒有證據。你去客棧找說書先生打聽打聽吧。\n");
	return;
    }
}
