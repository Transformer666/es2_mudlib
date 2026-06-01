// welltender.c -- 古井亭看井絞水的守井老叟（純氣氛閒談）；
//                 兼衛國鎮非戰鬥支線「鎮關炒米茶」的指路與授器人。
//
// 本檔原為古井亭看井的氣氛 NPC。為支線「鎮關炒米茶」加掛一段對白：
//   玩家須已自衛國客棧掌櫃接了任務（quest/weiguo_tea==1），方
//   ask welltender about 炒米茶 -> 老叟道出鎮口古井甜水的好處﹐當場絞一罐最甜冽的
//   井水、連瓦罐一併交與玩家﹐記 quest/weiguo_tea_crock = 1。指引玩家持井亭瓦罐
//   到炒米坊尋炒米師傅和茶。
//
// 信物採直接 new + move(who) 同步交付——對白由玩家 ask 觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記
// 旗標﹐不把交付放進延遲的 do_chat 回呼（與 d/ziyan springman、d/shuiyue herbman 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("守井老叟", ({ "welltender", "well keeper", "shoujinglaosou" }) );
	set("nickname", "守井老叟");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 65);
	set("gender", "male");
	set("long",
		"一位在古井亭看井絞水的老叟﹐生得清癯硬朗﹐裹著件漿洗\n"
		"得發白的短褐﹐成日守在井亭的轆轤邊﹐替挑水的鎮民絞水﹐也\n"
		"替煮茶燒飯的人家絞取最甜冽的井水。他在這古井亭看了幾十年\n"
		"的井﹐這眼老古井的脾性、水位的深淺﹐沒有他不熟的。得閒也\n"
		"可問問他﹕ask welltender about 炒米茶。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"守井老叟雙手把著轆轤緩緩絞下﹐又穩穩絞上一桶清水﹐倒進挑水鄉民的木桶裡。\n",
		"守井老叟瞇眼望著井口﹐緩緩道﹕這古井的水養人﹐吃了少病﹐煮茶燒飯也都離不得它哩。\n",
		"守井老叟舀起一瓢井水﹐看那水在瓢裡清冽見底﹐呵呵一笑﹕這眼老井﹐是咱衛國鎮的命根子喲。\n",
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
		return notify_fail("你想問這守井老叟甚麼﹖（試試 ask welltender about 炒米茶）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("守井老叟正把著轆轤替人絞水﹐一時沒理會你。\n");

	// 炒米茶 / 井水：支線「鎮關炒米茶」——指路、授井亭瓦罐
	if( arg == "welltender about 炒米茶"
	||  arg == "welltender about 古井"
	||  arg == "welltender about 井"
	||  arg == "welltender about 井水"
	||  arg == "welltender about 水"
	||  arg == "welltender about 瓦罐"
	||  arg == "welltender about tea"
	||  arg == "welltender about well" ) {
		object me = this_player();
		int q = me->query("quest/weiguo_tea");

		// 已完成：純氣氛收尾
		if( q >= 2 ) {
			do_chat((: command,
				"say 那罐炒米茶和成了﹖那敢情好﹗難為客官替客棧跑這一趟。咱這古井的水﹐沖上炒米坊的炒米﹐焦香回甘﹐是衛國送遠的老味道哩。" :));
			return 1;
		}

		// 進行中（已自掌櫃接任務）：道出井水好處、絞水授罐、記旗標
		if( q == 1 ) {
			// 已交付過（井亭瓦罐失落／誤毀）：補絞一罐﹐進度旗標不重置﹐免卡關
			if( me->query("quest/weiguo_tea_crock") ) {
				if( !present("well crock", me) && !present("tea crock", me) ) {
					object c = new(__DIR__"obj/well_crock");
					if( !c->move(me) ) c->move(environment());
					do_chat((: command,
						"say 咦﹐先前與客官的那罐井水呢﹖莫不是失落了﹖罷罷罷﹐老朽這就再與客官絞一罐——快拿去炒米坊尋炒米師傅和茶罷。" :));
				} else {
					do_chat((: command,
						"say 那罐井水不是早與客官了麼﹖快持去市集東北的炒米坊﹐尋那位炒米師傅﹐請他拿炒米沖成炒米茶（ask roaster about 炒米茶﹐或 give well crock to roaster），莫教客棧的掌櫃久等。" :));
				}
				return 1;
			}

			// 首次交付：先同步絞水交罐、後記旗標（玩家此刻必在場）
			{
				object c = new(__DIR__"obj/well_crock");
				if( !c->move(me) ) c->move(environment());
			}
			me->set("quest/weiguo_tea_crock", 1);
			message_vision(
				"守井老叟取過一隻乾淨的粗瓦罐﹐把著轆轤絞下﹐穩穩絞上一桶\n"
				"清冽的井水﹐盛了滿滿一罐﹐拿一片箬葉虛掩了罐口﹐遞到$N手裡。\n", me);
			do_chat(({
				(: command, "say 衛國客棧的掌櫃打發客官來和鎮關炒米茶﹖嗯﹐這事老朽再熟不過了。要和那炒米茶﹐頭一樁便是這眼老古井的甜水——咱這井是早年屯軍掘的﹐尋著了地底一脈活泉﹐水甜而冽﹐拿來沖茶最是回甘﹐尋常井水可比不得。" :),
				(: command, "say 喏﹐這罐水﹐是老朽剛絞上來的﹐最是甜冽﹐連盛水的瓦罐一併與客官使罷。客官拿著它﹐到市集東北的炒米坊去﹐尋那位炒米師傅——他焙的炒米是鎮上一絕﹐請他拿這井水沖了炒米﹐和成一罐鎮關炒米茶（ask roaster about 炒米茶﹐或 give well crock to roaster）﹐再持回客棧交與掌櫃便是。" :),
			}));
			return 1;
		}

		// 未接任務：純風味帶過，不推進（炒米茶的事先去問客棧掌櫃）
		do_chat((: command,
			"say 炒米茶﹖客官說的是拿這古井的水沖炒米和的鎮關炒米茶罷﹖那是咱鎮上送遠待客的好東西。客官若為這炒米茶的事﹐還是先去衛國客棧問問掌櫃罷。" :));
		return 1;
	}

	// 純氣氛閒談：古井／看井
	if( arg == "welltender about 衛國"
	||  arg == "welltender about 鎮"
	||  arg == "welltender about 轆轤"
	||  arg == "welltender about weiguo" ) {
		do_chat(({
			(: command, "say 這眼老古井啊﹐是早年戍邊的屯軍掘營時尋著的﹐一脈地底的活泉﹐百餘年不曾乾過﹐養著合鎮的人家。衛國這地方﹐城牆關門都舊了﹐倒是這口井﹐越老越甜。" :),
			(: command, "say 老朽在這轆轤邊絞了幾十年的水﹐替挑水的街坊絞﹐替煮茶焙米的人家絞﹐落得個自在。客官也嚐一瓢這井水﹐清冽回甘﹐保管把一路的乏都解了。" :),
		}));
		return 1;
	}

	return notify_fail("守井老叟瞇眼一笑﹕客官問這個做甚﹖這井水甜﹐舀一瓢嚐嚐罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖老朽一個看井絞水的山野之人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
