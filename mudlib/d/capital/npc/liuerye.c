// liuerye.c -- 劉二爺 (Jeweller liu)，吏部尚書府深居簡出的珠寶匠，
//              支線「珠寶匠的冥王寶戒」之委託人兼賜物人。
//
// 故事背景（依 docs 05 L114「劉二爺 (Jeweller liu) @ 尚書府 → 給冥王寶戒」；
//   並接 docs 05 L126「凌筠語 換闇之魔戒 (str+5)」之同類魔戒設定）：
//   這位劉二爺，是吏部尚書府後院一間僻靜耳房裡的老珠寶匠。尚書府門第顯赫、
//   珠翠成山，府裡上上下下的釵環玉墜、印鈕綬帶，幾十年來都出自他這雙枯瘦的
//   手。然他一生琢玉無數，獨有一件得意之作秘不示人——一塊不知得自何處、沁骨
//   生寒的玄黑寒鐵，與一顆其中幽幽轉著血芒的『冥王石』。他費了半生心血，將
//   這死氣凝成的冥王石琢成一枚『冥王寶戒』，戒中煉著一縷馭使陰煞、催發拙力
//   的冥王之力。只是這沉冥之力非有膽魄者不能駕馭，劉二爺琢成多年，遍尋不著
//   個堪受此物的人——他常說，這戒不是賣的，是要『等』一個人的。
//
// 支線流程（旗標存於玩家身上：quest/sq_liuerye；防重領）：
//   * 委託/賜物走 ask-path：玩家 ask liuerye about 冥王寶戒（亦容 寶戒/冥王/魔戒
//     等同義 topic、及英文 ring/quest）。劉二爺認得這位在江湖上闖出名號的少俠，
//     願將這枚等了多年的冥王寶戒相授——但他是個珠寶匠，這枚戒的鑲工、開光，須
//     得少俠出一筆『琢戒的工本』(50 金的玄鐵琢磨之費)，他方肯動手成全。
//   * 玩家身上備足工本(can_afford)，再 ask 一次 → 同步交付：pay_money 扣款 → 直接
//     new+move 冥王寶戒予玩家 → 記 quest/sq_liuerye=1（旗標於交付之後設、且 give
//     為同步 new+move——絕不放進延遲 do_chat closure，免玩家於回呼前離場致戒沒領
//     而 soft-lock，本專案頭號 bug class）。
//   * 防重領：quest/sq_liuerye>=1 或玩家身上已有冥王寶戒(present)→ 只給氣氛對白、
//     不重複收費、不重複發戒（雙重保險：旗標 + present 查找）。
//
// 入門條件（gate，可玩、wizard 可滿足）：須備琢戒工本 50 金(=500000 文之值)。
//   wizard 驗證：clone /obj/money/coin; call coin->set_amount(500000); 即可滿足。
//   gate 取「珠寶匠收工本」之合理設定（鏡 docs 鍾豪收禮金 10g 之 gold-gate 範式），
//   而非門派/主線旗標——支線可獨立完成、不依賴他檔旗標。
//
// 注意：本 NPC 自訂 do_ask（add_action "ask"），依 lesson #11「定義自訂 init/action
//   的 NPC 斷不 replace_program」——故本檔【不】replace_program。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

#define RING_FEE	500000		// 琢戒工本：50 金(=500000 文之值)

int do_ask(string arg);
private void give_ring(object who);

