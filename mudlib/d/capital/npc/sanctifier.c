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
// 注意：本 NPC（就主線七而言）不開啟任務、不給賞、不收回聖物（開啟與領賞皆在
//       monk.c）﹐只負責驗帖、收帖、賜聖物、推進旗標 1 -> 2。
//   收下信物（請帖）後不自行 destruct﹐由 give 指令將信物移入本 NPC（與
//   beasttalker／woodsman／shrinekeeper 一致）﹐並於旗標處作防重複推進。
//
// ════════════════════════════════════════════════════════════════════════════
// 正史主線第四章「蜈蚣war」：守木尊者即本章委託人與領賞人
// ════════════════════════════════════════════════════════════════════════════
//   故事背景（承接第三章 huitiangui/summit.c：天靈絕巔古碑揭出——斷京畿聖木、致
//     悔天鬼邪念外溢的真兇﹐乃其下盤蟠京畿地脈、蝕聖木之節以自肥的巨蜈）：
//     守木尊者守此聖木一脈、深知聖木殘節通連京畿地脈之祕。少俠既了結悔天鬼
//     (quest/main_canon3_done)﹐尊者便認出這位悔天鬼-slayer﹐道破那盤蟠京畿地脈、
//     蝕聖木殘節的巨蜈之患﹐並自淨室聖木舊址取出守木一脈密藏的鎮山聖劍『穿靈』
//     (npc/obj/chuanling)﹐託少俠持之降京畿地下、斫斷那為巨蜈所蝕的聖木殘節、了
//     結那蝕節的巨蜈。
//
//   任務流程（旗標存在玩家身上：quest/main_canon4 (0→1→2→3) + 防重領 quest/main_
//     canon4_done﹔另以 quest/main_canon4_nodes 計砍斷的聖木節數）。入門條件：須先
//     完成第三章(quest/main_canon3_done >= 1)。流程鏡前三章之 proven 機制：
//     0          : 接任務 -> 尊者認出悔天鬼-slayer﹐道破巨蜈蝕聖木殘節之患﹐clone
//                  聖劍穿靈交還玩家(give_chuanling)﹐命少俠自淨室石階降京畿地下﹐
//                  旗標設為 1（並開 sanctum.c 樹樁石階之門禁：須 main_canon4 >= 1）
//     1          : 已降地下﹐命斫斷聖木殘節——玩家持穿靈於聖木殘節密室(saintroot.c)
//                  逐節『砍』那三節聖木節(saintwood_node.c)﹐三節盡斷由 saintwood_
//                  node.c 推進旗標 1->2（巨蜈為斷節所驚、自蜈穴竄出﹐蜈穴洞開）
//     2          : 已斫斷聖木節、巨蜈現身﹐命入蜈穴(wuxue.c)了結巨蜈 -> 由 giant_
//                  centipede.c::die() 推進旗標 2->3﹐並自巨蜈屍身掉落交差信物「聖
//                  木殘根」+「破碎的印記」
//     3          : 持聖木殘根 + 破碎的印記回淨室交差 -> 同步交付 give_reward4()、記
//                  main_canon4_done﹔對白為蜈蚣war作結(聖木殘節淨化/巨蜈除)﹐並直
//                  接接引下一段「四鬼任務」(赤魈/青蛛/濁魚/旱魃)
//     _done      : 蜈蚣war已竟——只給朝向四鬼任務的純劇情伏筆﹐不重複給賞、不開新任務
//   LORE-RESOLVED：本章「蜈蚣war」諸元（穿靈/京畿地下/砍聖木節/巨蜈/聖木殘根/破碎
//     的印記/四鬼）逕用 docs 主線樹(05 L45-48)所載之名﹐非 villain-name-gated﹐故
//     明點。破碎的印記即 docs 所載、四神arc 將需湊全的「broken seal」之一(L52-54)。
//   給賞為同步交付（於 do_ask handler 內直接 new+move﹐且在記 _done 旗標之前）﹐絕
//     不放進延遲 do_chat closure——免玩家於回呼前離場致賞沒領而卡關（前三章習得之
//     教訓：延遲領賞會 soft-lock）。穿靈/聖木殘根/破碎的印記玩家若改以 give 交付﹐
//     尊者皆不收下（回 0、信物留玩家身上）﹐只提示改用 ask。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void give_chuanling(object who);
private void give_reward4(object who);

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
		// 第四章「蜈蚣war」招呼（須先完成第三章）——依第四章旗標(main_canon4)給對應
		// 提示。招呼一律走單一 do_chat（is_chatting 期間 do_ask 早退、待招呼畢方應）。
		if( this_player()->query("quest/main_canon3_done") ) {
			int q4 = this_player()->query("quest/main_canon4");
			if( this_player()->query("quest/main_canon4_done") )
				do_chat((: command,
					"say 是少俠﹗那蝕聖木的巨蜈既除﹐這京畿地脈﹐總算是安穩了。只是那四方為禍的鬼祟——赤魈、青蛛、濁魚、旱魃﹐怕又是一場硬仗啊。" :));
			else if( q4 == 3 )
				do_chat((: command,
					"say 少俠把那巨蜈了結了麼﹖快將那聖木殘根與破碎的印記拿來給老衲——ask sanctifier about 蜈蚣。" :));
			else if( q4 == 2 )
				do_chat((: command,
					"say 少俠既斫斷了那聖木殘節、驚得巨蜈現身﹐便入那蜈穴﹐持穿靈了結那蝕節的孽蜈罷﹗" :));
			else if( q4 == 1 )
				do_chat((: command,
					"say 少俠持了那柄穿靈﹐便自這樹樁之側的石階往下(down)降京畿地下﹐尋那為巨蜈所蝕的聖木殘節罷——切記須持穿靈﹐方斫得斷那聖木之節﹗" :));
			else
				do_chat((: command,
					"say 少俠便是上天靈絕巔、了結了那悔天鬼的少俠罷﹖老衲恭候多時了——絕巔古碑揭出的那樁更大的禍事﹐少俠可要聽老衲細說﹖ask sanctifier about 蜈蚣。" :));
			return;
		}

		if( this_player()->query("quest/main_omen7") == 1 )
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

