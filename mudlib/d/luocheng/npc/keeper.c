// keeper.c -- 羅城客棧的掌櫃；
//             兼羅城非戰鬥支線「羅城客棧的尋硯」的委託人與領賞人。
//
// 任務性質：純羅城氣氛的「尋物、送還、回報」支線﹐沒有戰鬥、不需殺任何東西﹐
//           也不靠任何運氣骰子——一路問著、取著、送還即成﹐必定可完成。一位匆匆
//           離店的候缺選官把一方心愛的端硯遺落在客棧﹐教店小二掃堂時收進了櫃格﹐
//           擱久了竟忘了原主﹔那選官如今正在隔鄰的聽濤茶樓對著冷茶出神。掌櫃要保
//           全客棧的臉面﹐央玩家把硯自店小二處取回、送還茶樓的選官﹐再帶選官的謝
//           帖回來回報。本支線自成一套旗標（quest/luocheng_yan*）﹐全程不出羅城這
//           幾間屋子﹐不讀、不動任何別的任務旗標（尤其不碰相府統領的雍和／朝廷／
//           侮天鬼／聖木主線伏筆）﹐純加深近畿顯貴衛城的市井人情。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/luocheng_yan==0) : 玩家 ask keeper about 端硯 ->
//       掌櫃道出選官遺硯、店小二誤收的難處﹐央玩家把硯取回、送還原主﹐
//       設 quest/luocheng_yan = 1（接下任務）。此時不交物——硯在店小二手裡。
//   尋物送還中 (quest/luocheng_yan==1) : 玩家分頭辦兩樁（推進在各該 NPC）：
//         - 店小二 (/d/luocheng/npc/barkeep，客棧前廳) ask about 端硯
//             -> 交付「端硯」實物﹐記 quest/luocheng_yan_found = 1
//         - 候缺選官 (/d/luocheng/npc/tea_guest，聽濤茶樓) give 端硯（或
//             ask about 端硯）-> 收回端硯、交付「謝帖」實物﹐
//             記 quest/luocheng_yan_returned = 1
//   可回報 (持謝帖在身) : 玩家持謝帖回客棧﹐
//         ask keeper about 端硯（或 give 謝帖 to keeper）->
//         掌櫃驗看謝帖、收下﹐給賞﹐設 quest/luocheng_yan = 2（完成﹐防重領）。
//   注：driver 的 give 指令僅認 "give <物> to <人>" / "give <人> <物>"﹐不認中文「給」﹔
//       故每個交還點都另備 "ask <npc> about 端硯" 的等效完成路徑（持物時 ask 即送件／
//       回報﹐由各該 NPC 同步給物或給賞﹐並自行銷除手中的送件信物）﹐確保必可完成。
//   已完成 (quest/luocheng_yan>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("掌櫃", ({ "luocheng keeper", "keeper", "innkeeper" }) );
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 50);
	set("gender", "male");
	set("long",
		"這位是羅城客棧的掌櫃﹐生得圓臉福相﹐一雙眼睛笑成了兩\n"
		"道縫﹐一手算盤撥得劈啪作響﹐一張嘴更是八面玲瓏。他迎送\n"
		"的多是候缺謁選的官人﹐應對進退極有分寸﹐連奉承都奉承得\n"
		"不著痕跡。近來他卻為著一樁客人遺落的物事暗暗犯愁﹐生怕\n"
		"墮了客棧待客周到的名聲。倦了的話﹐不妨在這客棧裡好生歇\n"
		"歇﹔得閒也可問問他﹕ask keeper about 端硯。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"掌櫃撥著算盤﹐口中念念有詞地核著今日的帳目。\n",
		"掌櫃滿面堆笑地招呼道﹕這位老爺打尖還是住店﹖樓上的上房清靜雅致﹐最宜養神哩﹗\n",
		"掌櫃壓低聲音道﹕往西出城走上一程便是帝都京畿了﹐老爺是要進京謁選的罷﹖小店住的多是這樣的貴客哩。\n",
	}));
	setup();
	carry_money("coin", 300);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( !is_fighting() ) {
		if( this_player() && interactive(this_player())
		&&  this_player()->query("quest/luocheng_yan") == 1 )
			do_chat((: command,
				"say 這位客官﹐託你料理的那方遺硯﹐可送還原主了麼﹖" :));
	}
}

