// diviner.c -- 雲遊道人，掛單於雪亭鎮飲風客棧的異人，
//              主線任務五「群獸朝靈」的委託人與領賞人
//
// 故事背景（承接主線四「獸亂之兆」）：
//   京畿神社守木老者與老松林老獵戶道破﹕將潰的聖木封印放出邪念﹐勾得走
//   獸發狂﹐成群朝天靈山而去——這是動物war的序章。這位雲遊道人本是隱於
//   市井的異人﹐多年來循著天靈山悔天鬼那縷邪念的牽動四海漂泊﹐近日輾轉
//   來到雪亭鎮飲風客棧掛單。他掐指推得﹕這滿山發狂的走獸﹐皆聽命於一頭
//   蟄伏荒野、喚作摩雲的獸王﹐而摩雲之亂﹐正是動物war的先聲。道人欲查實
//   群獸朝靈的去向﹐遂託這位循著聖木舊案一路追來、已知獸亂源頭的少俠﹐
//   持他親畫的觀獸符往老松林深處勘察﹐帶回群獸朝靈的實證。
//
// 任務流程（旗標存在玩家身上：quest/main_omen5）：
//   入門條件     : 須先完成主線四（quest/main_omen4 >= 3）﹐否則只喃喃推算﹐不開任務
//   未開始 (0)   : 玩家 ask diviner about 群獸 -> 道人交付「觀獸符」﹐旗標設為 1
//   進行中 (1)   : 玩家持觀獸符到老松林深處﹐交(give)給守山人(/d/hudao/npc/woodsman)
//                  守山人驗符後收下﹐道出群獸朝天靈山遷徙、獸王摩雲的影子﹐
//                  回給「獸群遷徙圖」﹐並把旗標推進為 2（推進在 woodsman.c）
//   已取得 (2)   : 玩家把遷徙圖帶回飲風客棧交(give)給雲遊道人 -> 領賞(give_reward)﹐旗標設為 3
//   已完成 (3)   : 不再重複給賞﹐do_ask 給出朝向摩雲／混沌珠／天靈山悔天鬼一段的純劇情伏筆

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("雲遊道人", ({ "wandering taoist", "taoist", "diviner", "yunyou" }) );
	set("nickname", "雲遊道人");
	set_attr("int", 23);
	set_attr("wis", 25);
	set_race("human");
	set_class("commoner");
	set_level(14);
	set_skill("unarmed", 20);
	set_skill("dodge", 25);
	set_skill("force", 30);
	set_skill("literate", 40);

	set("gender", "male");
	set("age", 58);
	set("long",
		"一位掛單在飲風客棧的雲遊道人﹐一身洗得發白的青布道袍﹐風塵\n"
		"僕僕﹐背上斜插一柄拂塵﹐腰間掛著個盛著籤筒與羅盤的舊布囊。\n"
		"他不似尋常賣卦的江湖術士那般招搖﹐只揀了客棧角落一張靜處的\n"
		"桌子﹐時而閉目掐指﹐時而就著燈火翻檢一卷捲了邊的舊圖。聽客\n"
		"棧的人說﹐這道長走南闖北﹐專愛追查些天地間的怪兆異事。這幾\n"
		"日他屢屢望向北面天靈山的方向﹐眉宇間鎖著化不開的憂色。\n"
		"你或許可以問問他﹕ask diviner about 群獸。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"雲遊道人閉目掐指﹐良久﹐輕輕嘆了口氣﹐又望向北面天靈山的方向。\n",
		"雲遊道人喃喃道﹕群獸朝靈﹐其首曰摩雲 ... 此乃大亂之兆啊 ...\n",
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
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 少俠﹐老松林深處那一趟﹐群獸朝靈的去向﹐可勘出名堂了麼﹖" :));
		else if( !q && this_player()->query("quest/main_omen4") >= 3 )
			do_chat((: command,
				"say 少俠身上 ... 竟也沾著一縷天靈山的氣息﹖看來你我追的﹐是同一樁禍事。" :));
	}
}

