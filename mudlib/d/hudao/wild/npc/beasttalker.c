// beasttalker.c -- 獸語者，棲身於野獸山林天靈山麓密窟的異人，
//                  主線任務六「摩雲蹤跡」的勘察對象
//
// 故事背景（承接主線五「群獸朝靈」）：
//   雪亭鎮飲風客棧那位隱居的老獵王﹐獵王世家三代追獵獸王摩雲﹐手裡有半卷
//   殘缺的《摩雲蹤跡圖》﹐卻因年邁與獸窟戾氣太重﹐再勘不出摩雲今時的去
//   向﹐遂託少俠持殘卷往野獸山林最深處尋人續補。這位獸語者本是隱於荒山、
//   通曉禽獸之語的異人﹐多年來循著獸群的躁動獨居於這天靈山麓的密窟——此處
//   正是獸王摩雲昔日蟄伏、近日又退守蓄勢的舊巢。他聽得懂群獸口中那縷恐懼
//   與騷動﹐又就摩雲遺於石壁的爪痕墨拓下來﹐遂憑那卷殘圖認出少俠是老獵王
//   遣來之人﹐將續補的蹤跡與爪拓一併交付少俠帶回。
//
// 任務流程（旗標存在玩家身上：quest/main_omen6，由 d/snow/npc/beastking.c 開啟）：
//   進行中 (1)  : 玩家持老獵王交付的「摩雲蹤跡圖殘卷」到天靈山麓密窟
//                 交(give)給獸語者 -> 獸語者驗卷後收下﹐續補蹤跡、道出摩雲
//                 退守天靈山麓蓄勢﹐回給「摩雲爪拓」﹐並把旗標推進為 2
//                 （推進在本檔）
//   已取得 (2)  : 玩家把爪拓帶回雪亭鎮交(give)給老獵王領賞（推進 2->3 在 beastking.c）
//
// 注意：本 NPC 不開啟任務、不給賞（開啟與領賞皆在 beastking.c）﹐只負責驗卷、
//       收卷、回爪拓、推進旗標 1 -> 2。
//   收下信物後不自行 destruct﹐由 give 指令將信物移入本 NPC（與 woodsman／
//   shrinekeeper 一致）﹐並於旗標處作防重複推進。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("獸語者", ({ "beast talker", "talker", "beasttalker" }) );
	set("nickname", "獸語者");
	set_attr("int", 22);
	set_attr("wis", 24);
	set_attr("con", 18);
	set_race("human");
	set_class("commoner");
	set_level(14);
	set_skill("unarmed", 26);
	set_skill("dodge", 30);
	set_skill("force", 28);
	set_skill("literate", 30);

	set("gender", "male");
	set("age", 52);
	set("long",
		"一位形容枯槁、闔目盤坐的異人﹐鬚髮蓬亂如荒草﹐一身補綴的\n"
		"粗麻短褐沾滿塵土﹐渾身透著股久居荒山、與禽獸為伍的野氣。\n"
		"他自小便能聽懂飛禽走獸口中的聲息﹐遂避開人煙﹐獨居於這天\n"
		"靈山麓的密窟﹐聆聽群獸的悲歡。這幾日他總側耳向北﹐眉頭深\n"
		"鎖——他聽見滿山的走獸口中﹐都翻滾著一股說不出的恐懼與躁動﹐\n"
		"彷彿在懼怕、又在朝拜著甚麼龐然的存在。\n"
		"你或許可以問問他﹕ask beasttalker about 摩雲。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"獸語者闔目側耳﹐良久﹐輕輕嘆了口氣﹐喃喃學了兩聲遠處走獸的悲鳴。\n",
		"獸語者喃喃道﹕牠們都在怕 ... 又都在拜 ... 摩雲啊摩雲﹐你究竟想做甚麼 ...\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen6");
		if( q == 1 )
			do_chat((: command,
				"say 這位少俠面生 ... 莫非是循著那卷摩雲蹤跡圖﹐尋到這密窟裡來的﹖" :));
	}
}

