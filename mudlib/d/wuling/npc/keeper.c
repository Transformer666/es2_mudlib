// keeper.c -- 五陵客棧的掌櫃（純氣氛閒談 + 指路﹐不接任務、不動旗標）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("掌櫃", ({ "keeper", "innkeeper", "wuling_keeper" }) );
	set("nickname", "掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 50);
	set("gender", "male");
	set("long",
		"五陵客棧的掌櫃是個慈眉善目的老者﹐打理這爿臨溪的客棧\n"
		"已有大半輩子。他生性恬淡﹐待客不慌不忙﹐閒來便倚著櫃臺﹐\n"
		"瞧著窗外溪上往來的渡船出神。倦了的旅人﹐儘可在這清靜的客\n"
		"棧裡尋張床鋪歇歇腳﹔得閒也可問問他﹕ask keeper about 武陵。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃倚著櫃臺﹐瞧著窗外溪上的渡船﹐神色恬淡。\n",
		"掌櫃笑容可掬地招呼道﹕客官打尖還是住店﹖咱這臨溪的客房﹐夜裡聽著水聲﹐睡得最是安穩。\n",
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目﹐不慌不忙。\n",
	}));
	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( !is_fighting() )
		do_chat((: command,
			"say 客官裡邊請﹗咱五陵客棧臨溪而築﹐床鋪潔淨、茶飯齊整﹐包您住得稱心﹗" :));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這掌櫃甚麼﹖（試試 ask keeper about 武陵）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("掌櫃正撥著算盤核帳﹐一時沒空理你。\n");

	if( arg == "keeper about 武陵"
	||  arg == "keeper about 水嵐"
	||  arg == "keeper about 五陵"
	||  arg == "keeper about 客棧"
	||  arg == "keeper about wuling" ) {
		do_chat(({
			(: command, "say 客官遠來辛苦。咱這水嵐武陵啊﹐是個與世無爭的去處﹐一道水嵐溪把鎮子攬在懷裡﹐溪邊的桃林一開﹐滿鎮都是花香﹐住下了便不想走嘍。" :),
			(: command, "say 鎮子小﹐機巧也少﹕街心往西是小店﹐往東是醉月茶寮﹐渡口、桃林都在腳下。客官若要訪冷梅莊﹐打渡口過溪﹐順北邊石徑上去便是了。" :),
		}));
		return 1;
	}

	return notify_fail("掌櫃陪笑道﹕客官若是打尖住店﹐只管吩咐﹔旁的小老兒可幫不上甚麼忙。（試試 ask keeper about 武陵）\n");
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位客官說笑了﹐小老兒一介開店的﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
