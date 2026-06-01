// tea_guest.c -- 聽濤茶樓裡候缺的選官（純氣氛，茶客閒談京中風向，隱隱透出朝廷耳目之嚴）；
//                兼羅城非戰鬥支線「羅城客棧的尋硯」的失主與回執信物交付人。
//
// 本檔原為純氣氛的茶客（閒談京中風向）。為支線「羅城客棧的尋硯」加掛收硯一段：
//   這位姓周的候缺選官﹐正是前些日子匆匆離店、把端硯遺落在羅城客棧的失主。
//   玩家自店小二取回端硯後﹐ask tea guest about 端硯（或 give 端硯 to tea guest）
//   -> 選官失而復得、大喜﹐取自己的名帖草書謝辭、交付「謝帖」實物託玩家轉交客棧
//   掌櫃﹐記 quest/luocheng_yan_returned = 1。
//   （driver give 指令不認中文「給」﹐故持硯 ask 即視同送還：同步交付謝帖、記旗標、
//     並銷除手中端硯﹐與經 give 指令觸發 accept_object 等效。）
// 不動其原有的閒談 chat_msg 與 accept_fight。
//
// 回執謝帖採直接 new + move(who) 同步交付——give／ask 皆由玩家觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記旗標
// （與本鎮 d/luocheng keeper、barkeep 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void hand_note(object me);

void create()
{
	set_name("候缺選官", ({ "tea guest", "guest", "xuanguan" }) );
	set_race("human");
	set_class("scholar");
	set_level(6);

	set("age", 44);
	set("gender", "male");
	set("long",
		"一位候缺謁選的外省官員﹐頭戴方巾﹐身著半舊的綢衫﹐獨\n"
		"坐窗邊﹐對著一盞早已涼透的茶出神。他來京裡候了大半年的\n"
		"缺﹐宦囊漸澀﹐眉宇間鬱結著一股鬱鬱不得志的悒悶﹐偶爾聽\n"
		"得鄰座官人低語﹐便不自覺地側耳留神。聽他偶爾自語﹐似在\n"
		"惦記著一方失落的舊硯。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"候缺選官對著那盞涼透的冷茶出神﹐長長地嘆了口氣。\n",
		"候缺選官苦笑道﹕在京裡候缺﹐候的是時運﹐也是門路。似我這般無依無傍的﹐怕是要候到鬍子白了。\n",
		"候缺選官壓低聲音道﹕兄台慎言。這羅城裡耳目最是繁密﹐隔牆便有耳﹐妄議朝政是要吃掛落的。\n",
		"候缺選官望著相府的方向﹐低聲道﹕聽聞相爺近來常為著些古怪的舊案召人入府密議﹐究竟是甚麼事﹐外頭誰也說不真切 ...\n",
	}));
	setup();
	carry_money("coin", 80);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 交付回執謝帖：選官取自己的名帖草書謝辭相託﹐記旗標 luocheng_yan_returned。
