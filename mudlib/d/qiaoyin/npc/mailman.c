// mailman.c -- 桐城派信使 (Mail man)：奉桐城派之命、長年奔走於各縣傳遞書信的
//              老信使。如今正歇腳於喬陰縣城大街，肩上那只油布信囊裡，藏著一封
//              足以引出武林至寶的密信——是為「桐城派任務」之起點。
//              (canon：docs 01-世界觀與劇情/05-主線任務與NPC.md L102
//               「桐城派信使 (Mail man) @ 喬陰縣城大街 → 桐城派任務起點，
//                可解到武林至寶『真正的桐城派信物』」)
//
// 故事背景：
//   喬陰縣城大街上﹐人來人往的酒旗書幡之間﹐倚著牆根坐著一個風塵僕僕的老
//   信使。他一身褪色的青布短打﹐肩上斜挎一只磨得發亮的油布信囊﹐囊裡裝的盡
//   是各方往來的書信。這信使是桐城派養著的老腳力﹐替門中傳遞了大半輩子的書
//   信﹐走遍了大江南北的縣城驛道。如今桐城派零落﹐他卻仍守著最後一樁差使——
//   囊中那封火漆密緘的書信﹐據說循著信中所指的舊蹤一路追查下去﹐終能尋回桐
//   城派失落多年的「真正的信物」。他不肯輕易託付﹐只待一個肯為桐城舊事奔走
//   的有心人。
//
// 任務流程（旗標存玩家身上）：
//   quest/tongcheng_start  : 任務「起點」已開啟之標記（給信時設為 1）。
//   quest/sq_tongchengxinshi : 信使「給物」之防重旗標（已交付過密信即記 1）。
//   未領 (0) : 玩家 ask mailman about 桐城（或 信物/密信/信使/任務 …）-> 信使略
//              一打量﹐見來客肯為桐城舊事上心﹐便自信囊中取出那封桐城密信相
//              授﹐同步交付、即記兩面旗標。並道明此乃長路之始。
//   已領 (1) : 不再重複給信（防重領）；ask 只給一段點撥循線追查的純劇情對白。
//   穩健性   : 若 sq 旗標已記為 1 但密信不在玩家身上（中途遺失／賣掉），補贈
//              一封、不重置進度（step-flag 在、物不在則重給）。
//
// 同步交付（本專案頭號 bug class 之防範）：給信一律在 do_ask handler 內直接
//   new()+move() 給玩家、且在設完成旗標之前——絕不放進延遲的 do_chat/closure
//   (玩家中途離場會「信沒了、旗標卻記完成」soft-lock)。do_chat 只擺氣氛對白。
//
// 注意：本 NPC 有 do_ask / init，**不** replace_program（runtime 鐵則 #11）。
//       die()/destruct() 不在此處；旗標／訊息均寫在交付之前（鐵則 #10）。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIY "桐城派信使" NOR, ({ "mailman", "mail man", "messenger", "桐城派信使", "信使", "tongcheng xinshi" }) );
	set("nickname", HIY "桐城派信使" NOR);
	set_race("human");
	set_class("commoner");
	set_level(8);
	set_attr("con", 18);
	set_attr("dex", 18);
	set_skill("unarmed", 18);
	set_skill("dodge", 20);
	set_skill("literate", 16);

	set("gender", "male");
	set("age", 57);
	set("long",
		"一個風塵僕僕的老信使﹐倚著大街的牆根坐著歇腳。他穿一身褪\n"
		"色的青布短打﹐草鞋磨穿了底﹐臉上溝壑縱橫﹐一看便是常年在驛道\n"
		"上奔走的腳力。他肩上斜挎著一只磨得發亮的油布信囊﹐囊口束得緊\n"
		"緊的﹐裡頭也不知裝著多少方往來的書信。聽他自言自語﹐這信使竟\n"
		"是桐城派養著的老腳力﹐替那如今已零落的門派傳了大半輩子的書\n"
		"信。他渾濁的眼裡偶爾掠過一絲執拗的光﹐像是還守著甚麼放不下的\n"
		"差使。\n"
		"你或許可以問問他：ask mailman about 桐城。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		"桐城派信使拍了拍肩上的信囊﹐喃喃道﹕走了一輩子的路﹐這最後一封信﹐總得交到對的人手上才成。\n",
		"桐城派信使望著大街上往來的人潮﹐長長嘆了口氣﹕桐城派零落至此﹐如今還記得它的﹐怕沒幾個了。\n",
		"桐城派信使捶了捶痠痛的腿腳﹐自語道﹕真正的信物若還在世上﹐也只有循著那條老路﹐一步步找回去了。\n",
	}));
	setup();
	carry_money("coin", 20);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !this_player()->query("quest/tongcheng_start") )
			do_chat((: command,
				"say 這位客官且留步——老漢瞧你像是個肯為人奔走的，可願聽老漢說一樁桐城派的舊事？(ask mailman about 桐城)" :));
	}
}

