// old_beggar.c - 老乞婆任務 NPC
// Quest: bring 棉襖 → 匕首 → 西瓜, rewards 念珠 + 白長袍

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("老乞婆", ({"old beggar", "beggar", "crone", "__ID_OLD_BEGGAR__"}));
	set_attr("str", 10);
	set_attr("dex", 12);
	set_attr("con", 11);
	set_attr("int", 18);
	set_attr("wis", 20);
	set_attr("spi", 22);
	set_race("human");
	set_class("commoner");
	set_level(15);

	set_skill("unarmed", 20);
	set_skill("dodge", 30);

	set("age", 72);
	set("gender", "female");
	set("long",
		"一個衣衫襤褸的老婆婆﹐滿頭白髮散亂地披在肩上﹐臉上佈滿\n"
		"了深深的皺紋。她蜷縮在牆角﹐不時用乾枯的手搓著身上單薄的\n"
		"衣裳﹐似乎很冷的樣子。雖然看起來落魄﹐但她的眼神中偶爾閃\n"
		"過一絲不凡的光芒。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老乞婆縮了縮身子﹐喃喃道﹕好冷啊 ...\n",
		"老乞婆嘆了口氣﹐望著來來往往的行人。\n",
		"老乞婆用手搓了搓胳膊﹐似乎在努力取暖。\n",
	}));

	setup();
	carry_money("coin", 5);
	carry_object(STOCK_ARMOR("cloth"))->wear();
}

int accept_fight()
{
	do_chat("老乞婆連忙擺手道﹕別 ... 別打我﹐我只是個老婆子。\n");
	return 0;
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;
	if( !userp(this_player()) ) return;

	if( this_player()->query("quest/old_beggar_done") ) {
		do_chat("老乞婆笑瞇瞇地看著你﹐說道﹕是你啊﹐好心人。\n");
		return;
	}

	switch( this_player()->query_temp("pending/old_beggar") ) {
	case 1:
		do_chat("老乞婆說道﹕好心人﹐我好冷啊﹐能不能幫我找件棉襖來穿﹖\n");
		break;
	case 2:
		do_chat("老乞婆說道﹕好心人﹐路上不太平﹐能不能幫我弄把匕首防身﹖\n");
		break;
	case 3:
		do_chat("老乞婆說道﹕好心人﹐我好渴好餓﹐能不能幫我找個西瓜來﹖\n");
		break;
	default:
		do_chat("老乞婆抬起頭﹐用可憐的眼神望著你﹐似乎想開口說話。\n");
		break;
	}
}

private void give_rewards(object player)
{
	object rosary, robe;

	if( !player || environment(player) != environment() ) return;

	rosary = new(__DIR__"obj/rosary");
	if( !rosary->move(player) )
		rosary->move(environment());

	robe = new(__DIR__"obj/white_robe");
	if( !robe->move(player) )
		robe->move(environment());

	player->set("quest/old_beggar_done", 1);
	player->gain_score("quest", 200);
}

int accept_object(object player, object ob)
{
	int stage;

	if( !userp(player) ) return 0;
	if( player->query("quest/old_beggar_done") ) {
		do_chat("老乞婆擺擺手道﹕你已經幫過我了﹐這個你自己留著吧。\n");
		return 0;
	}

	stage = player->query_temp("pending/old_beggar");

	// Stage 1: need 棉襖 (maro / cloth type clothing)
	if( stage == 1 ) {
		if( ob->id("maro") || ob->id("cotton coat") ) {
			do_chat(({
				"老乞婆接過棉襖﹐連忙穿上﹐感動地說道﹕太好了﹐真暖和 ...\n",
				"老乞婆說道﹕好心人﹐能不能再幫我一個忙﹖\n",
				"老乞婆說道﹕我身上沒有防身的東西﹐能不能幫我弄把匕首﹖\n",
			}));
			player->set_temp("pending/old_beggar", 2);
			return 1;
		}
		do_chat("老乞婆搖搖頭﹐說道﹕我需要一件棉襖﹐太冷了 ...\n");
		return 0;
	}

	// Stage 2: need 匕首 (dagger)
	if( stage == 2 ) {
		if( ob->id("dagger") ) {
			do_chat(({
				"老乞婆接過匕首﹐小心地藏在懷裡﹐說道﹕有了這個就安心多了。\n",
				"老乞婆說道﹕好心人﹐我還有最後一個請求 ...\n",
				"老乞婆說道﹕我又渴又餓﹐能不能幫我找個西瓜來﹖\n",
			}));
			player->set_temp("pending/old_beggar", 3);
			return 1;
		}
		do_chat("老乞婆說道﹕我需要一把匕首防身 ...\n");
		return 0;
	}

	// Stage 3: need 西瓜 (watermelon)
	if( stage == 3 ) {
		if( ob->id("watermelon") || ob->id("melon") ) {
			do_chat(({
				"老乞婆接過西瓜﹐大口大口地吃了起來。\n",
				"老乞婆吃完西瓜﹐忽然渾身一震﹐一股靈氣在經脈中流動。\n",
				"老乞婆站起身來﹐精神煥發﹐與先前判若兩人。\n",
				"老乞婆微笑道﹕多謝你了﹐好心人。這兩樣東西送給你﹐算是老婆子的一點心意。\n",
				(: give_rewards, this_player() :),
			}));
			return 1;
		}
		do_chat("老乞婆說道﹕我需要一個西瓜 ... 好渴 ...\n");
		return 0;
	}

	return 0;
}

void relay_say(object ob, string msg)
{
	int stage;

	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	if( ob->query("quest/old_beggar_done") ) return;

	stage = ob->query_temp("pending/old_beggar");

	if( !stage || stage == 0 ) {
		if( strsrch(msg, "幫") >= 0 || strsrch(msg, "忙") >= 0
		||	strsrch(msg, "怎麼了") >= 0 || strsrch(msg, "什麼事") >= 0 ) {
			do_chat(({
				"老乞婆感激地說道﹕你 ... 你願意幫我﹖\n",
				"老乞婆說道﹕我流落到這裡﹐身上又冷又餓﹐什麼都沒有 ...\n",
				"老乞婆說道﹕好心人﹐能不能先幫我找件棉襖來﹖我實在冷得受不了了。\n",
			}));
			ob->set_temp("pending/old_beggar", 1);
			return;
		}
		if( strsrch(msg, "冷") >= 0 || strsrch(msg, "棉襖") >= 0 ) {
			do_chat("老乞婆點點頭﹐哀求道﹕是啊﹐我好冷﹐能幫幫我嗎﹖\n");
			return;
		}
	}

	if( stage == 1 && strsrch(msg, "棉襖") >= 0 ) {
		do_chat("老乞婆說道﹕旅人身上有時會帶著棉襖﹐你去問問看吧。\n");
		return;
	}

	if( stage == 2 && strsrch(msg, "匕首") >= 0 ) {
		do_chat("老乞婆說道﹕鎮上的鐵匠鋪應該有賣匕首。\n");
		return;
	}

	if( stage == 3 && strsrch(msg, "西瓜") >= 0 ) {
		do_chat("老乞婆說道﹕聽說南邊的田裡有種西瓜﹐你去看看吧。\n");
		return;
	}
}
