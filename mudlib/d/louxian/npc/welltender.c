// welltender.c -- 甘泉井畔看顧井臺的守井老叟（純氣氛閒談）；
//                 兼婁縣非戰鬥支線「甘泉茶會」的注泉人。
//
// 本檔為井畔看井的氣氛 NPC（替鄉人看顧井臺、不教人糟蹋了這口好井）。為支線
// 「甘泉茶會」加掛注泉一段：
//   玩家自老圃討得封了雀舌的茶罐後﹐持茶罐 ask welltender about 甘泉（或
//   give tea caddy to welltender）-> 守井老叟接過茶罐﹐到井裡汲一注清冽的甘泉
//   活水注滿、封好罐口交還玩家﹐記 quest/louxian_filled = 1。
//   交付「甘泉茶罐」實物的同時銷除手中的「茶罐」。指引玩家持滿罐回甘泉客棧。
//   （driver give 指令不認中文「給」﹐故持茶罐 ask 即視同送件注泉：同步注泉、
//     交付滿罐、記旗標、並銷除空茶罐﹐與經 give 指令觸發 accept_object 等效。）
//
// 滿罐採直接 new + move(who) 同步交付——give／ask 皆由玩家觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記旗標
// （與 d/shuiyue angler 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void fill_caddy(object me);

