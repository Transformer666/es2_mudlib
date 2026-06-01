// boatman.c -- 望安港船塢的老船匠，往天龍島渡船的伏筆人物；
//              兼檒城非戰鬥支線「望安港的斷龍骨」的委託人與領賞人。
//
// 任務性質：純港城氣氛的「張羅料、跑腿」支線，沒有戰鬥、不需殺任何東西，
//           只是替老船匠打聽何處有堪作船骨的好木料、再向衛兵統領討一面官中
//           的領料木牌帶回來。本支線自成一套旗標（quest/fancheng_sea*），與
//           天龍島主線海路毫無瓜葛——既開不了渡船、也去不成天龍島，只把
//           「渡海大船斷了龍骨、修不得」這道伏筆做實了幾分，加深港城氛圍。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/fancheng_sea==0) : 玩家 ask boatman about 龍骨 ->
//       老船匠道出修船缺一截好龍骨﹐又自家腿腳不便、官料調撥又得個記認﹐
//       央玩家代為張羅兩樁﹐設 quest/fancheng_sea = 1（接下任務）：
//         (一) 向城裡識貨的人打聽何處有堪作船骨的好木料；
//         (二) 向衛兵統領劉開討一面官中的領料木牌。
//   蒐集中 (quest/fancheng_sea==1) : 玩家分頭辦妥兩樁（推進在各該 NPC）：
//         - 雜貨鋪老闆 (/d/fancheng/npc/peddler，海味雜貨鋪) ask about 龍骨
//             -> 道出老松林一帶的好松木﹐記 quest/fancheng_sea_wood = 1
//         - 衛兵統領劉開 (/d/fancheng/npc/captain，衛兵所) ask about 領料
//             -> 須已先問著木料來路（fancheng_sea_wood），方畫押交付
//                「領料木牌」實物﹐記 quest/fancheng_sea_tally = 1
//   可回報 (兩樁齊備、且持木牌在身) : 玩家持木牌回船塢﹐
//         give 木牌 to boatman（或 ask boatman about 龍骨）->
//         老船匠驗看木牌、收下﹐給賞並道幾句討海人的見識﹐
//         設 quest/fancheng_sea = 2（完成﹐防重複領賞）。
//   已完成 (quest/fancheng_sea>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("船屋老人", ({ "boatman", "old boatman", "boat man" }) );
	set("nickname", "老船匠");
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 67);
	set("gender", "male");
	set("long",
		"一位上了年紀的老船匠﹐須髮花白﹐脊背被經年的海風吹得\n"
		"佝僂了﹐一張臉曬得黝黑﹐皺紋深得像皴裂的船板。他一雙手\n"
		"佈滿了厚繭與舊疤﹐瞇著的眼睛卻仍利得很﹐望著海口時﹐眼\n"
		"底彷彿盛著大半輩子的潮起潮落。聽聞這港上的船﹐沒有他不\n"
		"識得的水路。你或許可以問問他﹕ask boatman about 天龍島。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"船屋老人瞇眼望著海口﹐枯瘦的手裡無意識地搓著一截麻繩。\n",
		"船屋老人輕輕嘆道﹕這片海啊﹐養人﹐也吞人﹐討海的命﹐都繫在風浪上哩。\n",
		"船屋老人喃喃道﹕外海那道暗流﹐近來邪性得很﹐連跑老了船的都不敢輕易往西去 ...\n",
	}));
	setup();
	carry_money("coin", 40);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !is_fighting() ) {
			int q = this_player()->query("quest/fancheng_sea");
			if( q == 1 )
				do_chat((: command,
					"say 客官﹐託你張羅的那龍骨木料﹐可有著落了麼﹖" :));
			else
				do_chat((: command,
					"say 客官也是來打聽船期的麼﹖唉﹐這光景﹐沒船往西去囉 ..." :));
		}
	}
}

// 領賞：給一封碎銀、一串銅錢、一道望安港船戶供奉的舊平安符﹐
// 並授江湖歷練、行旅見聞與一點市井聲望。
// 採直接 new + move(who) 交付﹐move 回 1 為成功（落在玩家身上）﹐
// 回 0（失敗）才退而落到地上﹐不走會因玩家走開而落空的延遲回呼。
private void give_reward(object who)
{
	object silver, coin, charm;

	if( !who || environment(who) != environment() ) return;

	silver = new("/obj/money/silver");
	silver->set_amount(2);
	if( !silver->move(who) ) silver->move(environment());

	coin = new("/obj/money/coin");
	coin->set_amount(60);
	if( !coin->move(who) ) coin->move(environment());

	charm = new(__DIR__"obj/peace_charm");
	if( !charm->move(who) ) charm->move(environment());

	who->gain_score("survive", 100);
	who->gain_score("explorer fame", 60);
	who->gain_score("reputation", 30);

	message_vision(
		"船屋老人在襟前的舊平安符上輕輕一按﹐解下繩來﹐連著一小封碎\n"
		"銀、一串銅錢﹐一併塞到$N手裡﹐枯手在$N腕上拍了拍。\n",
		who);
}