void create()
{
	set_name(HIR "劉二爺" NOR, ({ "liuerye", "jeweller liu", "jeweller", "liu" }) );
	set("nickname", "劉二爺");
	set_attr("str", 14);
	set_attr("int", 24);
	set_attr("dex", 22);
	set_attr("con", 16);
	set_race("human");
	set_class("commoner");
	set_level(11);
	set_skill("unarmed", 18);
	set_skill("dodge", 20);
	set_skill("literate", 30);
	set_skill("craft", 40);

	set("gender", "male");
	set("age", 67);
	set("long",
		"一位枯瘦矮小的老者，便佝僂著背坐在尚書府後院一間僻靜耳房的窗\n"
		"下。他一身洗得發白的青布短褐，袖口磨出了毛邊，鼻梁上架著一副\n"
		"水晶磨成的老花鏡，鏡片後一雙眼睛卻精光內斂、亮得驚人。他指間\n"
		"捻著一柄極細的玉銼，就著一線天光，正一絲不苟地琢磨著掌心一件\n"
		"瑩潤的玉飾——那雙手枯瘦如柴、青筋畢露，運起銼來卻穩如磐石，半\n"
		"分也不見顫。尚書府裡的釵環玉墜、印鈕綬帶，幾十年來都出自他這\n"
		"雙手。聽府裡的下人說，這位劉二爺的眼界與手藝，便是放眼整座京\n"
		"畿城，也是數一數二的；只是他性子孤介，深居簡出，等閒不肯為人\n"
		"動手。\n"
		"你或許可以問問他：ask liuerye about 冥王寶戒。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"劉二爺就著天光，捻著玉銼一絲不苟地琢磨著掌心的玉飾，半晌也不抬頭。\n",
		"劉二爺對著光眯眼端詳手中玉飾，低聲自語道：差之毫釐，便是天淵之別了 ...\n",
		"劉二爺枯瘦的手指拂過案頭一個烏沉沉的小木匣，眼底掠過一絲說不清的神色，旋即又埋首琢玉。\n",
	}));
	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_ask", "ask");

	if( this_player() && interactive(this_player()) && !is_chatting() ) {
		// 招呼一律走單一 do_chat（is_chatting 期間 do_ask 早退、待招呼畢方應）。
		if( this_player()->query("quest/sq_liuerye") >= 1
		||  present("mingwang ring", this_player()) )
			do_chat((: command,
				"say 少俠那枚冥王寶戒，可駕馭得了麼？那縷沉冥之力，非有膽魄者不能御——少俠戴穩了(wear ring)，臨敵自有妙用。" :));
		else
			do_chat((: command,
				"say 這位少俠面生 ... 卻有一身在江湖上闖出來的氣度。老朽這雙手裡，倒還壓著一件等了多年的物事。" :));
	}
}

// 同步交付冥王寶戒：直接 new+move 予玩家（玩家此刻必在場——環境校驗在前）。
// 防重複發戒：玩家若已持有冥王寶戒，不再重發。⚠ 同步 new+move，絕不放進延遲
// do_chat closure（免玩家於回呼前離場致戒沒領而 soft-lock）。
private void give_ring(object who)
{
	object ring;

	if( !who || environment(who) != environment() ) return;

	// 防重複發戒（雙重保險，與旗標互為冗餘）。
	if( present("mingwang ring", who) ) return;

	ring = new(__DIR__"obj/mingwang_ring");
	if( !ring->move(who) ) ring->move(environment());

	message_vision(
		HIY "劉二爺枯瘦的手指拂開案頭那個烏沉沉的小木匣，自匣中托出一枚入手"
		"沁骨生寒的玄黑寶戒。戒面那顆瑩黑如墨的冥王石裡，幽幽轉著一線游絲也似"
		"的血芒。老人就著天光端詳了$N半晌，眼底掠過一絲了卻多年心事的釋然，方"
		"才鄭重地將這枚『冥王寶戒』，交到了$N的手裡。\n" NOR, who);
}

