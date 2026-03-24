// grave_keeper.c
// Quest: gravekeeper_pendant
// Flow: talk about 師父/玉佩 -> get quest -> search coffin in tomb_inner
//       -> get jade_pendant -> give pendant to grave_keeper -> reward

#include <npc.h>

inherit F_VILLAGER;

void give_pendant_reward(object me);

void create()
{
	set_name("守墓人", ({"grave_keeper", "keeper"}));
	set_attr("str", 14);
	set_attr("con", 16);
	set_attr("dex", 12);
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 60);
	set("long",
		"一個形容枯槁的老人﹐穿著一件黑色的舊棉襖﹐臉色蠟黃﹐兩\n"
		"眼深陷。他獨自住在這破廟裡看守亂葬崗﹐也不知過了多少年。見\n"
		"到有人來﹐他也不驚不怕﹐只是淡淡地看了一眼。\n");
	set("chat_chance", 2);
	set("chat_msg", ({
		"守墓人沙啞地說道﹕活人不該來這種地方﹐趕緊走吧。\n",
		"守墓人往火堆裡添了根柴﹐火光映照著他枯瘦的臉龐。\n",
		"守墓人嘆道﹕這裡埋著的都是些無名之輩﹐死了連個收屍的人都沒有。\n",
		"守墓人低聲說道﹕夜裡別出去﹐外面有些……不乾淨的東西。\n",
	}));
	setup();
	carry_money("coin", 25);
}

int accept_object(string me_id, object ob)
{
	object giver;

	giver = this_player();
	if( !giver ) return 0;

	if( base_name(ob) == __DIR__"obj/jade_pendant" ) {
		if( giver->query("quest/gravekeeper_pendant_done") ) {
			do_chat("守墓人搖了搖頭﹐說道﹕你已經幫過我了﹐不用再費心。\n");
			return 0;
		}

		if( !giver->query_temp("pending/gravekeeper_pendant") ) {
			do_chat("守墓人疑惑地看著玉佩﹐說道﹕這是 ... 你從哪裡得來的﹖\n");
			return 0;
		}

		do_chat(({
			"守墓人顫抖著接過玉佩﹐老淚縱橫。\n",
			"守墓人哽咽道﹕師父 ... 徒兒不孝﹐這麼多年才把您的遺物找回來 ...\n",
			"守墓人將玉佩緊緊握在掌心﹐沉默了好一會兒。\n",
			"守墓人深吸一口氣﹐對你抱拳道﹕多謝小友﹐老朽一輩子的心願總算了了。\n",
			(: give_pendant_reward, giver :),
		}));
		return 1;
	}

	return 0;
}

void give_pendant_reward(object me)
{
	object lantern;

	if( !me || environment(me) != environment() ) return;
	if( me->query("quest/gravekeeper_pendant_done") ) return;

	me->set("quest/gravekeeper_pendant_done", 1);
	me->delete_temp("pending/gravekeeper_pendant");
	me->gain_score("quest", 100);

	lantern = new(__DIR__"obj/ghost_lantern");
	if( lantern ) {
		lantern->move(this_object());
		command("give lantern to " + me->query("id"));

		do_chat(({
			"守墓人說道﹕這盞鬼火燈是我在這墳場多年的一點心得﹐送你防身吧。\n",
			"守墓人說道﹕這墳場裡的孤魂野鬼﹐見了這燈便不敢靠近。\n",
		}));
	}
}

void relay_say(object me, string msg)
{
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "師父") >= 0 || strsrch(msg, "玉佩") >= 0
	||  strsrch(msg, "pendant") >= 0 || strsrch(msg, "master") >= 0 ) {
		if( me->query("quest/gravekeeper_pendant_done") ) {
			do_chat("守墓人輕輕摩挲著手中的玉佩﹐臉上露出一絲安慰的笑容。\n");
			return;
		}

		if( me->query_temp("pending/gravekeeper_pendant") ) {
			do_chat(({
				"守墓人說道﹕你找到師父的玉佩了嗎﹖\n",
				"守墓人說道﹕應該就在東邊那座古墓的石棺裡 ...\n",
			}));
			return;
		}

		do_chat(({
			"守墓人眼中閃過一絲哀傷﹐緩緩說道﹕\n",
			"守墓人說道﹕老朽從前跟著師父習武﹐師父是個了不起的人 ...\n",
			"守墓人說道﹕可惜師父遭人陷害﹐含冤而死﹐被草草葬在這亂葬崗。\n",
			"守墓人長嘆一聲﹐說道﹕師父生前有塊蓮花玉佩﹐刻著「清心」二字。\n",
			"守墓人說道﹕當年來不及收回﹐應該還在古墓的石棺裡 ...\n",
			"守墓人說道﹕老朽年邁體衰﹐那古墓裡又有殭屍出沒 ...\n",
			"守墓人用懇求的目光看著你﹐說道﹕小友﹐能否幫老朽取回那塊玉佩﹖\n",
			(: $1->set_temp("pending/gravekeeper_pendant", 1) :),
		}));
		return;
	}

	if( strsrch(msg, "墓碑") >= 0 || strsrch(msg, "碑文") >= 0
	||  strsrch(msg, "碑") >= 0 || strsrch(msg, "趙子清") >= 0 ) {
		if( me->query("quest/stele_prayer_done") ) {
			do_chat("守墓人說道﹕自從你祭拜了那塊墓碑﹐這裡的陰氣確實消散了不少。多謝你。\n");
			return;
		}
		do_chat(({
			"守墓人沉吟片刻﹐說道﹕你問那塊墓碑﹖\n",
			"守墓人說道﹕南邊的荒塚裡有一塊碑﹐上面刻的字比別的都清楚。\n",
			"守墓人嘆道﹕那是一個姓趙的書生﹐年紀輕輕就含冤而死。\n",
			"守墓人說道﹕老朽每隔些日子就幫他擦擦碑面﹐別的也做不了什麼。\n",
			"守墓人低聲說道﹕如果你有心﹐去那塊碑前祭拜一下吧﹐也許能讓那可憐的人安息。\n",
		}));
		return;
	}

	if( strsrch(msg, "古墓") >= 0 || strsrch(msg, "tomb") >= 0 ) {
		if( me->query_temp("pending/gravekeeper_pendant") )
			do_chat("守墓人說道﹕古墓就在東邊﹐穿過墳場就能看到了。裡面有殭屍﹐你小心。\n");
		else
			do_chat("守墓人說道﹕那座古墓不知是什麼年代的﹐裡面陰氣很重﹐最好別去。\n");
		return;
	}
}
