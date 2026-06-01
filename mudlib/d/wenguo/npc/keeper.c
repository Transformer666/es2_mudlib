// keeper.c -- 天風客棧的掌櫃；
//             兼文國縣非戰鬥支線「天風筆會」的委託人與領賞人。
//
// 任務性質：純文墨小縣氣氛的「配筆、和墨、回報」支線﹐沒有戰鬥、不需殺任何東西﹐
//           也不靠任何運氣骰子——一路問著、討著、配著、交還即成﹐必定可完成。
//           天風客棧的掌櫃要為一位遠來赴文會的舊識備一副文國最得意的「文房雅禮」﹐
//           偏生自己抽不開身﹐便央玩家去制筆作坊向老筆匠討一管新紮的「天風狼毫」、
//           安進筆匣﹐再到松煙墨坊尋墨工配一錠相稱的松煙好墨進匣﹐持回客棧交差。
//           本支線自成一套旗標（quest/wenguo_brush*）﹐全程不出文國縣這幾間屋子、
//           幾處景緻﹐不讀、不動任何別的任務旗標﹐純加深文墨小縣的人情風味。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/wenguo_brush==0) : 玩家 ask keeper about 文房 ->
//       掌櫃道出要備文房雅禮待客、自家抽不開身的難處﹐央玩家去配筆和墨﹐
//       設 quest/wenguo_brush = 1（接任務）。此時不交物——筆匣在老筆匠處討。
//   配筆和墨中 (quest/wenguo_brush==1) : 玩家分頭辦兩樁（推進在各該 NPC）：
//         - 老筆匠 (/d/wenguo/npc/brushmaker，制筆作坊) ask about 文房
//             -> 交付「天風筆匣」實物（內安新筆）﹐記 quest/wenguo_brush_case = 1
//         - 墨工   (/d/wenguo/npc/inkmaker ，松煙墨坊  ) 持天風筆匣
//             ask about 文房（或 give brush case to inkmaker）
//             -> 配墨﹕銷天風筆匣、交付「文房筆匣」實物﹐記 quest/wenguo_brush_filled = 1
//   可回報 (持文房筆匣在身) : 玩家持配齊的文房回客棧﹐
//         ask keeper about 文房（或 give writing case to keeper）->
//         掌櫃驗看筆墨、收下﹐給賞﹐設 quest/wenguo_brush = 2（完成﹐防重領）。
//   注：driver 的 give 指令僅認 "give <物> to <人>" / "give <人> <物>"﹐不認中文「給」﹔
//       故每個交還點都另備 "ask <npc> about 文房" 的等效完成路徑（持物時 ask 即送件／
//       回報﹐由各該 NPC 同步給物或給賞﹐並自行銷除手中的送件信物）﹐確保必可完成。
//   已完成 (quest/wenguo_brush>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("掌櫃", ({ "wenguo keeper", "keeper", "innkeeper" }) );
	set("nickname", "掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 48);
	set("gender", "male");
	set("long",
		"這位是天風客棧的掌櫃﹐生得白胖和氣﹐一張笑臉終日不\n"
		"離﹐待客最是周到熱絡﹐這「天風」二字的招牌在文國縣裡也\n"
		"算叫得響。近來他卻時時對著前廳那張書案出神﹐捻著指頭盤\n"
		"算著甚麼﹐似有一樁掛心的喜事。倦了的話﹐不妨在這客棧裡\n"
		"尋張床鋪﹐好生歇歇腳﹔得閒也可問問他﹕ask keeper about 文房。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃笑容可掬地招呼道﹕客官打尖還是住店﹖咱這臨窗的書案備著筆硯素箋﹐客官得空儘管題詠﹗\n",
		"掌櫃對著前廳那張書案出神﹐捻著指頭喃喃道﹕那副文房雅禮﹐筆、墨可得樣樣地道纔成 ...\n",
	}));
	setup();
	carry_money("coin", 200);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( !is_fighting() ) {
		if( this_player() && interactive(this_player())
		&&  this_player()->query("quest/wenguo_brush") == 1 )
			do_chat((: command,
				"say 客官﹐託你張羅的那副文房雅禮﹐可有著落了麼﹖" :));
		else
			do_chat((: command,
				"say 客官裡邊請﹗本店床鋪潔淨﹐臨窗備著筆硯﹐包您住得稱心﹗" :));
	}
}

