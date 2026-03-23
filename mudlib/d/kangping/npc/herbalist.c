// vim: syntax=lpc
// Quest: 採藥人的煩惱 (herbalist_herb)
// Flow: talk -> learn about fire_herb in cave -> search stone_cave
//       -> give herb to herbalist -> reward

#include <npc.h>

inherit F_VILLAGER;

void do_reward(object player);

void create()
{
    set_name("採藥人", ({"herbalist"}));
    set_attr("str", 12);
    set_attr("dex", 12);
    set_attr("con", 12);
    set_attr("int", 14);
    set_attr("spi", 14);
    set_attr("wis", 14);
    set_race("human");
    set_class("commoner");
    set_level(10);
    set("age", 50);
    set("gender", "male");
    set("long",
	"一個採藥人正在藥圃中仔細查看各種藥材﹐不時皺起眉頭﹐似乎\n"
	"有什麼心事。\n");
    set("chat_chance", 2);
    set("chat_msg", ({
	"採藥人嘆了口氣﹐自言自語道﹕唉﹐那火靈草……\n",
	"採藥人抬頭看了看北邊的山壁﹐眼中閃過一絲畏懼。\n",
    }));
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
    carry_money("coin", 50);
}

void do_reward(object player)
{
    if( !player || !present(player, environment()) ) return;
    if( player->query("quest/herbalist_herb_done") ) return;

    player->set("quest/herbalist_herb_done", 1);
    player->delete_temp("pending/herbalist_herb");
    player->gain_score("quest", 80);

    message_vision("$N從藥簍中取出一包藥材遞給$n﹐說道﹕這些是我自己配的金創藥﹐你帶著防身。\n",
	this_object(), player);
    player->carry_money("silver", 2);
    tell_object(player, "( 你獲得了二兩銀子和一包金創藥 )\n");
}

int accept_object(object who, object ob)
{
    if( !ob->id("fire herb") ) return 0;

    if( who->query("quest/herbalist_herb_done") ) {
	do_chat("採藥人搖搖頭﹐說道﹕不用了﹐上次那株已經夠用了。\n");
	return 0;
    }
    if( !who->query_temp("pending/herbalist_herb") ) {
	do_chat("採藥人好奇地看著你手中的草藥﹐說道﹕這是……火靈草﹖你從哪兒找到的﹖\n");
	return 0;
    }

    do_chat(({
	"採藥人接過火靈草﹐雙手微微顫抖﹐仔細端詳了一番。\n",
	"採藥人激動地說道﹕就是這個﹗就是火靈草﹗太好了﹗\n",
	"採藥人說道﹕有了這株火靈草﹐我就能配製出治療寒毒的藥方了。\n",
	"採藥人感激地說道﹕多謝你冒險相助﹐這點東西算是我的一點心意。\n",
	(: do_reward, who :),
    }));
    return 1;
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "心事") >= 0 || strsrch(msg, "煩惱") >= 0
    ||  strsrch(msg, "幫忙") >= 0 || strsrch(msg, "火靈草") >= 0 ) {
	if( ob->query("quest/herbalist_herb_done") ) {
	    do_chat("採藥人笑道﹕多虧了你﹐那藥方已經配好了﹐效果極佳。\n");
	    return;
	}
	if( ob->query_temp("pending/herbalist_herb") >= 2 ) {
	    do_chat("採藥人說道﹕火靈草長在北邊石洞裡﹐你去找找看吧﹐可要小心那頭怪物。\n");
	    return;
	}
	if( ob->query_temp("pending/herbalist_herb") == 1 ) {
	    do_chat(({
		"採藥人嘆了口氣﹐說道﹕不瞞你說﹐藥圃北邊的石洞裡長著一種極珍貴的火靈草。\n",
		"採藥人壓低了聲音﹕可是不知什麼時候﹐洞裡來了一頭可怕的東西﹐我根本不敢進去。\n",
		"採藥人說道﹕村裡有人染了寒毒﹐非火靈草不能解﹐可我實在沒膽量去取啊。\n",
		"採藥人看了你一眼﹐說道﹕你若是不怕危險﹐能否替我去洞裡找一株火靈草﹖\n",
	    }));
	    ob->set_temp("pending/herbalist_herb", 2);
	    return;
	}
	do_chat(({
	    "採藥人搖了搖頭﹐苦笑道﹕唉﹐別提了。\n",
	    "採藥人說道﹕我在這藥圃種了幾十年的藥﹐最近卻碰上了一件麻煩事。\n",
	}));
	ob->set_temp("pending/herbalist_herb", 1);
	return;
    }

    if( strsrch(msg, "石洞") >= 0 || strsrch(msg, "怪物") >= 0
    ||  strsrch(msg, "藥草") >= 0 || strsrch(msg, "寒毒") >= 0 ) {
	if( ob->query("quest/herbalist_herb_done") ) {
	    do_chat("採藥人說道﹕藥方已經配好了﹐不需要了。\n");
	    return;
	}
	if( !ob->query_temp("pending/herbalist_herb") )
	    ob->set_temp("pending/herbalist_herb", 1);
	if( ob->query_temp("pending/herbalist_herb") < 2 ) {
	    do_chat(({
		"採藥人說道﹕那石洞裡原本長著不少稀罕的藥草﹐尤其是火靈草﹐極為難得。\n",
		"採藥人壓低聲音﹕可不知何時來了一頭可怕的東西﹐進去的人都沒能活著出來。\n",
		"採藥人說道﹕你要是有膽量﹐去洞裡找一株火靈草回來﹐我必有重謝。\n",
	    }));
	    ob->set_temp("pending/herbalist_herb", 2);
	    return;
	}
	do_chat("採藥人說道﹕火靈草長在石洞深處﹐你去搜尋看看吧﹐千萬小心。\n");
	return;
    }
}
