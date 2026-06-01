// idler.c -- 縣前街牆根曬太陽的閒漢（純氣氛閒談）

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("閒漢", ({ "idler", "loafer", "xianhan" }) );
	set("nickname", "閒漢");
	set_race("human");
	set_class("commoner");
	set_level(2);

	set("age", 35);
	set("gender", "male");
	set("long",
		"一個遊手好閒的本地閒漢﹐裹著件鬆垮的舊棉袍﹐蹲在牆根\n"
		"下曬著太陽﹐叼著一桿旱煙袋﹐瞇眼瞧著街上往來的行人。他成\n"
		"日無所事事﹐東家長西家短的閒話倒是知道得最多。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"閒漢吧嗒著旱煙袋﹐瞇眼望著街上的行人﹐悠悠地吐出一口煙。\n",
		"閒漢懶洋洋地伸了個懶腰﹐換了個舒坦的姿勢繼續曬太陽。\n",
		"閒漢壓低嗓子道﹕後生家﹐這縣城裡頭的閒話﹐可沒有我老張不曉得的。\n",
	}));
	setup();
	carry_money("coin", 10);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想跟這閒漢打聽甚麼﹖（試試 ask idler about 斐縣）\n");

	if( arg == "idler about 斐縣"
	||  arg == "idler about 縣城"
	||  arg == "idler about 縣前街"
	||  arg == "idler about feixian"
	||  arg == "idler about town" ) {
		do_chat(({
			(: command, "say 斐縣啊﹐就這麼巴掌大的地方﹐一條縣前街從頭望得到尾。可別小瞧了它﹐打喬陰進山﹐這兒是必經的歇腳處﹐過往的客商都得在這兒打個尖。" :),
			(: command, "say 街東是雜貨鋪﹐街西那座土地祠香火可旺了﹐街南頭就是縣衙。閒著沒事﹐上錢記酒樓聽人擺龍門陣﹐最是消遣。" :),
		}));
		return 1;
	}

	return notify_fail("閒漢吐了個煙圈﹐懶懶地道﹕後生家問這做甚﹖閒著也是閒著﹐坐下嘮嘮罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎哎哎﹗有話好說﹗光天化日的﹐縣衙就在街那頭哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
