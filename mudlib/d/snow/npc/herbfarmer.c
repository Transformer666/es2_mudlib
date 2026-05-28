// herbfarmer.c -- 老藥農，雪亭鎮新手任務 2 的取貨對象
//
// 任務流程（旗標存在玩家身上：quest/snow_newbie2，由 axing.c 開啟）：
//   進行中 (1)  : 玩家從藥鋪學徒阿杏處接下任務後﹐到郊野找老藥農
//                 ask laoyaonong about 草藥 -> 老藥農給「草藥」﹐旗標設為 2
//   已取貨 (2)  : 玩家把草藥帶回藥鋪交(give)給阿杏領賞
//
// 注意：本 NPC 不開啟任務（開啟在 axing.c），只負責推進旗標 1 -> 2。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老藥農", ({ "laoyaonong", "farmer", "herb farmer" }) );
	set_race("human");
	set_class("commoner");
	set_level(3);
	set_skill("unarmed", 5);
	set_skill("dodge", 5);

	set("gender", "male");
	set("age", 61);
	set("long",
		"一個年過花甲的老藥農﹐背著個半舊的藥簍﹐褲腳沾滿了泥巴﹐\n"
		"正彎著腰在草叢間翻找草藥。他常年替鎮上的順生堂採藥﹐這一\n"
		"帶哪裡長著甚麼藥草﹐他閉著眼睛都摸得著。\n"
		"你或許可以問問他﹕ask laoyaonong about 草藥。\n");
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/snow_newbie2");
		if( q == 1 )
			do_chat((: command,
				"say 這位小哥﹐是順生堂阿杏丫頭叫你來取草藥的罷﹖" :));
	}
}

// 把一捆草藥交到玩家手上（先複製到自己身上，再 give 出去）
private void give_herb(object who)
{
	object herb;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	herb = new(__DIR__"obj/herb_bundle");
	herb->move(this_object());
	command("give herb bundle to " + who->query("id"));
}

int do_ask(string arg)
{
	object me = this_player();
	int q, q1;

	if( !arg || (arg != "laoyaonong about 草藥"
		&&   arg != "farmer about 草藥"
		&&   arg != "laoyaonong about herb"
		&&   arg != "farmer about herb") )
		return notify_fail("你想問老藥農甚麼﹖（試試 ask laoyaonong about 草藥）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老藥農正忙著﹐沒空理你。\n");

	q  = me->query("quest/snow_newbie2");
	q1 = me->query("quest/snow_newbie");

	// 沒接過順生堂的任務
	if( q < 1 ) {
		if( q1 < 3 )
			do_chat((: command,
				"say 老朽採的藥是有主的﹐你先去鎮上幫張婆婆送點心罷。" :));
		else
			do_chat((: command,
				"say 你要採藥﹖去鎮上順生堂找阿杏丫頭問問﹐她正缺人手呢。" :));
		return 1;
	}

	// 已取過貨（旗標 2 或更後），不重複給草藥
	if( q >= 2 ) {
		if( present("herb bundle", me) )
			do_chat((: command,
				"say 草藥都給你了﹐快拿回順生堂交給阿杏丫頭罷。" :));
		else
			// 萬一玩家把草藥弄丟了，補一捆給他
			do_chat(({
				"老藥農從藥簍裡又抓了一把草藥﹐重新紮成一捆。\n",
				(: command, "say 怎麼弄丟了﹖罷了﹐老朽再給你採一捆。" :),
				(: give_herb, me :),
			}));
		return 1;
	}

	// 任務進行中（q == 1）：交付草藥，旗標推進為 2
	me->set("quest/snow_newbie2", 2);
	do_chat(({
		(: command, "say 阿杏要的草藥老朽都採齊了﹐你拿好。" :),
		(: command, "say 趕緊送(give)回順生堂去﹐這藥可不經放。" :),
		(: give_herb, me :),
	}));
	return 1;
}

int accept_fight()
{
	do_chat((: command, "say 老朽一把年紀了﹐你別跟我過不去啊﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