// 收尾／回報：玩家把領料木牌交(give)回時，由 accept_object 觸發。
// 驗看木牌、給賞、設旗標 2（完成）。本函不經手木牌物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的木牌（與 d/snow diviner 一致）。
private void settle_quest(object me)
{
	// 收牌即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——木牌已被 give 指令於 accept_object 回 1 後銷除﹐
	// 若賞落在延遲回呼又逢玩家離場﹐便會「牌沒了、賞沒領、旗標卻記完成」而卡關。
	// do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/fancheng_sea", 2);
	do_chat(({
		(: command, "say 哦﹖牌子討來啦﹖快與老朽瞧瞧——唔﹐不錯﹐劉統領的押、料場的火印﹐都齊全。老松林的直紋松木﹐正是做龍骨的好料﹐客官這趟跑得在行﹗" :),
		(: command, "say 有了這面牌子﹐老朽便能往料場支料﹐慢工把這條斷了脊樑的大船重新接起來。只是料場路遠﹐下料、運料、再捻縫上灰﹐沒個三五月成不了事﹐客官要往西去﹐還得再耐心等等。" :),
		(: command, "say 這點碎銀銅錢、這道平安符﹐方纔已塞到客官手裡了﹐務必收好。符是老朽討海時貼身戴的﹐求個出海望平安——船修好了﹐外海那道邪性的暗流也得平了﹐才放得了船。來日水路通了往天龍島去﹐客官可記得來尋老朽搭船哪﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位老船匠甚麼﹖（試試 ask boatman about 天龍島）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("船屋老人正出神地望著海口﹐沒空理你。\n");

	// 龍骨 / 修船 / 船料：非戰鬥支線「望安港的斷龍骨」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」這一問法﹐方便玩家中途確認進度）
	if( arg == "boatman about 龍骨"
	||  arg == "old boatman about 龍骨"
	||  arg == "boatman about 修船"
	||  arg == "boatman about 船料"
	||  arg == "boatman about 木料"
	||  arg == "boatman about 任務"
	||  arg == "boatman about keel"
	||  arg == "boatman about repair"
	||  arg == "boatman about quest" ) {
		object me = this_player();
		int q = me->query("quest/fancheng_sea");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替老朽張羅來那截龍骨好料﹐這斷了脊樑的大船﹐總算有了重修的指望。" :),
				(: command, "say 待船修妥了、外海那道暗流也平了﹐往天龍島的水路自有再通的一日。客官來日要往西去﹐只管來船塢尋老朽便是。" :),
			}));
			return 1;
		}

		// 進行中（已接任務）：兩樁齊備則提示交牌領賞，否則報還差哪樁
		if( q == 1 ) {
			int got_wood  = me->query("quest/fancheng_sea_wood");
			int got_tally = me->query("quest/fancheng_sea_tally");

			// 兩樁齊備、且持木牌在身：ask 即當作送件處理——驗牌、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的木牌（與 accept_object
			// 經 give 指令回 1 後自動銷除木牌等效﹐免玩家留著「已交」的牌重複觸發）。
			if( got_wood && got_tally ) {
				if( present("wood tally", me) ) {
					object tally = present("wood tally", me);
					message_vision(
						"$N雙手把那面領料木牌奉與船屋老人。老船匠瞇眼接過﹐\n"
						"就著天光反覆驗看牌上的官押火印﹐連連頷首。\n", me);
					// 先同步給賞、記旗標﹐再銷除木牌（與 accept_object 經 give 等效）。
					settle_quest(me);
					if( tally ) destruct(tally);
				} else
					do_chat((: command,
						"say 咦﹐那面領料木牌呢﹖客官莫不是失落了﹖快回衛兵所尋劉統領補一面來﹐老朽驗看了纔好下料。（補得木牌後﹐ask boatman about 龍骨﹐或 give wood tally to boatman）" :));
				return 1;
			}

			// 未齊：報還差哪樁（先把整句湊好，再交給 command）
			{
				string s = "";
				string line;
				if( !got_wood )
					s += "城裡識貨的人那兒﹐打聽打聽何處有堪作船骨的好木料（去 ask 雜貨鋪老闆 about 龍骨）﹔";
				if( !got_tally )
					s += "衛兵所裡﹐向劉統領討一面官中的領料木牌（去 ask 劉統領 about 領料）﹔";
				line = "say 還沒齊全哩。客官再去" + s
					+ "兩樁都辦妥了﹐再持那面木牌回船塢來尋老朽。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出修船缺龍骨的難處、央玩家代為張羅，設旗標 1
		me->set("quest/fancheng_sea", 1);
		do_chat(({
			(: command, "say 客官也曉得這個﹖唉——那條跑遠海的渡船﹐上月教風暴打折了主桅﹐連龍骨都震裂了一截。沒一根紋理筆直、堅韌耐蛀的好龍骨換上﹐這船的脊樑便接不起來﹐自是開不得。" :),
			(: command, "say 偏生這港城的好木料﹐素來歸官中統一調撥﹐尋常買賣不著﹐得有個官面的記認方能去料場支領。老朽一把年紀﹐腿腳不便﹐又跑不動這些門路﹐這船便一直擱在塢裡修不得。" :),
			(: command, "say 客官若得閒﹐勞煩替老朽張羅兩樁﹕一是去城裡識貨的人那兒﹐打聽何處有堪作船骨的好木料——海味雜貨鋪那老闆走南闖北﹐最是識貨﹐ask 他 about 龍骨﹔二是去衛兵所﹐求劉統領畫押一面官中的領料木牌﹐ask 他 about 領料便是。兩樁都辦妥了﹐持那木牌回船塢來尋老朽﹐老朽必有酬謝﹗" :),
		}));
		return 1;
	}

	// 天龍島：未來海路的伏筆 -- 船在修、風浪未平，開不了任何東西
	if( arg == "boatman about 天龍島"
	||  arg == "old boatman about 天龍島"
	||  arg == "boatman about 天龍"
	||  arg == "boatman about dragon island"
	||  arg == "boatman about dragon" ) {
		do_chat(({
			(: command, "say 天龍島﹖嘿﹐客官也聽說過那地方。打這望安港往西﹐越過外海那片暗礁險灘﹐再行上三五日水路﹐才到得了那座海外仙山。" :),
			(: command, "say 只是這光景去不得喲。渡海的大船上月教風暴打折了主桅﹐這會兒還擱在塢裡修著﹐料還沒備齊呢。" :),
			(: command, "say 況且近來外海風浪未平﹐那道暗流邪性得很﹐便是船修好了﹐沒個風平浪靜的日子﹐老朽也不敢放船。客官且耐心等等罷﹐來日船修好了、風浪平了﹐自有再說。" :),
		}));
		return 1;
	}

	// 渡船 / 船期：同一個伏筆，換個問法
	if( arg == "boatman about 渡船"
	||  arg == "old boatman about 渡船"
	||  arg == "boatman about 船"
	||  arg == "boatman about 船期"
	||  arg == "boatman about ferry"
	||  arg == "boatman about boat" ) {
		do_chat(({
			(: command, "say 渡船﹖唉﹐客官來得不巧。那條跑遠海的大船﹐主桅教上月的風暴打折了﹐這會兒正翻在塢裡修著哩。" :),
			(: command, "say 船料還缺著一截好龍骨﹐慢工出細活﹐急不得。便是修好了﹐也得等外海那道邪性的暗流平了﹐才敢開船。客官要往西去﹐眼下是無船可渡的﹐再等些時日罷。" :),
		}));
		return 1;
	}

	// 望安港 / 海路：閒談海上見聞，純氣氛
	if( arg == "boatman about 望安港"
	||  arg == "boatman about 港"
	||  arg == "boatman about 海"
	||  arg == "boatman about 海路"
	||  arg == "boatman about harbor"
	||  arg == "boatman about sea" ) {
		do_chat(({
			(: command, "say 這望安港啊﹐是檒城的命根子。南來北往的番舶、漁舟﹐都打這兒進出﹐養活了滿城的討海人家。" :),
			(: command, "say 老朽在這塢裡捻了五十年的船縫﹐這港上的水路暗礁﹐閉著眼都摸得清。只可惜往西的遠海﹐這些年是越發去不得了 ..." :),
		}));
		return 1;
	}

	return notify_fail("船屋老人聽不明白你問的﹐只茫然望著海。（試試 ask boatman about 天龍島）\n");
}

// 收下信物：
//   領料木牌(wood tally) -- 支線「望安港的斷龍骨」送件﹐持牌且兩樁齊備時
//   收下、給賞、推進旗標 fancheng_sea 1 -> 2。
// 不在此 move／destruct 木牌——give 指令於本函回 1 後會自行 destruct 有值的
// 木牌（與 d/snow diviner 一致）﹔非送件玩家／未齊備則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("wood tally") ) {
		int q = who->query("quest/fancheng_sea");

		// 已完成或未接任務：婉拒，不收下（避免吞掉木牌、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這木牌 ... 客官還是自個兒收著罷，老朽眼下用不上。" :));
			return 0;
		}

		// 進行中但兩樁未齊：婉拒，提示尚須先問明木料來路
		if( !who->query("quest/fancheng_sea_wood")
		||  !who->query("quest/fancheng_sea_tally") ) {
			do_chat((: command,
				"say 牌子是有了，可料的來路還沒問著哩。客官且先去 ask 雜貨鋪老闆 about 龍骨，問明了何處有好松木，老朽才好憑這牌子下料。" :));
			return 0;
		}

		// 進行中、兩樁齊備：給賞、推進旗標（木牌由 give 指令於回 1 後自行銷除）
		settle_quest(who);
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老朽用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 客官這是做甚﹖老朽一把年紀的船匠﹐與你無冤無仇哪。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
