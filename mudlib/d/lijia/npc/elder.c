// elder.c -- 李氏祠堂的李家族長；
//            兼李家村非戰鬥支線「李家祭祖供果」的委託人與領賞人。
//
// 任務性質：純聚族而居莊稼村子氣氛的「揀果、配供、祭祖」支線﹐沒有戰鬥、不需殺任何東西﹐
//           也不靠任何運氣骰子——一路問著、揀著、配著、交還即成﹐必定可完成。
//           李氏宗祠近日要祭祀合族先祖﹐供桌上卻還缺一盤三牲鮮果的供品﹐族長要主持
//           合族大事抽不開身﹐便央玩家去村南果園向看園果農揀一籃供祖的鮮果﹐再到村南
//           魚塘尋守塘漁戶撈尾活鯉、配齊三牲鮮果的供盤﹐持回祠堂交差供奉先祖。
//           本支線自成一套旗標（quest/lijia_offer*）﹐全程不出李家村這幾間屋子、
//           幾處景緻﹐不讀、不動任何別的任務旗標（更不涉任何門派、機制掛鉤）﹐
//           純加深聚族而居莊稼村子的人情風味。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/lijia_offer==0) : 玩家 ask elder about 祭祖 ->
//       族長道出祠堂祭祖缺供品、自家要主持族事抽不開身的難處﹐央玩家去揀果配供﹐
//       設 quest/lijia_offer = 1（接任務）。此時不交物——盛果的供果籃在果園果農處討。
//   揀果配供中 (quest/lijia_offer==1) : 玩家分頭辦兩樁（推進在各該 NPC）：
//         - 看園果農 (/d/lijia/npc/picker，李家果園) ask about 鮮果
//             -> 交付「供果籃」實物（內盛新摘的供祖鮮果）﹐記 quest/lijia_offer_fruit = 1
//         - 守塘漁戶 (/d/lijia/npc/fisher ，村南魚塘) 持供果籃
//             ask about 鯉魚（或 give fruit basket to fisher）
//             -> 配供﹕銷供果籃、撈活鯉添牲禮配齊、交付「祭祖供盤」實物﹐記 quest/lijia_offer_fish = 1
//   可回報 (持祭祖供盤在身) : 玩家持配齊的供盤回祠堂﹐
//         ask elder about 祭祖（或 give offer tray to elder）->
//         族長驗看供盤、收下供奉先祖﹐給賞﹐設 quest/lijia_offer = 2（完成﹐防重領）。
//   注：driver 的 give 指令僅認 "give <物> to <人>" / "give <人> <物>"﹐不認中文「給」﹔
//       故每個交還點都另備 "ask <npc> about <topic>" 的等效完成路徑（持物時 ask 即送件／
//       回報﹐由各該 NPC 同步給物或給賞﹐並自行銷除手中的送件信物）﹐確保必可完成。
//   已完成 (quest/lijia_offer>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("族長", ({ "lijia elder", "elder", "clan elder" }) );
	set("nickname", "族長");
	set_race("human");
	set_class("commoner");
	set_level(7);

	set("age", 68);
	set("gender", "male");
	set("long",
		"這位是李家村合族的族長﹐生得清癯矍鑠﹐留著一把花白的\n"
		"長鬚﹐穿一件漿洗得乾淨的青布長衫﹐拄著根油亮的棗木拐杖。他\n"
		"管著合族李姓的大小事﹐論輩分、論德望都是村裡頭一份的人物﹐\n"
		"待人接物自有一派聚族長者的鄭重與慈和。他正立在供桌前料理近\n"
		"日合族祭祖的事宜﹐神色凝重。得閒可問問他﹕ask elder about 祭祖。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"族長拄著拐杖立在神龕前﹐仰望著歷代先祖的牌位﹐神色肅穆地默禱了一陣。\n",
		"族長捋著長鬚﹐對著空著的供桌出神﹐喃喃道﹕祭祖是合族頂頂要緊的大事﹐這供品可馬虎不得 ...\n",
		"族長和進祠堂上香的村人一一招呼﹐叮囑著祭祖那日的種種規矩禮數。\n",
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
		&&  this_player()->query("quest/lijia_offer") == 1 )
			do_chat((: command,
				"say 客官﹐託你張羅的那盤祭祖供品﹐可有著落了麼﹖" :));
		else
			do_chat((: command,
				"say 客官遠來﹐這是咱李家合族的宗祠﹐隨意上炷香﹐拜一拜咱李家的先祖罷。" :));
	}
}

// 領賞：給一封碎銀、一串銅錢、一道祠堂供過的「李氏香火福符」﹐
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

	charm = new(__DIR__"obj/lijia_token");
	if( !charm->move(who) ) charm->move(environment());

	who->gain_score("survive", 90);
	who->gain_score("explorer fame", 50);
	who->gain_score("reputation", 30);

	message_vision(
		"族長眉開眼笑﹐自錢匣裡數出一小封碎銀、一串銅錢﹐又自神龕前\n"
		"取來一道祭過的「李氏香火福符」﹐一併塞到$N手裡﹐連聲道謝。\n",
		who);
}

