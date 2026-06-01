// keeper.c -- 康平小店的店家；
//             兼康平村非戰鬥支線「康平新米飯糰」的委託人與領賞人。
//
// 任務性質：純莊稼村子氣氛的「碾米、蒸飯、回報」支線﹐沒有戰鬥、不需殺任何東西﹐
//           也不靠任何運氣骰子——一路問著、碾著、蒸著、交還即成﹐必定可完成。
//           康平小店的店家要為村裡的秋收謝場備一籠村裡最家常的喜飯「新米飯糰」﹐
//           偏生守著店灶抽不開身﹐便央玩家去村外田壟向田裡老農碾一缽自家新收的新
//           米、盛進陶缽﹐再到井臺尋灶上嬸子上籠蒸成新米飯糰﹐持回小店交差。
//           本支線自成一套旗標（quest/kangping_rice*）﹐全程不出康平村這幾間屋子、
//           幾處景緻﹐不讀、不動任何別的任務旗標﹐純加深莊稼村子的人情風味。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/kangping_rice==0) : 玩家 ask keeper about 新米 ->
//       店家道出要備新米飯糰辦秋收謝場、自家抽不開身的難處﹐央玩家去碾米蒸飯﹐
//       設 quest/kangping_rice = 1（接任務）。此時不交物——盛米的陶缽在田裡老農處討。
//   碾米蒸飯中 (quest/kangping_rice==1) : 玩家分頭辦兩樁（推進在各該 NPC）：
//         - 田裡老農 (/d/kangping/npc/farmer，村外田壟) ask about 新米
//             -> 交付「新米陶缽」實物（內盛新碾的新米）﹐記 quest/kangping_rice_bowl = 1
//         - 灶上嬸子 (/d/kangping/npc/cook  ，康平井臺) 持新米陶缽
//             ask about 新米（或 give rice bowl to cook）
//             -> 蒸飯﹕銷新米陶缽、交付「新米飯糰」實物﹐記 quest/kangping_rice_dough = 1
//   可回報 (持新米飯糰在身) : 玩家持蒸好的新米飯糰回小店﹐
//         ask keeper about 新米（或 give rice dough to keeper）->
//         店家驗看飯糰、收下﹐給賞﹐設 quest/kangping_rice = 2（完成﹐防重領）。
//   注：driver 的 give 指令僅認 "give <物> to <人>" / "give <人> <物>"﹐不認中文「給」﹔
//       故每個交還點都另備 "ask <npc> about 新米" 的等效完成路徑（持物時 ask 即送件／
//       回報﹐由各該 NPC 同步給物或給賞﹐並自行銷除手中的送件信物）﹐確保必可完成。
//   已完成 (quest/kangping_rice>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("店家", ({ "kangping keeper", "keeper", "innkeeper" }) );
	set("nickname", "店家");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 48);
	set("gender", "male");
	set("long",
		"這位是康平小店的店家﹐生得敦實和氣﹐一張莊稼人的憨\n"
		"厚笑臉終日不離﹐待客最是實誠周到﹐這「康平小店」雖小﹐\n"
		"在村裡卻是唯一一處打尖住店的去處。近來他卻時時望著堂角\n"
		"那口蒸籠出神﹐捻著指頭盤算著甚麼﹐似有一樁掛心的喜事。\n"
		"倦了的話﹐不妨在這小店裡尋張通鋪歇歇腳﹔得閒也可問問\n"
		"他﹕ask keeper about 新米。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"店家撥拉著一把舊算盤﹐口中念念有詞地核著今日的帳目。\n",
		"店家笑容可掬地招呼道﹕客官打尖還是住店﹖咱這灶上新米蒸的飯﹐熱乎乎、香噴噴﹐包您吃得舒坦﹗\n",
		"店家對著堂角的蒸籠出神﹐捻著指頭喃喃道﹕那籠秋收謝場的新米飯糰﹐新米、火候可得樣樣地道纔成 ...\n",
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
		&&  this_player()->query("quest/kangping_rice") == 1 )
			do_chat((: command,
				"say 客官﹐託你張羅的那籠新米飯糰﹐可有著落了麼﹖" :));
		else
			do_chat((: command,
				"say 客官裡邊請﹗本店通鋪潔淨﹐新米蒸飯﹐包您住得稱心﹗" :));
	}
}

