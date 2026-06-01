// fortuneteller.c -- 神算子﹐風城廣場的算命先生；
//                    兼風城非戰鬥支線「失算的籤筒」的委託人與領賞人。
//
// 設定來源（docs/01-世界觀與劇情/04-地圖與場景.md）：
//   風城地標「神算子」﹐算命師收 1 兩銀子﹐算「練是否滿」（天賦根器是否練到頂）。
//
// 算命機制現況：純風味。`算命`/`divine` 指令只給氣氛化的批命﹐不收錢、不真的
//   判讀天賦。（真正的天賦/練滿判讀須先重建 daemon/skill 與天賦上限﹐見
//   CLAUDE.md 鐵則 5；本檔不動算命指令的既有行為。）
//
// ── 非戰鬥支線「失算的籤筒」──────────────────────────────────────────
// 任務性質：純風城氣氛的「打聽、尋物、交還」支線﹐沒有戰鬥、不需殺任何東西﹐
//           也不靠任何運氣骰子——一路問著、尋著、交還即成﹐必定可完成。神算子
//           卜算用的龜甲卦錢前些日子在廣場朔風裡失落了一枚﹐少這一枚湊不成一副
//           便掐算不靈﹔玩家循線尋回交還即可。本支線自成一套旗標
//           （quest/fengcheng_gua*）﹐全程不出風城既有的幾間屋子﹐不讀、不動任何
//           別的任務旗標﹐純加深北地大城卦攤市井的氣氛。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/fengcheng_gua==0) : 玩家 ask fortuneteller about 龜甲 ->
//       神算子道出失落卦錢、掐算不靈的難處﹐央玩家代為循線尋回﹐
//       設 quest/fengcheng_gua = 1（接下任務）。
//   打聽中 (quest/fengcheng_gua==1) : 玩家循兩處線索尋物（推進在各該 NPC）：
//         - 差役 (/d/fengcheng/npc/runner ﹐聚風茶樓) ask about 龜甲
//             -> 道出曾見拾荒小乞兒在市集邊撿著亮晶晶的物事﹐
//                記 quest/fengcheng_gua_runner = 1（線索）
//         - 攤販 (/d/fengcheng/npc/peddler﹐風城市集) ask about 龜甲
//             -> 須已先問著差役的線索（gua_runner）﹐方說出小乞兒拿那枚舊錢
//                換了個奶餅﹐將「龜甲卦錢」實物交付玩家﹐
//                記 quest/fengcheng_gua_peddler = 1
//   可回報 (持龜甲卦錢在身) : 玩家持卦錢回卦攤﹐
//         give 龜甲卦錢 給 fortuneteller（或 ask fortuneteller about 龜甲）->
//         神算子驗看卦錢、收下﹐給賞並搖籤相贈﹐
//         設 quest/fengcheng_gua = 2（完成﹐防重複領賞）。
//   已完成 (quest/fengcheng_gua>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_divine(string arg);
int do_ask(string arg);

void create()
{
	set_name("神算子", ({ "fortuneteller", "fortune teller", "shensuanzi" }) );
	set_race("human");
	set_class("commoner");
	set_level(8);

	set("age", 63);
	set("gender", "male");
	set("long",
		"這位便是風城遠近聞名的算命先生「神算子」。他生得仙風道\n"
		"骨﹐一部花白的長鬚垂在胸前﹐頭戴一頂舊葛巾﹐身著洗得發白\n"
		"的青布道袍﹐一雙眼睛半開半闔﹐卻彷彿能看透人的窮通禍福。\n"
		"據說他鐵口直斷﹐連你天賦根器練到了幾分﹐他都算得出來。\n"
		"近來他卻時時蹙眉﹐似為攤上少了件甚麼物事而心緒不寧。你或\n"
		"許可以請他算上一卦﹕算命 (或 divine)﹔或問問\n"
		"他﹕ask fortuneteller about 龜甲。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"神算子閉目掐指﹐口中念念有詞﹐似在推演甚麼玄機。\n",
		"神算子捻著長鬚﹐淡淡道﹕施主印堂發亮﹐近日想必有番際遇。\n",
		"神算子睜眼一笑道﹕窮通禍福皆有定數﹐施主若有疑惑﹐不妨請老朽算上一卦。\n",
		"神算子悠悠道﹕天賦根器各有高下﹐練到幾分火候﹐老朽一算便知﹐只取紋銀一兩。\n",
		"神算子摩挲著桌上的龜甲銅錢﹐眉頭微蹙﹐似在數算著甚麼﹐口中喃喃﹕怎地總覺少了一枚 ...\n",
	}));
	setup();
	carry_money("coin", 100);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	// 中文動詞「算命」為設定上的主指令；但全 mudlib 僅此一處用中文 verb﹐
	// driver parser 對多位元組 verb 的支援未驗證﹐故另加 ASCII 別名 divine 作後備。
	add_action("do_divine", "算命");
	add_action("do_divine", "divine");

	// 支線「失算的籤筒」進行中的招呼（純風味﹐不影響算命指令）
	if( !is_fighting() && this_player() && interactive(this_player())
	&&  this_player()->query("quest/fengcheng_gua") == 1 )
		do_chat((: command,
			"say 施主來得正好——託你尋的那枚龜甲卦錢﹐可有著落了麼﹖" :));
}

