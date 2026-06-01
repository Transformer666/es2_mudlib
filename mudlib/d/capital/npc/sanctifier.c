// sanctifier.c -- 守木尊者，京畿神社聖木淨室中守木一脈的方外尊者，
//                 主線任務七「鎮邪求聖」的求聖（賜物）對象
//
// 故事背景（承接主線六「摩雲蹤跡」）：
//   隱居雪亭鎮的老獵王與天靈山麓的獸語者已道破﹕獸王摩雲受天靈山那縷邪念
//   牽動﹐退往天靈山麓蓄勢﹐欲制牠須得「破障同道」與「制邪聖物」。後海茶
//   館那位雲遊高僧精通鎮邪之道﹐遂指點少俠﹕三百年前那株被斷的聖木﹐其根
//   脈所鍾的一縷清正餘力至今猶蟄伏於京畿神社的聖木舊址﹐唯有自這縷餘力溫
//   養、開光而成的聖物﹐方能克制摩雲身上的邪念。高僧書一紙「淨木請帖」﹐
//   遣少俠往神龕後的聖木淨室求取。這位守木尊者﹐便是守木一脈中精擅開光淨
//   化之術的方外人﹐與京畿神社那位守木老者(shrinekeeper)同出一脈。
//
// 任務流程（旗標存在玩家身上：quest/main_omen7，由 d/capital/npc/monk.c 開啟）：
//   進行中 (1)  : 玩家持雲遊高僧的「淨木請帖」到聖木淨室
//                 交(give)給守木尊者 -> 尊者驗帖後收下﹐自聖木餘力中取出開光
//                 已成的「淨邪聖木牌」相贈﹐並把旗標推進為 2（推進在本檔）
//   已取得 (2)  : 玩家持聖木牌回後海茶館交(give)／問(ask)雲遊高僧驗訖領賞
//                 （推進 2->3 與領賞皆在 monk.c﹔聖木牌不收回、留與玩家決戰用）
//
// 注意：本 NPC 不開啟任務、不給賞、不收回聖物（開啟與領賞皆在 monk.c）﹐
//       只負責驗帖、收帖、賜聖物、推進旗標 1 -> 2。
//   收下信物（請帖）後不自行 destruct﹐由 give 指令將信物移入本 NPC（與
//   beasttalker／woodsman／shrinekeeper 一致）﹐並於旗標處作防重複推進。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("守木尊者", ({ "wood sage", "sage", "sanctifier" }) );
	set("nickname", "守木尊者");
	set_attr("int", 24);
	set_attr("wis", 26);
	set_attr("con", 20);
	set_race("human");
	set_class("commoner");
	set_level(16);
	set_skill("unarmed", 25);
	set_skill("dodge", 28);
	set_skill("force", 35);
	set_skill("literate", 40);

	set("gender", "male");
	set("age", 74);
	set("long",
		"一位趺坐在焦黑樹樁之側的方外尊者﹐鬚眉皆白﹐寶相莊嚴﹐一襲\n"
		"赭黃的僧袍纖塵不染。他闔目誦持﹐枯瘦的雙手結著一個古樸的手\n"
		"印﹐掌心隱隱托著一團那截聖木舊址透出的青芒﹐似在以那縷清正\n"
		"餘力溫養著甚麼。聽神社裡的人說﹐這位尊者與前殿掃灑的守木老\n"
		"者同出一脈﹐世代守的便是這截枯死的聖木﹐獨他精擅開光淨化、\n"
		"鎮壓邪念之術﹐尋常香客難得見他一面。\n"
		"你或許可以問問他﹕ask sanctifier about 聖物。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"守木尊者闔目誦持﹐掌心那團青芒明滅不定﹐口中梵唄低沉如遠雷。\n",
		"守木尊者喃喃道﹕聖木雖斷﹐餘力未絕 ... 這一縷清正﹐合該用在制那邪念上 ...\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen7");
		if( q == 1 )
			do_chat((: command,
				"say 這位少俠面生 ... 莫非是後海茶館那位高僧﹐遣來這淨室求取制邪聖物的﹖" :));
	}
}

