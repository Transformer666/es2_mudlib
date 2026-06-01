// washerwoman.c -- 甘泉井畔浣衣的村婦（純氣氛閒談﹐不接任務、不動旗標）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("浣衣婦", ({ "washerwoman", "village woman", "huanyifu" }) );
	set("nickname", "浣衣婦");
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 38);
	set("gender", "female");
	set("long",
		"一個尋常打扮的本縣村婦﹐挽著袖子蹲在甘泉井畔的青石\n"
		"上﹐木盆裡堆著一家老小的衣裳﹐手腕隨著捶衣的木杵一起一\n"
		"落﹐濺起細碎的水花。她臉膛被日頭曬得微紅﹐神色卻是鄉間婦\n"
		"人特有的那份爽利安詳﹐一面捶衣﹐一面與井邊的人說笑。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"浣衣婦舉起木杵﹐啪啪地捶著青石上的衣裳﹐濺起一串細碎的水花。\n",
		"浣衣婦把浣好的衣裳擰乾了﹐搭在臂彎裡﹐口中與旁邊汲水的人說笑了兩句。\n",
		"浣衣婦抬手抹了把額上的汗﹐衝你和氣地一笑﹐又低頭捶她的衣裳去了。\n",
	}));
	setup();
	carry_money("coin", 5);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這浣衣婦甚麼﹖（試試 ask washerwoman about 甘泉）\n");

	if( arg == "washerwoman about 甘泉"
	||  arg == "washerwoman about 井"
	||  arg == "washerwoman about 水"
	||  arg == "washerwoman about 婁縣"
	||  arg == "washerwoman about spring" ) {
		do_chat(({
			(: command, "say 客官是外鄉來的罷﹖咱這甘泉井的水啊﹐汲上來清凌凌的﹐喝著回甘﹐洗衣裳也省皂角﹐合縣人家都指著這口井過日子哩。" :),
			(: command, "say 不過近來這水滲得慢了些﹐打水都得多候一會兒﹐也不曉得是怎的。客官要逛﹐沿石板路往南就回街心了。" :),
		}));
		return 1;
	}

	return notify_fail("浣衣婦只顧捶著衣裳﹐衝你爽利地一笑﹐似是忙著手裡的活計。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗這位客官好沒道理﹗光天化日的﹐欺負我一個浣衣的婦道人家做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
