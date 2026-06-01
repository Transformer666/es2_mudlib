// elder.c -- 紫煙鎮心曬藥的老翁（純氣氛閒談 + 本地掌故﹐不接任務、不動旗標）。
//            對安神香湯一事略知一二﹐口風裡替紫煙小棧的散帳支線（香湯）做個指路
//            鋪墊﹐但本身不接任務、不交物、不記任何旗標。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("曬藥老翁", ({ "elder", "old man", "shaiyaolaweng" }) );
	set("nickname", "曬藥老翁");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 66);
	set("gender", "male");
	set("long",
		"紫煙鎮上一位曬藥的老翁﹐生得清癯矍鑠﹐一把花白的長\n"
		"鬚﹐成日坐在鎮心湯池邊的竹榻上﹐就著溫煦的湯氣翻曬一簸箕\n"
		"一簸箕的草藥香材。他在這溫泉鎮上住了一輩子﹐鎮裡鎮外的掌\n"
		"故人情、這一眼溫泉的來龍去脈﹐沒有他不曉得的。見了生客﹐\n"
		"他總愛和氣地指點兩句。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"曬藥老翁拈起簸箕裡的藥材抖了抖﹐就著湯池的暖氣翻晾﹐口中念念有詞地數著。\n",
		"曬藥老翁捋著花白的長鬚道﹕咱這紫煙鎮的草藥香材﹐借溫泉的湯氣慢慢焙曬﹐藥性香氣都養得格外足哩。\n",
		"曬藥老翁瞇眼望著裊裊的紫煙﹐悠悠道﹕住在這溫泉邊﹐筋骨鬆乏﹐人也長壽﹐老朽這把年紀﹐還能曬藥哩。\n",
	}));
	setup();
	carry_money("coin", 40);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想向曬藥老翁打聽甚麼﹖（試試 ask elder about 紫煙鎮，或 ask elder about 香湯）\n");

	if( arg == "elder about 紫煙鎮"
	||  arg == "elder about 鎮"
	||  arg == "elder about 紫煙"
	||  arg == "elder about 溫泉"
	||  arg == "elder about ziyan" ) {
		do_chat(({
			(: command, "say 後生家﹐咱這紫煙鎮僻是僻了些﹐景緻卻是極好的。鎮南那一眼紫煙溫泉﹐湯氣裊裊﹐晨昏一映泛出淡淡的紫煙﹐泡了舒筋活血﹐連江湖上的人都曉得它的名兒。" :),
			(: command, "say 鎮心南邊石階下去是溫泉﹐西北石階上去是焙香人歇腳的沉香小亭﹐都值得後生家去走走。咱鎮上慣用這溫泉的湯氣煮茶、焙香﹐香得很哪。" :),
		}));
		return 1;
	}

	// 香湯：純做指路鋪墊（指往紫煙小棧的掌櫃），本身不接任務、不記旗標
	if( arg == "elder about 香湯"
	||  arg == "elder about 沉香"
	||  arg == "elder about 香"
	||  arg == "elder about incense"
	||  arg == "elder about soup" ) {
		do_chat(({
			(: command, "say 安神香湯﹖那是咱紫煙鎮待客的一絕喲——拿紫煙溫泉新汲的活水﹐和上沉香小亭現焙的沉香末和成的﹐溫飲泡浴皆宜﹐最是安神解乏。" :),
			(: command, "say 這幾日紫煙小棧來了位睡不安穩的貴客﹐那掌櫃正張羅著要和一罐香湯款待他﹐偏又抽不開身呢。後生家若有心﹐不妨去小棧問問他（ask keeper about 香湯）﹐興許幫得上忙。" :),
		}));
		return 1;
	}

	return notify_fail("曬藥老翁捋鬚一笑﹕後生家問的這個﹐老朽一時也說不上來。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗後生家好生無禮﹗欺負我這把老骨頭做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
