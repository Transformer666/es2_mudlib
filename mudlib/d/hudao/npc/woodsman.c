// woodsman.c -- 守山人，常年在老松林深處結廬而居的山民，
//               主線任務五「群獸朝靈」的勘察對象
//
// 故事背景（承接主線四「獸亂之兆」）：
//   京畿神社守木老者與老松林老獵戶道破﹕將潰的聖木封印放出邪念﹐勾得走
//   獸發狂﹐成群朝天靈山而去——這是動物war的序章。雪亭鎮飲風客棧裡那位
//   循異兆而來的雲遊道人﹐查出群獸實是聽命於一頭蟄伏荒野、喚作摩雲的獸
//   王﹐遂交付少俠一道觀獸符﹐遣他往老松林深處勘察群獸朝靈的去向。這位
//   守山人世代住在林子最深處﹐近日親眼見著百獸結隊北徙、獸王影子掠過林
//   梢﹐正自心驚﹐遂憑那道觀獸符認出少俠是道人遣來的人﹐將自己就獸皮繪
//   下的獸群遷徙圖交付少俠﹐請他帶回去交與道人參詳。
//
// 任務流程（旗標存在玩家身上：quest/main_omen5，由 d/snow/npc/diviner.c 開啟）：
//   進行中 (1)  : 玩家持雲遊道人交付的「觀獸符」到老松林深處
//                 交(give)給守山人 -> 守山人驗符後收下﹐道出群獸朝天靈山
//                 遷徙、獸王摩雲的影子﹐回給「獸群遷徙圖」﹐並把旗標推進
//                 為 2（推進在本檔）
//   已取得 (2)  : 玩家把遷徙圖帶回雪亭鎮交(give)給雲遊道人領賞（推進 2->3 在 diviner.c）
//
// 注意：本 NPC 不開啟任務、不給賞（開啟與領賞皆在 diviner.c）﹐只負責驗符、
//       收符、回遷徙圖、推進旗標 1 -> 2。
//   收下信物後不自行 destruct﹐由 give 指令將信物移入本 NPC（與 hunter／
//   shrinekeeper 一致）﹐並於旗標處作防重複推進。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("守山人", ({ "woodsman", "hill man", "shoushan" }) );
	set("nickname", "守山人");
	set_attr("str", 21);
	set_attr("con", 19);
	set_race("human");
	set_class("commoner");
	set_level(13);
	set_skill("unarmed", 28);
	set_skill("dodge", 28);
	set_skill("blade", 22);
	set_skill("force", 22);

	set("gender", "male");
	set("age", 49);
	set("long",
		"一位世代住在老松林最深處的守山人﹐身材高大魁梧﹐須髮糾結如\n"
		"枯藤﹐一身獸皮裹得嚴實﹐渾身透著股與山林融為一體的野氣。他\n"
		"自小在這林子深處長大﹐林中草木鳥獸的脾性沒有不曉得的。這幾\n"
		"日他卻成日攥著手裡那柄削尖的木矛﹐脊背繃得死緊﹐每每抬眼望\n"
		"向北面天靈山的方向﹐眼神裡又是驚惶又是不解。\n"
		"你或許可以問問他﹕ask woodsman about 群獸。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"守山人攥緊了手裡的木矛﹐死死望著北面林梢﹐喉間擠出一聲悶哼。\n",
		"守山人喃喃道﹕都瘋了 ... 一窩蜂似地往天靈山奔 ... 那林子裡頭﹐究竟藏了個甚麼東西 ...\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen5");
		if( q == 1 )
			do_chat((: command,
				"say 這位少俠面生 ... 莫非是循著那道觀獸符的指引﹐尋到這林子深處來的﹖" :));
	}
}

