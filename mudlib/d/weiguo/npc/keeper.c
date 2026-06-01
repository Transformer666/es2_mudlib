// keeper.c -- 衛國客棧的掌櫃；
//             兼衛國鎮非戰鬥支線「鎮關炒米茶」的委託人與領賞人。
//
// 任務性質：純邊縣市鎮氣氛的「汲水、和茶、回報」支線﹐沒有戰鬥、不需殺任何東西﹐
//           也不靠任何運氣骰子——一路問著、汲著、和著、交還即成﹐必定可完成。
//           衛國客棧的掌櫃要為一位早年戍邊、如今退伍還鄉、途經衛國的老鏢頭舊識備
//           一罐衛國鎮最家常的送遠鄉味「鎮關炒米茶」﹐偏生自己抽不開身﹐便央玩家
//           去鎮口古井亭向守井老叟絞一罐老古井的甜水、盛進瓦罐﹐再到炒米坊尋炒米
//           師傅拿新焙的炒米沖成炒米茶﹐持回客棧交差。
//           本支線自成一套旗標（quest/weiguo_tea*）﹐全程不出衛國鎮這幾間屋子、
//           幾處景緻﹐不讀、不動任何別的任務旗標﹐純加深邊縣市鎮的人情風味。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/weiguo_tea==0) : 玩家 ask keeper about 炒米茶 ->
//       掌櫃道出要備鎮關炒米茶送遠、自家抽不開身的難處﹐央玩家去汲水和茶﹐
//       設 quest/weiguo_tea = 1（接任務）。此時不交物——盛水的瓦罐在守井老叟處討。
//   汲水和茶中 (quest/weiguo_tea==1) : 玩家分頭辦兩樁（推進在各該 NPC）：
//         - 守井老叟 (/d/weiguo/npc/welltender，古井亭) ask about 炒米茶
//             -> 交付「井亭瓦罐」實物（內盛古井甜水）﹐記 quest/weiguo_tea_crock = 1
//         - 炒米師傅 (/d/weiguo/npc/roaster   ，炒米坊) 持井亭瓦罐
//             ask about 炒米茶（或 give well crock to roaster）
//             -> 和茶﹕銷井亭瓦罐、交付「鎮關炒米茶」實物﹐記 quest/weiguo_tea_filled = 1
//   可回報 (持鎮關炒米茶在身) : 玩家持和好的炒米茶回客棧﹐
//         ask keeper about 炒米茶（或 give tea crock to keeper）->
//         掌櫃驗看茶湯、收下﹐給賞﹐設 quest/weiguo_tea = 2（完成﹐防重領）。
//   注：driver 的 give 指令僅認 "give <物> to <人>" / "give <人> <物>"﹐不認中文「給」﹔
//       故每個交還點都另備 "ask <npc> about 炒米茶" 的等效完成路徑（持物時 ask 即送件／
//       回報﹐由各該 NPC 同步給物或給賞﹐並自行銷除手中的送件信物）﹐確保必可完成。
//   已完成 (quest/weiguo_tea>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("掌櫃", ({ "weiguo keeper", "keeper", "innkeeper" }) );
	set("nickname", "掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 49);
	set("gender", "male");
	set("long",
		"這位是衛國客棧的掌櫃﹐生得白胖和氣﹐一張笑臉終日不\n"
		"離﹐待客最是周到熱絡﹐這「衛國」二字的招牌在這邊縣小鎮\n"
		"裡也算叫得響。近來他卻時時對著門外那條老官道出神﹐捻著\n"
		"指頭盤算著甚麼﹐似有一樁掛心的喜事。倦了的話﹐不妨在這\n"
		"客棧裡尋張床鋪﹐好生歇歇腳﹔得閒也可問問他﹕ask keeper about 炒米茶。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃笑容可掬地招呼道﹕客官打尖還是住店﹖咱這古井甜水煮的茶﹐比別處的都回甘哩﹗\n",
		"掌櫃對著門外的老官道出神﹐捻著指頭喃喃道﹕那罐鎮關炒米茶﹐井水、炒米可得樣樣地道纔成 ...\n",
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
		&&  this_player()->query("quest/weiguo_tea") == 1 )
			do_chat((: command,
				"say 客官﹐託你張羅的那罐鎮關炒米茶﹐可有著落了麼﹖" :));
		else
			do_chat((: command,
				"say 客官裡邊請﹗本店床鋪潔淨﹐古井煮茶﹐包您住得稱心﹗" :));
	}
}