int do_ask(string arg)
{
	object me = this_player();

	if( !arg || (arg != "liuerye about 冥王寶戒"
		&&   arg != "liuerye about 冥王"
		&&   arg != "liuerye about 寶戒"
		&&   arg != "liuerye about 魔戒"
		&&   arg != "liuerye about 戒"
		&&   arg != "liuerye about 冥王石"
		&&   arg != "liuerye about 任務"
		&&   arg != "jeweller liu about 冥王寶戒"
		&&   arg != "jeweller liu about 冥王"
		&&   arg != "jeweller liu about 寶戒"
		&&   arg != "jeweller about 冥王寶戒"
		&&   arg != "jeweller about 寶戒"
		&&   arg != "liu about 冥王寶戒"
		&&   arg != "liu about 寶戒"
		&&   arg != "liuerye about ring"
		&&   arg != "liuerye about quest"
		&&   arg != "jeweller liu about ring"
		&&   arg != "jeweller about ring") )
		return notify_fail("你想問這位珠寶匠甚麼？（試試 ask liuerye about 冥王寶戒）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("劉二爺正就著天光埋首琢玉，運銼之際分毫差不得，沒空理你。\n");

	// 已領過冥王寶戒（旗標 ≥1 或身上已有戒）：只給氣氛對白，不重複收費、不重複發戒。
	if( me->query("quest/sq_liuerye") >= 1 || present("mingwang ring", me) ) {
		do_chat(({
			(: command, "say 那枚冥王寶戒，老朽已交與少俠了。它是老朽窮半生之力、自那塊冥王石中琢成的——戒中所煉的那縷馭陰煞、催拙力的冥王之力，等的便是少俠這樣有膽魄的人。" :),
			(: command, "say 少俠且把它戴穩了(wear ring)，那沉冥之力自會漫入經脈、催發筋骨之力，更有一層煞氣護持周身。了卻這樁多年的心事，老朽這雙手，也算沒白琢它一場了。" :),
		}));
		return 1;
	}

	// 入門條件：須備琢戒工本 50 金。已備足 → 同步交付（扣款 → 發戒 → 記旗標）。
	// ⚠ 旗標(sq_liuerye)於 give_ring 同步交付「之後」設；give_ring 為直接 new+move，
	// 玩家此刻必在場——絕不把發戒放進延遲 do_chat closure（免 soft-lock）。
	if( me->can_afford(RING_FEE) ) {
		// 先扣琢戒工本（pay_money 同步扣款；can_afford 已確認足額）。
		me->pay_money(RING_FEE);

		// 同步交付冥王寶戒（直接 new+move，玩家必在場）。
		give_ring(me);

		// 賜物畢方記旗標（置於同步交付之後）。
		me->set("quest/sq_liuerye", 1);

		// 一點旅行見聞 / 聲望的小賞（支線量級，遠遜主線）。
		me->gain_score("explorer fame", 80);
		me->gain_score("reputation", 60);

		do_chat(({
			(: command, "say 好——這筆琢戒的工本，老朽收下了。少俠且看好了。" :),
			(: command, "say 這枚戒，老朽喚它『冥王寶戒』。戒胎是一塊不知得自何處、沁骨生寒的玄黑寒鐵；戒面這顆瑩黑如墨、其中幽幽轉著血芒的，便是九幽地脈死氣所凝的『冥王石』了。老朽費了半生的心血，才將這死氣凝成的石頭，琢成這麼一枚馭陰煞、催拙力的魔戒。" :),
			(: command, "say 這戒中的沉冥之力，非有膽魄者不能駕馭——老朽琢成它多年，遍尋不著個堪受此物的人。今日見了少俠，老朽這顆心，總算是放下了。少俠收好，戴穩了(wear ring)，臨敵時這沉冥之力自漫入經脈、催發筋骨之力，去罷——好生用它。" :),
		}));
		return 1;
	}

	// 未備足工本：委託——道明這枚冥王寶戒的來歷，並開出琢戒的工本(50 金)。
	do_chat(({
		(: command, "say 少俠也識得貨色。不錯——老朽這雙手裡，確壓著一件等了多年的物事。" :),
		(: command, "say 那是一枚『冥王寶戒』。戒胎是一塊沁骨生寒的玄黑寒鐵，戒面嵌著一顆其中幽幽轉著血芒的『冥王石』——那是九幽地脈死氣所凝之物。老朽窮半生之力，才將它琢成一枚馭使陰煞、催發拙力的魔戒。戴之臨敵，筋骨之力為之一壯，更有一層沉冥煞氣護持周身。" :),
		(: command, "say 只是這戒中沉冥之力，非有膽魄者不能御。老朽琢成多年，一直在等一個堪受此物的人——少俠這身氣度，倒教老朽動了心。然老朽是個珠寶匠，這戒的鑲工開光，總得有個工本：少俠且備下五十金的玄鐵琢磨之費，再來尋老朽——ask liuerye about 冥王寶戒，老朽便為少俠成全了這樁造化。" :),
	}));
	return 1;
}

// 委託/賜物走 ask-path 為主。玩家若改以 give 交付錢物，劉二爺不收下（回 0、物留
// 玩家身上），只提示改用 ask——既不吞物、領賞邏輯亦集中於 do_ask 一處。
int accept_object(object who, object ob)
{
	do_chat((: command, "say 少俠的好意老朽心領了——這琢戒的事，少俠口頭與老朽說一聲便是：ask liuerye about 冥王寶戒，老朽自會為少俠成全。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲！少俠息怒！老朽一個琢玉的老頭子，與少俠無冤無仇，這府裡可是動不得粗的哪！" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
