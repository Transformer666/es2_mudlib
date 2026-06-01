// keeper.c -- 悅客來客棧的掌櫃；
//             兼斐縣非戰鬥支線「悅客來的散帳」的委託人與領賞人。
//
// 任務性質：純縣城氣氛的「核帳、跑腿」支線﹐沒有戰鬥、不需殺任何東西﹐
//           也不靠任何運氣骰子——一路問著、交還即成﹐必定可完成。只是
//           替客棧掌櫃持收帳冊到城裡三家鋪子核對過路客商賒下的舊帳﹐再
//           交還掌櫃對帳。本支線自成一套旗標（quest/feixian_tab*）﹐全程
//           不出斐縣這八間屋子﹐不讀、不動任何別的任務旗標﹐純加深小縣
//           城市井往來的氣氛。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/feixian_tab==0) : 玩家 ask keeper about 散帳 ->
//       掌櫃道出客棧帳簿與各鋪賒帳對不攏的難處﹐當場交付一本「收帳冊」
//       實物﹐央玩家代為到三家鋪子核帳﹐設 quest/feixian_tab = 1（接任務）。
//   核帳中 (quest/feixian_tab==1) : 玩家持收帳冊﹐分頭到三家鋪子核賒帳
//       （推進在各該 NPC﹐皆須收帳冊在身方肯核）：
//         - 酒保   (/d/feixian/npc/barman ，錢記酒樓) ask about 賒帳
//             -> quest/feixian_tab_tavern = 1
//         - 茶博士 (/d/feixian/npc/teaman ，清風茶行) ask about 賒帳
//             -> quest/feixian_tab_tea    = 1
//         - 雜貨郎 (/d/feixian/npc/peddler，雜貨鋪  ) ask about 賒帳
//             -> quest/feixian_tab_shop   = 1
//       每核一家﹐quest/feixian_tab_count 計數 +1（0->3）。
//   可回報 (三家齊核、且持收帳冊在身) : 玩家持冊回客棧﹐
//       give 收帳冊 給 keeper（或 ask keeper about 散帳）->
//       掌櫃驗看收帳冊、收下對帳﹐給賞﹐設 quest/feixian_tab = 2（完成﹐防重領）。
//   已完成 (quest/feixian_tab>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("掌櫃", ({ "keeper", "innkeeper", "feixian_keeper" }) );
	set("nickname", "掌櫃");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 47);
	set("gender", "male");
	set("long",
		"這位是悅客來客棧的掌櫃﹐生得白胖和氣﹐一張笑臉終日不\n"
		"離﹐待客最是周到熱絡﹐難怪這「悅客來」三字的招牌叫得響。\n"
		"近來他撥著算盤直皺眉﹐似為店裡一樁對不攏的舊帳犯愁。倦了\n"
		"的話﹐不妨在這乾淨清靜的客棧裡尋張床鋪﹐好生歇歇腳﹔得閒\n"
		"也可問問他﹕ask keeper about 散帳。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃笑容可掬地招呼道﹕客官打尖還是住店﹖樓上的客房乾爽清靜﹐保管睡個好覺﹗\n",
		"掌櫃捋著袖子道﹕客官是打喬陰那頭過來的罷﹖那條土道近來平整﹐走著倒也不累。\n",
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
		&&  this_player()->query("quest/feixian_tab") == 1 )
			do_chat((: command,
				"say 客官﹐託你拿著收帳冊去核的那幾筆賒帳﹐可核齊了麼﹖" :));
		else
			do_chat((: command,
				"say 客官裡邊請﹗本店床鋪潔淨、茶飯齊整﹐包您住得稱心﹗" :));
	}
}

// 領賞：給一封碎銀、一串銅錢、一面客棧記給熟客的「常來竹牌」﹐
// 並授江湖歷練、行旅見聞與一點市井聲望。
// 採直接 new + move(who) 交付﹐move 回 1 為成功（落在玩家身上）﹐
// 回 0（失敗）才退而落到地上﹐不走會因玩家走開而落空的延遲回呼。
private void give_reward(object who)
{
	object silver, coin, tab;

	if( !who || environment(who) != environment() ) return;

	silver = new("/obj/money/silver");
	silver->set_amount(1);
	if( !silver->move(who) ) silver->move(environment());

	coin = new("/obj/money/coin");
	coin->set_amount(50);
	if( !coin->move(who) ) coin->move(environment());

	tab = new(__DIR__"obj/lucky_tab");
	if( !tab->move(who) ) tab->move(environment());

	who->gain_score("survive", 90);
	who->gain_score("explorer fame", 50);
	who->gain_score("reputation", 30);

	message_vision(
		"掌櫃眉開眼笑﹐自錢匣裡數出一小封碎銀、一串銅錢﹐又取出一面\n"
		"烙著「悅客來」的常來竹牌﹐一併塞到$N手裡﹐連聲道謝。\n",
		who);
}

