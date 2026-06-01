// farmer.c -- 井邊歇腳的老農，說古道今的鄉野人物（純氣氛/伏筆，不開任何任務）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老農", ({ "farmer", "old farmer", "peasant" }) );
	set("nickname", "老農");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 63);
	set("gender", "male");
	set("long",
		"一個飽經風霜的老農﹐臉膛黑紅﹐溝壑似的皺紋裡嵌著洗不\n"
		"淨的泥色﹐褲腳還沾著田裡的新泥。他蹲在井邊歇腳﹐叼著一桿\n"
		"旱煙袋﹐眯眼望著遠處的青山﹐肚裡裝著滿滿一肚子鄉野的奇談\n"
		"異聞。你或許可以問問他﹕ask farmer about 兆隱﹐或是\n"
		"ask farmer about 渾沌獸。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"老農吧嗒著旱煙袋﹐瞇眼望著遠山﹐悠悠地吐出一口煙。\n",
		"老農慢悠悠地道﹕咱這兆隱縣啊﹐地方是僻了些﹐可勝在山清水秀﹐少是非。\n",
		"老農壓低嗓子道﹕後生家﹐這山裡頭的怪事﹐可不少哩 ...\n",
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
		return notify_fail("你想問這位老農甚麼﹖（試試 ask farmer about 兆隱）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老農正眯眼出神地望著遠山﹐沒空理你。\n");

	// 兆隱縣：本地風土閒談，純氣氛
	if( arg == "farmer about 兆隱"
	||  arg == "old farmer about 兆隱"
	||  arg == "farmer about 兆隱縣"
	||  arg == "farmer about 縣城"
	||  arg == "farmer about zhaoyin"
	||  arg == "farmer about county" ) {
		do_chat(({
			(: command, "say 兆隱縣啊﹐打老輩子起便縮在這群山裡頭﹐外人輕易尋不著﹐官道也不打這兒過﹐倒落得個清靜。" :),
			(: command, "say 咱這兒民風純樸﹐山環水抱﹐一年到頭沒幾樁官司。後生家若是躲是非、避風頭﹐這兆隱縣可是再合適不過的去處囉。" :),
		}));
		return 1;
	}

	// 渾沌獸：地方傳說 / 伏筆 -- 那異獸偶爾竄到這僻遠山縣，純氣氛，開不了任何東西
	if( arg == "farmer about 渾沌獸"
	||  arg == "old farmer about 渾沌獸"
	||  arg == "farmer about 渾沌"
	||  arg == "farmer about 怪獸"
	||  arg == "farmer about 異獸"
	||  arg == "farmer about chaos beast"
	||  arg == "farmer about beast" ) {
		do_chat(({
			(: command, "say 渾沌獸﹖噓——後生家莫要聲張。那是樁邪門的事體。前些日子﹐有進山的獵戶撞見一頭從沒見過的大物﹐黑霧裹身﹐沒眉沒眼﹐見人也不傷﹐只一陣風似的竄沒了。" :),
			(: command, "say 老輩人說﹐那便是天地間一頭通了靈的渾沌異獸﹐四處流竄﹐躲著甚麼似的﹐時不時便竄到咱這僻遠山縣來藏身。它來無影去無蹤﹐你尋它不著﹐它卻興許正在哪片林子裡瞧著你哩。" :),
			(: command, "say 唉﹐這等山精野怪的勾當﹐咱莊稼人是說不出個所以然的。後生家聽個新鮮也就罷了﹐莫要當真去尋﹐仔細沖撞了不乾淨的東西。" :),
		}));
		return 1;
	}

	// 老王燒烤：給個本地指路的閒談
	if( arg == "farmer about 老王"
	||  arg == "farmer about 燒烤"
	||  arg == "farmer about 烤肉"
	||  arg == "farmer about laowang" ) {
		do_chat(({
			(: command, "say 哈哈﹐後生家也聞著那股香了﹖那是縣前街西頭老王的燒烤攤子﹐他那烤肉的手藝﹐方圓百里都掛了號的。" :),
			(: command, "say 趁熱去嚐上幾串罷﹐就著一壺村釀的濁酒﹐神仙也不換哩﹗" :),
		}));
		return 1;
	}

	return notify_fail("老農聽不大明白你問的﹐只憨憨地衝你笑。（試試 ask farmer about 兆隱）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗後生家這是做甚﹖老漢一把年紀的莊稼人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
