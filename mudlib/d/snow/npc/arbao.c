// vim: syntax=lpc
// arbao.c - 阿寶 (謎1: 阿寶在老榕樹等的人是誰？)
// Quest: deliver letter to recruiter, bring back reply

#include <npc.h>

inherit F_VILLAGER;

void give_quest_reward(object player);

void create()
{
	set_name("阿寶", ({"arbao", "abao"}));
	set_attr("str", 15);
	set_attr("dex", 19);
	set_attr("con", 17);
	set_attr("int", 19);
	set_attr("spi", 18);
	set_race("human");
	set_class("commoner");
	set_level(10);

	set_skill("dodge", 35);
	set_skill("dagger", 40);

	set("age", 16);
	set("gender", "female");
	set("long",
		"這個十五、六歲的小姑娘就是「阿寶」了﹐她身上雖然穿著粗布\n"
		"衣服﹐但卻十足是個美人胚子。她是瞎眼老太婆的孫女﹐平日裡\n"
		"幫忙打理家務﹐偶爾也會到鎮上走走。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"阿寶說道：奶奶的眼睛越來越不好了﹐真讓人擔心。\n",
		"阿寶低著頭﹐不知在想些什麼。\n",
		"阿寶好奇地打量著過路的江湖人。\n",
		"阿寶抬頭望了望老榕樹﹐輕輕嘆了口氣。\n",
	}));
	setup();
	carry_object(STOCK_ARMOR("cloth"))->wear();
	carry_object(STOCK_WEAPON("dagger"))->wield();
	carry_money("coin", 30);
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/arbao_letter_done") )
		return;

	if( this_player()->query_temp("pending/arbao_reply") )
		do_chat("阿寶滿懷期待地望著你﹐問道﹕有阿明哥哥的消息了嗎﹖\n");
}

private void give_quest_reward(object player)
{
	object money;

	if( !player || environment(player) != environment() ) return;

	player->set("quest/arbao_letter_done", 1);
	player->gain_score("quest", 80);

	money = new("/obj/money/coin");
	money->set_amount(50);
	if( !money->move(player) )
		money->move(environment());
}

int accept_object(object player, object ob)
{
	if( !userp(player) ) return 0;
	if( player->query("quest/arbao_letter_done") ) return 0;

	if( ob->id("reply letter") || ob->id("reply") ) {
		if( !player->query_temp("pending/arbao_reply") ) return 0;

		do_chat(({
			"阿寶接過信件﹐急忙拆開來看。\n",
			"阿寶的眼眶漸漸紅了﹐喃喃道﹕阿明哥哥平安就好 ...\n",
			"阿寶擦了擦眼淚﹐感激地說道﹕多謝你幫我打聽消息。\n",
			"阿寶說道﹕這點錢不算什麼﹐算是我的一點心意。\n",
			(: give_quest_reward, player :),
		}));
		player->delete_temp("pending/arbao_reply");
		return 1;
	}
	return 0;
}

void relay_say(object ob, string msg)
{
	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( ob->query("quest/arbao_letter_done") ) return;

	// Already has the reply, remind to give it
	if( ob->query_temp("pending/arbao_reply") ) {
		if( strsrch(msg, "阿明") >= 0 || strsrch(msg, "消息") >= 0 ) {
			do_chat("阿寶急切地說道﹕你有阿明哥哥的消息嗎﹖快告訴我﹗\n");
			return;
		}
		return;
	}

	// Already gave the letter to deliver
	if( ob->query_temp("pending/arbao_deliver") ) {
		if( strsrch(msg, "阿明") >= 0 || strsrch(msg, "信") >= 0 ) {
			do_chat("阿寶說道﹕拜託你把信帶到鎮北的軍營﹐交給招兵官就好。\n");
			return;
		}
		return;
	}

	// Trigger quest
	if( strsrch(msg, "等人") >= 0 || strsrch(msg, "等誰") >= 0
	||	strsrch(msg, "心事") >= 0 || strsrch(msg, "怎麼了") >= 0
	||	strsrch(msg, "阿明") >= 0 ) {
		object letter;

		do_chat(({
			"阿寶猶豫了一下﹐低聲說道﹕我在等一個人 ...\n",
			"阿寶說道﹕阿明哥哥去年去軍營當兵﹐說好了會常回來看我和奶奶的 ...\n",
			"阿寶說道﹕可是他走了之後就一直沒有消息﹐我好擔心。\n",
			"阿寶說道﹕大俠﹐你能不能幫我把這封信帶到鎮北的軍營﹐交給那裡的招兵官﹖\n",
			"阿寶說道﹕請他幫忙查查阿明哥哥的下落﹐拜託你了﹗\n",
		}));
		letter = new(__DIR__"obj/arbao_letter");
		letter->move(ob);
		ob->set_temp("pending/arbao_deliver", 1);
		return;
	}

	if( strsrch(msg, "奶奶") >= 0 || strsrch(msg, "婆婆") >= 0 ) {
		do_chat("阿寶說道﹕我奶奶的眼睛不太好﹐我得常常陪著她。\n");
		return;
	}
}
