// prisoner.c
// Quest: 黑風嶺救商人 (heifeng_rescue)
// Flow: talk to prisoner -> kill bandit_leader -> return to prisoner -> rescue complete

#include <npc.h>

inherit F_VILLAGER;

void give_rescue_reward(object player);

void create()
{
	set_name("被囚商人", ({"prisoner", "merchant"}));
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 40);
	set("long",
		"一個衣衫襤褸的商人﹐面容憔悴﹐身上有好幾處傷痕。他蜷縮\n"
		"在囚室的角落﹐看到有人來便用可憐巴巴的眼神望著你。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"商人哀求道﹕好漢﹐求求你救我出去﹐我一定重重酬謝﹗\n",
		"商人低聲說道﹕他們把我的貨物都搶走了……嗚嗚……\n",
		"商人嘆道﹕我是從喬陰來的商人﹐被這群強盜劫持到這裡已經三天了。\n",
	}));
	setup();
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/heifeng_rescue_done") )
		return;

	if( this_player()->query_temp("pending/heifeng_rescue") )
		do_chat("商人焦急地望著你﹐低聲說道﹕好漢﹐寨主殺了沒有﹖\n");
	else
		do_chat("商人連忙爬到你跟前﹐哀求道﹕好漢救命啊﹗求求你救我出去﹗\n");
}

private void give_rescue_reward(object player)
{
	object money;

	if( !player || environment(player) != environment() ) return;
	if( player->query("quest/heifeng_rescue_done") ) return;

	player->set("quest/heifeng_rescue_done", 1);
	player->gain_score("quest", 100);

	money = new("/obj/money/coin");
	money->set_amount(500);
	if( !money->move(player) )
		money->move(environment());
}

void relay_say(object ob, string msg)
{
	object leader;

	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "救") >= 0 || strsrch(msg, "幫") >= 0
	||  strsrch(msg, "放") >= 0 || strsrch(msg, "逃") >= 0 ) {
		if( ob->query("quest/heifeng_rescue_done") ) {
			do_chat("商人感激地說道﹕多虧了你的救命之恩﹐我這輩子都不會忘記。\n");
			return;
		}

		// Check if bandit_leader is alive in the hall
		leader = find_living("bandit_leader");

		if( leader && environment(leader)
		&&  environment(leader)->query("short") == "聚義廳" ) {
			if( !ob->query_temp("pending/heifeng_rescue") ) {
				do_chat(({
					"商人壓低聲音﹐急切地說道﹕好漢﹐你肯救我﹖\n",
					"商人說道﹕這黑風寨的寨主武藝高強﹐手下匪徒無數﹐我根本逃不出去。\n",
					"商人說道﹕只要你能殺了那寨主﹐匪徒群龍無首﹐我就能趁亂逃走。\n",
					"商人拉住你的衣角﹐說道﹕求你了﹗我在喬陰還有妻兒等著我回去啊﹗\n",
				}));
				ob->set_temp("pending/heifeng_rescue", 1);
			} else {
				do_chat("商人搖了搖頭﹐說道﹕寨主還活著﹐我走不了啊……你得先去聚義廳把他解決掉。\n");
			}
			return;
		}

		// Leader is dead - rescue succeeds
		if( !ob->query_temp("pending/heifeng_rescue") )
			ob->set_temp("pending/heifeng_rescue", 1);

		do_chat(({
			"商人驚喜地叫道﹕什麼﹖寨主死了﹖太好了﹗太好了﹗\n",
			"商人連忙站起身來﹐向你連連作揖﹕好漢大恩大德﹐小人沒齒難忘﹗\n",
			"商人從懷中掏出一個布包﹐說道﹕這是我藏起來的最後一點銀兩﹐請好漢務必收下。\n",
			"商人說道﹕我這就趁亂逃出去﹐回喬陰與家人團聚。好漢﹐後會有期﹗\n",
			(: give_rescue_reward, ob :),
		}));
		return;
	}

	if( strsrch(msg, "喬陰") >= 0 || strsrch(msg, "商人") >= 0
	||  strsrch(msg, "貨物") >= 0 ) {
		if( ob->query("quest/heifeng_rescue_done") ) {
			do_chat("商人說道﹕我已經安全了﹐多謝好漢。\n");
			return;
		}
		do_chat(({
			"商人嘆了口氣﹐說道﹕我是喬陰的布商﹐這次帶了一批絲綢往康平販賣。\n",
			"商人說道﹕不料路過黑風嶺時被截住﹐貨物全被搶走﹐人也被關在這裡。\n",
			"商人說道﹕寨主說要拿我向家裡勒索贖金﹐可我哪有那麼多錢﹖\n",
		}));
		return;
	}

	if( strsrch(msg, "寨主") >= 0 || strsrch(msg, "首領") >= 0
	||  strsrch(msg, "強盜") >= 0 ) {
		do_chat("商人壓低聲音說道﹕寨主就在北邊的聚義廳﹐武藝很高﹐你可得小心。\n");
		return;
	}
}