// 直接 new + move(me) 同步交付（玩家此刻必在場）﹐先交物、後記旗標。
private void hand_note(object me)
{
	object note = new(__DIR__"obj/thank_note");
	if( !note->move(me) ) note->move(environment());
	me->set("quest/luocheng_yan_returned", 1);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位選官甚麼﹖（試試 ask tea guest about 端硯）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("候缺選官正對著冷茶出神﹐一時沒理會你。\n");

	// 端硯 / 遺硯：支線「羅城客棧的尋硯」——失主收硯、交付回執謝帖
	if( arg == "tea guest about 端硯"
	||  arg == "guest about 端硯"
	||  arg == "tea guest about 硯"
	||  arg == "tea guest about 遺硯"
	||  arg == "tea guest about 失物"
	||  arg == "tea guest about inkstone"
	||  arg == "tea guest about yan" ) {
		object me = this_player();
		int q = me->query("quest/luocheng_yan");

		// 已完成或已收回硯：純氣氛收尾
		if( q >= 2 || me->query("quest/luocheng_yan_returned") ) {
			do_chat((: command,
				"say 那方端硯失而復得﹐全仗閣下高義。羅城客棧的掌櫃肯這般上心替我尋回﹐這份情﹐我周某記下了。" :));
			return 1;
		}

		// 進行中、持硯：ask 即當作送還處理——收硯、交付謝帖、記旗標
		// （此路不經 give 指令﹐故須在此自行銷除玩家手裡的端硯﹐
		//   與 accept_object 經 give 指令回 1 後自動銷除端硯等效﹐免玩家
		//   留著「已送還」的硯重複觸發。）
		if( q == 1 && present("duan yan", me) ) {
			object yan = present("duan yan", me);
			message_vision(
				"$N雙手把那方端硯奉還候缺選官。候缺選官一見﹐失聲輕呼﹐\n"
				"連忙離座接過﹐捧在掌心反覆摩挲﹐眼眶竟有些濕了。\n", me);
			// 先同步交付謝帖、記旗標、銷除端硯﹐再以 do_chat 收尾（謝帖已先到玩家手裡）。
			hand_note(me);
			if( yan ) destruct(yan);
			do_chat(({
				(: command, "say 這 ... 這正是我那方端硯﹗失而復得﹐失而復得啊﹗這硯是先父遺下的舊物﹐隨我多年﹐那日赴任的信兒來得急﹐慌亂中竟把它落在了客棧﹐我懊悔了這些時日﹗" :),
				(: command, "say 後來赴任未成﹐我又回了京﹐只當這硯是再也尋不回了。不想羅城客棧的掌櫃這般有心﹐竟差閣下替我尋了回來——這份情義﹐我周某沒齒難忘﹗" :),
				(: command, "say 閣下且慢——我這便取名帖寫幾句謝辭﹐煩閣下捎回客棧﹐替我謝過那位掌櫃。喏﹐這張謝帖﹐方纔已奉到閣下手裡了﹐務請持回客棧交與掌櫃（ask keeper about 端硯﹐或 give 謝帖 to keeper）﹐也好教掌櫃知道硯已物歸原主。" :),
			}));
			return 1;
		}

		// 進行中、未持硯：提示尚未取回／須去取硯
		if( q == 1 ) {
			do_chat((: command,
				"say 閣下也曉得我那方失落的硯﹖唉﹐若閣下能替我尋回﹐我周某感激不盡。聽聞是落在羅城客棧了﹐閣下若得閒﹐勞煩往客棧走一遭。" :));
			return 1;
		}

		// 未接任務：純風味帶過
		do_chat((: command,
			"say 不瞞閣下﹐我有一方先父遺下的端硯﹐前些日子匆忙離店﹐竟失落在羅城客棧了﹐這些時日我懊悔得很。唉﹐不提也罷。" :));
		return 1;
	}

	return notify_fail("候缺選官淡淡道﹕閣下問的這個﹐我一個候缺的閒人﹐怕是答不上來。（試試 ask tea guest about 端硯）\n");
}

// 收下信物：
//   端硯(duan yan) -- 支線「羅城客棧的尋硯」送還﹐持硯且任務進行中時
//   收下、交付回執謝帖、記旗標 luocheng_yan_returned。
// 不在此 move／destruct 端硯——give 指令於本函回 1 後會自行 destruct 有值的
// 端硯（與本鎮其餘送件 NPC、d/fancheng boatman 一致）﹔非送件玩家／時機不符
// 則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("duan yan") ) {
		int q = who->query("quest/luocheng_yan");

		// 未接任務／已完成：婉拒，不收下（避免吞掉端硯）
		if( q != 1 ) {
			do_chat((: command,
				"say 這方硯 ... 閣下還是自個兒收著罷，我一時也認不真這是不是我那方。" :));
			return 0;
		}

		// 已收回過（謝帖已交）：婉拒，提示謝帖已奉、徑去回報客棧
		if( who->query("quest/luocheng_yan_returned") ) {
			do_chat((: command,
				"say 我那方硯方纔已收回了﹐謝帖也奉與閣下了﹐閣下徑把謝帖捎回客棧﹐交與掌櫃便是（ask keeper about 端硯﹐或 give 謝帖 to keeper）。這方就煩閣下留著罷。" :));
			return 0;
		}

		// 進行中、持硯送還：收硯、交付謝帖、記旗標（端硯由 give 指令於回 1 後自行銷除）
		message_vision(
			"候缺選官一見$N奉還的端硯﹐失聲輕呼﹐連忙離座接過﹐捧在掌心\n"
			"反覆摩挲﹐眼眶竟有些濕了。\n", who);
		hand_note(who);
		do_chat(({
			(: command, "say 這 ... 這正是我那方端硯﹗失而復得﹐失而復得啊﹗這硯是先父遺下的舊物﹐隨我多年﹐那日赴任的信兒來得急﹐慌亂中竟把它落在了客棧﹐我懊悔了這些時日﹗" :),
			(: command, "say 不想羅城客棧的掌櫃這般有心﹐竟差閣下替我尋了回來——這份情義﹐我周某沒齒難忘﹗閣下且慢﹐我這便取名帖寫幾句謝辭。" :),
			(: command, "say 喏﹐這張謝帖﹐方纔已奉到閣下手裡了﹐煩閣下捎回客棧﹐務請交與那位掌櫃（ask keeper about 端硯﹐或 give 謝帖 to keeper）﹐也好教他知道硯已物歸原主﹐了卻一樁心事。" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個我用不上﹐閣下還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat("候缺選官駭得連連擺手﹕使不得﹗光天化日﹐茶樓裡眾目睽睽﹐你莫要害我﹗\n");
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
