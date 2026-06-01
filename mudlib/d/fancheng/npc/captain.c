// captain.c -- 檒城衛兵統領劉開，鎮守望安港的港城武官；
//              兼檒城非戰鬥支線「望安港的斷龍骨」的領料木牌交付人。
//
// 任務銜接（旗標皆存在玩家身上，支線由 /d/fancheng/npc/boatman.c 開啟）：
//   須先接任務且已問明木料來路 (quest/fancheng_sea==1 且 fancheng_sea_wood)﹐
//   ask captain about 領料 -> 劉開驗看來意﹐畫押一面官中的「領料木牌」交付玩家
//   （實物 /d/fancheng/npc/obj/wood_tally）﹐並記 quest/fancheng_sea_tally = 1。
//   未接任務 / 未問木料來路 / 已領過 / 已完成支線：只作對應的閒談﹐不重複交付。
//
// 注意：本 NPC 不開啟任務、不領賞﹔只負責驗來意、交付領料木牌、記旗標。
//       交付採「先 new 到自己身上、再 command give」之法（與 d/hudao woodsman 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("劉開", ({ "liu kai", "liukai", "captain", "kai" }) );
	set("nickname", "衛兵統領");
	set_attr("str", 24);
	set_attr("con", 22);
	set_attr("int", 18);
	set_race("human");
	set_class("fighter");
	set_level(22);

	set_skill("blade", 70);
	set_skill("parry", 60);
	set_skill("dodge", 50);
	set_skill("unarmed", 45);
	set_skill("force", 50);

	set("age", 41);
	set("gender", "male");
	set("long",
		"這位便是鎮守檒城的衛兵統領劉開。他身形魁梧﹐一張方臉曬\n"
		"得黝黑﹐頷下一部濃密的虬髯﹐眉宇間自有一股久經行伍的剽悍\n"
		"之氣。他披著一領半舊的皮甲﹐腰懸一柄寬刃的朴刀﹐按刀立在\n"
		"公案旁﹐目光如電﹐進出的生面孔都逃不過他的打量。聽聞這港\n"
		"城雖偏處西陲﹐卻多虧有他坐鎮﹐海寇也不敢輕易來犯。你或許\n"
		"可以問問他﹕ask captain about 檒城。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"劉開按著刀柄﹐緩緩踱步﹐銳利的目光掃過進出的人流。\n",
		"劉開沉聲道﹕我這檒城雖小﹐卻是西陲門戶﹐海防半點馬虎不得。\n",
		"劉開捋著虬髯﹐眉頭微皺﹐似在掛心著外海那些不安分的海寇。\n",
	}));
	setup();
	carry_object( STOCK_WEAPON("broadsword") )->wield();
	carry_money("coin", 150);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() ) {
			if( this_player()->query("quest/fancheng_sea") == 1
			&&  this_player()->query("quest/fancheng_sea_wood")
			&&  !this_player()->query("quest/fancheng_sea_tally") )
				do_chat((: command,
					"say 你便是老船匠遣來討領料木牌的﹖且報上來意。" :));
			else
				do_chat((: command,
					"say 生面孔﹖到我檒城的地界﹐安分守己便好。" :));
		}
	}
}

