// abang.c -- 運河渡口的漕幫老船工「阿邦」。漕幫支線「四鬼問環」第一步線索人。
//
// 【設定 / canon】依 ES2 設定﹐阿邦、阿義是漕幫渡口的船工（docs 05 L103「阿邦、阿義
//   @ 羿水河邊渡船頭 → 漕幫任務起點」）﹐領玩家認識漕幫、引向幫中耆宿江隕（由江隕授
//   「四鬼」之環﹐docs 05 L105）。
//
// 【支線「四鬼問環」第一步（quest/caobang_clue_a）】（決策 A 已拍板、序章直通 canon）：
//   玩家先向漕運碼頭周老大領了漕幫竹籌(quest/caobang_start)﹐持籌來向阿邦 ask about 四鬼﹐
//   阿邦這跑老了船的舊人便道出他所知的江隕與「四鬼舊環」的風聲、再指玩家去尋年輕船工
//   阿義問下一段——同步記 quest/caobang_clue_a = 1。
//   * 未持籌 / 未起差事(無 caobang_start 或籌不在身)：只給漕幫由來的純氣氛對白、指去尋
//     周老大領籌（不記旗標）。
//   * 持籌且已起差事：道線索、記 clue_a、指向阿義（同步——記旗標在 do_chat 氣氛之前）。
//   本支線自成 quest/caobang_* 旗標﹐絕不讀寫任何 旋芒 / main_canon / main_omen 旗標。
//
// 【同步交付】本步只設旗標、不交物﹐旗標一律在 do_ask handler 內、do_chat 氣氛對白之前
//   直接 set——do_chat 只擺氣氛（承本專案頭號 bug class 之防範）。
//
// 【runtime 鐵則】本 NPC 有 do_ask / init，**不** replace_program（#11）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("阿邦", ({ "abang", "boatman abang", "boatman" }) );
	set("nickname", "阿邦");
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 44);
	set("gender", "male");
	set("long",
		"渡口上一個跑老了船的漕幫船工﹐喚作阿邦。生得膀大腰圓﹐\n"
		"古銅色的脊背上盡是扛包磨出的厚繭﹐褲管捲到膝上﹐赤著一雙踩\n"
		"慣了跳板的大腳。他在這運河上替漕幫扛了半輩子的糧包﹐渡口上\n"
		"哪條船幾時靠、哪位管事的脾性如何﹐他都門兒清。閒下來愛蹲在\n"
		"纜樁上抽袋旱煙﹐和過往的人嘮兩句漕幫的閒話。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"阿邦把一個沉甸甸的糧包往肩上一掄﹐踩著顫巍巍的跳板穩穩上了岸﹐臉不紅氣不喘。\n",
		"阿邦蹲在纜樁上抽著旱煙﹐瞇眼瞧著一河的漕船﹐悠悠地吐出一口煙。\n",
		"阿邦衝著河上的船扯著嗓子喊了句號子﹐渾厚的嗓音在河面上盪開老遠。\n",
		"阿邦抹了把汗﹐朝禮堂那頭望了一眼﹐低聲道﹕咱漕幫的事﹐還得江老爺子拿主意哪。\n",
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
	object me = this_player();

	if( !arg )
		return notify_fail("你想跟這船工打聽甚麼﹖（試試 ask abang about 漕幫）\n");

	// 漕幫由來：純氣氛介紹這個執掌天下漕運的不結仇大幫
	if( arg == "abang about 漕幫"
	||  arg == "abang about 渡口"
	||  arg == "abang about 運河"
	||  arg == "abang about 漕運"
	||  arg == "abang about caobang"
	||  arg == "boatman about 漕幫" ) {
		do_chat(({
			(: command, "say 客官面生﹐頭一回到咱漕幫渡口罷﹖咱漕幫啊﹐管的是這天下的漕運——南邊的糧米綢緞﹐順著這條大運河﹐千里迢迢運進京畿來﹐靠的全是咱這幫跑船扛包的弟兄。" :),
			(: command, "say 咱漕幫幫眾數十萬﹐沿著大運河南北分舵林立﹐勢力大著哩。難得的是﹐咱漕幫雖大﹐在江湖上卻是從不與人結仇的——跑船的圖個四方通達、和氣生財﹐結那些梁子做甚﹖" :),
			(: command, "say 客官若有心入夥﹐只管往北穿過漕幫巷﹐到禮堂裡去走走。幫裡的事﹐自有禮堂的分舵主宋爺、還有咱幫中那位老前輩江爺照應。" :),
		}));
		return 1;
	}

	// 四鬼問環 第一步（quest/caobang_clue_a）：持籌問四鬼舊事，道線索、指向阿義。
	if( arg == "abang about 四鬼"
	||  arg == "abang about 舊環"
	||  arg == "abang about 問環"
	||  arg == "abang about 線索"
	||  arg == "abang about sigui" ) {

		if( is_fighting() || is_chatting() )
			return notify_fail("阿邦正扛著糧包踩跳板﹐一時顧不上你。\n");

		// 未起差事（沒領過漕幫竹籌）：只給氣氛、指去尋周老大領籌，不記旗標。
		if( me->query("quest/caobang_start") < 1 || !present("caobang tally", me) ) {
			do_chat(({
				(: command, "say 『四鬼』﹖嘖﹐客官這話﹐可不是隨口跟個扛包的打聽的。你連咱漕幫的竹籌都還沒領哩﹗" :),
				(: command, "say 客官要當真有心問這個﹐先沿河往東到漕運碼頭﹐尋那掌事的攬頭周老大領一枚漕幫的竹籌——憑那籌子﹐你才算咱漕幫的自己人﹐我才好跟你說這些幫裡的舊事。(ask zhoulaoda about 差事)" :),
			}));
			return 1;
		}

		// 持籌、已起差事：同步記 clue_a（在 do_chat 之前），道線索、指向阿義。
		if( me->query("quest/caobang_clue_a") < 1 )
			me->set("quest/caobang_clue_a", 1);
		do_chat(({
			(: command, "say （阿邦瞥見你腰間那枚漕幫竹籌﹐神色一鄭重﹐壓低了嗓子）哦﹖是揣著籌子來的——那是咱自己人了。客官要問『四鬼』﹖唉﹐這事說來話長。" :),
			(: command, "say 我這跑老了船的﹐只曉得個風聲﹕咱幫裡那位老前輩江隕江爺﹐手裡頭壓著一枚刻著四個古怪鬼名的舊銅環﹐說是甚麼『赤魈、青蛛、濁魚、旱魃』山林川原四鬼。江爺守著那環守了幾十年﹐等的就是個有膽識、肯為人奔走的後生﹐替他把那樁舊因果了結了。" :),
			(: command, "say 旁的我這扛包的嘴上說不周全。客官真要問﹐去尋阿義那渾小子——他年輕﹐耳朵尖﹐渡口上的閒話比我曉得的多﹐他就在這渡口幫著理船哩。(ask ayi about 四鬼)" :),
		}));
		return 1;
	}

	// 江隕 / 阿義：canon 引子——純氣氛點題、指路（不記旗標）。
	if( arg == "abang about 江隕"
	||  arg == "abang about 江爺"
	||  arg == "abang about jiangyun"
	||  arg == "abang about 阿義"
	||  arg == "abang about ayi" ) {
		do_chat(({
			(: command, "say 阿義那渾小子﹖他也是渡口的船工﹐打小跟我一塊兒在這河上跑的﹐就在這渡口幫著理船﹐客官回頭撞見便是。" :),
			(: command, "say 至於江爺——江隕老爺子﹐那可是咱漕幫頂頂有來歷的人物﹐這會兒就在北頭的禮堂裡。江湖上都曉得他手裡握著一樁了不得的舊事﹐甚麼『四鬼』的因由 ... 嘿﹐這個﹐你揣著籌子來問我（ask abang about 四鬼）﹐我才好跟你說。" :),
		}));
		return 1;
	}

	return notify_fail("阿邦咧嘴一笑﹐露出一口被旱煙燻黃的牙﹕客官問這做甚﹖跑船扛包的粗人﹐沒甚說頭。（試試 ask abang about 漕幫）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎哎﹗使不得﹗咱漕幫的渡口﹐是和氣做生意的地界﹐動甚麼粗﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
