// peddler.c -- 五味鋪的貨郎（F_VENDOR 販售乾糧吃食﹐兼武陵渡戰鬥支線
//             「武陵狼患」的委託人與領賞人）。
//
// 任務性質：自成一套的「剿除惡狼」戰鬥支線——近月來一頭獨眼惡狼盤踞武陵
//           古道北側的血徑(/d/wuling/wolftrail)﹐專撲過往行旅客商﹐攪得無人
//           敢出山﹐貨郎的買賣也清淡了。貨郎央玩家替武陵除了這頭禍害。本支線
//           自成一套旗標（quest/wuling_menace*）﹐與 main_omen 等他線毫無瓜葛。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/wuling_menace==0) : 玩家 ask peddler about 惡狼 ->
//       貨郎道出狼患、指出血徑去處﹐央玩家剿除﹐設 quest/wuling_menace = 1。
//   進行中 (quest/wuling_menace==1) : 玩家循武陵古道往北入「古道血徑」﹐
//       kill 獨眼惡狼。惡狼 die() 時於下手者身上記 quest/wuling_menace_slain = 1
//       （剿除憑證﹐推進在惡狼 npc/direwolf.c﹐非在此）。
//   可回報 (已得剿除憑證) : 玩家持憑證回五味鋪 ask peddler about 惡狼 ->
//       貨郎驗看、給賞﹐設 quest/wuling_menace = 2（完成﹐防重複領賞）。
//   未剿先報 (quest/wuling_menace==1 但無憑證) : 貨郎催玩家先去把狼除了。
//   已完成 (quest/wuling_menace>=2) : 不再給賞﹐只作純氣氛的收尾閒談。
//
// 給賞採直接 new + move(who) 同步交付（move 失敗才落地）﹐給畢即記旗標 2﹐
// 不走會因玩家走開而落空的延遲 do_chat 回呼——免「賞沒領、旗標卻記完成」卡關。

#include <npc.h>

inherit F_VILLAGER;
inherit F_VENDOR;

int do_ask(string arg);

void create()
{
	set_name("貨郎", ({ "peddler", "shopman", "wuling_peddler" }) );
	set("nickname", "貨郎");
	set_race("human");
	set_class("commoner");
	set_level(3);

	set("age", 45);
	set("gender", "male");
	set("long",
		"守著五味鋪的是個和氣的本地貨郎﹐生得敦厚﹐一張圓臉終\n"
		"日帶笑。鋪子雖小﹐油鹽醬醋、針線草鞋、乾糧吃食倒也一應俱\n"
		"全﹐都是武陵人家過日子離不得的零碎。他成日坐在櫃後搖著蒲\n"
		"扇﹐近來卻時時望著鎮外的古道唉聲嘆氣﹐似有樁心事。你可以用\n"
		"list 看他賣些什麼﹐用 buy 向他買東西﹔也或許可以問問他﹕\n"
		"ask peddler about 惡狼。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"貨郎搖著蒲扇﹐懶洋洋地打量著進門的客人﹐笑呵呵地招呼。\n",
		"貨郎理了理櫃上的針線草鞋﹐口中哼著一支不成調的鄉間小曲。\n",
		"貨郎笑道﹕客官要往山外去﹖路上耐放的乾糧﹐可得在小老兒這兒備足了。\n",
	}));
	// 五味鋪賣的是過日子的零碎與趕路的乾糧﹐沿用既有食物物件。
	set("merchandise", ([
		"/obj/food/manto" : 50,
		"/obj/food/ricedough" : 40,
		"/obj/food/pork" : 30,
		"/obj/food/fish" : 40,
	]));

	setup();
	carry_money("coin", 120);
}

void init()
{
	::init();
	add_action("do_vendor_list", "list");
	add_action("do_ask", "ask");

	// 已接「武陵狼患」而未領賞者，貨郎主動招呼一聲（沿用 farmer/boatman 慣式）。
	if( this_player() && interactive(this_player()) && !is_fighting() ) {
		if( this_player()->query("quest/wuling_menace") == 1 )
			do_chat((: command,
				"say 客官回來啦﹖那禍害道上的獨眼惡狼……可替咱武陵除了麼﹖" :));
	}
}

