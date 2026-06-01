// keeper.c -- 紫煙小棧的掌櫃；
//             兼紫煙鎮非戰鬥支線「紫煙小棧的安神香湯」的委託人與領賞人。
//
// 任務性質：純溫泉小鎮氣氛的「汲湯、和香、回報」支線﹐沒有戰鬥、不需殺任何東西﹐
//           也不靠任何運氣骰子——一路問著、汲著、和著、交還即成﹐必定可完成。
//           紫煙小棧的掌櫃要為一位遠來投宿、舟車勞頓的貴客備一罐紫煙鎮最得意的
//           「安神香湯」﹐偏生自己抽不開身﹐便央玩家去紫煙溫泉向司爐的燒湯老叟
//           汲一罐最新鮮的溫泉水、盛進陶罐﹐再到沉香小亭尋焙香師調進新焙的沉香末
//           和成香湯﹐持回客棧交差。
//           本支線自成一套旗標（quest/ziyan_incense*）﹐全程不出紫煙鎮這幾間屋子、
//           幾處景緻﹐不讀、不動任何別的任務旗標﹐純加深溫泉小鎮的人情風味。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/ziyan_incense==0) : 玩家 ask keeper about 香湯 ->
//       掌櫃道出要備安神香湯待客、自家抽不開身的難處﹐央玩家去汲湯和香﹐
//       設 quest/ziyan_incense = 1（接任務）。此時不交物——陶罐在燒湯老叟處討。
//   汲湯和香中 (quest/ziyan_incense==1) : 玩家分頭辦兩樁（推進在各該 NPC）：
//         - 燒湯老叟 (/d/ziyan/npc/springman ，紫煙溫泉) ask about 香湯
//             -> 交付「溫泉陶罐」實物（內盛溫泉水）﹐記 quest/ziyan_incense_crock = 1
//         - 焙香師   (/d/ziyan/npc/incenseman，沉香小亭) 持溫泉陶罐
//             ask about 香湯（或 give spring crock to incenseman）
//             -> 和香﹕銷溫泉陶罐、交付「安神香湯罐」實物﹐記 quest/ziyan_incense_filled = 1
//   可回報 (持安神香湯罐在身) : 玩家持和好的香湯回客棧﹐
//         ask keeper about 香湯（或 give incense crock to keeper）->
//         掌櫃驗看香湯、收下﹐給賞﹐設 quest/ziyan_incense = 2（完成﹐防重領）。
//   注：driver 的 give 指令僅認 "give <物> to <人>" / "give <人> <物>"﹐不認中文「給」﹔
//       故每個交還點都另備 "ask <npc> about 香湯" 的等效完成路徑（持物時 ask 即送件／
//       回報﹐由各該 NPC 同步給物或給賞﹐並自行銷除手中的送件信物）﹐確保必可完成。
//   已完成 (quest/ziyan_incense>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("掌櫃", ({ "ziyan keeper", "keeper", "innkeeper" }) );
	set("nickname", "掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 47);
	set("gender", "male");
	set("long",
		"這位是紫煙小棧的掌櫃﹐生得白胖和氣﹐一張笑臉終日不\n"
		"離﹐待客最是周到熱絡﹐這「紫煙」二字的招牌在鎮裡也算叫\n"
		"得響。近來他卻時時對著廳角那隻溫湯甕出神﹐捻著指頭盤算\n"
		"著甚麼﹐似有一樁掛心的喜事。倦了的話﹐不妨在這溫泉小棧\n"
		"裡尋張床鋪﹐泡個溫泉好生歇歇﹔得閒也可問問他﹕ask keeper about 香湯。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃笑容可掬地招呼道﹕客官打尖還是住店﹖咱這溫泉煮的茶、燒的湯﹐包您泡得舒坦、住得稱心﹗\n",
		"掌櫃對著廳角的溫湯甕出神﹐捻著指頭喃喃道﹕那罐安神香湯﹐溫泉、沉香可得樣樣地道纔成 ...\n",
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
		&&  this_player()->query("quest/ziyan_incense") == 1 )
			do_chat((: command,
				"say 客官﹐託你張羅的那罐安神香湯﹐可有著落了麼﹖" :));
		else
			do_chat((: command,
				"say 客官裡邊請﹗本店床鋪潔淨、溫泉舒坦﹐包您住得稱心﹗" :));
	}
}