// 把一道觀獸符交到玩家手上（先複製到自己身上，再 give 出去）
private void give_ward(object who)
{
	object ward;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	ward = new("/d/snow/npc/obj/beast_ward");
	ward->move(this_object());
	command("give beast ward to " + who->query("id"));
}

// 領賞：給一串銅錢、一帖傷藥﹐並授存活、俠義之舉、聲望與旅行見聞
private void give_reward(object who)
{
	object coin, pill;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(400);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/aquapill");
	if( !pill->move(who) ) pill->move(environment());

	who->gain_score("survive", 400);
	who->gain_score("emprise", 150);
	who->gain_score("reputation", 80);
	who->gain_score("explorer fame", 50);

	message_vision(
		"雲遊道人將那幅遷徙圖在燈下反覆推詳﹐臉色越發凝重﹐末了自布囊裡"
		"取出一串銅錢與一帖金液丹﹐鄭重地交到$N手裡。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "diviner about 群獸"
		&&   arg != "diviner about 摩雲"
		&&   arg != "diviner about 主線"
		&&   arg != "diviner about 任務"
		&&   arg != "taoist about 群獸"
		&&   arg != "taoist about 摩雲"
		&&   arg != "wandering taoist about 群獸"
		&&   arg != "wandering taoist about 摩雲"
		&&   arg != "diviner about quest"
		&&   arg != "diviner about task") )
		return notify_fail("你想問這位道人甚麼﹖（試試 ask diviner about 群獸）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("雲遊道人正閉目掐指推算著甚麼﹐沒空理你。\n");

	// 入門條件：須先完成主線四「獸亂之兆」
	if( me->query("quest/main_omen4") < 3 ) {
		do_chat(({
			(: command, "say 少俠面生 ... 也罷。天機渺渺﹐老道掐指算得這滿山走獸發狂﹐其後必有大亂﹐只是這亂從何起、根在何處﹐少俠若一無所知﹐老道與你說了也是枉然。" :),
			(: command, "say 少俠若真覺出這天地間的異兆﹐倒不如先去尋那些追查舊案的明白人——聽說封山派與京畿神社那邊﹐有人專管這等怪事。待你查清了獸亂的根由﹐再來尋老道罷。" :),
		}));
		return 1;
	}

	q = me->query("quest/main_omen5");

	// 主線五已全部完成：收尾、加深朝向摩雲／混沌珠／天靈山悔天鬼一段的伏筆（純劇情，不開任務）
	if( q >= 3 ) {
		do_chat(({
			(: command, "say 多虧少俠走這一趟﹐那幅遷徙圖老道已參詳明白——這滿山走獸﹐確是聽命於那頭喚作摩雲的獸王﹐齊齊朝天靈山而去。摩雲一動﹐這場動物war﹐便算是揭了序幕了。" :),
			(: command, "say 然摩雲不過是頭被驅策的猛獸罷了。真正勾動牠的﹐是天靈山深處那頭悔天鬼——三百年前斷木放出的邪物。老道追查多年﹐曉得那悔天鬼還連著一顆喚作『混沌珠』的至邪之物﹐珠在何處﹐這場禍事的死結便在何處。" :),
			(: command, "say 摩雲在前﹐其後尚有摩雲一脈、骨屍妖王、鬼王噬魂之輩﹐層層守著那混沌珠的下落﹐皆是衝著天靈山悔天鬼而來。老道一介方外之人﹐推得出天機﹐卻擋不住這場浩劫。少俠是有大氣運的人﹐這條追兇之路﹐往後還要靠你一步步走下去。" :),
		}));
		return 1;
	}

	// 已取得遷徙圖，回來交付（理應用 give 交付，這裡只作提示）
	if( q == 2 ) {
		if( present("beast trail", me) )
			do_chat((: command,
				"say 老松林深處那一趟有著落了罷﹖快把那幅獸群遷徙圖交(give)給老道參詳﹗" :));
		else
			do_chat((: command,
				"say 咦﹐那幅遷徙圖呢﹖少俠莫不是弄丟了﹖快回老松林深處﹐尋那守山人補繪一幅。" :));
		return 1;
	}

	// 任務進行中（已領觀獸符，還沒回來）
	if( q == 1 ) {
		if( present("beast ward", me) )
			do_chat((: command,
				"say 那道觀獸符少俠帶在身上了。出客棧往廣場去﹐自廣場南行出草棚﹐"
				"再往南便入了老松林﹐自老松林再往東﹐深處有位守山人——把符交(give)給他﹐自能勘出群獸朝靈的去向。" :));
		else
			// 萬一玩家把觀獸符弄丟了，補一道給他
			do_chat(({
				"雲遊道人搖頭一笑﹐又自布囊裡取出黃紙朱砂﹐重新畫就一道觀獸符。\n",
				(: command, "say 怎麼那符不見了﹖罷了﹐老道再與少俠畫一道便是﹐這回可收好了。" :),
				(: give_ward, me :),
			}));
		return 1;
	}

	// 尚未接任務：交付觀獸符，旗標設為 1
	me->set("quest/main_omen5", 1);
	do_chat(({
		(: command, "say 少俠既已查明這獸亂的根由﹐老道便不瞞你。老道雲遊四海數十年﹐追的便是天靈山那縷邪念的牽動——這幾日掐指推算﹐這滿山發狂的走獸﹐竟都聽命於一頭蟄伏荒野的獸王。" :),
		(: command, "say 那獸王喚作摩雲﹐生具懾服百獸之能。聖木封印一鬆﹐天靈山悔天鬼的邪念漫出﹐摩雲便受其驅策﹐召得百獸朝天靈山而去——這群獸朝靈﹐便是那場動物war的序幕啊。" :),
		(: command, "say 然天機渺渺﹐老道推得出摩雲之亂﹐卻看不真切群獸遷徙的實在去向。老道這裡有一道親畫的觀獸符﹐能感應走獸身上那縷戾氣。少俠可願持符往老松林深處走一遭﹐尋那守山人勘明群獸朝靈的去向﹐帶回實證來﹖" :),
		(: command, "say 切記﹕到了老松林深處﹐須把這符交(give)給那守山人﹐他自會將勘下的去向告知少俠。此事干係天下安危﹐萬望少俠謹慎﹗" :),
		(: give_ward, me :),
	}));
	return 1;
}