int do_divine(string arg)
{
	object me = this_player();

	if( !me || !interactive(me) ) return 0;

	if( is_fighting() || is_chatting() )
		return notify_fail("神算子正忙著﹐你且稍候片刻。\n");

	// TODO: 真正的機制應在此收取 1 兩銀子並以 query_skill() 判讀天賦/練滿狀況。
	//       目前僅作風味批命﹐不收費、不判讀。（本支線不動此既有行為。）
	do_chat(({
		"神算子拈起三枚銅錢﹐拋擲在青布上﹐俯身細看了片刻。\n",
		(: command, "say 施主且聽老朽一言——你天賦根器尚有可塑之機﹐勤加磨練﹐他日必成大器。" :),
		(: command, "say 只是這真正的玄機﹐須得老朽掐算良久方能道破﹐施主來日再來罷。" :),
	}));
	return 1;
}

// 領賞：給一封碎銀、一串銅錢、一支神算子親批的「上上平安籤」﹐
// 並授江湖歷練、行旅見聞與一點市井聲望。
// 採直接 new + move(who) 交付﹐move 回 1 為成功（落在玩家身上）﹐
// 回 0（失敗）才退而落到地上﹐不走會因玩家走開而落空的延遲回呼。
private void give_reward(object who)
{
	object silver, coin, sign;

	if( !who || environment(who) != environment() ) return;

	silver = new("/obj/money/silver");
	silver->set_amount(1);
	if( !silver->move(who) ) silver->move(environment());

	coin = new("/obj/money/coin");
	coin->set_amount(50);
	if( !coin->move(who) ) coin->move(environment());

	sign = new(__DIR__"obj/blessing_sign");
	if( !sign->move(who) ) sign->move(environment());

	who->gain_score("survive", 90);
	who->gain_score("explorer fame", 50);
	who->gain_score("reputation", 30);

	message_vision(
		"神算子大喜﹐自袖中摸出一小封碎銀、一串銅錢﹐又凝神搖出一支竹\n"
		"籤﹐提筆批就﹐連同謝禮一併鄭重地塞到$N手裡。\n",
		who);
}

