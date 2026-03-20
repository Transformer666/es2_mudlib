// escort.c - 老鏢師 (retired escort guard)
// Quest: talk to him about apprenticeship -> get guidance + first-time reward

#include <npc.h>

inherit F_VILLAGER;

void give_guide_reward(object player);

void create()
{
	set_name("老鏢師", ({"escort", "old escort", "biaoshi"}));
	set_attr("str", 20);
	set_attr("dex", 18);
	set_attr("con", 22);
	set_attr("int", 16);
	set_attr("wis", 18);
	set_attr("spi", 14);
	set_race("human");
	set_class("commoner");
	set_level(30);

	set_skill("blade", 70);
	set_skill("unarmed", 50);
	set_skill("parry", 60);
	set_skill("dodge", 55);

	set("age", 56);
	set("gender", "male");
	set("long",
		"一個身材魁梧的中年漢子﹐兩鬢已經花白﹐但目光依然炯炯有神。\n"
		"他穿著一件半舊的勁裝﹐腰間掛著一把沒有刀鞘的環首刀﹐看得出\n"
		"是走過江湖的人。他正悠閒地坐在路邊﹐一面喝茶一面看著來來往往\n"
		"的行人。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老鏢師喝了口茶﹐望著遠方若有所思。\n",
		"老鏢師嘆道﹕年輕的時候走遍大江南北﹐如今老了﹐只想安靜度日。\n",
		"老鏢師自言自語道﹕這雪亭鎮雖然不大﹐倒是臥虎藏龍啊。\n",
	}));

	setup();
	carry_money("silver", 2);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}

int accept_fight()
{
	do_chat("老鏢師擺了擺手﹐說道﹕老頭子退出江湖多年了﹐不打架。\n");
	return 0;
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/escort_guide_done") )
		return;

	if( this_player()->query_class() == "commoner"
	&&	!this_player()->query("title") )
		do_chat("老鏢師瞄了你一眼﹐說道﹕小伙子﹐看你孤身一人﹐可有拜師學藝的打算﹖\n");
}

private void give_guide_reward(object player)
{
	object money;

	if( !player || environment(player) != environment() ) return;

	player->set("quest/escort_guide_done", 1);
	player->gain_score("quest", 30);

	money = new("/obj/money/coin");
	money->set_amount(50);
	if( !money->move(player) )
		money->move(environment());
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( strsrch(msg, "拜師") >= 0 || strsrch(msg, "學武") >= 0
	||	strsrch(msg, "門派") >= 0 || strsrch(msg, "師父") >= 0 ) {
		if( ob->query("quest/escort_guide_done") ) {
			do_chat("老鏢師說道﹕之前不是跟你說過了嗎﹖去找那幾位前輩吧。\n");
			return;
		}
		do_chat(({
			"老鏢師放下茶杯﹐正色說道﹕想學武﹖好志氣。\n",
			"老鏢師說道﹕這雪亭鎮附近有好幾處可以拜師的地方。\n",
			"老鏢師說道﹕私塾裡的煉丹師可以教你煉丹之術﹐從學校往南找。\n",
			"老鏢師說道﹕軍營的招兵官收的是當兵的﹐想學刀法就去找他。\n",
			"老鏢師說道﹕鎮外還有幾個門派﹐不過那些地方可不是隨便就能進的。\n",
			"老鏢師說道﹕記住﹐想拜師就對著師父用 apprentice 指令。\n",
			"老鏢師說道﹕這點盤纏你拿著﹐路上買點吃的。\n",
			(: give_guide_reward, ob :),
		}));
		return;
	}

	if( strsrch(msg, "江湖") >= 0 || strsrch(msg, "鏢") >= 0 ) {
		do_chat(({
			"老鏢師嘆了口氣﹐說道﹕老頭子年輕時走南闖北押了幾十年鏢。\n",
			"老鏢師說道﹕見過的高手多了﹐也吃過不少虧﹐最後總算全身而退。\n",
			"老鏢師說道﹕如今退隱在這雪亭鎮﹐清閒度日。\n",
		}));
		return;
	}

	if( strsrch(msg, "煉丹") >= 0 || strsrch(msg, "丹") >= 0 ) {
		do_chat("老鏢師說道﹕私塾裡有位煉丹師﹐你去找他試試看。私塾在廣場西邊的街上。\n");
		return;
	}

	if( strsrch(msg, "當兵") >= 0 || strsrch(msg, "軍營") >= 0 ) {
		do_chat("老鏢師說道﹕軍營在廣場往北的街上﹐找招兵官就行了。\n");
		return;
	}

	if( strsrch(msg, "冷梅") >= 0 || strsrch(msg, "梅影風") >= 0 ) {
		do_chat("老鏢師說道﹕冷梅莊﹖那位梅莊主可不好惹﹐聽說在鎮的西南邊。\n");
		return;
	}

	if( strsrch(msg, "血印") >= 0 || strsrch(msg, "魚鐵山") >= 0 ) {
		do_chat("老鏢師說道﹕血印堂的魚鐵山﹖那是個狠角色﹐你要拜師得有心理準備。\n");
		return;
	}

	if( strsrch(msg, "苦笑") >= 0 || strsrch(msg, "劉乙") >= 0 ) {
		do_chat("老鏢師說道﹕苦笑門的劉乙忘玄﹐武功高深莫測﹐你可以去廣場東北方找他。\n");
		return;
	}
}