void create()
{
	set_name("守井老叟", ({ "welltender", "well keeper", "shoujing" }) );
	set("nickname", "守井老叟");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 61);
	set("gender", "male");
	set("long",
		"一位看顧甘泉井的守井老叟﹐須髮斑白﹐精神卻矍鑠﹐成日\n"
		"價坐在井臺旁的青石上﹐看著鄉人汲水浣衣﹐不教頑童糟蹋了這\n"
		"口養活全縣的好井。他在這井畔坐了幾十年﹐這口甘泉的脾性、\n"
		"汲水的深淺﹐沒有他不曉得的。得閒也可問問他﹕ask welltender about 甘泉。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"守井老叟坐在井臺旁的青石上﹐瞇眼看著鄉人來來去去地汲水浣衣﹐神色安詳。\n",
		"守井老叟搖頭道﹕這口井養活了全縣多少代人哪﹗汲水歸汲水﹐可不興往裡頭丟石子糟蹋了。\n",
		"守井老叟俯身打了一瓢井水嚐了嚐﹐咂咂嘴道﹕嗯﹐還是這個甘甜回味﹐錯不了。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 注泉：守井老叟到井裡汲一注清冽的甘泉活水注滿茶罐﹐交付甘泉茶罐、記旗標﹐
// 同時銷除玩家手中的空茶罐。直接 new + move(me) 同步交付（玩家此刻必在場）﹐
// 先交滿罐、銷空罐、後記旗標。
private void fill_caddy(object me)
{
	object empty = present("tea caddy", me);
	object full = new(__DIR__"obj/spring_caddy");
	if( !full->move(me) ) full->move(environment());
	if( empty ) destruct(empty);
	me->set("quest/louxian_filled", 1);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這守井老叟甚麼﹖（試試 ask welltender about 甘泉）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("守井老叟正瞇眼看著井臺﹐一時沒理會你。\n");

	// 甘泉 / 井 / 茶罐：支線「甘泉茶會」——持茶罐來注泉
	if( arg == "welltender about 甘泉"
	||  arg == "welltender about 泉"
	||  arg == "welltender about 井"
	||  arg == "welltender about 水"
	||  arg == "welltender about 茶罐"
	||  arg == "welltender about spring"
	||  arg == "welltender about well"
	||  arg == "welltender about water" ) {
		object me = this_player();
		int q = me->query("quest/louxian_spring");

		// 已完成或已注得甘泉：純氣氛收尾
		if( q >= 2 || me->query("quest/louxian_filled") ) {
			do_chat((: command,
				"say 那罐甘泉﹐老朽已替客官注滿了。客官快持回甘泉客棧交與掌櫃罷（ask keeper about 甘泉﹐或 give spring caddy to keeper），莫教那好茶好水擱壞了味。" :));
			return 1;
		}

		// 進行中、持茶罐：ask 即當作注泉處理——注泉、交滿罐、銷空罐、記旗標
		// （此路不經 give 指令﹐故由 fill_caddy 自行銷除玩家手裡的空茶罐﹐
		//   與 accept_object 經 give 指令回 1 後自動銷除空茶罐等效﹐免玩家
		//   留著空罐重複觸發。）
		if( q == 1 && present("tea caddy", me) ) {
			message_vision(
				"守井老叟接過$N手裡的茶罐﹐俯身打井裡汲起滿滿一瓢清冽的\n"
				"甘泉﹐傾進罐裡注得滿滿﹐又拿油紙仔細封了罐口。\n", me);
			// 先同步注泉、交付滿罐、銷空罐、記旗標﹐再以 do_chat 收尾（滿罐已先到玩家手裡）。
			fill_caddy(me);
			do_chat(({
				(: command, "say 客官是甘泉客棧掌櫃打發來注甘泉的罷﹖這罐雀舌嫩茶﹐老朽一聞便知是甘泉園老圃的手筆。" :),
				(: command, "say 老朽替客官打了滿滿一注井裡剛汲的甜水注進去﹐拿油紙封了罐口﹐免得潑灑走了味。這井水入口回甘﹐配上園裡的雀舌﹐烹出來的茶湯﹐那才叫一個清甘。" :),
				(: command, "say 喏﹐這隻茶水俱備的甘泉茶罐﹐方纔已奉到客官手裡了﹐快持回甘泉客棧交與掌櫃（ask keeper about 甘泉﹐或 give spring caddy to keeper）﹐也好教他早早烹一席好茶待客。" :),
			}));
			return 1;
		}

		// 進行中、未持茶罐：提示先去甘泉園向老圃討茶罐
		if( q == 1 ) {
			do_chat((: command,
				"say 客官要注甘泉﹖總得有個盛水的罐子罷。客官且去街心北邊的甘泉園﹐尋那位老圃討一隻封了雀舌的茶罐來（ask gardener about 甘泉）﹐老朽纔好替客官注水。" :));
			return 1;
		}

		// 未接任務：純風味帶過
		do_chat((: command,
			"say 甘泉﹖客官說的是這井裡的活水罷。這是咱全縣吃用的好水﹐客官若為這水的事﹐還是先去甘泉客棧問問掌櫃罷。" :));
		return 1;
	}

	// 純氣氛閒談：甘泉井
	if( arg == "welltender about 甘泉井"
	||  arg == "welltender about 井臺"
	||  arg == "welltender about 古碑"
	||  arg == "welltender about stone" ) {
		do_chat(({
			(: command, "say 這口甘泉井啊﹐自前朝便已著名﹐縣以泉名﹐連那南關門洞旁、井臺這兒立著的兩座『甘泉』古碑﹐都是記著這井的來歷的。" :),
			(: command, "say 井水清冽回甘﹐合縣人家、茶館客棧吃用的活水﹐全仗這一眼泉。老朽看顧這口井幾十年﹐別的不圖﹐只盼這甜水﹐能一輩一輩地養下去。" :),
		}));
		return 1;
	}

	return notify_fail("守井老叟瞇眼一笑﹕客官問這個做甚﹖渴了便打一瓢井水嚐嚐﹐甜著呢。\n");
}

// 收下信物：
//   茶罐(tea caddy) -- 支線「甘泉茶會」注泉﹐持茶罐且任務進行中時
//   收下、注泉、交付甘泉茶罐、記旗標 louxian_filled。
// 不在此 move／destruct 茶罐——give 指令於本函回 1 後會自行 destruct 有值的
// 茶罐（與 d/shuiyue angler 一致）﹔非送件玩家／時機不符則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("tea caddy") ) {
		int q = who->query("quest/louxian_spring");

		// 未接任務／已完成：婉拒，不收下（避免吞掉茶罐）
		if( q != 1 ) {
			do_chat((: command,
				"say 這茶罐 ... 客官還是自個兒收著罷，老朽一時也用不上。" :));
			return 0;
		}

		// 已注過泉（滿罐已交）：婉拒，提示徑去回報客棧
		if( who->query("quest/louxian_filled") ) {
			do_chat((: command,
				"say 客官的甘泉方纔已注滿了﹐這空罐就煩客官留著罷。快持那罐好茶好水回甘泉客棧交與掌櫃便是（ask keeper about 甘泉﹐或 give spring caddy to keeper）。" :));
			return 0;
		}

		// 進行中、持茶罐注泉：注泉、交付滿罐、記旗標（茶罐由 give 指令於回 1 後自行銷除）
		message_vision(
			"守井老叟接過$N遞來的茶罐﹐俯身打井裡汲起滿滿一瓢清冽的\n"
			"甘泉﹐傾進罐裡注得滿滿﹐又拿油紙仔細封了罐口。\n", who);
		// give 指令會於本函回 1 後自行 destruct 茶罐﹐故此處 fill_caddy 只交滿罐、記旗標﹔
		// 為穩妥﹐fill_caddy 內仍會嘗試銷除手中空罐（present 取到的即將被 give 銷除的同一個）。
		fill_caddy(who);
		do_chat(({
			(: command, "say 客官是甘泉客棧掌櫃打發來注甘泉的罷﹖這罐雀舌嫩茶﹐老朽一聞便知是甘泉園老圃的手筆。" :),
			(: command, "say 老朽替客官打了滿滿一注井裡剛汲的甜水注進去﹐拿油紙封了罐口。喏﹐這隻甘泉茶罐﹐方纔已奉到客官手裡了﹐快持回甘泉客棧交與掌櫃（ask keeper about 甘泉﹐或 give spring caddy to keeper）。" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老朽用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗客官好沒道理﹗欺負我一個看井的老頭子做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