// 主線六「摩雲蹤跡」：把一幅摩雲爪拓交到玩家手上（先複製到自己身上，再 give 出去）
private void give_rubbing(object who)
{
	object rubbing;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	rubbing = new("/d/hudao/wild/npc/obj/claw_rubbing");
	rubbing->move(this_object());
	command("give claw rubbing to " + who->query("id"));
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg || (arg != "beast talker about 摩雲"
		&&   arg != "beast talker about 獸王"
		&&   arg != "beast talker about 主線"
		&&   arg != "beast talker about 任務"
		&&   arg != "beasttalker about 摩雲"
		&&   arg != "beasttalker about 獸王"
		&&   arg != "beasttalker about 主線"
		&&   arg != "beasttalker about 任務"
		&&   arg != "beast talker about quest"
		&&   arg != "beast talker about task") )
		return notify_fail("你想問這位獸語者甚麼﹖（試試 ask beasttalker about 摩雲）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("獸語者正闔目側耳聆聽著甚麼﹐沒空理你。\n");

	// 尚未接主線六（旗標 <1）：不知來意﹐只道群獸異狀
	if( me->query("quest/main_omen6") < 1 ) {
		do_chat((: command,
			"say 少俠也聽見了麼﹖這滿山的走獸﹐口中都翻滾著一股恐懼與躁動 ... 牠們在怕一頭龐然的獸王﹐又身不由己地朝牠聚去。少俠若要究這獸王的根底﹐須有識得牠舊蹤的明白人指點﹐空口問我﹐我也說不清。" :));
		return 1;
	}

	// 進行中（旗標 1）：理應用 give 交付摩雲蹤跡圖殘卷
	if( me->query("quest/main_omen6") == 1 ) {
		if( present("trace scroll", me) )
			do_chat((: command,
				"say 少俠那卷蹤跡圖 ... 我認得﹐是獵王世家的手筆。少俠且把那卷殘圖交(give)給我﹐我循著群獸口中的聲息與這窟裡的爪痕﹐自能與你續補出摩雲今時的去向。" :));
		else
			do_chat((: command,
				"say 少俠空口無憑﹐這摩雲的去向干係重大﹐我豈能輕信﹖少俠且去尋那位隱居的老獵王﹐討那卷《摩雲蹤跡圖》殘卷來﹐我自有話說。" :));
		return 1;
	}

	// 已取得爪拓（旗標 2 或更後）
	if( present("claw rubbing", me) )
		do_chat((: command,
			"say 那幅爪拓我已交與少俠了﹐快帶回雪亭鎮﹐交還那位老獵王參詳罷。" :));
	else
		// 萬一玩家把爪拓弄丟了，補拓一幅給他
		do_chat(({
			"獸語者搖頭嘆了口氣﹐又取過一張薄棉紙﹐就著窟壁的爪痕重新墨拓起來。\n",
			(: command, "say 怎麼那爪拓不見了﹖罷了﹐這窟壁的爪痕還在﹐再與少俠拓一幅便是。" :),
			(: give_rubbing, me :),
		}));
	return 1;
}

// 收下信物：
//   摩雲蹤跡圖殘卷(trace scroll) -- 主線六「摩雲蹤跡」送件﹐旗標 main_omen6 1 -> 2﹐回給摩雲爪拓
// 收下後不自行 destruct﹐由 give 指令將信物移入本 NPC（與 woodsman／shrinekeeper 一致）﹐
// 並於旗標處作防重複推進。
int accept_object(object who, object ob)
{
	// 主線六：交付摩雲蹤跡圖殘卷
	if( ob->id("trace scroll") ) {
		// 不是正在送件的任務玩家（或已驗過）﹐仍收下避免卡物﹐但不重複推進
		if( who->query("quest/main_omen6") != 1 ) {
			do_chat((: command, "say 多謝少俠﹗" :));
			return 1;
		}

		who->set("quest/main_omen6", 2);
		do_chat(({
			(: command, "say 獵王世家的蹤跡圖 ... 不錯﹐這圖上的硃砂舊蹤我認得。少俠隨我來﹐瞧瞧這窟裡的爪痕﹐再聽聽群獸口中的聲息。" :),
			(: command, "say 少俠瞧這滿壁的爪痕——這便是那獸王摩雲蟄伏此處時所留。我這幾日聽得真切﹕滿山的走獸口中﹐都翻滾著對摩雲的恐懼﹐卻又身不由己地朝牠退守的方向聚去。" :),
			(: command, "say 我循著少俠這卷殘圖﹐又就群獸的聲息與這窟裡的新蹤續補﹐已勘得明白——摩雲受了天靈山那縷邪念的牽動﹐並未遠遁﹐反倒退往天靈山麓蓄養氣力去了。牠是要養足了兇威﹐再興一場更大的獸亂啊。" :),
			(: command, "say 少俠若要制牠﹐單憑一身武藝只怕不足——那山中邪障重重﹐須尋一位能破障的同道﹐再求一件能制那邪念本源的聖物﹐方有勝算。我就摩雲這道爪痕拓了一幅﹐連同續補的蹤跡都記在上頭。少俠帶回去交與那老獵王﹐請他早作籌謀。" :),
			(: give_rubbing, who :),
		}));
		return 1;
	}

	// 其餘物事：婉拒﹐不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個我用不上﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠這是做甚﹖我一個聽獸語的隱者﹐與你無冤無仇哪。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