// 主線七「鎮邪求聖」：把一面淨邪聖木牌交到玩家手上（先複製到自己身上，再 give 出去）
private void give_relic(object who)
{
	object relic;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	relic = new("/d/capital/npc/obj/holy_relic");
	relic->move(this_object());
	command("give holy relic to " + who->query("id"));
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg || (arg != "wood sage about 聖物"
		&&   arg != "wood sage about 摩雲"
		&&   arg != "wood sage about 聖木"
		&&   arg != "wood sage about 主線"
		&&   arg != "wood sage about 任務"
		&&   arg != "sage about 聖物"
		&&   arg != "sage about 聖木"
		&&   arg != "sanctifier about 聖物"
		&&   arg != "sanctifier about 摩雲"
		&&   arg != "sanctifier about 聖木"
		&&   arg != "sanctifier about 主線"
		&&   arg != "sanctifier about 任務"
		&&   arg != "wood sage about relic"
		&&   arg != "wood sage about quest"
		&&   arg != "wood sage about task") )
		return notify_fail("你想問這位尊者甚麼﹖（試試 ask sanctifier about 聖物）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("守木尊者正闔目誦持﹐溫養著掌心那縷聖木餘力﹐沒空理你。\n");

	// 尚未接主線七（旗標 <1）：不知來意﹐只道聖木舊事
	if( me->query("quest/main_omen7") < 1 ) {
		do_chat((: command,
			"say 這淨室所供﹐乃三百年前那株被斷聖木的舊址﹐根脈所鍾的一縷清正餘力﹐至今未散。然這制邪聖物干係重大﹐豈是逢人便授的﹖少俠若無高僧的請帖﹐老衲愛莫能助。" :));
		return 1;
	}

	// 進行中（旗標 1）：理應用 give 交付淨木請帖
	if( me->query("quest/main_omen7") == 1 ) {
		if( present("purify token", me) )
			do_chat((: command,
				"say 少俠那紙請帖 ... 老衲認得﹐是後海茶館那位高僧的手筆。少俠且把那帖子交(give)給老衲驗過﹐老衲自當為少俠取那制邪聖物。" :));
		else
			do_chat((: command,
				"say 少俠空口無憑﹐這制邪聖物老衲豈能輕授﹖少俠且回後海茶館﹐尋那位雲遊高僧討一紙『淨木請帖』來﹐老衲自有交代。" :));
		return 1;
	}

	// 已取得聖物（旗標 2 或更後）
	if( present("holy relic", me) )
		do_chat((: command,
			"say 那面淨邪聖木牌老衲已交與少俠了﹐快帶回後海茶館﹐請那位高僧驗過罷。切記﹐這聖物要一路帶在身邊﹐他日上天靈山制摩雲﹐全仗它護持。" :));
	else
		// 萬一玩家把聖物弄丟了，再溫養取出一面相贈
		do_chat(({
			"守木尊者搖頭一嘆﹐又佝僂著身子﹐到那焦黑樹樁邊小心翼翼自青芒中取出一面木牌。\n",
			(: command, "say 怎麼那聖木牌不見了﹖罷了﹐念在這聖物干係天下安危﹐老衲再以聖木餘力為少俠溫養一面。這回可要妥善收著了。" :),
			(: give_relic, me :),
		}));
	return 1;
}

// 收下信物：
//   淨木請帖(purify token) -- 主線七「鎮邪求聖」求聖﹐旗標 main_omen7 1 -> 2﹐賜給淨邪聖木牌
// 收下後不自行 destruct﹐由 give 指令將信物移入本 NPC（與 beasttalker／shrinekeeper 一致）﹐
// 並於旗標處作防重複推進。
int accept_object(object who, object ob)
{
	// 主線七：交付淨木請帖
	if( ob->id("purify token") ) {
		// 不是正在求聖的任務玩家（或已驗過）﹐仍收下避免卡物﹐但不重複推進
		if( who->query("quest/main_omen7") != 1 ) {
			do_chat((: command, "say 多謝少俠﹗" :));
			return 1;
		}

		who->set("quest/main_omen7", 2);
		do_chat(({
			(: command, "say 高僧的『淨木請帖』 ... 不錯﹐這梵印與字跡老衲認得。少俠隨老衲到這樹樁前來。" :),
			(: command, "say 少俠瞧見了麼﹖這截焦黑的老樹樁﹐便是三百年前那株鎮天地、封邪物的聖木被斷後所遺的舊址。木雖枯死﹐根脈所鍾的一縷清正餘力卻未全散——你看那斷口處的青芒﹐便是了。" :),
			(: command, "say 老衲守此一脈﹐獨擅開光淨化之術。前些時日已自這縷餘力中溫養、開光了一面淨邪聖木牌﹐專能護持人心、抵禦那自天靈山漫來的邪念。摩雲一脈之邪﹐皆源自天靈山那縷牽動百獸的邪念﹐唯有這聖物﹐方能破那山中重重邪障。" :),
			(: command, "say 這聖物老衲贈與少俠了。切記﹐它不是尋常物事﹐須得一路妥善帶在身邊——他日上天靈山與摩雲周旋﹐全仗它護持心神、破那邪障。少俠驗過﹐回去也好教那位高僧寬心。" :),
			(: give_relic, who :),
		}));
		return 1;
	}

	// 其餘物事：婉拒﹐不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 此乃清淨之地﹐老衲了無長物﹐這個受不起﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠息怒﹗老衲一個守木誦經的方外之人﹐與少俠無冤無仇哪。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
