// keeper.c -- 甘泉客棧的掌櫃；
//             兼婁縣非戰鬥支線「甘泉茶會」的委託人與領賞人。
//
// 任務性質：純小縣氣氛的「採茶、汲泉、回報」支線﹐沒有戰鬥、不需殺任何東西﹐
//           也不靠任何運氣骰子——一路問著、取著、注著、交還即成﹐必定可完成。
//           甘泉客棧的掌櫃要為一位遠來的舊識備一席婁縣最得意的「甘泉茶」﹐偏生
//           自己抽不開身﹐便央玩家去甘泉園向老圃討一撮新摘的「甘泉雀舌」嫩茶、封
//           進茶罐﹐再到甘泉井畔尋守井老叟注一罐井裡的甘泉活水﹐持回客棧交差。
//           本支線自成一套旗標（quest/louxian_spring*）﹐全程不出婁縣這幾間屋子、
//           幾處景緻﹐不讀、不動任何別的任務旗標﹐純加深小縣的人情風味。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/louxian_spring==0) : 玩家 ask keeper about 甘泉 ->
//       掌櫃道出要備甘泉茶待客、自家抽不開身的難處﹐央玩家去甘泉園採茶、
//       甘泉井汲水﹐設 quest/louxian_spring = 1（接任務）。此時不交物——茶罐在老圃處討。
//   採茶汲泉中 (quest/louxian_spring==1) : 玩家分頭辦兩樁（推進在各該 NPC）：
//         - 老圃   (/d/louxian/npc/gardener  ，甘泉園  ) ask about 甘泉
//             -> 交付「茶罐」實物（內封雀舌嫩茶）﹐記 quest/louxian_caddy = 1
//         - 守井老叟 (/d/louxian/npc/welltender，甘泉井  ) 持茶罐
//             ask about 甘泉（或 give tea caddy to welltender）
//             -> 注泉﹕銷茶罐、交付「甘泉茶罐」實物﹐記 quest/louxian_filled = 1
//   可回報 (持甘泉茶罐在身) : 玩家持滿罐回客棧﹐
//         ask keeper about 甘泉（或 give spring caddy to keeper）->
//         掌櫃驗看茶水、收下﹐給賞﹐設 quest/louxian_spring = 2（完成﹐防重領）。
//   注：driver 的 give 指令僅認 "give <物> to <人>" / "give <人> <物>"﹐不認中文「給」﹔
//       故每個交還點都另備 "ask <npc> about 甘泉" 的等效完成路徑（持物時 ask 即送件／
//       回報﹐由各該 NPC 同步給物或給賞﹐並自行銷除手中的送件信物）﹐確保必可完成。
//   已完成 (quest/louxian_spring>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("掌櫃", ({ "louxian keeper", "keeper", "innkeeper" }) );
	set("nickname", "掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 47);
	set("gender", "male");
	set("long",
		"這位是甘泉客棧的掌櫃﹐生得白胖和氣﹐一張笑臉終日不\n"
		"離﹐待客最是周到熱絡﹐這「甘泉」二字的招牌在婁縣裡也算\n"
		"叫得響。近來他卻時時對著前廳那口水缸出神﹐捻著指頭盤算\n"
		"著甚麼﹐似有一樁掛心的喜事。倦了的話﹐不妨在這客棧裡尋\n"
		"張床鋪﹐好生歇歇腳﹔得閒也可問問他﹕ask keeper about 甘泉。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃笑容可掬地招呼道﹕客官打尖還是住店﹖咱這甘泉煮的茶水﹐比別處的都甜上三分哩﹗\n",
		"掌櫃對著前廳那口水缸出神﹐捻著指頭喃喃道﹕那席甘泉茶﹐茶葉、井水﹐可得樣樣地道纔成 ...\n",
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
		&&  this_player()->query("quest/louxian_spring") == 1 )
			do_chat((: command,
				"say 客官﹐託你張羅的那席甘泉茶的茶料﹐可有著落了麼﹖" :));
		else
			do_chat((: command,
				"say 客官裡邊請﹗本店床鋪潔淨﹐甘泉煮茶﹐包您住得稱心﹗" :));
	}
}