// 領賞：給一封碎銀、一串銅錢、一面客棧記給嘉賓的「衛國木牌」﹐
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

	charm = new(__DIR__"obj/weiguo_token");
	if( !charm->move(who) ) charm->move(environment());

	who->gain_score("survive", 90);
	who->gain_score("explorer fame", 50);
	who->gain_score("reputation", 30);

	message_vision(
		"掌櫃眉開眼笑﹐自錢匣裡數出一小封碎銀、一串銅錢﹐又取出一面\n"
		"刻著「衛國」的棗木牌﹐一併塞到$N手裡﹐連聲道謝。\n",
		who);
}

// 收尾／回報：玩家把鎮關炒米茶交(give)回時，由 accept_object 觸發。
// 驗看茶湯、給賞、設旗標 2（完成）。本函不經手鎮關炒米茶物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的鎮關炒米茶（與 d/shuiyue keeper、
// d/ziyan keeper、d/louxian keeper 一致）。
private void settle_quest(object me)
{
	// 收罐即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——鎮關炒米茶已被 give 指令於 accept_object 回 1 後
	// 銷除﹐若賞落在延遲回呼又逢玩家離場﹐便會「罐沒了、賞沒領、旗標卻記完成」
	// 而卡關。do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/weiguo_tea", 2);
	do_chat(({
		(: command, "say 哎呀﹐這炒米茶和成了﹗快與小老兒嚐嚐——唔﹐古井的水甜﹐炒米的香焦﹐這一口下去﹐正是衛國的老味道﹗客官這趟跑得仔細﹐可解了小老兒一樁心事。" :),
		(: command, "say 不瞞客官﹐這罐茶是備給一位早年戍邊、如今退伍還鄉的老鏢頭舊識的﹐他打這兒過﹐最念著當年出關喝慣的這碗鎮關炒米茶。如今井水、炒米俱備﹐小老兒這便能拿這碗鄉味替他餞行了。這點碎銀銅錢﹐方纔已塞到客官手裡﹐務必收好。" :),
		(: command, "say 另有一面『衛國木牌』﹐也一併與客官﹐往後打衛國鎮經過﹐只管進店歇腳吃茶﹐圖個衛國送遠的好意頭﹗本店悅近來遠﹐客官常來﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位掌櫃甚麼﹖（試試 ask keeper about 炒米茶）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("掌櫃正撥著算盤核帳﹐一時沒空理你。\n");

	// 炒米茶 / 鎮關茶 / 茶料：非戰鬥支線「鎮關炒米茶」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」「茶罐」等問法﹐方便玩家中途確認進度）
	if( arg == "keeper about 炒米茶"
	||  arg == "weiguo keeper about 炒米茶"
	||  arg == "innkeeper about 炒米茶"
	||  arg == "keeper about 鎮關茶"
	||  arg == "keeper about 茶"
	||  arg == "keeper about 炒米"
	||  arg == "keeper about 茶罐"
	||  arg == "keeper about 任務"
	||  arg == "keeper about tea"
	||  arg == "keeper about quest" ) {
		object me = this_player();
		int q = me->query("quest/weiguo_tea");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替小店和了那罐鎮關炒米茶﹐那位老鏢頭嚐了﹐連說還是這碗衛國的老味道地道﹐就著它喝了三大碗﹐歡喜得很哩。" :),
				(: command, "say 往後過衛國鎮﹐只管進店歇腳吃茶。衛國客棧這四個字﹐圖的就是個賓至如歸﹗" :),
			}));
			return 1;
		}

		// 汲水和茶中（已接任務）：持和好的炒米茶則 ask 即驗茶領賞﹐否則依進度提示下一步
		if( q == 1 ) {
			// 已和好炒米茶：ask keeper about 炒米茶 即當作回報——驗看茶湯、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的鎮關炒米茶（與 accept_object
			// 經 give 指令回 1 後自動銷除鎮關炒米茶等效）。縱炒米茶失落亦直接認功給賞﹐免卡關。
			if( me->query("quest/weiguo_tea_filled") ) {
				object box = present("tea crock", me);
				if( box ) destruct(box);
				message_vision(
					"$N把那隻和好炒米茶的瓦罐奉與掌櫃。掌櫃揭了箬葉的封口﹐\n"
					"湊近聞了聞那一縷焦香回甘的茶氣﹐眉開眼笑。\n", me);
				settle_quest(me);
				return 1;
			}

			// 進行中：依「是否已自守井老叟討得瓦罐」分頭提示（先把整句湊好，再交給 command）
			{
				string line;
				if( !me->query("quest/weiguo_tea_crock") )
					line = "say 還沒著落麼﹖客官且去場南石徑盡頭的古井亭﹐尋那位守井的老叟絞一罐古井甜水回來（ask welltender about 炒米茶）。要和這鎮關炒米茶﹐頭一樁便是這口老古井的甜水﹐盛水的瓦罐他那兒也有﹐討一隻來便是。";
				else if( present("well crock", me) )
					line = "say 井水既向守井老叟絞著了﹐就去市集東北的炒米坊﹐尋那位炒米師傅﹐請他拿新焙的炒米沖成炒米茶（ask roaster about 炒米茶﹐或 give well crock to roaster）。和齊了﹐再持回小老兒這兒。";
				else
					line = "say 咦﹐先前向守井老叟絞的那罐井水呢﹖客官莫不是失落了﹖不妨事﹐再去古井亭尋守井老叟問問（ask welltender about 炒米茶），他那兒還記著這樁事。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出要備鎮關炒米茶送遠、自家抽不開身的難處、央玩家汲水和茶，設旗標 1
		// 此時不交物——盛水的瓦罐須玩家去古井亭向守井老叟討。
		me->set("quest/weiguo_tea", 1);
		do_chat(({
			(: command, "say 客官問著了小老兒的心事。是這麼回事﹕這兩日有位多年不見的舊識要打這兒過——他早年在咱衛國戍邊﹐如今退伍還鄉﹐最念著當年出關喝慣的那碗『鎮關炒米茶』。小老兒想備一罐像樣的炒米茶﹐拿這碗鄉味替他餞個行。" :),
			(: command, "say 偏生這鎮關炒米茶﹐最講究的就是井水、炒米兩樣都得地道﹕水要鎮口老古井剛絞的甜水﹐米要炒米坊現焙的炒米﹐拿甜水沖了炒米纔成﹐缺一不可。小老兒守著店抽不開身﹐這事便一直擱著。" :),
			(: command, "say 客官若得閒﹐勞煩替小老兒料理這樁事﹕先去場南石徑盡頭的古井亭﹐尋那位守井老叟絞一罐古井甜水、盛進瓦罐（ask welltender about 炒米茶）﹔再到市集東北的炒米坊﹐尋那位炒米師傅拿新焙的炒米沖成炒米茶（ask roaster about 炒米茶）。和齊了﹐持回客棧來尋小老兒（ask keeper about 炒米茶）﹐小老兒必有酬謝﹗" :),
		}));
		return 1;
	}

	return notify_fail("掌櫃陪笑道﹕客官若是打尖住店﹐只管吩咐﹔旁的小老兒可幫不上甚麼忙。（試試 ask keeper about 炒米茶）\n");
}

// 收下信物：
//   鎮關炒米茶(tea crock) -- 支線「鎮關炒米茶」回報﹐持和好的炒米茶且任務進行中時
//   收下、給賞、推進旗標 weiguo_tea 1 -> 2。
// 不在此 move／destruct 鎮關炒米茶——give 指令於本函回 1 後會自行 destruct 有值的
// 鎮關炒米茶（與 d/shuiyue keeper、d/ziyan keeper、d/louxian keeper 一致）﹔
// 非回報玩家／時機不符則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("tea crock") ) {
		int q = who->query("quest/weiguo_tea");

		// 已完成或未接任務：婉拒，不收下（避免吞掉炒米茶罐、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這罐茶 ... 客官還是自個兒收著罷，小老兒這會兒用不上。" :));
			return 0;
		}

		// 進行中但還沒和好炒米茶（理應不會持有 tea crock，穩妥起見仍判一次）：婉拒
		if( !who->query("quest/weiguo_tea_filled") ) {
			do_chat((: command,
				"say 客官這罐 ... 莫不是還沒到炒米坊和茶罷﹖且先持井水到炒米坊尋炒米師傅沖一罐炒米茶來﹐小老兒纔好驗。" :));
			return 0;
		}

		// 進行中、已和好炒米茶、持罐回報：給賞、推進旗標（鎮關炒米茶由 give 指令於回 1 後自行銷除）
		message_vision(
			"$N把那隻和好炒米茶的瓦罐奉與掌櫃。掌櫃揭了箬葉的封口﹐\n"
			"湊近聞了聞那一縷焦香回甘的茶氣﹐眉開眼笑。\n", who);
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