// 領賞：給一封碎銀、一串銅錢、一面客棧記給嘉賓的「天風竹牌」﹐
// 並授江湖歷練、行旅見聞與一點市井聲望。
// 採直接 new + move(who) 交付﹐move 回 1 為成功（落在玩家身上）﹐
// 回 0（失敗）才退而落到地上﹐不走會因玩家走開而落空的延遲回呼。
private void give_reward(object who)
{
	object silver, coin, charm;

	if( !who || environment(who) != environment() ) return;

	silver = new("/obj/money/silver");
	silver->set_amount(1);
	if( !silver->move(who) ) silver->move(environment());

	coin = new("/obj/money/coin");
	coin->set_amount(50);
	if( !coin->move(who) ) coin->move(environment());

	charm = new(__DIR__"obj/wenguo_token");
	if( !charm->move(who) ) charm->move(environment());

	who->gain_score("survive", 90);
	who->gain_score("explorer fame", 50);
	who->gain_score("reputation", 30);

	message_vision(
		"掌櫃眉開眼笑﹐自錢匣裡數出一小封碎銀、一串銅錢﹐又取出一面\n"
		"烙著「天風」的竹牌﹐一併塞到$N手裡﹐連聲道謝。\n",
		who);
}

// 收尾／回報：玩家把文房筆匣交(give)回時，由 accept_object 觸發。
// 驗看筆墨、給賞、設旗標 2（完成）。本函不經手文房筆匣物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的文房筆匣（與 d/shuiyue keeper、
// d/louxian keeper、d/fancheng boatman 一致）。
private void settle_quest(object me)
{
	// 收匣即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——文房筆匣已被 give 指令於 accept_object 回 1 後
	// 銷除﹐若賞落在延遲回呼又逢玩家離場﹐便會「匣沒了、賞沒領、旗標卻記完成」
	// 而卡關。do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/wenguo_brush", 2);
	do_chat(({
		(: command, "say 哎呀﹐筆墨齊了﹗快與小老兒瞧瞧——唔﹐這筆鋒尖圓飽滿﹐這墨烏亮清香﹐筆配墨﹐樣樣地道﹗客官這趟跑得仔細﹐可解了小老兒一樁心事。" :),
		(: command, "say 不瞞客官﹐這副文房是備給一位遠來赴文會的舊識的﹐他早年在咱文國住過﹐最認這『翰墨之鄉』的筆墨。如今筆、墨俱備﹐小老兒這便能送他一副像樣的雅禮了。這點碎銀銅錢﹐方纔已塞到客官手裡﹐務必收好。" :),
		(: command, "say 另有一面『天風竹牌』﹐也一併與客官﹐往後打文國縣經過﹐只管進店歇腳吃茶﹐圖個天風送遠的好意頭﹗本店悅近來遠﹐客官常來﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位掌櫃甚麼﹖（試試 ask keeper about 文房）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("掌櫃正撥著算盤核帳﹐一時沒空理你。\n");

	// 文房 / 筆會 / 筆墨：非戰鬥支線「天風筆會」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」「筆匣」等問法﹐方便玩家中途確認進度）
	if( arg == "keeper about 文房"
	||  arg == "wenguo keeper about 文房"
	||  arg == "innkeeper about 文房"
	||  arg == "keeper about 筆"
	||  arg == "keeper about 墨"
	||  arg == "keeper about 筆會"
	||  arg == "keeper about 筆墨"
	||  arg == "keeper about 筆匣"
	||  arg == "keeper about 任務"
	||  arg == "keeper about brush"
	||  arg == "keeper about ink"
	||  arg == "keeper about quest" ) {
		object me = this_player();
		int q = me->query("quest/wenguo_brush");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替小店張羅了那副文房雅禮﹐那位舊識嚐了那筆墨﹐連說還是這『翰墨之鄉』的東西地道﹐歡喜得很哩。" :),
				(: command, "say 往後過文國縣﹐只管進店歇腳吃茶。天風客棧這四個字﹐圖的就是個賓至如歸﹗" :),
			}));
			return 1;
		}

		// 配筆和墨中（已接任務）：持配齊的文房則 ask 即驗筆墨領賞﹐否則依進度提示下一步
		if( q == 1 ) {
			// 已配齊文房：ask keeper about 文房 即當作回報——驗看筆墨、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的文房筆匣（與 accept_object
			// 經 give 指令回 1 後自動銷除文房筆匣等效）。縱文房筆匣失落亦直接認功給賞﹐免卡關。
			if( me->query("quest/wenguo_brush_filled") ) {
				object box = present("writing case", me);
				if( box ) destruct(box);
				message_vision(
					"$N把那隻筆墨俱備的文房筆匣奉與掌櫃。掌櫃揭了匣蓋﹐撚起\n"
					"那管狼毫對著天光看了看鋒﹐又就著鼻子聞了聞那錠墨﹐眉開眼笑。\n", me);
				settle_quest(me);
				return 1;
			}

			// 進行中：依「是否已自老筆匠討得筆匣」分頭提示（先把整句湊好，再交給 command）
			{
				string line;
				if( !me->query("quest/wenguo_brush_case") )
					line = "say 還沒著落麼﹖客官且去大街西北的制筆作坊﹐尋那位老筆匠問問（ask brushmaker about 文房）。那作坊紮的『天風狼毫』是頂好的筆﹐安筆的筆匣他也有﹐討一管來便是。";
				else if( present("brush case", me) )
					line = "say 筆匣既向老筆匠討著了﹐就去翰墨廣場東邊的松煙墨坊﹐尋那位墨工﹐配一錠相稱的松煙好墨進匣（ask inkmaker about 文房﹐或 give brush case to inkmaker）。配齊了﹐再持回小老兒這兒。";
				else
					line = "say 咦﹐先前向老筆匠討的那隻筆匣呢﹖客官莫不是失落了﹖不妨事﹐再去制筆作坊尋老筆匠問問（ask brushmaker about 文房），他那兒還記著這樁事。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出要備文房雅禮待客、自家抽不開身的難處、央玩家配筆和墨，設旗標 1
		// 此時不交物——安筆的筆匣須玩家去制筆作坊向老筆匠討。
		me->set("quest/wenguo_brush", 1);
		do_chat(({
			(: command, "say 客官問著了小老兒的心事。是這麼回事﹕過幾日縣裡有場文會﹐有位多年不見的舊識要打這兒過﹐他早年在咱文國住過﹐最認這『翰墨之鄉』的筆墨。小老兒想備一副像樣的文房雅禮﹐好好送他一回。" :),
			(: command, "say 偏生這文房雅禮﹐最講究的就是筆、墨兩樣都得地道﹕筆要制筆作坊新紮的『天風狼毫』﹐墨要松煙墨坊現配的松煙好墨﹐缺一不可。小老兒守著店抽不開身﹐這事便一直擱著。" :),
			(: command, "say 客官若得閒﹐勞煩替小老兒料理這樁事﹕先去大街西北的制筆作坊﹐尋那位老筆匠討一管新紮的天風狼毫、安進筆匣（ask brushmaker about 文房）﹔再到翰墨廣場東邊的松煙墨坊﹐尋那位墨工配一錠相稱的好墨進匣（ask inkmaker about 文房）。齊備了﹐持回客棧來尋小老兒（ask keeper about 文房）﹐小老兒必有酬謝﹗" :),
		}));
		return 1;
	}

	return notify_fail("掌櫃陪笑道﹕客官若是打尖住店﹐只管吩咐﹔旁的小老兒可幫不上甚麼忙。（試試 ask keeper about 文房）\n");
}

// 收下信物：
//   文房筆匣(writing case) -- 支線「天風筆會」回報﹐持配齊的文房且任務進行中時
//   收下、給賞、推進旗標 wenguo_brush 1 -> 2。
// 不在此 move／destruct 文房筆匣——give 指令於本函回 1 後會自行 destruct 有值的
// 文房筆匣（與 d/shuiyue keeper、d/louxian keeper、d/fancheng boatman 一致）﹔
// 非回報玩家／時機不符則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("writing case") ) {
		int q = who->query("quest/wenguo_brush");

		// 已完成或未接任務：婉拒，不收下（避免吞掉文房筆匣、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這副文房 ... 客官還是自個兒收著罷，小老兒這會兒用不上。" :));
			return 0;
		}

		// 進行中但還沒配齊文房（理應不會持有 writing case，穩妥起見仍判一次）：婉拒
		if( !who->query("quest/wenguo_brush_filled") ) {
			do_chat((: command,
				"say 客官這筆匣 ... 莫不是還沒到墨坊配墨罷﹖且先持筆匣到松煙墨坊尋墨工配一錠好墨來﹐小老兒纔好驗。" :));
			return 0;
		}

		// 進行中、已配齊文房、持滿匣回報：給賞、推進旗標（文房筆匣由 give 指令於回 1 後自行銷除）
		message_vision(
			"$N把那隻筆墨俱備的文房筆匣奉與掌櫃。掌櫃揭了匣蓋﹐撚起\n"
			"那管狼毫對著天光看了看鋒﹐又就著鼻子聞了聞那錠墨﹐眉開眼笑。\n", who);
		settle_quest(who);
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個小老兒用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位客官說笑了﹐小老兒一介生意人﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
