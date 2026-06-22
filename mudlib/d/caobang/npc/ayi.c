// ayi.c -- 運河渡口的漕幫小船工「阿義」。漕幫支線「四鬼問環」第二步線索人。
//
// 【設定 / canon】依 ES2 設定﹐阿邦、阿義是漕幫渡口的船工（docs 05 L103）﹐領玩家入
//   漕幫、引向幫中耆宿江隕（由江隕授「四鬼」之環﹐docs 05 L105）。阿義嘴快耳尖、熱心
//   指路。
//
// 【支線「四鬼問環」第二步（quest/caobang_clue_b）】（決策 A 已拍板）：
//   玩家持籌、得了阿邦的線索(quest/caobang_clue_a)後﹐向阿義 ask about 四鬼﹐阿義便把
//   渡口上聽來的下一段風聲——酒館外那討飯的老乞丐原是漕幫舊人、最曉得江爺與四鬼的根
//   底——說與玩家﹐再指去尋那老乞丐。同步記 quest/caobang_clue_b = 1。
//   * 未持籌 / 未得 clue_a：只給氣氛、指去先尋阿邦問起（不記旗標）。
//   * 持籌且已得 clue_a：道線索、記 clue_b、指向酒館外老乞丐（記旗標在 do_chat 之前）。
//   本支線自成 quest/caobang_* 旗標﹐絕不讀寫任何 旋芒 / main_canon / main_omen 旗標。
//
// 【同步交付】本步只設旗標、不交物﹐旗標一律在 do_chat 氣氛對白之前直接 set。
//
// 【runtime 鐵則】本 NPC 有 do_ask / init，**不** replace_program（#11）。

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
	object me = this_player();

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

	// 四鬼問環 第二步（quest/caobang_clue_b）：承阿邦線索，道下一段風聲、指向老乞丐。
	if( arg == "ayi about 四鬼"
	||  arg == "ayi about 舊環"
	||  arg == "ayi about 問環"
	||  arg == "ayi about 線索"
	||  arg == "ayi about sigui" ) {

		if( is_fighting() || is_chatting() )
			return notify_fail("阿義正手腳麻利地理著纜﹐一時顧不上你。\n");

		// 未持籌 / 未得 clue_a：只給氣氛、指去先尋阿邦問起，不記旗標。
		if( me->query("quest/caobang_start") < 1 || !present("caobang tally", me) ) {
			do_chat((: command, "say 客官面生﹐連咱漕幫的竹籌都還沒揣著哩﹗『四鬼』這等幫裡的舊事﹐我可不敢跟外人混說。客官要當真有心問﹐先去碼頭尋周老大領了籌子﹐再來。(ask zhoulaoda about 差事)" :));
			return 1;
		}
		if( me->query("quest/caobang_clue_a") < 1 ) {
			do_chat((: command, "say 哎呀客官﹐這事可不興沒頭沒腦地問我﹗你先去尋邦哥——就是那老船工阿邦﹐他跑船的年頭比我長﹐這四鬼的風聲﹐該先聽他說個頭緒。(ask abang about 四鬼)" :));
			return 1;
		}

		// 持籌、已得 clue_a：同步記 clue_b（在 do_chat 之前），道線索、指向老乞丐。
		if( me->query("quest/caobang_clue_b") < 1 )
			me->set("quest/caobang_clue_b", 1);
		do_chat(({
			(: command, "say （阿義往四下瞄了一眼﹐神祕兮兮地湊近）邦哥讓你來問我的﹖嘿﹐那四鬼舊環的事﹐我也只聽了個風聲——可我曉得誰曉得得最清楚﹗" :),
			(: command, "say 客官打渡口往西南拐﹐有座飄著酒旗的小酒館﹐門外蹲著個討飯的老乞丐。客官莫小瞧那老叫花子——他年輕時也是這河上跑船的漕幫舊人﹐落魄了才討飯的。幫裡的老人都說﹐江爺那枚四鬼舊環的根底﹐連同當年布那封印的舊事﹐這滿渡口﹐就數那老乞丐曉得得最透。" :),
			(: command, "say 客官揣著籌子去尋他﹐問他這『四鬼』的源流——他若肯說﹐你再回禮堂尋江爺﹐這環的因由便齊全了。(ask beggar about 四鬼)" :),
		}));
		return 1;
	}

	// 江隕 / 宋安江：canon 引子——純氣氛點題、指路（不記旗標）
	if( arg == "ayi about 江隕"
	||  arg == "ayi about 江爺"
	||  arg == "ayi about jiangyun"
	||  arg == "ayi about 宋安江"
	||  arg == "ayi about songanjiang" ) {
		do_chat(({
			(: command, "say 宋爺就是禮堂的分舵主宋安江﹐管著咱京畿這一處的大小幫務﹐人最是爽利仗義﹐客官到了禮堂自會見著。" :),
			(: command, "say 江爺嘛 ... 江隕老爺子﹐輩分高得很﹐就在禮堂裡頭。聽幫裡的老人講﹐江爺手裡頭壓著一樁天大的舊事﹐甚麼『四鬼』的淵源 ... 客官真好奇﹐揣著籌子來問我（ask ayi about 四鬼）﹐我才好跟你說個風聲。" :),
		}));
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