// 領賞：給一封碎銀、一串銅錢、一面客棧記給嘉賓的「甘泉竹牌」﹐
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

	charm = new(__DIR__"obj/ganquan_token");
	if( !charm->move(who) ) charm->move(environment());

	who->gain_score("survive", 90);
	who->gain_score("explorer fame", 50);
	who->gain_score("reputation", 30);

	message_vision(
		"掌櫃眉開眼笑﹐自錢匣裡數出一小封碎銀、一串銅錢﹐又取出一面\n"
		"烙著「甘泉」的竹牌﹐一併塞到$N手裡﹐連聲道謝。\n",
		who);
}

// 收尾／回報：玩家把甘泉茶罐交(give)回時，由 accept_object 觸發。
// 驗看茶水、給賞、設旗標 2（完成）。本函不經手甘泉茶罐物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的甘泉茶罐（與 d/shuiyue keeper、
// d/fancheng boatman 一致）。
private void settle_quest(object me)
{
	// 收罐即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——甘泉茶罐已被 give 指令於 accept_object 回 1 後
	// 銷除﹐若賞落在延遲回呼又逢玩家離場﹐便會「罐沒了、賞沒領、旗標卻記完成」
	// 而卡關。do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/louxian_spring", 2);
	do_chat(({
		(: command, "say 哎呀﹐茶料齊了﹗快與小老兒瞧瞧——唔﹐這雀舌嫩得正好﹐這井水又清又甜﹐茶配水﹐樣樣地道﹗客官這趟跑得仔細﹐可解了小老兒一樁心事。" :),
		(: command, "say 不瞞客官﹐這席茶是備給一位多年不見的舊識的﹐他最念著咱婁縣這口甘泉的味兒。如今茶、水俱備﹐小老兒這便能烹一席像樣的甘泉茶待他了。這點碎銀銅錢﹐方纔已塞到客官手裡﹐務必收好。" :),
		(: command, "say 另有一面『甘泉竹牌』﹐也一併與客官﹐往後打婁縣經過﹐只管進店歇腳吃茶﹐圖個甘泉潤客的好意頭﹗本店悅近來遠﹐客官常來﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位掌櫃甚麼﹖（試試 ask keeper about 甘泉）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("掌櫃正撥著算盤核帳﹐一時沒空理你。\n");

	// 甘泉 / 茶會 / 茶料：非戰鬥支線「甘泉茶會」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」「茶罐」等問法﹐方便玩家中途確認進度）
	if( arg == "keeper about 甘泉"
	||  arg == "louxian keeper about 甘泉"
	||  arg == "innkeeper about 甘泉"
	||  arg == "keeper about 泉"
	||  arg == "keeper about 茶"
	||  arg == "keeper about 茶會"
	||  arg == "keeper about 茶料"
	||  arg == "keeper about 茶罐"
	||  arg == "keeper about 任務"
	||  arg == "keeper about spring"
	||  arg == "keeper about tea"
	||  arg == "keeper about quest" ) {
		object me = this_player();
		int q = me->query("quest/louxian_spring");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替小店張羅了那席甘泉茶的茶料﹐那位舊識嚐了﹐連說還是這口甘泉的味兒地道﹐歡喜得很哩。" :),
				(: command, "say 往後過婁縣﹐只管進店歇腳吃茶。甘泉客棧這四個字﹐圖的就是個賓至如歸﹗" :),
			}));
			return 1;
		}

		// 採茶汲泉中（已接任務）：持滿罐則 ask 即驗茶領賞﹐否則依進度提示下一步
		if( q == 1 ) {
			// 已注得甘泉：ask keeper about 甘泉 即當作回報——驗看茶水、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的甘泉茶罐（與 accept_object
			// 經 give 指令回 1 後自動銷除甘泉茶罐等效）。縱甘泉茶罐失落亦直接認功給賞﹐免卡關。
			if( me->query("quest/louxian_filled") ) {
				object caddy = present("spring caddy", me);
				if( caddy ) destruct(caddy);
				message_vision(
					"$N把那隻茶水俱備的甘泉茶罐奉與掌櫃。掌櫃揭了油紙的封口﹐\n"
					"就著鼻子聞了聞﹐又撚出一葉茶來細看﹐眉開眼笑。\n", me);
				settle_quest(me);
				return 1;
			}

			// 進行中：依「是否已自老圃討得茶罐」分頭提示（先把整句湊好，再交給 command）
			{
				string line;
				if( !me->query("quest/louxian_caddy") )
					line = "say 還沒著落麼﹖客官且去街心北邊的甘泉園﹐尋那位侍弄茶圃的老圃問問（ask gardener about 甘泉）。那園裡的『甘泉雀舌』是頂好的茶﹐封茶的小罐他也有﹐討一隻來便是。";
				else if( present("tea caddy", me) )
					line = "say 茶罐既向老圃討著了﹐就去街心北邊的甘泉井畔﹐尋那位守井的老叟﹐注一罐井裡的甘泉活水回來（ask welltender about 甘泉﹐或 give tea caddy to welltender）。注滿了﹐再持回小老兒這兒。";
				else
					line = "say 咦﹐先前向老圃討的那隻茶罐呢﹖客官莫不是失落了﹖不妨事﹐再去甘泉園尋老圃問問（ask gardener about 甘泉），他那兒還記著這樁事。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出要備甘泉茶待客、自家抽不開身的難處、央玩家採茶汲泉，設旗標 1
		// 此時不交物——封茶的茶罐須玩家去甘泉園向老圃討。
		me->set("quest/louxian_spring", 1);
		do_chat(({
			(: command, "say 客官問著了小老兒的心事。是這麼回事﹕過幾日有位多年不見的舊識要打這兒過﹐他早年在咱婁縣住過﹐最念著這口甘泉煮的茶。小老兒想備一席像樣的甘泉茶﹐好好待他一回。" :),
			(: command, "say 偏生這甘泉茶﹐最講究的就是茶、水兩樣都得地道﹕茶要甘泉園裡新摘的『甘泉雀舌』﹐水要井裡剛汲的甘泉活水﹐缺一不可。小老兒守著店抽不開身﹐這事便一直擱著。" :),
			(: command, "say 客官若得閒﹐勞煩替小老兒料理這樁事﹕先去街心北邊的甘泉園﹐尋那位老圃討一撮新摘的雀舌、封進茶罐（ask gardener about 甘泉）﹔再到甘泉井畔﹐尋守井老叟注一罐井裡的甘泉活水（ask welltender about 甘泉）。齊備了﹐持回客棧來尋小老兒（ask keeper about 甘泉）﹐小老兒必有酬謝﹗" :),
		}));
		return 1;
	}

	return notify_fail("掌櫃陪笑道﹕客官若是打尖住店﹐只管吩咐﹔旁的小老兒可幫不上甚麼忙。（試試 ask keeper about 甘泉）\n");
}

// 收下信物：
//   甘泉茶罐(spring caddy) -- 支線「甘泉茶會」回報﹐持滿罐且任務進行中時
//   收下、給賞、推進旗標 louxian_spring 1 -> 2。
// 不在此 move／destruct 甘泉茶罐——give 指令於本函回 1 後會自行 destruct 有值的
// 甘泉茶罐（與 d/shuiyue keeper、d/fancheng boatman 一致）﹔非回報玩家／時機不符
// 則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("spring caddy") ) {
		int q = who->query("quest/louxian_spring");

		// 已完成或未接任務：婉拒，不收下（避免吞掉甘泉茶罐、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這罐茶 ... 客官還是自個兒收著罷，小老兒這會兒用不上。" :));
			return 0;
		}

		// 進行中但還沒注得甘泉（理應不會持有 spring caddy，穩妥起見仍判一次）：婉拒
		if( !who->query("quest/louxian_filled") ) {
			do_chat((: command,
				"say 客官這罐 ... 莫不是還沒到井畔注水罷﹖且先持茶罐到甘泉井尋守井老叟注一罐甘泉來﹐小老兒纔好驗。" :));
			return 0;
		}

		// 進行中、已注得甘泉、持滿罐回報：給賞、推進旗標（甘泉茶罐由 give 指令於回 1 後自行銷除）
		message_vision(
			"$N把那隻茶水俱備的甘泉茶罐奉與掌櫃。掌櫃揭了油紙的封口﹐\n"
			"就著鼻子聞了聞﹐又撚出一葉茶來細看﹐眉開眼笑。\n", who);
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
