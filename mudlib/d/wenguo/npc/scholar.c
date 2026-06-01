// scholar.c -- 文國大街上流連筆鋪的青衫書生（純氣氛閒談 + 本地指路﹐不接任務、不動旗標）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("書生", ({ "scholar", "student", "shusheng" }) );
	set("nickname", "書生");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 24);
	set("gender", "male");
	set("long",
		"一個青衫方巾的年輕書生﹐生得面如冠玉、眉目清朗﹐袖著\n"
		"手在街心的筆鋪墨坊前流連﹐時而拈起一管筆對著天光看鋒﹐時\n"
		"而就著鼻子聞一聞新墨的香﹐口中喃喃地品評著高下。他像是縣\n"
		"學裡備考的生員﹐談起這『翰墨之鄉』的筆墨來頭頭是道﹐見了\n"
		"問路的生客﹐倒也樂得拱手指點一番。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"書生拈起一管筆對著天光看了看鋒﹐微微頷首﹐似是頗為中意。\n",
		"書生就著鼻子聞了聞一錠新墨﹐閉目品味片刻﹐讚道﹕好墨﹗這松煙和得地道。\n",
		"書生負手望著街心的文昌閣﹐口中念念有詞﹐似在溫習應考的文章。\n",
	}));
	setup();
	carry_money("coin", 15);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這書生甚麼﹖（試試 ask scholar about 文國）\n");

	if( arg == "scholar about 文國"
	||  arg == "scholar about 縣"
	||  arg == "scholar about 文國縣"
	||  arg == "scholar about 翰墨"
	||  arg == "scholar about 路"
	||  arg == "scholar about wenguo"
	||  arg == "scholar about way" ) {
		do_chat(({
			(: command, "say 兄臺面生﹐是初到敝縣罷﹖咱文國雖是北疆小縣﹐卻文風極盛﹐人稱『翰墨之鄉』——這一條大街上﹐筆鋪、墨坊、紙莊、書肆一家挨著一家﹐兄臺循著墨香逛去﹐錯不了。" :),
			(: command, "say 兄臺要尋宿﹐東邊便是天風客棧﹔要吃茶論文﹐東南文瀾茶肆最好。若有興致看看好筆好墨怎麼來的﹐西北制筆作坊、廣場東邊松煙墨坊﹐都可一觀﹔廣場西邊墨池小園﹐更是讀書人靜心的好去處。" :),
		}));
		return 1;
	}

	return notify_fail("書生拱手一揖﹕兄臺問這個做甚﹖這滿街的筆墨書香﹐慢慢逛便是。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗兄臺好沒道理﹗在下一介手無縛雞之力的書生﹐與兄臺無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