// 同步給信：直接 new()+move() 給玩家。先試 move 到玩家身上，
// 不成（負重等）則落在環境地上——絕不靜默丟失。
private void give_letter(object who)
{
	object letter;

	if( !who || environment(who) != environment() ) return;

	letter = new(__DIR__"obj/tongcheng_letter");
	if( !letter->move(who) ) letter->move(environment());

	message_vision(
		"桐城派信使解開肩上的油布信囊﹐自囊底鄭重地摸出一封火漆密緘的書信﹐"
		"雙手捧著﹐慎重地交到$N手中。\n",
		who);

	who->gain_score("emprise", 80);
	who->gain_score("reputation", 30);
	who->gain_score("explorer fame", 20);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "mailman about 桐城"
		&&   arg != "mailman about 桐城派"
		&&   arg != "mailman about 信物"
		&&   arg != "mailman about 密信"
		&&   arg != "mailman about 信使"
		&&   arg != "mailman about 任務"
		&&   arg != "mailman about tongcheng"
		&&   arg != "mailman about letter"
		&&   arg != "messenger about 桐城") )
		return notify_fail("你想問這位信使甚麼？（試試 ask mailman about 桐城）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("桐城派信使正歇著腳喘氣，沒空理你。\n");

	q = me->query("quest/sq_tongchengxinshi");

	// 已領過密信：純劇情點撥，不重發（防重領）。
	if( q >= 1 ) {
		// 穩健性：旗標在、密信卻不在身上（遺失／賣掉）-> 補贈一封、不重置進度。
		if( !present("tongcheng letter", me) ) {
			// 同步補贈：give_letter 直接 new+move（玩家此刻必在場）；do_chat 只留氣氛對白。
			// 不可把 give_letter 塞進 do_chat 陣列——那會延後數心跳異步執行，違同步交付契約。
			give_letter(me);
			do_chat((: command, "say 客官那封密信怎不見了？這等要緊東西可丟不得！罷了，老漢這信囊裡還抄謄著一封，再付與你便是——這回務必收好了。" :));
			return 1;
		}
		do_chat(({
			(: command, "say 客官那封桐城密信可還收著？好。那火漆上的舊印款識古拙﹐老漢也識它不得——客官且先到城西喬陰書局走一趟﹐問那位識古的老書商替你認認這枚舊印﹐他自會指你下一程的去處。(ask bookseller about 火漆)" :),
			(: command, "say 老漢一把年紀﹐走不動了﹐這樁差使便全託付給客官了。但能尋回那真正的信物﹐也不枉桐城派一場興衰。去罷﹐路上小心。" :),
		}));
		return 1;
	}

	// 首次：同步給信、即記旗標（give_letter 為直接 new+move，玩家此刻必在場）。
	// 先給物、後記旗標——免於回呼前離場致信沒領、旗標卻記完成而卡關（鐵則 #10）。
	give_letter(me);
	me->set("quest/sq_tongchengxinshi", 1);
	me->set("quest/tongcheng_start", 1);
	do_chat(({
		(: command, "say 客官肯駐足聽老漢一句﹐便是與這桐城派有了緣分。老漢替桐城派傳了大半輩子的信﹐如今門派零落﹐只剩老漢還守著最後一樁差使。" :),
		(: command, "say 老漢這信囊底﹐藏著一封火漆密緘的書信。信中所言﹐乃是桐城派失落多年的『真正的信物』之線索——那可是一件武林至寶啊。只是路途迢遞﹐須循著信中舊蹤﹐一處處訪查下去﹐方有緣得見。" :),
		(: command, "say 看客官是個有心肯奔走的﹐這封密信﹐老漢便託付與你了。封上那火漆舊印老漢也識它不得﹐客官且先到城西喬陰書局﹐問那識古的老書商替你認認這枚舊印(ask bookseller about 火漆)﹐他自會指你下一程的去處——這只是一樁長路的開端。珍重﹐老漢就在這大街上等客官的好消息。" :),
	}));
	return 1;
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品（尤不收回桐城密信）。
int accept_object(object who, object ob)
{
	if( ob->id("tongcheng letter") ) {
		do_chat((: command,
			"say 客官快收回——這密信既已付與你﹐便是你的差使了﹐老漢怎能再收？收好了循線去查便是。" :));
		return 0;
	}
	do_chat((: command,
		"say 老漢一個跑腿的﹐受不起客官這個﹐還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 客官息怒——老漢一把年紀的信使﹐手無縛雞之力﹐與客官無冤無仇﹐何苦動這刀兵？" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