// 收下信物：
//   獸群遷徙圖(beast trail) -- 主線五「群獸朝靈」交還﹐旗標 main_omen5 2 -> 3﹐領賞(give_reward)
// 收下後不自行 destruct﹐由 give 指令將信物移入本 NPC（與 hunter／shrinekeeper 一致）﹐
// 並於最終旗標處作防重複領獎。
int accept_object(object who, object ob)
{
	// 主線五：交還獸群遷徙圖
	if( ob->id("beast trail") ) {
		// 已領過賞（旗標已 >=3）：道謝收下﹐不重複給賞
		if( who->query("quest/main_omen5") >= 3 ) {
			do_chat((: command, "say 那幅遷徙圖老道早已收訖﹐正日夜參詳著﹐多謝少俠跑這一趟了﹗" :));
			return 1;
		}
		// 尚未進行到交付這一步（旗標不為 2）：仍收下避免卡物﹐但不推進、不給賞
		if( who->query("quest/main_omen5") != 2 ) {
			do_chat((: command, "say 多謝少俠﹗" :));
			return 1;
		}

		who->set("quest/main_omen5", 3);
		do_chat(({
			(: command, "say 這便是群獸朝靈的去向麼 ... 嘶﹗少俠瞧這獸徑的脈絡﹐百川歸海﹐齊指天靈山——還有這團黑影﹐果然是摩雲。老道推算多時﹐今日總算坐實了。" :),
			(: give_reward, who :),
			(: command, "say 這點銅錢與丹藥﹐少俠收著防身。少俠肯為這天下蒼生涉險勘察﹐老道這方外之人﹐承你的情了﹗" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒﹐不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 老道雲遊之人﹐了無長物﹐這個受不起﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠息怒﹗老道一個雲遊的方外之人﹐與少俠無冤無仇哪。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
