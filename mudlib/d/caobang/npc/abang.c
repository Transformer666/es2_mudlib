// abang.c -- 運河渡口的漕幫老船工「阿邦」。純氣氛閒談 NPC：不接任務、不交物、不動旗標。
//
// 【設定 / canon】依 ES2 設定﹐阿邦、阿義是漕幫渡口的船工﹐本是漕幫「四鬼問環」
//   支線的起點關鍵人（領玩家入漕幫、引見幫中耆宿江隕﹐由江隕授「四鬼」之環）。
//
// 【A-gated TODO】「四鬼問環」整條主線支線﹐其開展繫於另一樁尚未拍板的主線抉擇(決策 A)﹐
//   因此本檔【不】實作任何任務﹕只把阿邦寫成領玩家認識漕幫、嘴上點到「江隕」「四鬼」
//   canon 角色的氣氛船工。
//   == 待決策 A 拍板後再補的支線（此處一律不做、不設旗標）==
//     - 由阿邦/阿義正式「引見江隕」的接線
//     - 江隕授「四鬼」指環 -> 赤魈/青蛛/濁魚/旱魃 的問環支線
//   本檔絕不讀寫任何 四鬼 / 旋芒 / main_omen / 主線 旗標。

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

	// 江隕：canon 引子（「四鬼問環」支線授環人）——此處只作氣氛點題﹐不接任何任務
	if( arg == "abang about 江隕"
	||  arg == "abang about 江爺"
	||  arg == "abang about jiangyun"
	||  arg == "abang about 四鬼"
	||  arg == "abang about 阿義"
	||  arg == "abang about ayi" ) {
		do_chat(({
			(: command, "say 阿義那渾小子﹖他也是渡口的船工﹐打小跟我一塊兒在這河上跑的﹐就在這渡口幫著理船﹐客官回頭撞見便是。" :),
			(: command, "say 至於江爺——江隕老爺子﹐那可是咱漕幫頂頂有來歷的人物﹐這會兒就在北頭的禮堂裡。江湖上都曉得他手裡握著一樁了不得的舊事﹐甚麼『四鬼』的因由 ... 嘿﹐這個﹐可不是我一個扛包的嘴上能混說的。客官有那緣分﹐自個兒去禮堂尋江爺問罷。" :),
		}));
		// TODO(decision-A)：待主線抉擇 A 拍板﹐此處方接「引見江隕→授四鬼之環」支線﹔
		//                   現階段一律只給氣氛對白﹐不設任何 四鬼/旋芒/主線 旗標。
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
