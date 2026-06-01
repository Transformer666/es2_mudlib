// passer.c -- 五向路口往來的路人（純氣氛閒談 + 本地指路）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("路人", ({ "passer", "passerby", "townman" }) );
	set("nickname", "路人");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 41);
	set("gender", "male");
	set("long",
		"一個尋常的斐縣縣民﹐挑著副空了的菜擔﹐方趕完集要回鄉\n"
		"去。他在五向路口略略停了步﹐瞇眼瞧著路碑辨認去向﹐一臉鄉\n"
		"下人趕集慣了的從容。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"路人挑著菜擔﹐在路碑前停了停﹐辨了辨去向﹐又慢悠悠地走了。\n",
		"路人朝你拱了拱手﹐算是打了個招呼。\n",
		"路人說道﹕客官面生得很﹐是頭一回到斐縣罷﹖這五向路口岔得繞﹐莫要走錯了道。\n",
		"路人指著西邊那面大旗道﹕餓了渴了﹐就上錢記酒樓坐坐﹐那滷味可是一絕哩。\n",
	}));
	setup();
	carry_money("coin", 25);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位路人甚麼﹖（試試 ask passer about 路）\n");

	if( arg == "passer about 路"
	||  arg == "passer about 五向路口"
	||  arg == "passer about 路口"
	||  arg == "passer about 斐縣"
	||  arg == "passer about way"
	||  arg == "passer about feixian" ) {
		do_chat(({
			(: command, "say 客官聽好了﹕這五向路口﹐西去是錢記酒樓﹐北去是清風茶行﹐東邊是悅客來客棧﹐往南那條縣前街通著縣衙與雜貨鋪。" :),
			(: command, "say 那西南一條土道﹐穿過田壟便接回喬陰市集了。客官要往哪兒去﹐照著路碑走﹐準錯不了。" :),
		}));
		return 1;
	}

	return notify_fail("路人挑著擔子﹐衝你憨憨一笑﹐似是沒聽明白。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖咱一個趕集的莊稼人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
