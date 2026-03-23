// vim: syntax=lpc
// NPC: /d/baihua/npc/shrine_keeper.c
// Quest: 仙女畫卷之謎 (quest/shrine_painting_done)

#include <npc.h>

inherit F_VILLAGER;

void give_quest_reward(object player);

void create()
{
	set_name("祠堂婆婆", ({"shrine_keeper", "keeper"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 70);
	set("gender", "female");
	set("long",
		"一個滿頭銀髮的老婆婆﹐穿著一件素淨的藍花布衫。她是百花\n"
		"村祠堂的看守人﹐每天按時上香、擺放供品﹐把祠堂打掃得纖塵\n"
		"不染。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"婆婆輕輕拂去供桌上的灰塵﹐換上一盤新摘的鮮花。\n",
		"婆婆雙手合十﹐對著牌位喃喃祝禱。\n",
		"婆婆望著牆上那幅仙女畫卷﹐露出慈祥的微笑。\n",
	}));

	setup();
	carry_money("coin", 8);
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/shrine_painting_done") )
		return;

	if( this_player()->query_temp("pending/shrine_jade_found") )
		do_chat("婆婆看到你手中的東西﹐眼睛一亮﹕那是 ... 你是在畫卷後面找到的﹖\n");
}

private void give_quest_reward(object player)
{
	object money;

	if( !player || environment(player) != environment() ) return;

	player->set("quest/shrine_painting_done", 1);
	player->gain_score("quest", 100);

	money = new("/obj/money/silver");
	money->set_amount(5);
	if( !money->move(player) )
		money->move(environment());
}

int accept_object(object player, object ob)
{
	if( !userp(player) ) return 0;
	if( player->query("quest/shrine_painting_done") ) return 0;

	if( ob->id("jade") || ob->id("jade offering") || ob->id("offering") ) {
		do_chat(({
			"婆婆顫抖著雙手接過古玉﹐眼眶泛紅。\n",
			"婆婆喃喃道﹕這是 ... 花籃玉﹗我聽老一輩人說起過﹗\n",
			"婆婆說道﹕傳說百花村的守護仙女留下了一件信物﹐就藏在她的畫像之後。\n",
			"婆婆說道﹕只要這塊玉還在祠堂裡﹐百花村便能四季花開不敗。\n",
			"婆婆感激地說道﹕多虧了你﹐把這寶物重新找了回來。這點錢你拿著﹐算是村裡人的一點心意。\n",
			(: give_quest_reward, player :),
		}));
		return 1;
	}
	return 0;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( ob->query("quest/shrine_painting_done") ) {
		if( strsrch(msg, "畫卷") >= 0 || strsrch(msg, "仙女") >= 0
		||  strsrch(msg, "古玉") >= 0 ) {
			do_chat("婆婆微笑道﹕多虧了你把花籃玉找了回來﹐你看﹐供桌上的花開得更好了呢。\n");
			return;
		}
		return;
	}

	if( ob->query_temp("pending/shrine_jade_found") ) {
		if( strsrch(msg, "古玉") >= 0 || strsrch(msg, "找到") >= 0
		||  strsrch(msg, "花籃") >= 0 ) {
			do_chat("婆婆激動地說道﹕真的找到了﹗快給我看看﹗\n");
			return;
		}
		return;
	}

	if( ob->query_temp("pending/shrine_painting") ) {
		if( strsrch(msg, "畫卷") >= 0 || strsrch(msg, "仙女") >= 0 ) {
			do_chat("婆婆說道﹕去看看那幅畫卷吧﹐用 examine painting 仔細瞧瞧。\n");
			return;
		}
		return;
	}

	if( strsrch(msg, "畫卷") >= 0 || strsrch(msg, "仙女") >= 0
	||  strsrch(msg, "守護神") >= 0 || strsrch(msg, "祠堂") >= 0
	||  strsrch(msg, "怎麼了") >= 0 || strsrch(msg, "故事") >= 0 ) {
		do_chat(({
			"婆婆抬頭望著畫卷﹐緩緩說道﹕這幅畫啊﹐掛在這裡不知多少年了。\n",
			"婆婆說道﹕聽老一輩人說﹐畫上的仙女是百花村的守護神。\n",
			"婆婆說道﹕以前祠堂裡的花一年四季都開得好好的﹐可這些年漸漸不如從前了。\n",
			"婆婆嘆了口氣﹕老人們說﹐仙女留下了一件寶物﹐只要寶物還在﹐花就不會凋謝。\n",
			"婆婆說道﹕可是那件寶物到底在哪裡﹐誰也不知道 ... 也許就藏在這祠堂的某個角落吧。\n",
		}));
		ob->set_temp("pending/shrine_painting", 1);
		return;
	}

	if( strsrch(msg, "百花") >= 0 || strsrch(msg, "村子") >= 0 ) {
		do_chat("婆婆微笑道﹕百花村雖小﹐卻是個好地方﹐一年到頭都有花開。\n");
		return;
	}
}
