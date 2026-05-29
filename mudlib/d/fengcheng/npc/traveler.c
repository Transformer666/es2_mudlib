// traveler.c

#include <npc.h>

inherit F_VILLAGER;

void create()
{
	set_name("行腳商旅", ({ "traveler", "merchant", "shanglu" }) );
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 45);
	set("gender", "male");
	set("long",
		"一個風塵僕僕的行腳商旅﹐身披一件落滿風沙的氈袍﹐腳邊\n"
		"堆著幾只馱貨的皮囊。他走南闖北﹐見多識廣﹐一雙眼睛精明\n"
		"得很﹐想是常年在這北地與塞外之間販貨營生。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"行腳商旅撥弄著腳邊的皮囊﹐盤算著這一趟販貨的進項。\n",
		"行腳商旅歎道﹕從風城往南到京畿那一路﹐莽莽原野渺無人煙﹐獨個兒趕路最是兇險。\n",
		"行腳商旅壓低聲音道﹕塞外的皮貨藥材在南邊能翻上幾倍的價﹐只是這趟關隘的稅卡又緊了。\n",
		"行腳商旅說道﹕兄台若要往南﹐不妨在春風客棧歇上一宿﹐尋幾個結伴的同行﹐路上也有個照應。\n",
	}));
	setup();
	carry_money("coin", 200);
}

int accept_fight(object ob)
{
	do_chat("行腳商旅護住身邊的皮囊﹐連聲道﹕好漢饒命﹗小本生意﹐沒幾個錢哪﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