// 領賞：給一封碎銀、一串銅錢、一面客棧記給嘉賓的「紫煙香牌」﹐
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

	charm = new(__DIR__"obj/ziyan_token");
	if( !charm->move(who) ) charm->move(environment());

	who->gain_score("survive", 90);
	who->gain_score("explorer fame", 50);
	who->gain_score("reputation", 30);

	message_vision(
		"掌櫃眉開眼笑﹐自錢匣裡數出一小封碎銀、一串銅錢﹐又取出一面\n"
		"印著「紫煙」的香牌﹐一併塞到$N手裡﹐連聲道謝。\n",
		who);
}

// 收尾／回報：玩家把安神香湯罐交(give)回時，由 accept_object 觸發。
// 驗看香湯、給賞、設旗標 2（完成）。本函不經手安神香湯罐物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的安神香湯罐（與 d/shuiyue keeper、
// d/wenguo keeper、d/louxian keeper 一致）。
private void settle_quest(object me)
{
	// 收罐即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——安神香湯罐已被 give 指令於 accept_object 回 1 後
	// 銷除﹐若賞落在延遲回呼又逢玩家離場﹐便會「罐沒了、賞沒領、旗標卻記完成」
	// 而卡關。do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/ziyan_incense", 2);
	do_chat(({
		(: command, "say 哎呀﹐這香湯和成了﹗快與小老兒聞聞——唔﹐溫泉的礦氣裡透著沉香的清甜﹐溫潤安神﹐正是這個味兒﹗客官這趟跑得仔細﹐可解了小老兒一樁心事。" :),
		(: command, "say 不瞞客官﹐這罐香湯是備給一位遠來投宿的貴客的﹐那位舟車勞頓、夜裡睡不安穩﹐小老兒想拿這安神香湯替他溫飲、泡浴﹐好生款待一回。如今溫泉、沉香俱備﹐小老兒這便能款待他了。這點碎銀銅錢﹐方纔已塞到客官手裡﹐務必收好。" :),
		(: command, "say 另有一面『紫煙香牌』﹐也一併與客官﹐往後打紫煙鎮經過﹐只管進店泡湯吃茶﹐圖個紫煙安神的好意頭﹗本店悅近來遠﹐客官常來﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位掌櫃甚麼﹖（試試 ask keeper about 香湯）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("掌櫃正撥著算盤核帳﹐一時沒空理你。\n");

	// 香湯 / 溫泉 / 沉香：非戰鬥支線「安神香湯」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」「香罐」等問法﹐方便玩家中途確認進度）
	if( arg == "keeper about 香湯"
	||  arg == "ziyan keeper about 香湯"
	||  arg == "innkeeper about 香湯"
	||  arg == "keeper about 溫泉"
	||  arg == "keeper about 沉香"
	||  arg == "keeper about 香"
	||  arg == "keeper about 香罐"
	||  arg == "keeper about 任務"
	||  arg == "keeper about incense"
	||  arg == "keeper about soup"
	||  arg == "keeper about quest" ) {
		object me = this_player();
		int q = me->query("quest/ziyan_incense");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替小店和了那罐安神香湯﹐那位貴客泡了溫飲了﹐連說睡得從沒這般安穩﹐歡喜得很哩。" :),
				(: command, "say 往後過紫煙鎮﹐只管進店泡湯吃茶。紫煙小棧這四個字﹐圖的就是個賓至如歸﹗" :),
			}));
			return 1;
		}

		// 汲湯和香中（已接任務）：持和好的香湯則 ask 即驗香湯領賞﹐否則依進度提示下一步
		if( q == 1 ) {
			// 已和好香湯：ask keeper about 香湯 即當作回報——驗看香湯、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的安神香湯罐（與 accept_object
			// 經 give 指令回 1 後自動銷除安神香湯罐等效）。縱香湯罐失落亦直接認功給賞﹐免卡關。
			if( me->query("quest/ziyan_incense_filled") ) {
				object crock = present("incense crock", me);
				if( crock ) destruct(crock);
				message_vision(
					"$N把那隻和好香湯的陶罐奉與掌櫃。掌櫃揭了荷葉的封口﹐\n"
					"湊近聞了聞那一縷溫潤的沉香﹐眉開眼笑。\n", me);
				settle_quest(me);
				return 1;
			}

			// 進行中：依「是否已自燒湯老叟討得溫泉陶罐」分頭提示（先把整句湊好，再交給 command）
			{
				string line;
				if( !me->query("quest/ziyan_incense_crock") )
					line = "say 還沒著落麼﹖客官且去鎮南的紫煙溫泉﹐尋那位司爐的燒湯老叟問問（ask springman about 香湯）。要和安神香湯﹐頭一樁便是汲一罐最新鮮的紫煙溫泉水﹐盛湯的陶罐他那兒也有﹐討一隻來便是。";
				else if( present("spring crock", me) )
					line = "say 溫泉水既向燒湯老叟汲著了﹐就去鎮心西北石階上的沉香小亭﹐尋那位焙香師﹐請他調進新焙的沉香末和成香湯（ask incenseman about 香湯﹐或 give spring crock to incenseman）。和齊了﹐再持回小老兒這兒。";
				else
					line = "say 咦﹐先前向燒湯老叟汲的那罐溫泉水呢﹖客官莫不是失落了﹖不妨事﹐再去鎮南的紫煙溫泉尋燒湯老叟問問（ask springman about 香湯），他那兒還記著這樁事。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出要備安神香湯待客、自家抽不開身的難處、央玩家汲湯和香，設旗標 1
		// 此時不交物——盛湯的陶罐須玩家去紫煙溫泉向燒湯老叟討。
		me->set("quest/ziyan_incense", 1);
		do_chat(({
			(: command, "say 客官問著了小老兒的心事。是這麼回事﹕這兩日店裡來了位遠道投宿的貴客﹐舟車勞頓﹐夜裡總睡不安穩。小老兒想備一罐咱紫煙鎮最得意的『安神香湯』﹐替他溫飲、泡浴﹐好好款待一回。" :),
			(: command, "say 偏生這安神香湯﹐最講究的就是溫泉、沉香兩樣都得地道﹕水要紫煙溫泉新汲的活泉﹐香要沉香小亭現焙的沉香﹐拿溫泉水和了沉香末纔成﹐缺一不可。小老兒守著店抽不開身﹐這事便一直擱著。" :),
			(: command, "say 客官若得閒﹐勞煩替小老兒料理這樁事﹕先去鎮南的紫煙溫泉﹐尋那位司爐的燒湯老叟汲一罐最新鮮的溫泉水、盛進陶罐（ask springman about 香湯）﹔再到鎮心西北石階上的沉香小亭﹐尋那位焙香師調進新焙的沉香末和成香湯（ask incenseman about 香湯）。和齊了﹐持回客棧來尋小老兒（ask keeper about 香湯）﹐小老兒必有酬謝﹗" :),
		}));
		return 1;
	}

	return notify_fail("掌櫃陪笑道﹕客官若是打尖住店、泡個溫泉﹐只管吩咐﹔旁的小老兒可幫不上甚麼忙。（試試 ask keeper about 香湯）\n");
}

// 收下信物：
//   安神香湯罐(incense crock) -- 支線「安神香湯」回報﹐持和好的香湯且任務進行中時
//   收下、給賞、推進旗標 ziyan_incense 1 -> 2。
// 不在此 move／destruct 安神香湯罐——give 指令於本函回 1 後會自行 destruct 有值的
// 安神香湯罐（與 d/shuiyue keeper、d/wenguo keeper、d/louxian keeper 一致）﹔
// 非回報玩家／時機不符則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("incense crock") ) {
		int q = who->query("quest/ziyan_incense");

		// 已完成或未接任務：婉拒，不收下（避免吞掉香湯罐、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這罐香湯 ... 客官還是自個兒收著罷，小老兒這會兒用不上。" :));
			return 0;
		}

		// 進行中但還沒和好香湯（理應不會持有 incense crock，穩妥起見仍判一次）：婉拒
		if( !who->query("quest/ziyan_incense_filled") ) {
			do_chat((: command,
				"say 客官這罐 ... 莫不是還沒到沉香小亭和香罷﹖且先持溫泉水到沉香小亭尋焙香師和一罐香湯來﹐小老兒纔好驗。" :));
			return 0;
		}

		// 進行中、已和好香湯、持罐回報：給賞、推進旗標（安神香湯罐由 give 指令於回 1 後自行銷除）
		message_vision(
			"$N把那隻和好香湯的陶罐奉與掌櫃。掌櫃揭了荷葉的封口﹐\n"
			"湊近聞了聞那一縷溫潤的沉香﹐眉開眼笑。\n", who);
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