// 第四章「蜈蚣war」接任務：自淨室聖木舊址取出守木一脈密藏的鎮山聖劍『穿靈』
// (npc/obj/chuanling)交還玩家。此劍為斫斷聖木殘節之鑰。who=接任務的玩家﹔同步交付
// （於 do_ask handler 內直接 new+move﹐玩家此刻必在場）。防重複發劍：玩家若已持有
// 穿靈﹐不再重發。
private void give_chuanling(object who)
{
	object sword;

	if( !who || environment(who) != environment() ) return;

	// 防重複發劍。
	if( present("chuanling", who) ) return;

	sword = new(__DIR__"obj/chuanling");
	if( !sword->move(who) ) sword->move(environment());

	message_vision(
		HIY "守木尊者起身踱至那截焦黑的樹樁之後﹐自一方塵封的暗格中﹐雙手"
		"捧出一柄青中泛玄、半木半鐵的古劍。他以聖木餘力的青芒拂拭劍身﹐那"
		"劍脊年輪般的紋路霎時幽幽亮起﹐一縷清正而沉雄的靈氣自劍中漫出。尊"
		"者將這柄『穿靈』聖劍鄭重交到$N手裡。\n" NOR, who);
}

// 第四章「蜈蚣war」交差領賞（arc 終局決戰之賞——蝕聖木、亂京畿地脈的禍根斷絕）：
// 較第三章 give_reward3 同檔之厚賞。銅錢 1600、金液丹一帖、並一柄續命金丹﹐並授冠
// 絕之聲望/內丹(score)等閱歷。同步交付——於 do_ask handler 內直接呼叫（環境校驗在
// 前）。聖木殘根/破碎的印記為交差信物﹐尊者驗訖即還、不收回（破碎的印記尤須留與玩
// 家﹐為日後四神/渾沌印記之線索鋪路）。
private void give_reward4(object who)
{
	object coin, pill, pill2;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(1600);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/aquapill");
	if( !pill->move(who) ) pill->move(environment());

	pill2 = new("/obj/medication/alchemist/major_heal_pill");
	if( !pill2->move(who) ) pill2->move(environment());

	// 聲望/內丹(score) boost：與第三章 give_reward3 同檔（arc 終局決戰）。
	who->gain_score("survive", 3000);
	who->gain_score("emprise", 1000);
	who->gain_score("reputation", 600);
	who->gain_score("martial fame", 560);
	who->gain_score("explorer fame", 260);

	message_vision(
		HIY "守木尊者自$N手中接過那截聖木殘根﹐以掌心聖木餘力的青芒緩緩裹住、"
		"溫養——只見那為巨蜈蝕得焦黑將枯的殘根﹐斷口處的青芒竟一分一分地重新明"
		"亮了起來。尊者神色欣慰而肅穆﹐自懷中取出一串沉甸甸的銅錢、兩帖丹藥﹐"
		"鄭重交到$N手裡﹐又以指尖在$N眉心一點﹐傳了一縷溫養精氣的內丹真意。那"
		"枚破碎的印記﹐尊者卻又還回$N手中﹐道是『他日另有大用』。\n" NOR, who);
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
		&&   arg != "wood sage about task"
		// 第四章「蜈蚣war」topics（穿靈/巨蜈/聖木殘節 等，非 villain-name-gated）
		&&   arg != "sanctifier about 蜈蚣"
		&&   arg != "sanctifier about 巨蜈"
		&&   arg != "sanctifier about 穿靈"
		&&   arg != "sanctifier about 聖木殘節"
		&&   arg != "sanctifier about 聖木節"
		&&   arg != "sanctifier about 聖木殘根"
		&&   arg != "sanctifier about 印記"
		&&   arg != "sanctifier about 四鬼"
		&&   arg != "wood sage about 蜈蚣"
		&&   arg != "wood sage about 巨蜈"
		&&   arg != "wood sage about 穿靈"
		&&   arg != "wood sage about 聖木殘節"
		&&   arg != "wood sage about 聖木殘根"
		&&   arg != "sage about 蜈蚣"
		&&   arg != "sage about 穿靈"
		&&   arg != "sanctifier about centipede"
		&&   arg != "sanctifier about chuanling"
		&&   arg != "wood sage about centipede") )
		return notify_fail("你想問這位尊者甚麼﹖（試試 ask sanctifier about 聖物）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("守木尊者正闔目誦持﹐溫養著掌心那縷聖木餘力﹐沒空理你。\n");

	// ════════════════════════════════════════════════════════════════════
	// 正史第四章「蜈蚣war」：須先完成第三章(quest/main_canon3_done >= 1)﹐守木尊者
	// 即由主線七賜物人轉為第四章委託人與領賞人。旗標 quest/main_canon4 (0→1→2→3) +
	// 防重領 quest/main_canon4_done。流程鏡前三章之 proven 機制（見檔頭詳述）：
	//   0   : 接任務 -> 認出悔天鬼-slayer、道破巨蜈蝕聖木殘節之患﹐clone 穿靈交還
	//         (give_chuanling)﹐命降京畿地下﹐旗標設為 1（開 sanctum.c 石階門禁）
	//   1   : 已降地下﹐命持穿靈斫斷聖木殘節 -> 三節盡斷由 saintwood_node.c 推進為 2
	//   2   : 巨蜈現身﹐命入蜈穴了結巨蜈 -> 由 giant_centipede.c::die() 推進為 3﹐
	//         並自巨蜈屍身掉落「聖木殘根」+「破碎的印記」
	//   3   : 持二物回淨室交差 -> 同步交付 give_reward4()、記 main_canon4_done﹔對白
	//         為蜈蚣war作結﹐並接引下一段「四鬼任務」(赤魈/青蛛/濁魚/旱魃)
	//   _done : 蜈蚣war已竟——只給朝向四鬼任務的純劇情伏筆﹐不重複給賞、不開新任務
	// 此塊置於主線七邏輯之前﹐就 main_canon3_done 把關﹔未及第四章者落入下方主線七
	// 既有邏輯﹐互不干涉。
	// ════════════════════════════════════════════════════════════════════
	if( me->query("quest/main_canon3_done") ) {
		int q4 = me->query("quest/main_canon4");

		// 第四章已交差領賞（main_canon4_done）：蜈蚣war已竟——只給朝向四鬼任務的純
		// 劇情伏筆(赤魈/青蛛/濁魚/旱魃)﹐不重複給賞、不開新任務。
		if( me->query("quest/main_canon4_done") ) {
			do_chat(({
				(: command, "say 那盤蟠京畿地脈、蝕聖木之節的巨蜈既為少俠所誅﹐這株鎮天地的聖木殘節得以重歸淨室溫養﹐京畿一域的地脈﹐總算是調順安穩了。斷京畿聖木、致那悔天鬼邪念外溢的禍根﹐至此方算真個斷絕——少俠這一場蜈蚣之戰﹐功在社稷蒼生。" :),
				(: command, "say 只是 ... 老衲溫養那破碎的印記時﹐自殘印僅存的封印之力中﹐窺見了一樁更深的隱憂。那聖木之節既為巨蜈蝕斷﹐當年布在京畿地脈、鎮鎖那縷至邪邪念的數方神印便已殘破——封印一鬆﹐其下封鎮的四方為禍的鬼祟﹐怕是要應劫而出了。" :),
				(: command, "say 那是四方亙古的厲鬼——赤魈、青蛛、濁魚、旱魃。牠們各據一方水土﹐借那殘破的封印之隙蠢蠢欲動。少俠且養精蓄銳：尋那卯天樹下開啟封印的門道﹐逐一了結這四鬼之患——這破碎的印記少俠須好生收著﹐他日湊全諸方殘印、會同四方神祇之力﹐另有大用。這﹐又是一場接一場的硬仗了。" :),
			}));
			return 1;
		}

		// 第四章已誅巨蜈（旗標 3）：理應持聖木殘根 + 破碎的印記回來交差領賞
		if( q4 == 3 ) {
			if( present("saintwood root", me) && present("broken seal", me) ) {
				// 同步給賞、即記 _done（give_reward4 為直接 new+move﹐玩家此刻必在場）。
				// 不把給賞放進延遲 do_chat——免玩家於回呼前離場致賞沒領而卡關。
				give_reward4(me);
				me->set("quest/main_canon4_done", 1);
				do_chat(({
					(: command, "say 少俠把那聖木殘根與破碎的印記給老衲 ... 唔﹗這殘根雖為巨蜈蝕得焦黑﹐根脈最深處那一縷清正餘力竟還未斷絕——好﹗那盤蟠地脈、蝕節三百年的巨蜈﹐當真為少俠所誅了﹗" :),
					(: command, "say 這截殘根﹐老衲這便以聖木餘力溫養復甦﹔聖木殘節既不再為孽蜈所蝕﹐這京畿地脈所養的聖木一脈﹐方有重續之望。少俠斷那禍根、淨那地脈﹐這份功德﹐老衲必稟明守木一脈、記在少俠名下。" :),
					(: command, "say 這串銅錢、這兩帖丹藥﹐是老衲的一點心意﹐少俠萬莫推辭。只是這枚破碎的印記﹐老衲卻要還與少俠——它原是當年鎮京畿地脈、封那邪念的數方神印之一﹐如今封印既鬆﹐其下封鎮的四方厲鬼：赤魈、青蛛、濁魚、旱魃﹐怕是要應劫而出了。少俠且好生收著這殘印﹐尋那卯天樹下開啟封印的門道﹐去了結那四鬼之患罷——這條路﹐怕還長著呢。" :),
				}));
			}
			else
				do_chat((: command,
					"say 少俠不是說那巨蜈伏誅之際﹐自牠軀節間滾落了一截聖木殘根、一枚破碎的印記麼﹖那殘根是復甦聖木的根本﹐那印記他日另有大用﹐萬不可遺落在那蜈穴之中——快回蜈穴﹐自巨蜈屍身中尋了那聖木殘根與破碎的印記來給老衲。" :));
			return 1;
		}

		// 第四章已斫斷聖木節、巨蜈現身（旗標 2）：提示入蜈穴了結巨蜈
		if( q4 == 2 ) {
			do_chat((: command,
				"say 少俠斫斷了那三節為巨蜈所蝕的聖木殘節﹐驚得那蝕節的孽蜈自蜈穴竄出了罷﹖那巨蜈便是斷京畿聖木、致悔天鬼邪念外溢的真兇——少俠且持穿靈入那蜈穴﹐了結了這條盤蟠地脈三百年的孽蜈。斷了牠﹐這蝕木亂脈的禍根﹐方算真個斷絕。" :));
			return 1;
		}

		// 第四章進行中（旗標 1）：提示去向（持穿靈降地下、砍聖木殘節）
		if( q4 == 1 ) {
			do_chat((: command,
				"say 少俠持了那柄穿靈聖劍﹐便自這樹樁之側的石階往下(down)﹐循聖木根脈降入京畿地下——過神社地窖、入京畿地脈﹐尋至那聖木殘節密室。那聖木之節堅逾精鐵、凡刀不能傷﹐少俠須先持穿靈、握在手中(wield chuanling)﹐再逐節『砍』斷那為巨蜈所蝕的聖木殘節。三節盡斷﹐那蝕節的巨蜈自會現身。" :));
			return 1;
		}

		// 尚未接第四章（旗標 0）：認出悔天鬼-slayer、道破巨蜈之患﹐clone 穿靈交還﹐
		// 命降京畿地下﹐旗標設為 1。砍節計數歸零（穩健起見﹐防任何重玩殘值）。
		give_chuanling(me);
		me->set("quest/main_canon4_nodes", 0);
		me->set("quest/main_canon4", 1);
		do_chat(({
			(: command, "say 少俠便是持淨邪鎮魂印登天靈絕巔、了結了那悔天鬼的少俠罷﹖老衲守此聖木一脈﹐絕巔的訊息﹐早已隨地脈傳到了這淨室。少俠了結那獸亂之源、平了綿延三百年的獸亂﹐當真是功在天下——只是那絕巔古碑揭出的禍事﹐老衲卻是比誰都明白的。" :),
			(: command, "say 斷這株京畿聖木的﹐並非悔天鬼一鬼——實為其下那條盤蟠京畿地脈、蝕聖木之節以自肥的巨蜈﹗聖木有節﹐節節通連天下地脈﹔那巨蜈三百年來纏蝕聖木殘節、攫食地脈靈氣﹐愈長愈巨。悔天鬼的邪念﹐不過是那巨蜈蝕節時溢出地表的餘毒罷了。這蝕木亂脈的真兇一日不除﹐這天下的禍根便一日不算斷絕。" :),
			(: command, "say 然那聖木之節深蟠地脈之下、堅逾精鐵﹐尋常刀兵斫之難傷分毫。所幸老衲守木一脈﹐世代密藏著一柄鎮山的聖劍——它以那株聖木最堅韌的一段心節為胎、外覆玄鐵鑄鋒﹐專能斫斷聖木之節、穿透其所鍾的清正靈氣﹐故名『穿靈』。老衲這便將它取出﹐交與少俠。" :),
			(: command, "say 少俠持這柄穿靈﹐自這樹樁之側的石階往下(down)﹐循聖木深蟠的根脈降入京畿地下——過神社地窖、京畿地脈﹐尋至那聖木殘節密室﹐持穿靈砍斷那為巨蜈所蝕的聖木殘節。三節盡斷﹐那蝕節的巨蜈自會現身﹔了結了牠﹐速持那聖木殘根回這淨室來尋老衲。此去地脈深險、巨蜈兇悍﹐萬望少俠珍重﹗" :),
		}));
		return 1;
	}

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

	// 第四章「蜈蚣war」：交差走 ask-path 為主（ask sanctifier about 蜈蚣）。玩家若改
	// 以 give 交付聖木殘根/破碎的印記/穿靈﹐尊者皆不收下（回 0、信物留玩家身上）﹐只
	// 提示改用 ask——既不吞信物、亦不誤收聖劍﹐領賞邏輯集中於 do_ask 一處。
	if( ob->id("saintwood root") || ob->id("broken seal") ) {
		do_chat((: command, "say 這聖木殘根與破碎的印記乾係重大﹐少俠且收好、莫遞來遞去——口頭與老衲說一聲便是﹕ask sanctifier about 蜈蚣﹐老衲自當為少俠溫養那殘根、定奪這印記。" :));
		return 0;
	}
	if( ob->id("chuanling") ) {
		do_chat((: command, "say 這柄穿靈聖劍是老衲託付與少俠斫斷聖木殘節、了結巨蜈用的﹐少俠須隨身帶著、握在手中方斫得斷那聖木之節——快收回去罷﹗" :));
		return 0;
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
