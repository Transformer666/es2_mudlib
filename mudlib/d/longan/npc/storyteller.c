// vim: syntax=lpc
// Quest: 說書人的遺物 (storyteller_pendant)
// Flow: talk -> learn about lost jade pendant -> talk to gardener for clue
//       -> search lake_cave -> give pendant to storyteller -> reward

#include <npc.h>

inherit F_VILLAGER;

void do_reward(object player);

void create()
{
	set_name("說書人", ({"storyteller", "old_man"}));
	set_race("human");
	set_class("commoner");
	set_level(8);

	set_skill("unarmed", 20);

	set("age", 60);
	set("gender", "male");
	set("long",
		"一位鬚髮斑白的老者，身穿褪色的灰布長衫，手持一把摺扇。他\n"
		"坐在廣場角落的石凳上，繪聲繪色地講述著江湖上的奇聞軼事，周\n"
		"圍聚攏了不少聽眾。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"說書人一拍醒木，朗聲道：話說當年天邪國一戰，那可是驚天動地！\n",
		"說書人搖著摺扇，笑道：列位看倌，且聽下回分解。\n",
		"說書人呷了口茶，清了清嗓子，繼續說道：卻說那封山派的劍法……\n",
		"說書人嘆道：江湖險惡，世事難料啊。\n",
	}));

	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_money("coin", 50);
}

void do_reward(object player)
{
	if( !player || !present(player, environment()) ) return;
	if( player->query("quest/storyteller_pendant_done") ) return;

	player->set("quest/storyteller_pendant_done", 1);
	player->delete_temp("pending/storyteller_pendant");
	player->gain_score("quest", 100);

	player->carry_money("silver", 3);
	tell_object(player, "( 你獲得了三兩銀子 )\n");
}

int accept_object(object who, object ob)
{
	if( !ob->id("jade pendant") ) return 0;

	if( who->query("quest/storyteller_pendant_done") ) {
		do_chat("說書人搖搖頭﹐說道﹕不用了﹐玉佩已經找回來了。\n");
		return 0;
	}
	if( !who->query_temp("pending/storyteller_pendant") ) {
		do_chat("說書人好奇地打量著玉佩﹐說道﹕這玉佩……倒是個好東西。\n");
		return 0;
	}

	do_chat(({
		"說書人接過玉佩﹐雙手微微顫抖﹐老淚縱橫。\n",
		"說書人顫聲道﹕這……這正是家父的遺物﹗「韓」字……沒錯﹐就是這枚玉佩﹗\n",
		"說書人擦了擦眼淚﹐說道﹕想不到幾十年了﹐竟然還能找回來。\n",
		"說書人深吸一口氣﹐感激地說道﹕多謝你冒著生命危險幫我找回了這枚玉佩﹐這份恩情我永遠記在心裡。\n",
		"說書人從懷中取出幾兩碎銀﹐說道﹕這點銀子不成敬意﹐你收下吧。\n",
		(: do_reward, who :),
	}));
	return 1;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "往事") >= 0 || strsrch(msg, "故事") >= 0
	||  strsrch(msg, "傷心") >= 0 || strsrch(msg, "家人") >= 0 ) {
		if( ob->query("quest/storyteller_pendant_done") ) {
			do_chat("說書人撫摸著胸前的玉佩﹐微笑道﹕多虧了你﹐家父的遺物失而復得﹐老夫心中甚慰。\n");
			return;
		}
		if( ob->query_temp("pending/storyteller_pendant") >= 2 ) {
			do_chat("說書人說道﹕那枚玉佩就是在城東花園後面的湖底洞穴裡丟的﹐你去找找看吧﹐可要當心那條龍。\n");
			return;
		}
		if( ob->query_temp("pending/storyteller_pendant") == 1 ) {
			do_chat(({
				"說書人收起摺扇﹐神色黯然﹐說道﹕其實老夫年輕時也是江湖中人。\n",
				"說書人嘆道﹕家父當年是有名的劍客﹐留給我一枚刻有「韓」字的玉佩﹐是我最珍貴的東西。\n",
				"說書人說道﹕三十年前我途經城東的湖邊﹐不料驚動了洞裡的黑龍﹐慌忙逃命時玉佩掉在了洞中。\n",
				"說書人苦笑道﹕那條黑龍兇猛無比﹐我這把老骨頭根本不敢再靠近。花園裡的老園丁也知道這件事。\n",
			}));
			ob->set_temp("pending/storyteller_pendant", 2);
			return;
		}
		do_chat(({
			"說書人手中的摺扇停了下來﹐沉默了片刻。\n",
			"說書人嘆道﹕說了一輩子別人的故事﹐其實老夫自己也有一段遺憾。\n",
		}));
		ob->set_temp("pending/storyteller_pendant", 1);
		return;
	}

	if( strsrch(msg, "玉佩") >= 0 || strsrch(msg, "遺物") >= 0
	||  strsrch(msg, "黑龍") >= 0 || strsrch(msg, "洞穴") >= 0 ) {
		if( ob->query("quest/storyteller_pendant_done") ) {
			do_chat("說書人摸了摸懷中的玉佩﹐笑道﹕已經找回來了﹐多謝你。\n");
			return;
		}
		if( !ob->query_temp("pending/storyteller_pendant") )
			ob->set_temp("pending/storyteller_pendant", 1);
		if( ob->query_temp("pending/storyteller_pendant") < 2 ) {
			do_chat(({
				"說書人嘆道﹕那枚玉佩是家父的遺物﹐三十年前掉在了湖底洞穴裡。\n",
				"說書人說道﹕洞裡有一條黑龍盤踞﹐誰也不敢靠近。你若是有膽量﹐幫我找回來如何﹖\n",
			}));
			ob->set_temp("pending/storyteller_pendant", 2);
			return;
		}
		do_chat("說書人說道﹕城東花園後面就是那個湖底洞穴﹐玉佩應該還在裡面﹐你去找找看吧。\n");
		return;
	}
}