// 收尾／回報：玩家把祭祖供盤交(give)回時，由 accept_object 觸發。
// 驗看供盤、給賞、設旗標 2（完成）。本函不經手祭祖供盤物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的祭祖供盤（與 d/kangping keeper、
// d/weiguo keeper、d/ziyan keeper 一致）。
private void settle_quest(object me)
{
	// 收盤即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——祭祖供盤已被 give 指令於 accept_object 回 1 後
	// 銷除﹐若賞落在延遲回呼又逢玩家離場﹐便會「盤沒了、賞沒領、旗標卻記完成」
	// 而卡關。do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/lijia_offer", 2);
	do_chat(({
		(: command, "say 哎呀﹐這供盤配得齊整﹗活鯉鮮蹦、鮮果飽滿﹐三牲俱全——好﹗有了這盤體面的供品﹐合族祭祖的大事便齊備了﹗客官這趟跑得仔細﹐可解了老朽一樁心事。" :),
		(: command, "say 不瞞客官﹐咱李家村合村都是一個老祖宗的子孫﹐這一年裡頭的祭祖﹐是合族頂頂要緊的大事﹐圖的就是個慎終追遠、福蔭子孫。如今供品齊備﹐老朽這便能領著合族子孫上香叩拜先祖了。這點碎銀銅錢﹐方纔已塞到客官手裡﹐務必收好。" :),
		(: command, "say 另有一道祠堂祭過的『李氏香火福符』﹐也一併與客官﹐沾一沾咱李家先祖的香火福分。往後打李家村經過﹐合村李姓都記著客官這份情﹐只管進村歇腳吃飯﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位族長甚麼﹖（試試 ask elder about 祭祖）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("族長正料理著合族祭祖的事宜﹐一時沒空理你。\n");

	// 祭祖 / 供品 / 供盤：非戰鬥支線「祭祖供果」的委託 / 進度 / 回報領賞
	// （亦涵蓋「先祖」「祠堂」「任務」等問法﹐方便玩家中途確認進度）
	if( arg == "elder about 祭祖"
	||  arg == "lijia elder about 祭祖"
	||  arg == "clan elder about 祭祖"
	||  arg == "elder about 供品"
	||  arg == "elder about 供盤"
	||  arg == "elder about 先祖"
	||  arg == "elder about 祠堂"
	||  arg == "elder about 任務"
	||  arg == "elder about offer"
	||  arg == "elder about tray"
	||  arg == "elder about quest" ) {
		object me = this_player();
		int q = me->query("quest/lijia_offer");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替合族備齊了那盤祭祖供品﹐祭祖那日﹐合族老小在這宗祠前上香叩拜﹐辦得體體面面﹐先祖在天有靈﹐也必歡喜。" :),
				(: command, "say 往後過李家村﹐只管進村歇腳吃飯。咱李家聚族而居﹐最重一個情義二字﹐客官替咱盡過心﹐便是咱李家記著的善客了。" :),
			}));
			return 1;
		}

		// 揀果配供中（已接任務）：持配齊的供盤則 ask 即驗供盤領賞﹐否則依進度提示下一步
		if( q == 1 ) {
			// 已配齊供盤：ask elder about 祭祖 即當作回報——驗看供盤、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的祭祖供盤（與 accept_object
			// 經 give 指令回 1 後自動銷除祭祖供盤等效）。縱供盤失落亦直接認功給賞﹐免卡關。
			if( me->query("quest/lijia_offer_fish") ) {
				// 用獨有 id「lijiagongpan」銷除本任務供盤﹐免與任何 /obj/food
				// 既有吃食相混而誤銷玩家自買的東西。
				object d = present("lijiagongpan", me);
				if( d ) destruct(d);
				message_vision(
					"$N把那方紅漆木盤捧到族長面前。族長端詳著盤上鮮蹦的活鯉、\n"
					"飽滿的鮮果﹐三牲俱全﹐捋鬚頷首﹐眉開眼笑。\n", me);
				settle_quest(me);
				return 1;
			}

			// 進行中：依「是否已自果園果農討得供果籃」分頭提示（先把整句湊好，再交給 command）
			{
				string line;
				if( !me->query("quest/lijia_offer_fruit") )
					line = "say 還沒著落麼﹖客官且去村心南面的李家果園﹐尋那位看園的果農問問（ask picker about 鮮果）。要配這祭祖的供盤﹐頭一樁便是一籃自家園裡新摘、揀過的供祖鮮果﹐盛果的竹籃他那兒也有﹐討一籃來便是。";
				else if( present("lijiagongguo", me) )
					line = "say 供果既向果農揀著了﹐就去村心東南田埂下去的村南魚塘﹐尋那位守塘的漁戶﹐請他撈尾活鯉、配齊這三牲鮮果的供盤（ask fisher about 鯉魚﹐或 give fruit basket to fisher）。配齊了﹐再持回祠堂我這兒。";
				else
					line = "say 咦﹐先前向果農揀的那籃供果呢﹖客官莫不是失落了﹖不妨事﹐再去李家果園尋果農問問（ask picker about 鮮果），他那兒還記著這樁事。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出祠堂祭祖缺供品、自家要主持族事抽不開身的難處、央玩家揀果配供，設旗標 1
		// 此時不交物——盛果的供果籃須玩家去李家果園向看園果農討。
		me->set("quest/lijia_offer", 1);
		do_chat(({
			(: command, "say 客官問著了老朽的心事。是這麼回事﹕咱李家村合村都是一個老祖宗的子孫﹐這幾日合族要在這宗祠裡祭祀歷代先祖。老朽身為族長﹐少不得備一盤三牲鮮果的供品﹐供奉在先祖牌位前﹐圖個慎終追遠的孝心。" :),
			(: command, "say 偏生這祭祖的供盤﹐最講究的就是鮮果、活鯉兩樣都得新鮮體面﹕果要園裡新摘、揀過的好果子﹐魚要塘裡現撈、鮮蹦的活鯉﹐配上牲禮擺得齊整纔成﹐缺一不可。老朽要主持合族的禮數抽不開身﹐這供品便一直缺著。" :),
			(: command, "say 客官若得閒﹐勞煩替老朽料理這樁事﹕先去村心南面的李家果園﹐尋那位看園果農揀一籃供祖的鮮果、盛進竹籃（ask picker about 鮮果）﹔再到村心東南的村南魚塘﹐尋那位守塘漁戶撈尾活鯉、配齊供盤（ask fisher about 鯉魚）。配齊了﹐持回祠堂來尋老朽（ask elder about 祭祖）﹐老朽必有酬謝﹗" :),
		}));
		return 1;
	}

	// 純氣氛閒談：李家村 / 先祖由來
	if( arg == "elder about 李家村"
	||  arg == "elder about 李家"
	||  arg == "elder about 村"
	||  arg == "elder about lijia" ) {
		do_chat(({
			(: command, "say 客官是頭一回到咱李家村罷﹖咱這小村在雪亭鎮南邊﹐百十年前﹐咱李家的始祖帶著一族人來此落腳開村﹐墾田種果﹐傳到如今﹐合村幾百口人﹐論起來都是他老人家的子孫。" :),
			(: command, "say 聚族而居的村子﹐最重一個孝悌、一個情義。這宗祠便是合族的根﹐一年裡頭幾場祭祖﹐合族老小不論走得多遠﹐都要趕回來上香叩拜。客官若不趕路﹐留下吃碗咱李家的新米飯罷。" :),
		}));
		return 1;
	}

	return notify_fail("族長捋著長鬚和氣一笑﹕客官若是來上香拜祖、歇腳吃飯﹐只管隨意﹔旁的老朽可幫不上甚麼忙。（試試 ask elder about 祭祖）\n");
}

// 收下信物：
//   祭祖供盤(offer tray) -- 支線「祭祖供果」回報﹐持配齊的供盤且任務進行中時
//   收下、給賞、推進旗標 lijia_offer 1 -> 2。
// 不在此 move／destruct 祭祖供盤——give 指令於本函回 1 後會自行 destruct 有值的
// 祭祖供盤（與 d/kangping keeper、d/weiguo keeper、d/ziyan keeper 一致）﹔
// 非回報玩家／時機不符則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("offer tray") ) {
		int q = who->query("quest/lijia_offer");

		// 已完成或未接任務：婉拒，不收下（避免吞掉供盤、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這盤供品 ... 客官還是自個兒收著罷，老朽這會兒用不上。" :));
			return 0;
		}

		// 進行中但還沒配齊供盤（理應不會持有 offer tray，穩妥起見仍判一次）：婉拒
		if( !who->query("quest/lijia_offer_fish") ) {
			do_chat((: command,
				"say 客官這個 ... 莫不是還沒到魚塘配齊供盤罷﹖且先持供果到村南魚塘尋守塘漁戶配齊了﹐老朽纔好驗。" :));
			return 0;
		}

		// 進行中、已配齊供盤、持盤回報：給賞、推進旗標（祭祖供盤由 give 指令於回 1 後自行銷除）
		message_vision(
			"$N把那方紅漆木盤捧到族長面前。族長端詳著盤上鮮蹦的活鯉、\n"
			"飽滿的鮮果﹐三牲俱全﹐捋鬚頷首﹐眉開眼笑。\n", who);
		settle_quest(who);
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老朽用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object player)
{
	do_chat("族長捋鬚正色道﹕這位客官說笑了﹐這是咱李家祭祖的清淨地界﹐老朽一介管村事的莊稼老兒﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
