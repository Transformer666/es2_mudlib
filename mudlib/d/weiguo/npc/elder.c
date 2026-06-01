// elder.c -- 衛國市集的老村正（純氣氛閒談 + 本地掌故﹐不接任務、不動旗標）。
//            對鎮關炒米茶一事略知一二﹐口風裡替衛國客棧的炒米茶支線做個指路鋪墊﹐
//            但本身不接任務、不交物、不記任何旗標。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老村正", ({ "elder", "village head", "cunzheng" }) );
	set("nickname", "老村正");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 66);
	set("gender", "male");
	set("long",
		"衛國鎮的老村正﹐生得清癯矍鑠﹐一把花白的長鬚﹐拄著一\n"
		"根油亮的棗木杖﹐在市集的旗桿邊踱步閒看。他在這邊縣小鎮住\n"
		"了一輩子﹐鎮裡鎮外的掌故人情、這座老關隘的來龍去脈﹐沒有\n"
		"他不曉得的。見了生客﹐他總愛和氣地指點兩句。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"老村正拄著棗木杖﹐繞著場心的舊旗桿緩緩踱步﹐不時抬頭望望桿頭的彩布幌子。\n",
		"老村正捋著花白的長鬚道﹕咱這衛國鎮﹐早年是戍邊的軍屯關隘﹐如今刀兵入庫﹐倒落得個太平安生哩。\n",
		"老村正瞇眼望著北面的老官道﹐悠悠地道﹕這道上﹐當年送過多少出關的兵﹐如今送的都是趕集的鄉民嘍。\n",
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
		return notify_fail("你想向老村正打聽甚麼﹖（試試 ask elder about 衛國鎮，或 ask elder about 炒米茶）\n");

	if( arg == "elder about 衛國鎮"
	||  arg == "elder about 鎮"
	||  arg == "elder about 衛國"
	||  arg == "elder about 關"
	||  arg == "elder about weiguo" ) {
		do_chat(({
			(: command, "say 後生家﹐咱這衛國鎮偏是偏了些﹐來歷卻不小。早年這兒是戍邊的軍屯關隘﹐鎮牆、關門、校場、軍井﹐都是那時候立下的。後來邊事平了﹐屯軍撤了﹐軍戶就地落籍﹐纔成了如今這座趕集過活的市鎮。" :),
			(: command, "say 你瞧這市集﹐原是屯軍的校場﹔鎮口那眼老古井﹐是屯軍掘的軍井﹔連客棧﹐早年都是接待軍使糧官的驛站。處處都是老關隘的影子哩。" :),
		}));
		return 1;
	}

	// 炒米茶：純做指路鋪墊（指往衛國客棧的掌櫃），本身不接任務、不記旗標
	if( arg == "elder about 炒米茶"
	||  arg == "elder about 茶"
	||  arg == "elder about 炒米"
	||  arg == "elder about 鎮關茶"
	||  arg == "elder about tea" ) {
		do_chat(({
			(: command, "say 哦﹖後生家也曉得咱衛國的鎮關炒米茶﹖那可是咱這邊地送遠待客的老鄉味——拿鎮口古井的甜水﹐沖炒米坊現焙的炒米和成﹐焦香頂飢、回甘解乏﹐當年屯軍出關喝的就是這一口。" :),
			(: command, "say 說起這個﹐衛國客棧的掌櫃近來正為這事上心呢——聽說有位早年戍邊的老鏢頭舊識要打這兒過﹐他想備一罐像樣的炒米茶替人餞行﹐偏又抽不開身。後生家若有心﹐不妨去客棧問問他（ask keeper about 炒米茶﹐就在市集東邊）﹐興許幫得上忙。" :),
		}));
		return 1;
	}

	return notify_fail("老村正捋鬚一笑﹕後生家問的這個﹐老朽一時也說不上來。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗後生家好生無禮﹗欺負我這把老骨頭做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