// 收尾／回報：玩家把龜甲卦錢交(give)回時，由 accept_object 觸發。
// 驗看卦錢、給賞、設旗標 2（完成）。本函不經手卦錢物件——give 指令於
// accept_object 回 1 後會自行 destruct 有值的卦錢（與 d/fancheng boatman、
// d/feixian keeper 一致）。
private void settle_quest(object me)
{
	// 收錢即同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
	// 不把給賞放進延遲的 do_chat——龜甲卦錢已被 give 指令於 accept_object 回 1 後
	// 銷除﹐若賞落在延遲回呼又逢玩家離場﹐便會「錢沒了、賞沒領、旗標卻記完成」
	// 而卡關。do_chat 僅作收尾氣氛對白。
	give_reward(me);
	me->set("quest/fengcheng_gua", 2);
	do_chat(({
		(: command, "say 哎呀﹐正是這枚﹗施主請看——龜甲為胎、黃銅鑄邊﹐背鐫一個篆『卜』字﹐正是老朽那副卦錢裡失落的一枚。少了它湊不成數﹐這些日子老朽掐算總覺著差了一線﹐可教施主尋回來了﹗" :),
		(: command, "say 那日朔風一捲﹐這枚卦錢便沒了影﹐老朽尋遍攤前也尋不著﹐原來是輾轉落到市集去了。施主肯為老朽這點身外之物奔走打聽﹐這份心﹐難得﹗" :),
		(: command, "say 這點碎銀銅錢﹐方纔已塞到施主手裡﹐務必收好。另有老朽誠心替施主搖的一支『上上平安籤』﹐籤辭批的是『失而復得、心正運通、出入平安』——施主佩著﹐圖個好彩頭。卦錢既已成副﹐施主來日若要算那天賦根器練滿了沒有﹐只管再來﹗" :),
	}));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位神算子甚麼﹖（試試 ask fortuneteller about 龜甲）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("神算子正閉目掐算﹐一時沒空理你。\n");

	// 龜甲 / 卦錢：非戰鬥支線「失算的籤筒」的委託 / 進度 / 回報領賞
	// （亦涵蓋「任務」「卦攤」等問法﹐方便玩家中途確認進度）
	if( arg == "fortuneteller about 龜甲"
	||  arg == "fortune teller about 龜甲"
	||  arg == "fortuneteller about 卦錢"
	||  arg == "fortuneteller about 龜甲卦錢"
	||  arg == "fortuneteller about 籤筒"
	||  arg == "fortuneteller about 卦攤"
	||  arg == "fortuneteller about 任務"
	||  arg == "fortuneteller about gua coin"
	||  arg == "fortuneteller about coin"
	||  arg == "fortuneteller about quest" ) {
		object me = this_player();
		int q = me->query("quest/fengcheng_gua");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧施主替老朽尋回那枚失落的龜甲卦錢﹐如今這副卦錢又成了數﹐老朽掐算起來﹐也順手多了。" :),
				(: command, "say 窮通禍福皆有定數﹐唯這人情冷暖難算。施主肯為老朽奔走﹐便是樁算不出的善緣。往後過風城﹐只管來攤前坐坐﹐老朽與施主說說這北地的卦理。" :),
			}));
			return 1;
		}

		// 打聽中（已接任務）：持卦錢則提示交還領賞，否則報還線索進度
		if( q == 1 ) {
			// 已尋回卦錢、且持錢在身：ask 即當作交還——驗錢、給賞、完成。
			// 此路不經 give 指令﹐故須在此自行銷除玩家手裡的卦錢（與 accept_object
			// 經 give 指令回 1 後自動銷除卦錢等效﹐免玩家留著「已交」的錢重複觸發）。
			if( present("gua coin", me) ) {
				object coin = present("gua coin", me);
				message_vision(
					"$N雙手把那枚龜甲卦錢奉與神算子。神算子凝目一看﹐\n"
					"指尖摩挲著錢背的篆『卜』字﹐花白的長鬚都顫了起來。\n", me);
				// 先同步給賞、記旗標﹐再銷除卦錢（與 accept_object 經 give 等效）。
				settle_quest(me);
				if( coin ) destruct(coin);
				return 1;
			}

			// 尚未尋回：依線索進度提示下一步（先把整句湊好，再交給 command）
			{
				string line;
				if( !me->query("quest/fengcheng_gua_runner") )
					line = "say 還沒著落麼﹖那日風大﹐卦錢怕是教風捲到旁處去了。施主不妨先去聚風茶樓﹐尋那當值的差役問問（ask 差役 about 龜甲）——公門中人眼尖﹐街面上的動靜﹐他多半留著心。";
				else if( !me->query("quest/fengcheng_gua_peddler") )
					line = "say 差役說有個拾荒的小乞兒在市集邊撿著了亮晶晶的物事﹖那就有譜了﹗施主快去風城市集﹐尋那守小吃攤的婦人問問（ask 攤販 about 龜甲）——小乞兒拾了東西﹐多半拿去換吃食了﹐那婦人興許曉得下落。";
				else
					line = "say 攤販既說那枚舊錢在她手裡﹐施主可向她討了來﹐持回卦攤交與老朽便是。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：道出失落卦錢、掐算不靈的難處、央玩家循線尋回，設旗標 1
		me->set("quest/fengcheng_gua", 1);
		do_chat(({
			(: command, "say 施主好眼力﹐竟瞧出老朽的心事。實不相瞞——老朽卜算窮通禍福﹐靠的是一副祖傳的龜甲卦錢﹐統共幾枚﹐缺一不可。前些日子廣場上朔風大作﹐一捲之下﹐竟把其中一枚捲沒了影。" :),
			(: command, "say 龜甲為胎、黃銅鑄邊﹐背鐫一個篆『卜』字——便是那麼一枚舊錢。少了它﹐這副卦錢湊不成數﹐老朽掐算起來總差著一線﹐這幾日替人批命﹐心裡都不踏實。老朽守著卦攤走不開﹐又抹不下臉去街面上四處翻找。" :),
			(: command, "say 施主若得閒﹐勞煩替老朽循線尋上一尋﹕風大﹐卦錢多半教捲到旁處、教人拾了去。先去聚風茶樓尋那當值的差役問問（ask 差役 about 龜甲）﹐公門中人眼尖﹐街面動靜他留著心﹔再順著話頭往下打聽。尋著了持回卦攤交與老朽﹐老朽必有酬謝﹗" :),
		}));
		return 1;
	}

	return notify_fail("神算子捻著長鬚﹐淡淡道﹕施主問的這個﹐老朽卦上可算不出來。（試試 ask fortuneteller about 龜甲﹐或 算命）\n");
}

// 收下信物：
//   龜甲卦錢(gua coin) -- 支線「失算的籤筒」送件﹐持錢且任務進行中時
//   收下、給賞、推進旗標 fengcheng_gua 1 -> 2。
// 不在此 move／destruct 卦錢——give 指令於本函回 1 後會自行 destruct 有值的
// 卦錢（與 d/fancheng boatman、d/feixian keeper 一致）﹔非送件玩家／時機不符
// 則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("gua coin") ) {
		int q = who->query("quest/fengcheng_gua");

		// 已完成或未接任務：婉拒，不收下（避免吞掉卦錢、不重複給賞）
		if( q != 1 ) {
			do_chat((: command,
				"say 這枚卦錢 ... 施主還是自個兒收著罷，老朽眼下用不上。" :));
			return 0;
		}

		// 進行中、持卦錢交還：給賞、推進旗標（卦錢由 give 指令於回 1 後自行銷除）
		settle_quest(who);
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老朽用不上﹐施主還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹐天機不可洩漏﹐動手更是大大的不該﹗施主息怒、息怒﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
