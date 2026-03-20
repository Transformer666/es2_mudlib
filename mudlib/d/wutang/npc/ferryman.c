// ferryman.c
// Quest: 過河的船在哪裡？ (五堂鎮 riddle 6)

#include <npc.h>

inherit F_VILLAGER;

void complete_ferry_quest(object player);

void create()
{
    set_name("渡船夫", ({"ferryman"}));
    set_attr("str", 16);
    set_attr("con", 18);
    set_race("human");
    set_class("commoner");
    set_level(10);

    set("age", 50);
    set("gender", "male");
    set("long",
	"一個皮膚黝黑的老船夫﹐雙手滿是老繭﹐正坐在碼頭邊抽著旱\n"
	"煙。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
	"渡船夫吐了一口煙﹐說道﹕河水最近漲了﹐渡船怕是要再等等了。\n",
	"渡船夫說道﹕以前這渡口可熱鬧了﹐每天都有商旅往來。\n",
	"渡船夫望著河面﹐似乎在想什麼心事。\n",
    }));
    setup();
    carry_money("coin", 50);
}

void init()
{
    ::init();
    if( is_fighting() || is_chatting() ) return;
    if( !userp(this_player()) ) return;

    if( !this_player()->query("quest/ferryman_guide_done") )
	do_chat("渡船夫瞄了你一眼﹐說道﹕你也想過河﹖\n");
}

private void complete_ferry_quest(object player)
{
    if( !player || environment(player) != environment() ) return;
    if( player->query("quest/ferryman_guide_done") ) return;

    player->set("quest/ferryman_guide_done", 1);
    player->gain_score("quest", 50);
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "船") >= 0 || strsrch(msg, "渡") >= 0
    ||  strsrch(msg, "過河") >= 0 || strsrch(msg, "碼頭") >= 0 ) {
	if( ob->query("quest/ferryman_guide_done") ) {
	    do_chat("渡船夫說道﹕之前不是跟你說過了嗎﹖就在這碼頭邊﹐用 board 就能搭船。\n");
	    return;
	}
	do_chat(({
	    "渡船夫磕了磕煙斗﹐說道﹕想過河啊﹖\n",
	    "渡船夫說道﹕這碼頭上就有渡船﹐你用 board 就能搭船了。\n",
	    "渡船夫說道﹕不過河水最近漲了些﹐你可得小心。\n",
	    "渡船夫說道﹕過了河就是鯉君渡﹐那邊也有渡船往來﹐南來北往都方便。\n",
	    (: complete_ferry_quest, ob :),
	}));
	return;
    }

    if( strsrch(msg, "鯉君") >= 0 ) {
	do_chat("渡船夫說道﹕鯉君渡在河的對岸﹐那裡是南北交通的要道。\n");
	return;
    }
}
