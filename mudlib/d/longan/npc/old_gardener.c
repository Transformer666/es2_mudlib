// vim: syntax=lpc
// Quest support: storyteller_pendant (gardener provides clue)

#include <npc.h>

inherit F_VILLAGER;

void create()
{
    set_name("老園丁", ({"gardener"}));
    set_attr("str", 10);
    set_attr("dex", 10);
    set_attr("con", 11);
    set_attr("int", 12);
    set_attr("spi", 12);
    set_attr("wis", 14);
    set_race("human");
    set_class("commoner");
    set_level(8);
    set("age", 60);
    set("gender", "male");
    set("long", "一位白髮蒼蒼的老園丁，正彎著腰在花園中侍弄花草。\n");
    set("chat_chance", 5);
    set("chat_msg", ({
        "老園丁嘟囔道：今年的雨水不錯，花兒長得好。\n",
        "老園丁仔細端詳著一株草藥，若有所思。\n",
        "老園丁抬頭看看天色，自言自語道：看這天氣，明天該是個晴天。\n",
    }));
    setup();
    carry_object("/obj/area/obj/cloth")->wear();
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "玉佩") >= 0 || strsrch(msg, "說書人") >= 0
    ||  strsrch(msg, "韓") >= 0 || strsrch(msg, "遺物") >= 0 ) {
	if( ob->query("quest/storyteller_pendant_done") ) {
	    do_chat("老園丁笑道﹕聽說說書人的玉佩找回來了﹐那可是好事啊。\n");
	    return;
	}
	if( ob->query_temp("pending/storyteller_pendant") ) {
	    do_chat(({
		"老園丁直起腰來﹐想了想﹐說道﹕你問那說書人的玉佩啊﹖\n",
		"老園丁說道﹕我記得前些年﹐有一次我去北邊的洞口附近除草﹐好像在水邊看到過什麼亮晃晃的東西。\n",
		"老園丁壓低聲音﹕不過那洞裡有條大蟲﹐你可得小心。到了洞裡﹐在水邊找找看吧。\n",
	    }));
	    return;
	}
	do_chat("老園丁搖搖頭﹐說道﹕什麼玉佩﹖老頭子不太清楚﹐你去問問廣場上的說書人吧。\n");
	return;
    }

    if( strsrch(msg, "洞穴") >= 0 || strsrch(msg, "黑龍") >= 0
    ||  strsrch(msg, "大蟲") >= 0 || strsrch(msg, "北邊") >= 0 ) {
	do_chat(({
	    "老園丁臉色一變﹐壓低聲音說道﹕你說北邊那個洞﹖\n",
	    "老園丁說道﹕裡面住著一條大蟲﹐兇得很﹐一般人靠近就沒命了。你可千萬別亂闖。\n",
	}));
	return;
    }
}
