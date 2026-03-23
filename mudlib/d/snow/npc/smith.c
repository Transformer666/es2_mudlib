// smith.c
// Quest: 鐵匠的寶鐵 (smith_black_iron)
// Flow: talk about iron -> learn smith needs black iron -> find ore at riverbank
//       -> give ore to smith -> smith forges a black iron dagger as reward

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

void do_reward_blade(object player);

void create()
{
    set_name("鐵匠", ({ "smith" }) );
    set_race("human");
    set_level(13);
    set_stat_maximum("kee", 80);
    set_attr("str", 19);
    set_attr("cor", 17);
    set_attr("cps", 15);
    set_attr("dex", 18);

    set("long",
	"一個身材粗壯的鐵匠﹐正忙碌地工作著。\n"
	"如果你想買一些鐵器﹐可以用 list 看有哪些東西﹐用 buy 向鐵匠購買。\n");

    set("merchandise", ([
	__DIR__"obj/hoe": 3,
	__DIR__"obj/shovel": 5,
	"/obj/area/obj/dagger": 10,
	"/obj/area/obj/shortsword": 5,
    ]));

    set("chat_chance", 5);
    set("chat_msg", ({
	"鐵匠將一塊燒紅的鐵塊「嗤」地一聲浸入一旁的水箱中。\n",
	"鐵匠用手中的鐵鎚在鐵砧上用力敲打。\n",
	"鐵匠說道﹕站開點﹐小心別燙著了。\n",
	"鐵匠說道﹕唉 ... 真把我給忙壞了。\n",
    }));
    setup();
    carry_object(__DIR__"obj/smock")->wear();
}

int accept_fight()
{
    do_chat("鐵匠瞪了瞪眼﹐說道﹕走開﹐我正忙著。\n");
    return 0;
}

void init()
{
    ::init();
    add_action("do_vendor_list", "list");
}

void do_reward_blade(object player)
{
    object blade;

    if( !player || !present(player, environment()) ) return;
    if( player->query("quest/smith_black_iron_done") ) return;

    player->set("quest/smith_black_iron_done", 1);
    player->delete_temp("pending/smith_black_iron");
    player->gain_score("quest", 60);

    blade = new(__DIR__"obj/black_iron_dagger");
    blade->move(player);
    message_vision("鐵匠把剛鍛好的短刀交給了$N。\n", player);
    tell_object(player, "( 你獲得了一把玄鐵短刀 )\n");
}

int accept_object(object who, object ob)
{
    object thing;

    if( ob->id("black iron") ) {
	if( who->query("quest/smith_black_iron_done") ) {
	    do_chat("鐵匠說道﹕不用了﹐上次的玄鐵已經夠了。\n");
	    return 0;
	}
	if( !who->query_temp("pending/smith_black_iron") ) {
	    do_chat("鐵匠說道﹕這是什麼石頭﹖\n");
	    return 0;
	}
	do_chat(({
	    "鐵匠接過礦石﹐翻來覆去地仔細端詳。\n",
	    "鐵匠驚喜地說道﹕好傢伙﹗成色這麼好的玄鐵可不多見﹗\n",
	    "鐵匠說道﹕你等著﹐我這就給你打把好刀﹗\n",
	    "鐵匠挽起袖子﹐將礦石放進爐中﹐拉起風箱。\n",
	    "鐵匠抄起大鐵鎚﹐在鐵砧上叮叮噹噹地鍛打起來。\n",
	    (: do_reward_blade, who :),
	}));
	return 1;
    }

    if( !ob->id("lo iron") ) return 0;
    call_out((: command, "say 喔！要製成箭嗎, 那簡單, 馬上就可以做好.\n" :), 1);
    thing = new(__DIR__"obj/arrow");
    thing->move(who);
    call_out((: message_vision, "鐵匠把剛做好的箭交給了$N。\n", this_player() :), 2);
    return 1;
}

void relay_say(object ob, string msg)
{
    if( !userp(ob) ) return;
    if( is_fighting() || is_chatting() ) return;

    if( strsrch(msg, "鐵") >= 0 || strsrch(msg, "材料") >= 0
    ||  strsrch(msg, "玄鐵") >= 0 || strsrch(msg, "礦石") >= 0
    ||  strsrch(msg, "幫忙") >= 0 || strsrch(msg, "忙") >= 0 ) {
	if( ob->query("quest/smith_black_iron_done") ) {
	    do_chat("鐵匠笑道﹕上次你帶回來的玄鐵﹐成色真不錯﹐那把刀用著可好﹖\n");
	    return;
	}
	if( ob->query_temp("pending/smith_black_iron") ) {
	    do_chat("鐵匠說道﹕河邊的岩壁上應該能找到玄鐵﹐你去看看吧。\n");
	    return;
	}
	do_chat(({
	    "鐵匠嘆了口氣﹐說道﹕唉﹐最近好鐵越來越難找了。\n",
	    "鐵匠說道﹕我聽老一輩的人講﹐鎮子河邊的岩壁上偶爾能見到玄鐵礦脈。\n",
	    "鐵匠說道﹕那可是鍛造利器的上等材料﹐可惜我走不開啊。\n",
	    "鐵匠看了你一眼﹐說道﹕你要是能幫我找一塊回來﹐我給你打把好刀﹗\n",
	}));
	ob->set_temp("pending/smith_black_iron", 1);
	return;
    }
}