// 收尾／回報：玩家把收帳冊交(give)回時，由 accept_object 觸發。
// 驗看收帳冊、給賞、設旗標 2（完成）。本函不經手收帳冊物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的收帳冊（與 d/fancheng boatman 一致）。
private void settle_quest(object me)
{
	// 收冊即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——收帳冊已被 give 指令於 accept_object 回 1 後
	// 銷除﹐若賞落在延遲回呼又逢玩家離場﹐便會「冊沒了、賞沒領、旗標卻記完成」
	// 而卡關。do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/feixian_tab", 2);
	do_chat(({
		(: command, "say 哎呀﹐都核齊啦﹖快與小老兒瞧瞧——唔﹐錢記的酒帳、清風的茶帳、雜貨鋪的零碎﹐筆筆都對上了號﹗客官這趟跑得仔細﹐可解了小老兒一樁心病。" :),
		(: command, "say 這幾筆陳年的散帳對不攏﹐小老兒夜裡撥算盤都撥不安生。如今帳一清﹐心也定了。這點碎銀銅錢﹐方纔已塞到客官手裡﹐務必收好。" :),
		(: command, "say 另有一面『常來竹牌』﹐也一併與客官﹐往後打斐縣經過﹐只管進店歇腳吃茶﹐圖個情分﹗本店悅近來遠﹐客官常來﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位掌櫃甚麼﹖（試試 ask keeper about 散帳）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("掌櫃正撥著算盤核帳﹐一時沒空理你。\n");

	// 散帳 / 收帳冊：非戰鬥支線「悅客來的散帳」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」「賒帳」等問法﹐方便玩家中途確認進度）
	if( arg == "keeper about 散帳"
	||  arg == "innkeeper about 散帳"
	||  arg == "keeper about 收帳冊"
	||  arg == "keeper about 收帳"
	||  arg == "keeper about 賒帳"
	||  arg == "keeper about 對帳"
	||  arg == "keeper about 帳"
	||  arg == "keeper about 任務"
	||  arg == "keeper about tab"
	||  arg == "keeper about ledger"
	||  arg == "keeper about quest" ) {
		object me = this_player();
		int q = me->query("quest/feixian_tab");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替小老兒把那幾筆散帳核了個明白﹐如今帳簿與各鋪的條子筆筆對得上號﹐小老兒這心裡頭﹐踏實多啦。" :),
				(: command, "say 客官持著那面常來竹牌﹐便是本店記著的老主顧了。往後過斐縣﹐只管進來歇腳﹐悅客來這三個字﹐圖的就是個賓至如歸﹗" :),
			}));
			return 1;
		}

		// 核帳中（已接任務）：三家齊核則提示交冊領賞，否則報還差哪幾家
		if( q == 1 ) {
			int n = me->query("quest/feixian_tab_count");

			// 防卡關：任務中若收帳冊不在身上（失落／誤毀），補發一本﹐進度旗標不動。
			if( !present("tab ledger", me) ) {
				object book = new(__DIR__"obj/tab_ledger");
				if( !book->move(me) ) book->move(environment());
				do_chat((: command,
					"say 咦﹐客官的收帳冊呢﹖莫不是失落了﹖不妨事﹐小老兒這兒還有底冊﹐再與客官補一本﹐先前核過的小老兒都記著﹐客官接著核未了的便是。" :));
				return 1;
			}

			// 三家齊核、且持收帳冊在身：ask 即當作回報——驗冊、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的收帳冊（與 accept_object
			// 經 give 指令回 1 後自動銷除收帳冊等效﹐免玩家留著「已交」的冊重複觸發）。
			// 註：上面已先補發過失落的收帳冊﹐故能行到此處必持冊在身。
			if( n >= 3 ) {
				if( present("tab ledger", me) ) {
					object book = present("tab ledger", me);
					message_vision(
						"$N雙手把那本收帳冊奉還掌櫃。掌櫃接過攤在櫃上﹐撥著算盤\n"
						"逐筆與店裡的帳簿核對﹐眉頭漸漸舒展開來。\n", me);
					// 先同步給賞、記旗標﹐再銷除收帳冊（與 accept_object 經 give 等效）。
					settle_quest(me);
					if( book ) destruct(book);
				} else
					do_chat((: command,
						"say 咦﹐那本收帳冊呢﹖客官莫不是失落了﹖沒了冊子﹐小老兒這帳可對不成。客官仔細尋尋﹐尋著了再來。" :));
				return 1;
			}

			// 未齊：報還差哪幾家未核（先把整句湊好，再交給 command）
			{
				string s = "";
				string line;
				if( !me->query("quest/feixian_tab_tavern") )
					s += "西邊錢記酒樓的酒保（ask 酒保 about 賒帳）、";
				if( !me->query("quest/feixian_tab_tea") )
					s += "北邊清風茶行的茶博士（ask 茶博士 about 賒帳）、";
				if( !me->query("quest/feixian_tab_shop") )
					s += "縣前街雜貨鋪的雜貨郎（ask 雜貨郎 about 賒帳）、";
				line = "say 才核著" + n + "家哩﹐還不齊。客官持著收帳冊﹐再去尋"
					+ s + "把賒帳的條子核對謄錄回來﹐三家都核齊了﹐再持冊回客棧來尋小老兒對帳。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出散帳難處、當場交付收帳冊、央玩家代核，設旗標 1
		// 收帳冊為直接 new+move 交付﹐玩家此刻必在場（do_ask 由玩家觸發）。
		{
			object book = new(__DIR__"obj/tab_ledger");
			if( !book->move(me) ) book->move(environment());
		}
		me->set("quest/feixian_tab", 1);
		do_chat(({
			(: command, "say 唉﹐客官問著了小老兒的心事。是這麼回事﹕咱悅客來在這五向路口開店﹐南來北往的客商多﹐有那相熟的、趕著上路的﹐一時手頭不便﹐便在城裡幾家相與的鋪子賒下些酒飯茶水﹐記在咱悅客來的帳上﹐回頭一併結。" :),
			(: command, "say 偏生年深日久﹐人來人往﹐咱店裡的帳簿與各鋪自記的條子﹐竟對不攏了﹐多一筆少一筆的﹐小老兒撥算盤都撥不安生。小老兒守著店走不開﹐這事便一直擱著。" :),
			(: command, "say 客官若得閒﹐勞煩持這本收帳冊﹐替小老兒跑一趟﹕到西邊錢記酒樓尋酒保、北邊清風茶行尋茶博士、縣前街雜貨鋪尋雜貨郎﹐分頭 ask 他們 about 賒帳﹐把各鋪代記的賒帳條子核對謄錄回來。三家都核齊了﹐再持冊回客棧來尋小老兒對帳﹐小老兒必有酬謝﹗" :),
		}));
		return 1;
	}

	return notify_fail("掌櫃陪笑道﹕客官若是打尖住店﹐只管吩咐﹔旁的小老兒可幫不上甚麼忙。（試試 ask keeper about 散帳）\n");
}

// 收下信物：
//   收帳冊(tab ledger) -- 支線「悅客來的散帳」送件﹐持冊且三家齊核時
//   收下、給賞、推進旗標 feixian_tab 1 -> 2。
// 不在此 move／destruct 收帳冊——give 指令於本函回 1 後會自行 destruct 有值的
// 收帳冊（與 d/fancheng boatman 一致）﹔非送件玩家／未齊核則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("tab ledger") ) {
		int q = who->query("quest/feixian_tab");

		// 已完成或未接任務：婉拒，不收下（避免吞掉收帳冊、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這收帳冊 ... 客官還是自個兒收著罷，小老兒這會兒用不上。" :));
			return 0;
		}

		// 進行中但三家未齊：婉拒，提示尚須核齊三家
		if( who->query("quest/feixian_tab_count") < 3 ) {
			do_chat((: command,
				"say 帳還沒核齊哩。客官且先持著這冊子﹐到錢記酒樓、清風茶行、雜貨鋪三處 ask 他們 about 賒帳﹐把賒帳的條子都核對謄錄了﹐小老兒纔好對帳。" :));
			return 0;
		}

		// 進行中、三家齊核：給賞、推進旗標（收帳冊由 give 指令於回 1 後自行銷除）
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
