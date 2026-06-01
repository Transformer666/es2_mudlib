// keeper.c -- 福安客棧的掌櫃；
//             兼水月村非戰鬥支線「福安客棧的清泉」的委託人與領賞人。
//
// 任務性質：純水鄉氣氛的「尋源、盛水、回報」支線﹐沒有戰鬥、不需殺任何東西﹐
//           也不靠任何運氣骰子——一路問著、取著、盛著、交還即成﹐必定可完成。
//           福安客棧與合村人家引的都是村後水月瀑布瀑下的活水﹐近來那泉眼教秋汛
//           沖落的亂石壅住了﹐水變了苦澀。掌櫃央玩家去瀑下尋採藥老叟問清泉的源
//           頭、討個盛水的竹筒﹐再到浣月潭尋釣叟到疏通好的泉眼盛一筒甜泉回來。
//           本支線自成一套旗標（quest/shuiyue_spring*）﹐全程不出水月村這幾間屋
//           子、幾處景緻﹐不讀、不動任何別的任務旗標﹐純加深水鄉小村的人情。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/shuiyue_spring==0) : 玩家 ask keeper about 清泉 ->
//       掌櫃道出井水變味、泉眼壅塞的難處﹐央玩家去瀑下尋採藥老叟﹐
//       設 quest/shuiyue_spring = 1（接任務）。此時不交物——竹筒在老叟處討。
//   尋源盛水中 (quest/shuiyue_spring==1) : 玩家分頭辦兩樁（推進在各該 NPC）：
//         - 採藥老叟 (/d/shuiyue/npc/herbman，水月瀑布) ask about 清泉
//             -> 交付「空竹筒」實物﹐記 quest/shuiyue_spring_jug = 1
//         - 釣叟     (/d/shuiyue/npc/angler ，浣月潭  ) 持空竹筒
//             ask about 清泉（或 give bamboo jug to angler）
//             -> 盛泉﹕銷空竹筒、交付「清泉竹筒」實物﹐記 quest/shuiyue_spring_filled = 1
//   可回報 (持清泉竹筒在身) : 玩家持滿筒回客棧﹐
//         ask keeper about 清泉（或 give spring jug to keeper）->
//         掌櫃驗看清泉、收下﹐給賞﹐設 quest/shuiyue_spring = 2（完成﹐防重領）。
//   注：driver 的 give 指令僅認 "give <物> to <人>" / "give <人> <物>"﹐不認中文「給」﹔
//       故每個交還點都另備 "ask <npc> about 清泉" 的等效完成路徑（持物時 ask 即送件／
//       回報﹐由各該 NPC 同步給物或給賞﹐並自行銷除手中的送件信物）﹐確保必可完成。
//   已完成 (quest/shuiyue_spring>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("掌櫃", ({ "shuiyue keeper", "keeper", "innkeeper" }) );
	set("nickname", "掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 49);
	set("gender", "male");
	set("long",
		"這位是福安客棧的掌櫃﹐生得白胖和氣﹐一張笑臉終日不\n"
		"離﹐待客最是周到熱絡﹐難怪這「福安」二字的招牌在谷裡叫\n"
		"得響。近來他卻時時對著前廳那口走了味的水缸蹙眉﹐似為店\n"
		"裡吃用的活水犯愁。倦了的話﹐不妨在這臨溪的客棧裡尋張床\n"
		"鋪﹐好生歇歇腳﹔得閒也可問問他﹕ask keeper about 清泉。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃笑容可掬地招呼道﹕客官打尖還是住店﹖樓上的客房臨著溪水﹐枕著水聲睡個好覺﹗\n",
		"掌櫃舀了一瓢水缸裡的水﹐皺眉嚐了嚐﹐又無奈地嘆了口氣﹕這水﹐怎的就苦了呢 ...\n",
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
		&&  this_player()->query("quest/shuiyue_spring") == 1 )
			do_chat((: command,
				"say 客官﹐託你料理的那眼清泉﹐可有著落了麼﹖" :));
		else
			do_chat((: command,
				"say 客官裡邊請﹗本店床鋪潔淨、臨溪清涼﹐包您住得稱心﹗" :));
	}
}

