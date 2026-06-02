// ayi.c -- 運河渡口的漕幫小船工「阿義」。純氣氛閒談 NPC：不接任務、不交物、不動旗標。
//
// 【設定 / canon】依 ES2 設定﹐阿邦、阿義是漕幫渡口的船工﹐本是漕幫「四鬼問環」
//   支線的起點關鍵人（領玩家入漕幫、引見幫中耆宿江隕﹐由江隕授「四鬼」之環）。
//
// 【A-gated TODO】「四鬼問環」整條主線支線﹐其開展繫於另一樁尚未拍板的主線抉擇(決策 A)﹐
//   因此本檔【不】實作任何任務﹕阿義只是個嘴快熱心、會替玩家指路（往禮堂尋江隕、宋安江）
//   的氣氛小船工﹐點到 canon 角色為止。
//   == 待決策 A 拍板後再補的支線（此處一律不做、不設旗標）：見 abang.c 同段註記。==
//   本檔絕不讀寫任何 四鬼 / 旋芒 / main_omen / 主線 旗標。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("阿義", ({ "ayi", "boatman ayi", "young boatman" }) );
	set("nickname", "阿義");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 22);
	set("gender", "male");
	set("long",
		"渡口上一個年輕的漕幫船工﹐喚作阿義。生得精瘦結實﹐一張\n"
		"曬黑的臉上透著機靈﹐腰裡束著條青布帶子﹐手腳麻利地替靠岸的\n"
		"漕船理纜、搭板。他打小跟著老船工阿邦在這運河上跑船﹐嘴快心\n"
		"熱﹐見了生客便愛湊上來搭話﹐替人指點渡口、禮堂的去處。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"阿義手腳麻利地把纜繩在石樁上繞了個結實的扣﹐又蹦上船去搭跳板。\n",
		"阿義扯著嗓子應和著岸上的號子﹐一面替靠岸的漕船理著纜。\n",
		"阿義抹了把汗﹐衝著過往的人咧嘴一笑﹕客官要尋人﹖往北禮堂裡去﹐宋爺、江爺都在哩﹗\n",
	}));
	setup();
	carry_money("coin", 15);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想跟這小船工打聽甚麼﹖（試試 ask ayi about 漕幫）\n");

	// 漕幫由來 / 指路：純氣氛
	if( arg == "ayi about 漕幫"
	||  arg == "ayi about 渡口"
	||  arg == "ayi about 運河"
	||  arg == "ayi about 禮堂"
	||  arg == "ayi about caobang"
	||  arg == "ayi about 阿邦"
	||  arg == "ayi about abang" ) {
		do_chat(({
			(: command, "say 客官好﹗咱漕幫的渡口﹐天下糧船泰半打這兒進京﹗我叫阿義﹐打小跟邦哥——就是那位老船工阿邦﹐在這河上跑船。客官有甚麼要打聽的﹐只管問我﹗" :),
			(: command, "say 咱漕幫雖是江湖上數一數二的大幫﹐可從不跟人結仇的——跑船的和氣生財嘛。客官要尋幫裡管事的﹐往北穿過漕幫巷﹐到禮堂去﹕分舵主宋爺、還有咱幫裡那位老前輩江爺﹐都在禮堂裡頭。" :),
		}));
		return 1;
	}

	// 江隕：canon 引子（授「四鬼」之環的人）——此處只氣氛點題﹐不接任何任務
	if( arg == "ayi about 江隕"
	||  arg == "ayi about 江爺"
	||  arg == "ayi about jiangyun"
	||  arg == "ayi about 四鬼"
	||  arg == "ayi about 宋安江"
	||  arg == "ayi about songanjiang" ) {
		do_chat(({
			(: command, "say 宋爺就是禮堂的分舵主宋安江﹐管著咱京畿這一處的大小幫務﹐人最是爽利仗義﹐客官到了禮堂自會見著。" :),
			(: command, "say 江爺嘛 ... 江隕老爺子﹐輩分高得很﹐就在禮堂裡頭。聽幫裡的老人講﹐江爺手裡頭壓著一樁天大的舊事﹐甚麼『四鬼』的淵源 ... 唉﹐這個我也只是聽個風聲﹐當不得真。客官真好奇﹐自個兒去禮堂尋江爺﹐當面討教罷﹗" :),
		}));
		// TODO(decision-A)：「四鬼問環」支線繫於主線抉擇 A﹐拍板前不接任務、不設任何旗標。
		return 1;
	}

	return notify_fail("阿義嘿嘿一笑﹕客官問倒我了﹗這個我可不曉得。要不﹐往北禮堂裡尋宋爺、江爺問問﹖（試試 ask ayi about 漕幫）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲喂﹗客官息怒﹗我一個跑船的小子﹐哪經得起您動手呀﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
