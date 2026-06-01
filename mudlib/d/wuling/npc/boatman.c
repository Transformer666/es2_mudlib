// boatman.c -- 水嵐渡口的船夫（純氣氛閒談﹐含一段對冷梅莊的引子﹐
//              純對白指引﹐不接任務、不設任何旗標、不與冷梅莊掛鉤）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("船夫", ({ "boatman", "ferryman", "chuanfu" }) );
	set("nickname", "船夫");
	set_race("human");
	set_class("commoner");
	set_level(4);

	set("age", 56);
	set("gender", "male");
	set("long",
		"渡口的老船夫赤著一雙古銅色的腳﹐褲管捲到膝上﹐戴一頂\n"
		"半舊的箬笠﹐臉上的皺紋裡盛著一輩子的風霜與水氣。他在這水\n"
		"嵐溪上撐了半生的渡船﹐溪裡哪一處深、哪一處淺﹐閉著眼也摸\n"
		"得清。閒來無客可渡﹐便蹲在埠頭抽著旱煙﹐望著對岸的桃林出\n"
		"神。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"船夫蹲在埠頭抽著旱煙﹐瞇眼望著對岸的桃林﹐悠悠地吐出一口煙。\n",
		"船夫慢條斯理地把纜繩在木樁上繞了兩圈﹐又坐回船頭。\n",
		"船夫望著溪水道﹕這水嵐溪的水﹐打山裡冷梅莊那頭流下來﹐清冽得很哪。\n",
	}));
	setup();
	carry_money("coin", 20);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想跟這船夫打聽甚麼﹖（試試 ask boatman about 冷梅莊）\n");

	if( arg == "boatman about 渡口"
	||  arg == "boatman about 水嵐"
	||  arg == "boatman about 溪"
	||  arg == "boatman about 武陵"
	||  arg == "boatman about ferry" ) {
		do_chat(({
			(: command, "say 客官要渡溪﹖這水嵐溪看著平緩﹐底下卻有暗流﹐沒個熟手撐船﹐可過不得。老漢在這溪上撐了快四十年的船嘍。" :),
			(: command, "say 過了溪﹐西邊有道溪橋通著鎮子﹐北邊一條石徑往山裡去。客官隨意﹐老漢這船﹐什麼時候招呼都成。" :),
		}));
		return 1;
	}

	// 對冷梅莊的引子：純氣氛指引﹐不觸動任何任務旗標、不與該門派檔案掛鉤
	if( arg == "boatman about 冷梅莊"
	||  arg == "boatman about 冷梅"
	||  arg == "boatman about 梅影風"
	||  arg == "boatman about hanmei" ) {
		do_chat(({
			(: command, "say 客官也曉得冷梅莊﹖那是江湖上一等一的大幫﹐就在這溪北的山裡頭。莊主梅影風是位了不得的人物﹐使一手冷梅劍法﹐冷得人骨頭裡都打顫。" :),
			(: command, "say 難得的是﹐這偌大一個冷梅莊﹐在江湖上竟是從不與人結仇的。莊裡的弟子來來去去﹐老漢這渡船載過不知多少回了。客官若有心拜在門下﹐順著北邊石徑上山去尋便是﹐莊門就在那山坳裡頭。" :),
			(: command, "say 只是那山高路遠﹐莊規又嚴﹐老漢一個撐船的﹐也只能送客官到溪這頭。往後的路﹐還得客官自個兒走嘍。" :),
		}));
		return 1;
	}

	return notify_fail("船夫吧嗒著旱煙﹐衝你憨憨一笑﹕客官要渡溪﹐只管招呼。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎﹗使不得使不得﹗老漢一把年紀﹐撐船的手藝﹐可經不起客官這般折騰哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
