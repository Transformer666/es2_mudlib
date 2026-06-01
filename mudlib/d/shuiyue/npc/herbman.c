// herbman.c -- 水月瀑布崖下採藥的老叟（純氣氛閒談）；
//              兼水月村非戰鬥支線「福安客棧的清泉」的指路與授器人。
//
// 本檔原為瀑下採藥的氣氛 NPC。為支線「福安客棧的清泉」加掛一段對白：
//   玩家須已自福安客棧掌櫃接了任務（quest/shuiyue_spring==1），方
//   ask herbman about 清泉 -> 老叟道出泉眼教秋汛亂石壅塞的底細﹐當場把自己隨身
//   盛水的「空竹筒」交與玩家﹐記 quest/shuiyue_spring_jug = 1。指引玩家持空竹筒
//   到浣月潭尋釣叟﹐到疏通好的泉眼盛泉。
// 不動其原有的閒談 chat_msg 與 accept_fight。
//
// 信物採直接 new + move(who) 同步交付——對白由玩家 ask 觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記
// 旗標﹐不把交付放進延遲的 do_chat 回呼（與 d/luocheng barkeep 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("採藥老叟", ({ "herbman", "herb gatherer", "laosou" }) );
	set("nickname", "採藥老叟");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 67);
	set("gender", "male");
	set("long",
		"一位在瀑下採藥的老叟﹐生得清癯硬朗﹐背著一隻磨得發亮\n"
		"的竹簍﹐腰間別著把小藥鋤﹐赤腳穩穩地立在濕滑的石罅間採著\n"
		"喜陰的草藥。他在這水月瀑布下採了幾十年的藥﹐這一脈活水、\n"
		"瀑後的泉眼﹐沒有他不熟的。得閒也可問問他﹕ask herbman about 清泉。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"採藥老叟俯身在石縫間﹐小心地剜起一叢喜陰的草藥﹐抖落根上的泥﹐收進竹簍。\n",
		"採藥老叟瞇眼望著飛瀑﹐緩緩道﹕這瀑下的水氣養人﹐石頭上的好藥﹐都是這水霧滋出來的。\n",
		"採藥老叟搖頭嘆道﹕自打秋汛沖下那堆亂石﹐泉眼滲得細了﹐連帶這崖下的藥草都蔫了幾分哩。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這採藥老叟甚麼﹖（試試 ask herbman about 清泉）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("採藥老叟正俯身剜著石縫裡的藥草﹐一時沒理會你。\n");

	// 清泉 / 泉眼：支線「福安客棧的清泉」——指路、授空竹筒
	if( arg == "herbman about 清泉"
	||  arg == "herbman about 泉"
	||  arg == "herbman about 泉眼"
	||  arg == "herbman about 活水"
	||  arg == "herbman about 竹筒"
	||  arg == "herbman about spring"
	||  arg == "herbman about water" ) {
		object me = this_player();
		int q = me->query("quest/shuiyue_spring");

		// 已完成：純氣氛收尾
		if( q >= 2 ) {
			do_chat((: command,
				"say 那眼泉疏通了﹖那敢情好﹗難為客官替村裡跑這一趟。泉眼一通﹐這崖下的藥草也該回過神來了。" :));
			return 1;
		}

		// 進行中（已自掌櫃接任務）：道出泉眼底細、交付空竹筒、記旗標
		if( q == 1 ) {
			// 已交付過（空竹筒失落／誤毀）：補發一節﹐進度旗標不重置﹐免卡關
			if( me->query("quest/shuiyue_spring_jug") ) {
				if( !present("bamboo jug", me) && !present("spring jug", me) ) {
					object j = new(__DIR__"obj/bamboo_jug");
					if( !j->move(me) ) j->move(environment());
					do_chat((: command,
						"say 咦﹐先前與客官的那節竹筒呢﹖莫不是失落了﹖罷罷罷﹐老朽這兒還有一節﹐再與客官一節——快拿去浣月潭尋釣叟盛泉罷。" :));
				} else {
					do_chat((: command,
						"say 那竹筒不是早與客官了麼﹖快持去東南的浣月潭﹐尋那位釣叟﹐到疏通好的泉眼盛一筒甜泉（ask angler about 清泉﹐或 give bamboo jug to angler），莫教客棧的掌櫃久等。" :));
				}
				return 1;
			}

			// 首次交付：先同步交物、後記旗標（玩家此刻必在場）
			{
				object j = new(__DIR__"obj/bamboo_jug");
				if( !j->move(me) ) j->move(environment());
			}
			me->set("quest/shuiyue_spring_jug", 1);
			do_chat(({
				(: command, "say 福安客棧的掌櫃打發客官來問清泉的源頭﹖嗯﹐這事老朽再清楚不過了。咱村裡引的活水﹐源頭就在這瀑後崖壁的一道泉眼﹐石縫裡沁出來的水﹐比尋常井水甜上十分。" :),
				(: command, "say 偏生前些日子那場秋汛﹐自崖頂沖下一堆亂石﹐把那道泉眼壅住了大半﹐水滲得細了﹐村裡缸裡井裡的水﹐這才慢慢變了苦澀。老朽前兒個下力氣把那堆亂石撥開疏通了﹐如今泉眼又汩汩地出水了﹐只是位置隱蔽﹐尋常人摸不著。" :),
				(: command, "say 喏﹐這節空竹筒﹐是老朽隨身盛水的家什﹐就與客官使罷。客官拿著它﹐到東南柳堤下的浣月潭去﹐尋那位常在潭邊垂釣的釣叟——他最曉得泉眼的去處﹐讓他替客官盛一筒甜泉（ask angler about 清泉﹐或 give bamboo jug to angler）﹐再持回客棧交與掌櫃便是。" :),
			}));
			return 1;
		}

		// 未接任務：純風味帶過，不推進（清泉的事先去問客棧掌櫃）
		do_chat((: command,
			"say 清泉﹖客官說的是這瀑後泉眼的活水罷﹖唉﹐那泉眼前陣子教亂石壅了﹐老朽雖把石頭撥開了﹐這水的事﹐還得問村裡管事的——客官若有心﹐先去福安客棧問問掌櫃罷。" :));
		return 1;
	}

	// 純氣氛閒談：瀑布／採藥
	if( arg == "herbman about 瀑布"
	||  arg == "herbman about 水月"
	||  arg == "herbman about 藥"
	||  arg == "herbman about falls" ) {
		do_chat(({
			(: command, "say 這水月瀑布啊﹐是江湖上掛了名的好景緻﹐月夜裡飛瀑映月﹐水裡天上各是一輪明月﹐老朽看了幾十年﹐還是看不厭。" :),
			(: command, "say 瀑下水霧終年不散﹐石頭上盡是喜陰的好藥﹐老朽就指著採這些藥﹐換幾個鹽米錢﹐落得個自在。" :),
		}));
		return 1;
	}

	return notify_fail("採藥老叟瞇眼一笑﹕客官問這個做甚﹖這瀑下風光好﹐多看兩眼罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖老朽一個採藥的山野之人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