// 領賞：給一封碎銀、一串銅錢、一面客棧記給熟客的「福安竹牌」﹐
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

	charm = new(__DIR__"obj/fuan_charm");
	if( !charm->move(who) ) charm->move(environment());

	who->gain_score("survive", 90);
	who->gain_score("explorer fame", 50);
	who->gain_score("reputation", 30);

	message_vision(
		"掌櫃眉開眼笑﹐自錢匣裡數出一小封碎銀、一串銅錢﹐又取出一面\n"
		"烙著「福安」的竹牌﹐一併塞到$N手裡﹐連聲道謝。\n",
		who);
}

// 收尾／回報：玩家把清泉竹筒交(give)回時，由 accept_object 觸發。
// 驗看清泉、給賞、設旗標 2（完成）。本函不經手清泉竹筒物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的清泉竹筒（與 d/luocheng keeper、
// d/feixian keeper、d/fancheng boatman 一致）。
private void settle_quest(object me)
{
	// 收筒即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——清泉竹筒已被 give 指令於 accept_object 回 1 後
	// 銷除﹐若賞落在延遲回呼又逢玩家離場﹐便會「筒沒了、賞沒領、旗標卻記完成」
	// 而卡關。do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/shuiyue_spring", 2);
	do_chat(({
		(: command, "say 哎呀﹐這不是瀑後泉眼的水麼﹖快與小老兒嚐嚐——唔﹐清冽甘甜﹐正是這個味兒﹗客官這趟跑得仔細﹐可解了小老兒一樁心病。" :),
		(: command, "say 這店裡合村人家吃用全仗這一脈活水﹐水一壞﹐小老兒夜裡都睡不安生。如今泉眼疏通了﹐水也甜了﹐心便定了。這點碎銀銅錢﹐方纔已塞到客官手裡﹐務必收好。" :),
		(: command, "say 另有一面『福安竹牌』﹐也一併與客官﹐往後打水月村經過﹐只管進店歇腳吃茶﹐圖個福壽安康的好意頭﹗本店悅近來遠﹐客官常來﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位掌櫃甚麼﹖（試試 ask keeper about 清泉）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("掌櫃正撥著算盤核帳﹐一時沒空理你。\n");

	// 清泉 / 活水 / 井水：非戰鬥支線「福安客棧的清泉」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」「竹筒」等問法﹐方便玩家中途確認進度）
	if( arg == "keeper about 清泉"
	||  arg == "shuiyue keeper about 清泉"
	||  arg == "innkeeper about 清泉"
	||  arg == "keeper about 泉"
	||  arg == "keeper about 活水"
	||  arg == "keeper about 井水"
	||  arg == "keeper about 水"
	||  arg == "keeper about 竹筒"
	||  arg == "keeper about 任務"
	||  arg == "keeper about spring"
	||  arg == "keeper about water"
	||  arg == "keeper about quest" ) {
		object me = this_player();
		int q = me->query("quest/shuiyue_spring");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替小店把那眼清泉的亂石疏通了﹐如今缸裡的水又清又甜﹐合村人家都念著客官的好哩。" :),
				(: command, "say 往後過水月村﹐只管進店歇腳吃茶。福安客棧這四個字﹐圖的就是個賓至如歸﹗" :),
			}));
			return 1;
		}

		// 尋源盛水中（已接任務）：持滿筒則 ask 即驗水領賞﹐否則依進度提示下一步
		if( q == 1 ) {
			// 已盛得清泉：ask keeper about 清泉 即當作回報——驗看清泉、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的清泉竹筒（與 accept_object
			// 經 give 指令回 1 後自動銷除清泉竹筒等效）。縱清泉竹筒失落亦直接認功給賞﹐免卡關。
			if( me->query("quest/shuiyue_spring_filled") ) {
				object jug = present("spring jug", me);
				if( jug ) destruct(jug);
				message_vision(
					"$N把那節盛滿清泉的竹筒奉與掌櫃。掌櫃揭了竹葉的封口﹐\n"
					"舀出一瓢嚐了嚐﹐眉頭漸漸舒展開來。\n", me);
				settle_quest(me);
				return 1;
			}

			// 進行中：依「是否已自老叟討得空竹筒」分頭提示（先把整句湊好，再交給 command）
			{
				string line;
				if( !me->query("quest/shuiyue_spring_jug") )
					line = "say 還沒著落麼﹖客官且去村後的水月瀑布﹐尋崖下那位採藥的老叟問問（ask herbman about 清泉）。他在瀑下採藥幾十年﹐那泉眼的底細沒人比他更清楚﹐討個盛水的竹筒﹐他也有。";
				else if( present("bamboo jug", me) )
					line = "say 空竹筒既向老叟討著了﹐就去東南柳堤下的浣月潭﹐尋那位釣叟﹐到疏通好的泉眼盛一筒甜泉回來（ask angler about 清泉﹐或 give bamboo jug to angler）。盛滿了﹐再持回小老兒這兒。";
				else
					line = "say 咦﹐先前向老叟討的那節空竹筒呢﹖客官莫不是失落了﹖不妨事﹐再去瀑下尋採藥老叟問問（ask herbman about 清泉），他那兒還記著這樁事。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出井水變味、泉眼壅塞的難處、央玩家尋源盛水，設旗標 1
		// 此時不交物——盛水的竹筒須玩家去瀑下向採藥老叟討。
		me->set("quest/shuiyue_spring", 1);
		do_chat(({
			(: command, "say 唉﹐客官問著了小老兒的心事。是這麼回事﹕咱福安客棧、連著合村人家﹐吃用的全是村後水月瀑布瀑下那一眼泉的活水﹐順著竹筧一路引到村心的古井來﹐素來清甜得很。" :),
			(: command, "say 偏生前些日子一場秋汛﹐把瀑後泉眼底下沖落了一堆亂石﹐把那道沁水的石縫壅住了大半﹐泉水滲得細了﹐缸裡井裡的水﹐這便慢慢透出股苦澀來。小老兒守著店走不開﹐這事便一直擱著。" :),
			(: command, "say 客官若得閒﹐勞煩替小老兒料理這樁事﹕先去村後的水月瀑布﹐尋崖下那位採藥老叟問問清泉的源頭、討個盛水的竹筒（ask herbman about 清泉）﹔再到東南的浣月潭﹐尋那位釣叟到疏通好的泉眼盛一筒甜泉回來（ask angler about 清泉）。盛得了﹐持回客棧來尋小老兒（ask keeper about 清泉）﹐小老兒必有酬謝﹗" :),
		}));
		return 1;
	}

	return notify_fail("掌櫃陪笑道﹕客官若是打尖住店﹐只管吩咐﹔旁的小老兒可幫不上甚麼忙。（試試 ask keeper about 清泉）\n");
}

// 收下信物：
//   清泉竹筒(spring jug) -- 支線「福安客棧的清泉」回報﹐持滿筒且任務進行中時
//   收下、給賞、推進旗標 shuiyue_spring 1 -> 2。
// 不在此 move／destruct 清泉竹筒——give 指令於本函回 1 後會自行 destruct 有值的
// 清泉竹筒（與 d/luocheng keeper、d/fancheng boatman 一致）﹔非回報玩家／時機不符
// 則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("spring jug") ) {
		int q = who->query("quest/shuiyue_spring");

		// 已完成或未接任務：婉拒，不收下（避免吞掉清泉竹筒、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這筒水 ... 客官還是自個兒收著罷，小老兒這會兒用不上。" :));
			return 0;
		}

		// 進行中但還沒盛得清泉（理應不會持有 spring jug，穩妥起見仍判一次）：婉拒
		if( !who->query("quest/shuiyue_spring_filled") ) {
			do_chat((: command,
				"say 客官這筒水 ... 莫不是還沒到瀑後的泉眼盛罷﹖且先持竹筒到浣月潭尋釣叟盛一筒甜泉來﹐小老兒纔好驗。" :));
			return 0;
		}

		// 進行中、已盛得清泉、持滿筒回報：給賞、推進旗標（清泉竹筒由 give 指令於回 1 後自行銷除）
		message_vision(
			"$N把那節盛滿清泉的竹筒奉與掌櫃。掌櫃揭了竹葉的封口﹐\n"
			"舀出一瓢嚐了嚐﹐眉頭漸漸舒展開來。\n", who);
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
