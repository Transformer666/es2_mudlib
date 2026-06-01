// child.c -- 婁縣街心嬉戲的頑童（純氣氛閒談﹐不接任務、不動旗標）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("頑童", ({ "child", "village child", "wantong" }) );
	set("nickname", "頑童");
	set_race("human");
	set_class("commoner");
	set_level(1);

	set("age", 9);
	set("gender", "male");
	set("long",
		"一個七八歲的本縣頑童﹐光著一雙泥腳丫﹐穿件打了補丁卻\n"
		"漿洗得乾淨的小褂﹐沿著街心那道淺淺的水渠跑來跑去﹐折了紙\n"
		"船放在渠裡﹐看它一路漂遠了﹐又笑著追上去。他生得虎頭虎\n"
		"腦﹐一雙眼睛亮晶晶的﹐見了生客﹐便睜大眼好奇地打量。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"頑童折了一隻紙船放進街心的水渠﹐拍著手看它順流漂遠了去。\n",
		"頑童光著腳丫在水渠邊蹦來跳去﹐口中咿咿呀呀地唱著不成調的童謠。\n",
		"頑童睜著一雙亮晶晶的大眼好奇地打量你﹐忽地又咧嘴一笑﹐跑開了。\n",
	}));
	setup();
	carry_money("coin", 2);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這頑童甚麼﹖（試試 ask child about 甘泉）\n");

	if( arg == "child about 甘泉"
	||  arg == "child about 井"
	||  arg == "child about 婁縣"
	||  arg == "child about 水渠"
	||  arg == "child about spring" ) {
		do_chat(({
			(: command, "say 大叔你是外鄉來的吧﹖往北跑就是甘泉井啦﹗那水可甜可甜了﹐俺娘天天去那兒打水洗衣裳。" :),
			(: command, "say 守井的老爺爺最兇啦﹐俺往井裡丟石子﹐他就瞪俺﹗嘻嘻——大叔你要去甘泉園嗎﹖那兒有好多茶樹﹐還有一座小石橋哩﹗" :),
		}));
		return 1;
	}

	return notify_fail("頑童咧嘴一笑﹐光著腳丫蹦開了﹐只顧追他渠裡的紙船去。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哇——大人欺負小孩子啦﹗俺要去告訴俺娘﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