// 交付領料木牌：先 new 一面木牌到自己身上，再以 give 指令移交玩家
// （與 d/hudao/npc/woodsman 的 give_map 一致﹐避免直接 move 落空）。
private void give_tally(object who)
{
	object tally;

	if( !who || environment(who) != environment() ) {
		command("say 人呢﹖");
		return;
	}
	tally = new(__DIR__"obj/wood_tally");
	tally->move(this_object());
	command("give wood tally to " + who->query("id"));
	who->set("quest/fancheng_sea_tally", 1);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問劉統領甚麼﹖（試試 ask captain about 檒城）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("劉開正按刀巡視﹐沒空理你。\n");

	// 領料 / 木牌：非戰鬥支線「望安港的斷龍骨」的領料木牌交付
	if( arg == "captain about 領料"
	||  arg == "liu kai about 領料"
	||  arg == "captain about 木牌"
	||  arg == "captain about 龍骨"
	||  arg == "captain about 修船"
	||  arg == "captain about tally"
	||  arg == "captain about keel" ) {
		object me = this_player();
		int q = me->query("quest/fancheng_sea");

		// 已領過木牌（或支線已完成）：只重述，不重複交付
		if( q >= 2 || me->query("quest/fancheng_sea_tally") ) {
			do_chat((: command,
				"say 那面領料木牌我不是已畫了押交與你了﹖速速持去料場支料﹐莫要遺失了﹐那是官中的記認。" :));
			return 1;
		}

		// 未接任務：不明就裡，公事公辦地擋回
		if( q < 1 ) {
			do_chat((: command,
				"say 領料木牌﹖那是官中料場支料的記認﹐豈是隨口便給的﹖你若無正經來由﹐休要在此糾纏。" :));
			return 1;
		}

		// 進行中但尚未問明木料來路：要玩家先弄清要支何料
		if( !me->query("quest/fancheng_sea_wood") ) {
			do_chat((: command,
				"say 老船匠修船要料﹖也罷。只是你連要支甚麼木料、往何處料場都還沒弄清﹐我這木牌如何填寫﹖你先去 ask 雜貨鋪老闆 about 龍骨﹐問明了好松木的來路﹐再來尋我畫押。" :));
			return 1;
		}

		// 進行中、已問明木料來路、未領過：即刻畫押交付木牌（give_tally 同步給物
		// 並於成功後才記旗標）﹐避免玩家於延遲回呼前離場導致「記了旗標卻沒拿到牌」
		// 的卡關。do_chat 僅作驗來意的氣氛對白。
		give_tally(me);
		do_chat(({
			(: command, "say 哦﹖老船匠那條折了主桅的渡海大船﹐要修了﹖那是西陲海路上頭一等的大船﹐早該修了。修它﹐我這守港的也樂見。" :),
			(: command, "say 老松林的直紋松﹐是做龍骨的好料﹐我已與你畫押了一面領料木牌。憑這牌子﹐你去料場支一截好松木﹐再交還老船匠﹐由他驗看下料。" :),
			(: command, "say 木牌收好﹐莫要遺失——那上頭有我的押、料場的火印﹐是官中的記認。早些把料張羅齊了﹐這船修得越快﹐我這海防也越添一分指望。去罷﹗" :),
		}));
		return 1;
	}

	// 檒城：港城的由來與治安
	if( arg == "captain about 檒城"
	||  arg == "liu kai about 檒城"
	||  arg == "captain about city"
	||  arg == "captain about fancheng" ) {
		do_chat(({
			(: command, "say 我檒城臨海而立﹐是這西陲一帶唯一像樣的商港。南來北往的番舶漁舟皆泊在望安港裡﹐城裡城外﹐十之七八都靠這片海吃飯。" :),
			(: command, "say 港城人雜﹐三教九流都有﹐難免有那不開眼的宵小。我手下這幾十號弟兄日夜巡著﹐倒也還鎮得住。你既來了﹐守著規矩﹐自然無事。" :),
		}));
		return 1;
	}

	// 港 / 望安港 / 海寇：港務與海防
	if( arg == "captain about 港"
	||  arg == "captain about 望安港"
	||  arg == "captain about 海寇"
	||  arg == "captain about 海防"
	||  arg == "captain about harbor"
	||  arg == "captain about pirate" ) {
		do_chat(({
			(: command, "say 望安港是檒城的命脈﹐這海防自然是我這統領頭一樁的差事。外海有幾股海寇﹐近來愈發猖獗﹐專劫往來的番舶貨船﹐著實可恨。" :),
			(: command, "say 我已加派了人手上城頭瞭望﹐入夜便敲鐘戒備。只盼上頭早些撥下戰船﹐我也好出海會一會那幫賊子﹗" :),
		}));
		return 1;
	}

	// 雍和：埋一點羅城／雍和首相的傳聞（與設定相關，純氣氛）
	if( arg == "captain about 雍和"
	||  arg == "captain about 羅城"
	||  arg == "captain about yonghe"
	||  arg == "captain about luocheng" ) {
		do_chat(({
			(: command, "say 雍和大人麼 ... 那是當朝的首相﹐位高權重﹐尋常人哪輕易見得著。聽聞羅城那邊﹐近來頗有些與雍和大人相關的風聲。" :),
			(: command, "say 這等朝堂上的大事﹐豈是我這守港的武夫該議論的﹖客官若真有心打聽﹐往東北的羅城走一遭﹐興許能聽著些門道。我可甚麼都沒說。" :),
		}));
		return 1;
	}

	return notify_fail("劉開皺眉道﹕這個 ... 我一介武夫﹐答不上來。（試試 ask captain about 檒城）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 放肆﹗竟敢在我檒城衛兵所裡撒野﹖來人﹐給我拿下﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