// 主線五「群獸朝靈」：把一幅獸群遷徙圖交到玩家手上（先複製到自己身上，再 give 出去）
private void give_map(object who)
{
	object map;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	map = new("/d/snow/npc/obj/beast_trail_map");
	map->move(this_object());
	command("give beast trail to " + who->query("id"));
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg || (arg != "woodsman about 群獸"
		&&   arg != "woodsman about 摩雲"
		&&   arg != "woodsman about 獸王"
		&&   arg != "woodsman about 主線"
		&&   arg != "woodsman about 任務"
		&&   arg != "hill man about 群獸"
		&&   arg != "hill man about 摩雲"
		&&   arg != "woodsman about quest"
		&&   arg != "woodsman about task") )
		return notify_fail("你想問這位守山人甚麼﹖（試試 ask woodsman about 群獸）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("守山人正攥著木矛死死盯著北面林梢﹐沒空理你。\n");

	// 尚未接主線五（旗標 <1）：不知來意﹐只道林中怪事
	if( me->query("quest/main_omen5") < 1 ) {
		do_chat((: command,
			"say 少俠也覺出這林子不對了麼﹖近來百獸發瘋似地往天靈山奔 ... 老朽守了一輩子山﹐從沒見過這等怪事。少俠若真要究這根底﹐須有識得異兆的明白人指點﹐空口問老朽﹐老朽也說不清。" :));
		return 1;
	}

	// 進行中（旗標 1）：理應用 give 交付觀獸符
	if( me->query("quest/main_omen5") == 1 ) {
		if( present("beast ward", me) )
			do_chat((: command,
				"say 少俠那道觀獸符﹐老朽認得——是雲遊道長的手筆。少俠且把符交(give)給老朽﹐老朽便將這幾日勘下的獸群去向﹐一併與你說了。" :));
		else
			do_chat((: command,
				"say 少俠空口無憑﹐這獸群的去向干係重大﹐老朽豈能輕信﹖少俠且去尋那位雲遊道長﹐討道觀獸符來﹐老朽自有話說。" :));
		return 1;
	}

	// 已取得遷徙圖（旗標 2 或更後）
	if( present("beast trail", me) )
		do_chat((: command,
			"say 那幅遷徙圖老朽已交與少俠了﹐快帶回雪亭鎮﹐交還那位雲遊道長參詳罷。" :));
	else
		// 萬一玩家把遷徙圖弄丟了，補繪一幅給他
		do_chat(({
			"守山人搖頭嘆了口氣﹐又取過一張舊獸皮﹐就著炭條重新勾畫起獸徑來。\n",
			(: command, "say 怎麼那圖不見了﹖罷了﹐這幾日的獸徑老朽都記在心裡﹐再與少俠繪一幅便是。" :),
			(: give_map, me :),
		}));
	return 1;
}

// 收下信物：
//   觀獸符(beast ward) -- 主線五「群獸朝靈」送件﹐旗標 main_omen5 1 -> 2﹐回給獸群遷徙圖
// 收下後不自行 destruct﹐由 give 指令將信物移入本 NPC（與 hunter／shrinekeeper 一致）﹐
// 並於旗標處作防重複推進。
int accept_object(object who, object ob)
{
	// 主線五：交付觀獸符
	if( ob->id("beast ward") ) {
		// 不是正在送件的任務玩家（或已驗過）﹐仍收下避免卡物﹐但不重複推進
		if( who->query("quest/main_omen5") != 1 ) {
			do_chat((: command, "say 多謝少俠﹗" :));
			return 1;
		}

		who->set("quest/main_omen5", 2);
		do_chat(({
			(: command, "say 雲遊道長的觀獸符 ... 不錯﹐這符上的清氣老朽認得。少俠隨老朽來﹐瞧瞧老朽這幾日勘下的東西。" :),
			(: command, "say 少俠瞧這滿地新踩的獸徑——白猴、野豬、連那些素來獨來獨往的猛獸﹐這幾日竟成群結隊地往北面天靈山奔﹐百川歸海似的﹐再不肯回頭。" :),
			(: command, "say 前夜老朽守在崖邊﹐遠遠望見群獸之首掠過一道龐然的黑影﹐遮天蔽日﹐獸群見了那影子﹐竟齊齊伏地嘶鳴﹐像是 ... 像是在朝拜。老朽聽林子裡的老人說過﹐那是頭喚作摩雲的獸王。" :),
			(: command, "say 老朽就獸皮繪了這幅遷徙圖﹐獸徑、去向、那獸王的影子﹐都記在上頭。少俠帶回去交與雲遊道長﹐請他參詳這摩雲的根底——這場群獸朝靈﹐只怕是天大的禍事之始。" :),
			(: give_map, who :),
		}));
		return 1;
	}

	// 其餘物事：婉拒﹐不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老朽用不上﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠這是做甚﹖老朽一個守山的﹐與你無冤無仇哪。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
