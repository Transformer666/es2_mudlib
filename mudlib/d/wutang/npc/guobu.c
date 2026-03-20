// guobu.c
// Quest: 郭布要收的徒弟在哪裡？
// Flow: ask guobu -> he asks you to find a boy -> find boy at river_bend -> report back

#include <npc.h>

inherit F_VILLAGER;

void give_quest_reward(object player);

void create()
{
    set_name("郭布", ({"guobu"}));
    set_attr("str", 20);
    set_attr("dex", 18);
    set_attr("wis", 16);
    set_race("human");
    set_class("fighter");
    set_level(35);

    set_skill("sword", 80);
    set_skill("dodge", 60);

    set("age", 55);
    set("gender", "male");
    set("long",
	"一個身材高大的老者﹐雖然年紀不小了﹐但雙目依然炯炯有神﹐\n"
	"身上散發著一股久經沙場的氣息。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
	"郭布嘆了口氣﹐自言自語道﹕唉﹐何時才能找到一個合適的傳人呢。\n",
	"郭布似乎在回憶什麼﹐眼神變得悠遠。\n",
    }));
    setup();
    carry_money("coin", 200);
}

void init()
{
    ::init();
    if( is_fighting() || is_chatting() ) return;
    if( !userp(this_player()) ) return;

    if( this_player()->query("quest/guobu_apprentice_done") )
	return;

    if( this_player()->query_temp("pending/guobu_apprentice") == 2 )
	do_chat("郭布看見你回來了﹐連忙問道﹕找到那個孩子了嗎﹖\n");
}

private void give_quest_reward(object player)
{
    object money;

    if( !player || environment(player) != environment() ) return;

    player->set("quest/guobu_apprentice_done", 1);
    player->gain_score("quest", 80);

    money = new("/obj/money/coin");
    money->set_amount(200);
    if( !money->move(player) )
	money->move(environment());
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "徒弟") >= 0 || strsrch(msg, "傳人") >= 0
    ||  strsrch(msg, "收徒") >= 0 || strsrch(msg, "弟子") >= 0 ) {
	if( ob->query("quest/guobu_apprentice_done") ) {
	    do_chat("郭布微微一笑道﹕多虧了你﹐我已經收了那孩子為徒了。\n");
	    return;
	}
	if( ob->query_temp("pending/guobu_apprentice") ) {
	    do_chat("郭布說道﹕那孩子應該在碼頭南邊的河灣﹐你去看看吧。\n");
	    return;
	}
	do_chat(({
	    "郭布嘆了口氣﹐說道﹕老夫一身武藝﹐卻苦於沒有傳人。\n",
	    "郭布說道﹕前些天我在碼頭附近閒逛﹐看見一個小夥子在河灣獨自練拳。\n",
	    "郭布說道﹕那孩子根骨不錯﹐招式雖然生疏﹐但勁道十足﹐是塊練武的料。\n",
	    "郭布說道﹕只是老夫拉不下臉去問﹐你能不能替我去碼頭南邊的河灣看看﹐問問那孩子願不願意拜師﹖\n",
	}));
	ob->set_temp("pending/guobu_apprentice", 1);
	return;
    }

    if( strsrch(msg, "找到") >= 0 || strsrch(msg, "河灣") >= 0
    ||  strsrch(msg, "小童") >= 0 || strsrch(msg, "阿虎") >= 0
    ||  strsrch(msg, "願意") >= 0 ) {
	if( ob->query("quest/guobu_apprentice_done") ) {
	    do_chat("郭布微微一笑道﹕多虧了你﹐我已經收了那孩子為徒了。\n");
	    return;
	}
	if( ob->query_temp("pending/guobu_apprentice") == 2 ) {
	    do_chat(({
		"郭布眼睛一亮﹐說道﹕真的﹖那孩子願意拜師﹖\n",
		"郭布高興地一拍大腿﹐說道﹕太好了﹗老夫這就去找他﹗\n",
		"郭布拱手道﹕多謝你跑這一趟﹐這點錢你拿著﹐算是老夫的謝禮。\n",
		(: give_quest_reward, ob :),
	    }));
	    return;
	}
	do_chat("郭布疑惑道﹕你在說什麼﹖\n");
	return;
    }
}