// 領賞：給一小封碎銀、一串銅錢、一株山裡人家備著的野山蔘﹐
// 並授存活歷練、武名與一點市井聲望。
// 採直接 new + move(who) 同步交付﹐move 回 1 為成功（落在玩家身上）﹐
// 回 0（失敗）才退而落到地上﹐不走會因玩家走開而落空的延遲回呼。
private void give_reward(object who)
{
	object silver, coin, herb;

	if( !who || environment(who) != environment() ) return;

	silver = new("/obj/money/silver");
	silver->set_amount(2);
	if( !silver->move(who) ) silver->move(environment());

	coin = new("/obj/money/coin");
	coin->set_amount(80);
	if( !coin->move(who) ) coin->move(environment());

	herb = new("/obj/medication/wild_ginseng");
	if( !herb->move(who) ) herb->move(environment());

	who->gain_score("survive", 120);
	who->gain_score("martial fame", 60);
	who->gain_score("reputation", 40);

	message_vision(
		"貨郎喜得從櫃後繞出來﹐自錢匣裡摸出一小封碎銀、一串銅錢﹐又取\n"
		"出一株用紅紙裹著的野山蔘﹐一併塞到$N手裡﹐連聲道謝。\n",
		who);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這貨郎些甚麼﹖（試試 ask peddler about 武陵）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("貨郎正忙著，騰不出空理你。\n");

	// 惡狼 / 狼患：戰鬥支線「武陵狼患」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」這一問法﹐方便玩家中途確認進度）
	if( arg == "peddler about 惡狼"
	||  arg == "peddler about 狼患"
	||  arg == "peddler about 狼"
	||  arg == "peddler about 獨眼惡狼"
	||  arg == "peddler about 獨眼"
	||  arg == "peddler about 任務"
	||  arg == "peddler about wolf"
	||  arg == "peddler about direwolf"
	||  arg == "peddler about quest" ) {
		object me = this_player();
		int q = me->query("quest/wuling_menace");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧客官替咱武陵除了那禍害﹗如今那血徑也太平了﹐出山的客商又敢上路﹐小老兒這買賣﹐也漸漸有了起色。" :),
				(: command, "say 客官真真是咱武陵的恩人哪﹗往後路過﹐只管來鋪裡歇腳﹐小老兒請客﹗" :),
			}));
			return 1;
		}

		// 已接任務、且已得剿除憑證：驗看、同步給賞、設旗標 2（完成）
		if( q == 1 && me->query("quest/wuling_menace_slain") ) {
			// 同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
			// 不把給賞放進延遲的 do_chat——免玩家於回呼前離場致賞沒領、旗標卻記完成而卡關。
			give_reward(me);
			me->set("quest/wuling_menace", 2);
			do_chat(({
				(: command, "say 哦﹖客官把那獨眼惡狼給宰了﹖當真﹖哎呀呀﹐可教咱武陵闔鎮都鬆了一口大氣啦﹗" :),
				(: command, "say 那孽畜傷了好幾條人命﹐連官府都束手無策﹐沒承想竟教客官給除了。這點碎銀銅錢、一株山裡的野山蔘﹐方纔已塞到客官手裡了﹐務必收好﹐算是小老兒與這滿鎮人的一點謝意。" :),
				(: command, "say 客官這般的好身手、好心腸﹐小老兒打心眼裡敬服。往後出山的路﹐總算又太平了﹗" :),
			}));
			return 1;
		}

		// 已接任務、但尚未剿除：催玩家先去把狼除了
		if( q == 1 ) {
			do_chat(({
				(: command, "say 客官還沒動手麼﹖那獨眼惡狼﹐就盤踞在鎮外武陵古道北側那條血徑裡頭。" :),
				(: command, "say 客官出了鎮口﹐循古道往東走上一段﹐留心北邊竹林裡那條雜草半掩的窄徑﹐拐進去便是了。那孽畜凶得很﹐客官可帶趁手的兵刃去﹐把牠除了再回來尋小老兒﹗" :),
			}));
			return 1;
		}

		// 尚未接任務（旗標 0）：訴說狼患、指出去處、央玩家剿除，設旗標 1
		me->set("quest/wuling_menace", 1);
		do_chat(({
			(: command, "say 唉﹐客官有所不知。咱武陵本是與世無爭的好地方﹐偏生這兩三個月裡﹐鎮外那武陵古道上鬧起了狼患——一頭獨眼的青灰惡狼﹐專一撲噬落單的行旅客商﹐已傷了好幾條人命啦﹗" :),
			(: command, "say 如今那道上人心惶惶﹐出山的客商不敢上路﹐進山的也斷了蹤﹐連小老兒這鋪子的買賣都清淡了大半。報了官﹐衙裡也只當是尋常野狼﹐遲遲不見人來剿。" :),
			(: command, "say 看客官這身手﹐定是有本事的俠士﹗那惡狼就盤踞在鎮外古道北側一條雜草半掩的血徑裡——客官出鎮口循古道往東﹐留心北邊竹林那條窄徑﹐拐進去便是。客官若肯仗義除了這禍害﹐替咱武陵剷了這條人命﹐小老兒與這滿鎮的鄉親﹐必有重謝﹗" :),
		}));
		return 1;
	}

	if( arg == "peddler about 武陵"
	||  arg == "peddler about 水嵐"
	||  arg == "peddler about 五味鋪"
	||  arg == "peddler about 鋪子"
	||  arg == "peddler about wuling" ) {
		do_chat(({
			(: command, "say 客官別看咱五味鋪寒酸﹐這武陵鎮上﹐就數小老兒這兒貨色最全了。鎮子小﹐人也少﹐巴掌大的地方﹐東到醉月茶寮﹐西到五陵客棧﹐抬腳就到。" :),
			(: command, "say 客官若是要進山訪那冷梅莊﹐打渡口過了溪﹐順著北邊那條石徑走便是。那一路梅花開得好﹐只是莊裡的規矩大﹐客官好生著些。" :),
		}));
		return 1;
	}

	return notify_fail("貨郎搖著蒲扇﹐衝你憨憨一笑﹕客官要買些甚麼﹐只管挑罷。\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲喲﹗客官這是做甚﹖小老兒一個守鋪子的﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