// 領賞：給一封碎銀、一串銅錢、一面小店記給嘉賓的「康平竹牌」﹐
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

	charm = new(__DIR__"obj/kangping_token");
	if( !charm->move(who) ) charm->move(environment());

	who->gain_score("survive", 90);
	who->gain_score("explorer fame", 50);
	who->gain_score("reputation", 30);

	message_vision(
		"店家眉開眼笑﹐自錢匣裡數出一小封碎銀、一串銅錢﹐又取出一面\n"
		"寫著「康平」的青竹牌﹐一併塞到$N手裡﹐連聲道謝。\n",
		who);
}

// 收尾／回報：玩家把新米飯糰交(give)回時，由 accept_object 觸發。
// 驗看飯糰、給賞、設旗標 2（完成）。本函不經手新米飯糰物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的新米飯糰（與 d/shuiyue keeper、
// d/weiguo keeper、d/ziyan keeper 一致）。
private void settle_quest(object me)
{
	// 收糰即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——新米飯糰已被 give 指令於 accept_object 回 1 後
	// 銷除﹐若賞落在延遲回呼又逢玩家離場﹐便會「糰沒了、賞沒領、旗標卻記完成」
	// 而卡關。do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/kangping_rice", 2);
	do_chat(({
		(: command, "say 哎呀﹐這新米飯糰蒸成了﹗快與我掂掂——唔﹐捏得結實﹐荷葉的清香裹著新米的暖香﹐這一口下去﹐正是咱康平村的豐年味﹗客官這趟跑得仔細﹐可解了我一樁心事。" :),
		(: command, "say 不瞞客官﹐這籠飯糰是備給村裡秋收謝場的——今年年成好﹐合村老小要在曬場上擺一場謝天的酒飯﹐這頭一籠新米飯糰﹐圖的就是個『身康家平、五穀豐登』的彩頭。如今新米、火候俱備﹐我這便能拿它去張羅謝場了。這點碎銀銅錢﹐方纔已塞到客官手裡﹐務必收好。" :),
		(: command, "say 另有一面『康平竹牌』﹐也一併與客官﹐往後打康平村經過﹐只管進店歇腳吃飯﹐圖個身康家平的好意頭﹗本店悅近來遠﹐客官常來﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位店家甚麼﹖（試試 ask keeper about 新米）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("店家正撥著算盤核帳﹐一時沒空理你。\n");

	// 新米 / 飯糰 / 謝場：非戰鬥支線「新米飯糰」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」「飯」等問法﹐方便玩家中途確認進度）
	if( arg == "keeper about 新米"
	||  arg == "kangping keeper about 新米"
	||  arg == "innkeeper about 新米"
	||  arg == "keeper about 飯糰"
	||  arg == "keeper about 飯"
	||  arg == "keeper about 謝場"
	||  arg == "keeper about 喜飯"
	||  arg == "keeper about 任務"
	||  arg == "keeper about rice"
	||  arg == "keeper about dough"
	||  arg == "keeper about quest" ) {
		object me = this_player();
		int q = me->query("quest/kangping_rice");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替小店蒸了那籠新米飯糰﹐秋收謝場上﹐合村老小就著這新米喜飯吃得歡天喜地﹐都說今年這謝場辦得體面哩。" :),
				(: command, "say 往後過康平村﹐只管進店歇腳吃飯。康平小店這四個字﹐圖的就是個身康家平、賓至如歸﹗" :),
			}));
			return 1;
		}

		// 碾米蒸飯中（已接任務）：持蒸好的飯糰則 ask 即驗飯糰領賞﹐否則依進度提示下一步
		if( q == 1 ) {
			// 已蒸好飯糰：ask keeper about 新米 即當作回報——驗看飯糰、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的新米飯糰（與 accept_object
			// 經 give 指令回 1 後自動銷除新米飯糰等效）。縱飯糰失落亦直接認功給賞﹐免卡關。
			if( me->query("quest/kangping_rice_dough") ) {
				// 用獨有 id「xinmifantuan」銷除本任務飯糰，免與雜貨鋪所售
				// /obj/food/ricedough（同 id「rice dough」）相混而誤銷玩家自買的飯。
				object d = present("xinmifantuan", me);
				if( d ) destruct(d);
				message_vision(
					"$N把那個荷葉包著的新米飯糰奉與店家。店家揭開荷葉的封口﹐\n"
					"湊近聞了聞那一縷新米蒸熟的暖香﹐眉開眼笑。\n", me);
				settle_quest(me);
				return 1;
			}

			// 進行中：依「是否已自田裡老農討得新米陶缽」分頭提示（先把整句湊好，再交給 command）
			{
				string line;
				if( !me->query("quest/kangping_rice_bowl") )
					line = "say 還沒著落麼﹖客官且去村心南面的村外田壟﹐尋那位歇晌的田裡老農問問（ask farmer about 新米）。要蒸這新米飯糰﹐頭一樁便是一缽自家田裡新收、現碾的新米﹐盛米的陶缽他那兒也有﹐討一隻來便是。";
				else if( present("rice bowl", me) )
					line = "say 新米既向田裡老農碾著了﹐就去村心西北窄巷盡頭的井臺﹐尋那位灶上嬸子﹐請她把新米上籠蒸成飯糰（ask cook about 新米﹐或 give rice bowl to cook）。蒸好了﹐再持回小店我這兒。";
				else
					line = "say 咦﹐先前向田裡老農碾的那缽新米呢﹖客官莫不是失落了﹖不妨事﹐再去村外田壟尋田裡老農問問（ask farmer about 新米），他那兒還記著這樁事。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出要備新米飯糰辦秋收謝場、自家抽不開身的難處、央玩家碾米蒸飯，設旗標 1
		// 此時不交物——盛米的陶缽須玩家去村外田壟向田裡老農討。
		me->set("quest/kangping_rice", 1);
		do_chat(({
			(: command, "say 客官問著了我的心事。是這麼回事﹕今年咱康平村年成好﹐合村老小要在村心曬場上擺一場秋收謝天的酒飯。我這小店掌灶﹐少不得蒸一籠村裡最家常的喜飯『新米飯糰』﹐圖個五穀豐登的彩頭﹐打頭一道。" :),
			(: command, "say 偏生這新米飯糰﹐最講究的就是新米、火候兩樣都得地道﹕米要田裡剛收、現碾的新米﹐飯要井臺灶上現蒸的飯糰﹐拿新米上籠蒸熟捏成纔香﹐缺一不可。我守著店灶抽不開身﹐這事便一直擱著。" :),
			(: command, "say 客官若得閒﹐勞煩替我料理這樁事﹕先去村心南面的村外田壟﹐尋那位田裡老農碾一缽新收的新米、盛進陶缽（ask farmer about 新米）﹔再到村心西北窄巷盡頭的井臺﹐尋那位灶上嬸子把新米上籠蒸成飯糰（ask cook about 新米）。蒸齊了﹐持回小店來尋我（ask keeper about 新米）﹐我必有酬謝﹗" :),
		}));
		return 1;
	}

	return notify_fail("店家陪笑道﹕客官若是打尖住店、吃碗熱飯﹐只管吩咐﹔旁的我可幫不上甚麼忙。（試試 ask keeper about 新米）\n");
}

// 收下信物：
//   新米飯糰(rice dough) -- 支線「新米飯糰」回報﹐持蒸好的飯糰且任務進行中時
//   收下、給賞、推進旗標 kangping_rice 1 -> 2。
// 不在此 move／destruct 新米飯糰——give 指令於本函回 1 後會自行 destruct 有值的
// 新米飯糰（與 d/shuiyue keeper、d/weiguo keeper、d/ziyan keeper 一致）﹔
// 非回報玩家／時機不符則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("rice dough") ) {
		int q = who->query("quest/kangping_rice");

		// 已完成或未接任務：婉拒，不收下（避免吞掉飯糰、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這個飯糰 ... 客官還是自個兒收著罷，我這會兒用不上。" :));
			return 0;
		}

		// 進行中但還沒蒸好飯糰（理應不會持有 rice dough，穩妥起見仍判一次）：婉拒
		if( !who->query("quest/kangping_rice_dough") ) {
			do_chat((: command,
				"say 客官這個 ... 莫不是還沒到井臺蒸飯罷﹖且先持新米到井臺尋灶上嬸子蒸一籠飯糰來﹐我纔好驗。" :));
			return 0;
		}

		// 進行中、已蒸好飯糰、持糰回報：給賞、推進旗標（新米飯糰由 give 指令於回 1 後自行銷除）
		message_vision(
			"$N把那個荷葉包著的新米飯糰奉與店家。店家揭開荷葉的封口﹐\n"
			"湊近聞了聞那一縷新米蒸熟的暖香﹐眉開眼笑。\n", who);
		settle_quest(who);
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個我用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object player)
{
	do_chat("店家陪笑道﹕這位客官說笑了﹐我一介開店的莊稼人﹐怎敢與您動手。\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
