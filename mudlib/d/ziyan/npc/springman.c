// springman.c -- 紫煙溫泉司爐看泉的燒湯老叟（純氣氛閒談）；
//                 兼紫煙鎮非戰鬥支線「安神香湯」的指路與授器人。
//
// 本檔原為溫泉畔司爐的氣氛 NPC。為支線「安神香湯」加掛一段對白：
//   玩家須已自紫煙小棧掌櫃接了任務（quest/ziyan_incense==1），方
//   ask springman about 香湯 -> 老叟道出紫煙溫泉水和香的好處﹐當場汲一罐最新鮮的
//   溫泉水、連陶罐一併交與玩家﹐記 quest/ziyan_incense_crock = 1。指引玩家持溫泉陶罐
//   到沉香小亭尋焙香師和香。
// 不動其原有的閒談 chat_msg 與 accept_fight。
//
// 信物採直接 new + move(who) 同步交付——對白由玩家 ask 觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記
// 旗標﹐不把交付放進延遲的 do_chat 回呼（與 d/shuiyue herbman 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("燒湯老叟", ({ "springman", "spring keeper", "shaotanglaosou" }) );
	set("nickname", "燒湯老叟");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 64);
	set("gender", "male");
	set("long",
		"一位在紫煙溫泉司爐看泉的老叟﹐生得清癯硬朗﹐裹著件被\n"
		"湯氣熏得發白的短褐﹐成日守在泉畔的湯灶邊﹐替泡湯的客人添\n"
		"柴看溫﹐也替鎮上煮茶焙香的人家汲取最新鮮的溫泉。他在這紫\n"
		"煙溫泉司了幾十年的爐﹐這一眼湯泉的脾性、水溫的火候﹐沒有\n"
		"他不熟的。得閒也可問問他﹕ask springman about 香湯。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"燒湯老叟俯身往湯灶裡添了根柴﹐又拿長柄木瓢探了探池裡的水溫﹐微微頷首。\n",
		"燒湯老叟瞇眼望著裊裊的湯氣﹐緩緩道﹕這紫煙泉的水養人﹐泡了舒筋﹐煮茶焙香也都離不得它哩。\n",
		"燒湯老叟舀起一瓢溫泉﹐看那水在瓢裡泛著淡淡的紫煙﹐呵呵一笑﹕這一眼活泉﹐是咱紫煙鎮的命根子喲。\n",
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
		return notify_fail("你想問這燒湯老叟甚麼﹖（試試 ask springman about 香湯）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("燒湯老叟正俯身往湯灶裡添柴看溫﹐一時沒理會你。\n");

	// 香湯 / 溫泉：支線「安神香湯」——指路、授溫泉陶罐
	if( arg == "springman about 香湯"
	||  arg == "springman about 溫泉"
	||  arg == "springman about 泉"
	||  arg == "springman about 湯"
	||  arg == "springman about 陶罐"
	||  arg == "springman about incense"
	||  arg == "springman about soup"
	||  arg == "springman about spring" ) {
		object me = this_player();
		int q = me->query("quest/ziyan_incense");

		// 已完成：純氣氛收尾
		if( q >= 2 ) {
			do_chat((: command,
				"say 那罐香湯和成了﹖那敢情好﹗難為客官替小棧跑這一趟。咱這紫煙泉的水﹐和上鎮裡的沉香﹐安神得很哩。" :));
			return 1;
		}

		// 進行中（已自掌櫃接任務）：道出泉水好處、汲水授罐、記旗標
		if( q == 1 ) {
			// 已交付過（溫泉陶罐失落／誤毀）：補汲一罐﹐進度旗標不重置﹐免卡關
			if( me->query("quest/ziyan_incense_crock") ) {
				if( !present("spring crock", me) && !present("incense crock", me) ) {
					object c = new(__DIR__"obj/spring_crock");
					if( !c->move(me) ) c->move(environment());
					do_chat((: command,
						"say 咦﹐先前與客官的那罐溫泉水呢﹖莫不是失落了﹖罷罷罷﹐老朽這就再與客官汲一罐——快拿去沉香小亭尋焙香師和香罷。" :));
				} else {
					do_chat((: command,
						"say 那罐溫泉水不是早與客官了麼﹖快持去鎮心西北石階上的沉香小亭﹐尋那位焙香師﹐請他調進沉香末和成香湯（ask incenseman about 香湯﹐或 give spring crock to incenseman），莫教小棧的掌櫃久等。" :));
				}
				return 1;
			}

			// 首次交付：先同步汲水交罐、後記旗標（玩家此刻必在場）
			{
				object c = new(__DIR__"obj/spring_crock");
				if( !c->move(me) ) c->move(environment());
			}
			me->set("quest/ziyan_incense_crock", 1);
			message_vision(
				"燒湯老叟取過一隻乾淨的紫泥陶罐﹐俯身在泉眼最盛處舀了滿滿\n"
				"一罐溫泉水﹐拿一片荷葉虛掩了罐口﹐遞到$N手裡。\n", me);
			do_chat(({
				(: command, "say 紫煙小棧的掌櫃打發客官來和安神香湯﹖嗯﹐這事老朽再熟不過了。要和那香湯﹐頭一樁便是這紫煙泉的水——咱這泉水含著地底的礦氣﹐溫潤回甘﹐拿來和香、泡浴最是安神﹐尋常井水可比不得。" :),
				(: command, "say 喏﹐這罐水﹐是老朽在泉眼最盛處新汲的﹐最是鮮活﹐連盛湯的陶罐一併與客官使罷。客官拿著它﹐到鎮心西北石階上的沉香小亭去﹐尋那位焙香師——他焙的沉香是鎮上一絕﹐請他拿這溫泉水調進沉香末﹐和成一罐安神香湯（ask incenseman about 香湯﹐或 give spring crock to incenseman）﹐再持回小棧交與掌櫃便是。" :),
			}));
			return 1;
		}

		// 未接任務：純風味帶過，不推進（香湯的事先去問客棧掌櫃）
		do_chat((: command,
			"say 香湯﹖客官說的是拿這紫煙泉的水和的安神香湯罷﹖那是咱鎮上待客的好東西。客官若為這香湯的事﹐還是先去紫煙小棧問問掌櫃罷。" :));
		return 1;
	}

	// 純氣氛閒談：溫泉／司爐
	if( arg == "springman about 紫煙"
	||  arg == "springman about 鎮"
	||  arg == "springman about 湯灶"
	||  arg == "springman about ziyan" ) {
		do_chat(({
			(: command, "say 這紫煙溫泉啊﹐是咱鎮上世代倚著過活的一眼活泉﹐湯氣裊裊﹐晨昏一映便泛出淡淡的紫煙﹐紫煙鎮的名號就是從這兒來的。" :),
			(: command, "say 老朽在這湯灶邊司了幾十年的爐﹐替泡湯的客人看溫添柴﹐替煮茶焙香的人家汲水﹐落得個自在。客官也下池泡泡﹐保管把一身的乏都泡開了。" :),
		}));
		return 1;
	}

	return notify_fail("燒湯老叟瞇眼一笑﹕客官問這個做甚﹖這溫泉舒坦﹐下池泡泡罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖老朽一個司爐看泉的山野之人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
