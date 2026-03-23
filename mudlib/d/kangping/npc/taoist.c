// vim: syntax=lpc
// Quest: 安懶道人的考驗 (anlan_test)
// Flow: talk to taoist -> learn about lost jade flute in bamboo grove
//       -> search bamboo grove -> give flute to taoist -> reward

#include <npc.h>

inherit F_SCHOLAR;

void do_reward(object player);

void create()
{
	set_name("安懶道人", ({"taoist", "anlan"}));
	set_attr("str", 20);
	set_attr("con", 25);
	set_attr("dex", 30);
	set_race("human");
	set_class("taoist");
	set_level(40);

	set_skill("sword", 120);
	set_skill("dodge", 110);
	set_skill("parry", 100);
	set_skill("internal", 100);

	set("age", 65);
	set("gender", "male");
	set("long",
		"一個身穿舊道袍的老道士﹐鶴髮童顏﹐面帶微笑。他手持一柄\n"
		"拂塵﹐腳踩布鞋﹐看起來懶洋洋的﹐似乎隨時都要打瞌睡。但他\n"
		"偶爾一閃的目光卻精芒四射﹐顯然是個深藏不露的高手。\n");
	set("chat_chance", 1);
	set("chat_msg", ({
		"安懶道人打了個哈欠﹐自言自語道﹕無量天尊﹐又是無聊的一天。\n",
		"安懶道人靠在藤椅上﹐似睡非睡﹐嘴角掛著一絲笑意。\n",
		"安懶道人忽然睜開眼睛﹐念道﹕道可道﹐非常道……接著又閉上了眼。\n",
	}));
	setup();
	carry_money("coin", 200);
	set_temp("apply/vision_of_ghost", 1);
}

void do_reward(object player)
{
	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/anlan_test_done") ) return;

	player->set("quest/anlan_test_done", 1);
	player->delete_temp("pending/anlan_test");
	player->gain_score("quest", 80);

	player->carry_money("silver", 3);
	tell_object(player, "( 你獲得了三兩銀子 )\n");
}

int accept_object(object who, object ob)
{
	if( !ob->id("jade flute") ) return 0;

	if( who->query("quest/anlan_test_done") ) {
		do_chat("安懶道人擺擺手﹐說道﹕不必了﹐玉笛已經找回來了。\n");
		return 0;
	}
	if( !who->query_temp("pending/anlan_test") ) {
		do_chat("安懶道人瞥了一眼﹐懶洋洋地說道﹕嗯﹖這笛子倒是不錯。\n");
		return 0;
	}

	do_chat(({
		"安懶道人睜開眼睛﹐接過玉笛﹐仔細端詳了一番。\n",
		"安懶道人眼中閃過一絲欣慰﹐說道﹕就是這支笛子﹗跟了我四十年了。\n",
		"安懶道人將玉笛湊到嘴邊﹐輕輕吹了一聲﹐笛音清越悠揚﹐餘韻不絕。\n",
		"安懶道人收好玉笛﹐微笑道﹕你這年輕人﹐倒是不錯﹐肯跑這一趟。\n",
		"安懶道人從藤椅下摸出幾兩碎銀﹐丟了過來﹐說道﹕拿著吧﹐算是貧道的一點心意。\n",
		(: do_reward, who :),
	}));
	return 1;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "學") >= 0 || strsrch(msg, "教") >= 0
	||  strsrch(msg, "武功") >= 0 || strsrch(msg, "考驗") >= 0
	||  strsrch(msg, "拜師") >= 0 || strsrch(msg, "道") >= 0 ) {
		if( ob->query("quest/anlan_test_done") ) {
			do_chat("安懶道人擺擺手﹐說道﹕別煩我﹐讓貧道安靜一會兒。\n");
			return;
		}
		if( ob->query_temp("pending/anlan_test") >= 2 ) {
			do_chat("安懶道人打了個哈欠﹕村南竹林裡﹐落葉底下找找﹐快去快回。\n");
			return;
		}
		if( ob->query_temp("pending/anlan_test") == 1 ) {
			do_chat(({
				"安懶道人懶洋洋地睜開一隻眼﹐說道﹕哦﹐你還沒走﹖\n",
				"安懶道人說道﹕也罷﹐貧道有支玉笛﹐前些日子在村南竹林裡打盹﹐醒來就不見了。\n",
				"安懶道人嘆道﹕那竹林裡落葉太厚﹐蹲下去找嫌累﹐你要是能幫我找回來……\n",
				"安懶道人又閉上眼﹐含糊道﹕嗯﹐找回來再說。\n",
			}));
			ob->set_temp("pending/anlan_test", 2);
			return;
		}
		do_chat(({
			"安懶道人打了個大大的哈欠﹐慢吞吞地說道﹕學什麼學﹐累不累啊。\n",
			"安懶道人擺擺手﹕倒是有件小事﹐不知你願不願意跑一趟。\n",
		}));
		ob->set_temp("pending/anlan_test", 1);
		return;
	}

	if( strsrch(msg, "玉笛") >= 0 || strsrch(msg, "竹林") >= 0
	||  strsrch(msg, "笛") >= 0 || strsrch(msg, "小事") >= 0 ) {
		if( ob->query("quest/anlan_test_done") ) {
			do_chat("安懶道人摸了摸懷中的玉笛﹐微笑道﹕已經找回來了﹐多謝。\n");
			return;
		}
		if( !ob->query_temp("pending/anlan_test") )
			ob->set_temp("pending/anlan_test", 1);
		if( ob->query_temp("pending/anlan_test") < 2 ) {
			do_chat(({
				"安懶道人說道﹕貧道有支隨身帶了四十年的玉笛﹐前些日子在村南竹林裡打盹時弄丟了。\n",
				"安懶道人嘆道﹕那竹林裡落葉太厚﹐蹲下去找太費勁﹐你要是肯幫忙﹐貧道自當感謝。\n",
			}));
			ob->set_temp("pending/anlan_test", 2);
			return;
		}
		do_chat("安懶道人打了個哈欠﹕村南竹林裡﹐落葉底下找找看吧。\n");
		return;
	}
}