// 領賞：給一封碎銀、一串銅錢、一枝客棧備著饋客的湖筆﹐
// 並授江湖歷練、行旅見聞與一點市井聲望。
// 採直接 new + move(who) 交付﹐move 回 1 為成功（落在玩家身上）﹐
// 回 0（失敗）才退而落到地上﹐不走會因玩家走開而落空的延遲回呼。
private void give_reward(object who)
{
	object silver, coin, pen;

	if( !who || environment(who) != environment() ) return;

	silver = new("/obj/money/silver");
	silver->set_amount(1);
	if( !silver->move(who) ) silver->move(environment());

	coin = new("/obj/money/coin");
	coin->set_amount(50);
	if( !coin->move(who) ) coin->move(environment());

	pen = new(__DIR__"obj/wenfang_pen");
	if( !pen->move(who) ) pen->move(environment());

	who->gain_score("survive", 90);
	who->gain_score("explorer fame", 50);
	who->gain_score("reputation", 30);

	message_vision(
		"掌櫃眉開眼笑﹐自錢匣裡數出一小封碎銀、一串銅錢﹐又取出一枝\n"
		"刻著「羅城客棧」的湖筆﹐一併塞到$N手裡﹐連聲道謝。\n",
		who);
}

// 收尾／回報：玩家把謝帖交(give)回時，由 accept_object 觸發。
// 驗看謝帖、給賞、設旗標 2（完成）。本函不經手謝帖物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的謝帖（與 d/fancheng boatman、
// d/feixian keeper、d/fengcheng fortuneteller 一致）。
private void settle_quest(object me)
{
	// 收帖即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——謝帖已被 give 指令於 accept_object 回 1 後
	// 銷除﹐若賞落在延遲回呼又逢玩家離場﹐便會「帖沒了、賞沒領、旗標卻記完成」
	// 而卡關。do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/luocheng_yan", 2);
	do_chat(({
		(: command, "say 哎呀﹐這不是周老爺的謝帖麼﹖快與小老兒瞧瞧——唔﹐失硯復得、申謝叨擾﹐還記著託客官捎句後會有期的話。好哇好哇﹐那方硯總算物歸原主了﹗" :),
		(: command, "say 客人遺落的物事在小店出了岔子﹐這臉面上頭最是要緊﹐小老兒這幾日提著的心﹐可算落了地。客官這趟跑得周到﹐既全了周老爺的心愛之物﹐也全了小店待客的名聲。" :),
		(: command, "say 這點碎銀銅錢﹐方纔已塞到客官手裡﹐務必收好。另有一枝小店饋客的湖筆﹐也一併與客官﹐圖個書卷的雅氣。往後過羅城﹐只管進店歇腳吃茶﹐小店悅近來遠﹐客官常來﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位掌櫃甚麼﹖（試試 ask keeper about 端硯）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("掌櫃正撥著算盤核帳﹐一時沒空理你。\n");

	// 端硯 / 遺硯：非戰鬥支線「羅城客棧的尋硯」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」「失物」等問法﹐方便玩家中途確認進度）
	if( arg == "keeper about 端硯"
	||  arg == "luocheng keeper about 端硯"
	||  arg == "innkeeper about 端硯"
	||  arg == "keeper about 硯"
	||  arg == "keeper about 遺硯"
	||  arg == "keeper about 失物"
	||  arg == "keeper about 謝帖"
	||  arg == "keeper about 任務"
	||  arg == "keeper about inkstone"
	||  arg == "keeper about yan"
	||  arg == "keeper about quest" ) {
		object me = this_player();
		int q = me->query("quest/luocheng_yan");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替小店把那方遺硯送還了周老爺﹐了結了這樁失物﹐小店待客周到的名聲﹐可全仗客官保全了。" :),
				(: command, "say 往後過羅城﹐只管進店歇腳吃茶。羅城客棧這四個字﹐圖的就是個賓至如歸﹗" :),
			}));
			return 1;
		}

		// 尋物送還中（已接任務）：依進度提示下一步，已送還原主則 ask 即驗帖領賞
		if( q == 1 ) {
			// 已送還原主：ask keeper about 端硯 即當作回報——驗看謝帖、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的謝帖（與 accept_object
			// 經 give 指令回 1 後自動銷除謝帖等效）。謝帖縱失落也直接認功給賞﹐免卡關。
			if( me->query("quest/luocheng_yan_returned") ) {
				object note = present("thank note", me);
				if( note ) destruct(note);
				settle_quest(me);
				return 1;
			}

			// 進行中：依「是否已自店小二取得端硯」分頭提示（先把整句湊好，再交給 command）
			{
				string line;
				if( !me->query("quest/luocheng_yan_found") )
					line = "say 還沒著落麼﹖那方硯﹐多半是教掃堂的店小二連著雜物收進櫃格去了。客官且去前廳尋那店小二問問（ask barkeep about 端硯）﹐把硯取回來。";
				else if( present("duan yan", me) )
					line = "say 硯既自店小二處取回來了﹐快趁周老爺還在聽濤茶樓﹐把這方硯送還與他（ask tea guest about 端硯﹐或 give 端硯 to tea guest）。他失而復得﹐必定歡喜。";
				else
					line = "say 咦﹐先前取回的那方端硯呢﹖客官莫不是失落了﹖不妨事﹐客官再去前廳尋店小二問問（ask barkeep about 端硯），他那兒還記著這樁事。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出選官遺硯、店小二誤收的難處、央玩家取回送還，設旗標 1
		// 此時不交物——硯在店小二手裡，須玩家去前廳向店小二討。
		me->set("quest/luocheng_yan", 1);
		do_chat(({
			(: command, "say 唉﹐客官問著了小老兒的一樁心病。是這麼回事﹕半月前有位姓周的選官在小店歇了幾日﹐忽得了候補的信兒﹐慌慌張張便往京裡赴任去了﹐臨走竟把一方隨身的端硯落在了上房。" :),
			(: command, "say 偏生那日小店待客忙亂﹐掃堂的店小二把那方硯當作客人不要的零碎﹐連著雜物一併收進了櫃格﹐擱了這些時日﹐竟忘了原主。前兒個小老兒盤點櫃格﹐方瞧見那方硯﹐這才想起是周老爺的心愛之物——客人遺落的物事在小店出了這等岔子﹐傳揚出去﹐小店這臉面可往哪兒擱﹖" :),
			(: command, "say 說來也巧﹐那周老爺赴任未成﹐近日又回了京﹐這會兒正在隔鄰的聽濤茶樓裡候缺呢。客官若得閒﹐勞煩替小老兒料理這樁失物﹕先去前廳尋那店小二﹐把硯取回來（ask barkeep about 端硯）﹔再趁周老爺還在茶樓﹐把硯送還與他（ask tea guest about 端硯）。事辦妥了﹐持周老爺的回信兒回來尋小老兒（ask keeper about 端硯）﹐小老兒必有酬謝﹗" :),
		}));
		return 1;
	}

	return notify_fail("掌櫃陪笑道﹕客官若是打尖住店﹐只管吩咐﹔旁的小老兒可幫不上甚麼忙。（試試 ask keeper about 端硯）\n");
}

// 收下信物：
//   謝帖(thank note) -- 支線「羅城客棧的尋硯」回報﹐持帖且任務進行中時
//   收下、給賞、推進旗標 luocheng_yan 1 -> 2。
// 不在此 move／destruct 謝帖——give 指令於本函回 1 後會自行 destruct 有值的
// 謝帖（與 d/fancheng boatman 一致）﹔非回報玩家／時機不符則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("thank note") ) {
		int q = who->query("quest/luocheng_yan");

		// 已完成或未接任務：婉拒，不收下（避免吞掉謝帖、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這謝帖 ... 客官還是自個兒收著罷，小老兒這會兒用不上。" :));
			return 0;
		}

		// 進行中但硯還沒送還原主：婉拒，提示尚須先送還端硯
		if( !who->query("quest/luocheng_yan_returned") ) {
			do_chat((: command,
				"say 咦﹖這謝帖 ... 客官莫不是還沒把硯送還周老爺罷﹖客官且先持那方端硯到聽濤茶樓尋他﹐give 與他﹐他自會有個准信兒。" :));
			return 0;
		}

		// 進行中、已送還原主、持帖回報：給賞、推進旗標（謝帖由 give 指令於回 1 後自行銷除）
		settle_quest(who);
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個小老兒用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object player)
{
	do_chat("掌櫃陪笑道﹕這位老爺說笑了﹐小老兒一介生意人﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
