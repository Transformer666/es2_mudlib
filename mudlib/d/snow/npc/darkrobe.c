// NPC: /d/snow/npc/darkrobe.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("黑袍老人", ({"darkrobe", "old_man", "elder"}));
	set_attr("str", 18);
	set_attr("dex", 20);
	set_attr("con", 17);
	set_attr("int", 22);
	set_attr("wis", 24);
	set_attr("spi", 20);
	set_race("human");
	set_class("commoner");
	set_level(35);

	set_skill("unarmed", 60);
	set_skill("force", 70);
	set_skill("regular force", 80);
	map_skill("force", "regular force");

	advance_stat("gin", 150);
	advance_stat("kee", 120);

	set("age", 68);
	set("gender", "male");
	set("long",
		"一個穿著黑色長袍的老人﹐面容消瘦而憔悴﹐深邃的眼窩裡透\n"
		"出一股難以言喻的悲傷。他佝僂著身子坐在破舊莊園的牆角﹐不\n"
		"時望向遠方﹐嘴裡喃喃自語著什麼。雖然衣著破舊﹐但舉手投足\n"
		"之間隱隱有一股不凡的氣度。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"黑袍老人喃喃自語道﹕小語兒 ... 你到底在哪裡 ...\n",
		"黑袍老人望著遠方﹐長長地嘆了一口氣。\n",
		"黑袍老人閉上眼睛﹐似乎在回憶著什麼往事。\n",
	}));

	setup();
	carry_money("silver", 3);
	carry_object(STOCK_ARMOR("robe"))->wear();
}

int accept_fight()
{
	do_chat("黑袍老人搖了搖頭﹐說道﹕老朽無意與人動手﹐你走吧。\n");
	return 0;
}

void init()
{
	::init();
	if( is_fighting() || is_chatting() ) return;

	if( this_player()->query_temp("try/darkrobe") )
		do_chat("黑袍老人見到你﹐急切地問道﹕可有小語兒的消息﹖\n");
	else
		do_chat("黑袍老人抬起頭﹐用混濁的眼睛打量著你﹐似乎想說什麼。\n");
}

void relay_say(object ob, string msg)
{
	int tmp;

	if( !userp(ob) ) return;
	if( is_fighting() || is_chatting() ) return;

	tmp = ob->query_temp("try/darkrobe");

	if( !tmp || tmp == 0 ) {
		if( strsrch(msg, "女兒") >= 0 || strsrch(msg, "小語") >= 0 ) {
			do_chat(({
				"黑袍老人眼眶一紅﹐說道﹕你 ... 你知道小語兒的消息﹖\n",
				"黑袍老人說道﹕小語兒是我的女兒﹐三個月前出門採藥就再也沒有回來 ...\n",
				"黑袍老人說道﹕我找遍了附近的山林﹐問遍了鎮上的人﹐都沒有她的消息。\n",
				"黑袍老人說道﹕如果你願意幫我找到她﹐老朽感激不盡。\n",
			}));
			ob->set_temp("try/darkrobe", 1);
		}
		return;
	}
}
