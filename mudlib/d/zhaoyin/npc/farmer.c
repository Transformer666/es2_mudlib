// farmer.c -- 井邊歇腳的老農，說古道今的鄉野人物；
//             兼兆隱縣非戰鬥調查支線「渾沌獸的蹤跡」的委託人與領賞人。
//
// 任務性質：純地方氣氛的「打聽傳聞」支線，沒有戰鬥、不需殺任何東西，
//           只是替老農悄悄探聽渾沌獸現蹤的傳聞，問齊三位縣民的說法後回報。
//           本支線自成一套旗標（quest/zhaoyin_chaos*），與主線渾沌/摩雲一脈
//           毫無瓜葛——只加深這僻遠山縣的傳說氛圍，推進、解開不了任何主線。
//
// 任務流程（旗標皆存在玩家身上）：
//   未開始 (quest/zhaoyin_chaos==0) : 玩家 ask farmer about 渾沌獸 ->
//       老農託他悄悄向城裡幾位見多識廣的縣民打聽渾沌獸的傳聞﹐
//       設 quest/zhaoyin_chaos = 1（接下任務）。
//   蒐集線索 (quest/zhaoyin_chaos==1) : 玩家分別去 ask 三位縣民 about 渾沌獸，
//       各得一段不同的傳聞片段﹐每問著一位便記下一條線索（推進在各該 NPC）：
//         - 獵戶 (/d/zhaoyin/npc/hunter，城門)    -> quest/zhaoyin_chaos_clue_hunter
//         - 賣貨郎 (/d/zhaoyin/npc/monger，縣前街) -> quest/zhaoyin_chaos_clue_monger
//         - 老捕快 (/d/zhaoyin/npc/runner，縣衙前) -> quest/zhaoyin_chaos_clue_runner
//       每記一條線索﹐quest/zhaoyin_chaos_clues 計數 +1（0->3）。
//   可回報 (三條線索齊全) : 玩家持齊三條線索回井邊 ask farmer about 渾沌獸 ->
//       老農聽訖串起傳聞﹐給賞並道出加深謎團的鄉野見解﹐
//       設 quest/zhaoyin_chaos = 2（完成﹐防重複領賞）。
//   已完成 (quest/zhaoyin_chaos>=2) : 不再給賞﹐只作純氣氛的收尾閒談。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老農", ({ "farmer", "old farmer", "peasant" }) );
	set("nickname", "老農");
	set_race("human");
	set_class("commoner");
	set_level(5);

	set("age", 63);
	set("gender", "male");
	set("long",
		"一個飽經風霜的老農﹐臉膛黑紅﹐溝壑似的皺紋裡嵌著洗不\n"
		"淨的泥色﹐褲腳還沾著田裡的新泥。他蹲在井邊歇腳﹐叼著一桿\n"
		"旱煙袋﹐眯眼望著遠處的青山﹐肚裡裝著滿滿一肚子鄉野的奇談\n"
		"異聞。近來他似有樁放不下的心事﹐不時望著遠山喃喃自語。你\n"
		"或許可以問問他﹕ask farmer about 兆隱﹐或是\n"
		"ask farmer about 渾沌獸。\n");
	set("chat_chance", 4);
	set("chat_msg", ({
		(: random_move :),
		"老農吧嗒著旱煙袋﹐瞇眼望著遠山﹐悠悠地吐出一口煙。\n",
		"老農慢悠悠地道﹕咱這兆隱縣啊﹐地方是僻了些﹐可勝在山清水秀﹐少是非。\n",
		"老農壓低嗓子道﹕後生家﹐這山裡頭的怪事﹐可不少哩 ...\n",
	}));
	setup();
	carry_money("coin", 15);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/zhaoyin_chaos");
		if( q == 1 )
			do_chat((: command,
				"say 後生家﹐託你打聽的那渾沌獸的傳聞﹐可問著些甚麼了麼﹖" :));
	}
}

// 領賞：給一串銅錢、一株鄉間補身的野山蔘（山裡人家的土儀）﹐
// 並授存活歷練與旅行見聞。
// 採直接 new + move(who) 交付﹐move 失敗才落到地上﹐不走 command give、
// 不走會因玩家走開而落空的延遲 do_chat 回呼。
private void give_reward(object who)
{
	object coin, herb;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(80);
	if( !coin->move(who) ) coin->move(environment());

	herb = new("/obj/medication/wild_ginseng");
	if( !herb->move(who) ) herb->move(environment());

	who->gain_score("survive", 120);
	who->gain_score("explorer fame", 80);

	message_vision(
		"老農起身在褲腿上磕了磕煙灰﹐自懷裡摸出一小串銅錢﹐又取出一株\n"
		"用紅紙裹著的野山蔘﹐一併塞到$N手裡﹐說是這山裡人家的一點土儀。\n",
		who);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這位老農甚麼﹖（試試 ask farmer about 兆隱）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老農正眯眼出神地望著遠山﹐沒空理你。\n");

	// 兆隱縣：本地風土閒談，純氣氛
	if( arg == "farmer about 兆隱"
	||  arg == "old farmer about 兆隱"
	||  arg == "farmer about 兆隱縣"
	||  arg == "farmer about 縣城"
	||  arg == "farmer about zhaoyin"
	||  arg == "farmer about county" ) {
		do_chat(({
			(: command, "say 兆隱縣啊﹐打老輩子起便縮在這群山裡頭﹐外人輕易尋不著﹐官道也不打這兒過﹐倒落得個清靜。" :),
			(: command, "say 咱這兒民風純樸﹐山環水抱﹐一年到頭沒幾樁官司。後生家若是躲是非、避風頭﹐這兆隱縣可是再合適不過的去處囉。" :),
		}));
		return 1;
	}

	// 渾沌獸：非戰鬥調查支線「渾沌獸的蹤跡」的委託 / 蒐證進度 / 回報領賞
	// （亦涵蓋「線索」這一問法﹐方便玩家中途確認進度）
	if( arg == "farmer about 渾沌獸"
	||  arg == "old farmer about 渾沌獸"
	||  arg == "farmer about 渾沌"
	||  arg == "farmer about 怪獸"
	||  arg == "farmer about 異獸"
	||  arg == "farmer about 線索"
	||  arg == "farmer about 傳聞"
	||  arg == "farmer about 任務"
	||  arg == "farmer about chaos beast"
	||  arg == "farmer about beast"
	||  arg == "farmer about clue"
	||  arg == "farmer about quest" ) {
		object me = this_player();
		int q = me->query("quest/zhaoyin_chaos");

		// 已完成：純氣氛收尾，不再給賞
		if( q >= 2 ) {
			do_chat(({
				(: command, "say 多虧後生家替老漢把這幾樁傳聞都打聽明白了。看來那渾沌獸見人不傷、四處藏躲﹐倒不像是來作惡的——它躲的、怕的﹐興許是旁的甚麼東西哩。" :),
				(: command, "say 罷了罷了﹐這等山精野怪的因由﹐豈是咱莊稼人能說透的。後生家心裡有個底也就是了﹐往後進山﹐自個兒留神著些。" :),
			}));
			return 1;
		}

		// 蒐集線索中（已接任務）：依已得線索數給進度提示，齊三條則回報領賞
		if( q == 1 ) {
			int n = me->query("quest/zhaoyin_chaos_clues");

			// 三條線索齊全：串起傳聞、給賞、設旗標 2（完成）
			if( n >= 3 ) {
				// 同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
				// 不把給賞放進延遲的 do_chat——免玩家於回呼前離場致賞沒領、旗標卻記完成而卡關。
				give_reward(me);
				me->set("quest/zhaoyin_chaos", 2);
				do_chat(({
					(: command, "say 哦﹖後生家都問著啦﹖快說與老漢聽聽——進山的獵戶親眼撞見過、走村串戶的貨郎也聽人提過、連縣衙的捕快都記著檔哩。這麼一湊﹐可就由不得人不信了。" :),
					(: command, "say 你瞧﹕那大物黑霧裹身、沒眉沒眼﹐見人也不傷﹐只一個勁兒地往沒人的荒祠野林裡躲。老漢琢磨著﹐它哪裡是來害人的——分明是它自個兒在怕著、躲著甚麼﹐才一路逃到咱這僻遠山縣來藏身的。" :),
					(: command, "say 這點銅錢與山參﹐後生家拿著﹐算是老漢的一點謝意。它躲的究竟是甚麼凶煞﹐唉……那可就不是咱這小縣城打聽得出來的了。後生家聽過便罷﹐切莫聲張﹐更莫當真去招惹了它。" :),
				}));
				return 1;
			}

			// 線索未齊：報還差哪幾位縣民未問（先把整句湊好，再交給 command）
			{
				string s = "";
				string line;
				if( !me->query("quest/zhaoyin_chaos_clue_hunter") )
					s += "城門邊那進過山的獵戶、";
				if( !me->query("quest/zhaoyin_chaos_clue_monger") )
					s += "街上走村串戶的賣貨郎、";
				if( !me->query("quest/zhaoyin_chaos_clue_runner") )
					s += "縣衙前當值的老捕快、";
				line = "say 才問著" + n + "處哩﹐還不夠。後生家再去尋"
					+ s + "問問（ask 他們 about 渾沌獸）﹐把話湊齊了再回來說與老漢。";
				do_chat((: command, line :));
			}
			return 1;
		}

		// 尚未接任務（旗標 0）：訴說渾沌獸傳聞、央玩家代為打聽，設旗標 1
		me->set("quest/zhaoyin_chaos", 1);
		do_chat(({
			(: command, "say 渾沌獸﹖噓——後生家莫要聲張。那是樁邪門的事體。前些日子﹐有進山的獵戶撞見一頭從沒見過的大物﹐黑霧裹身﹐沒眉沒眼﹐見人也不傷﹐只一陣風似的竄沒了。" :),
			(: command, "say 老漢這心裡頭啊﹐一直擱著這樁事——那異獸究竟是何來路、為何竄到咱這僻遠山縣來﹖老漢腿腳不便﹐又抹不開臉去四處打聽﹐生怕教人當成老糊塗。" :),
			(: command, "say 後生家若得閒﹐勞煩替老漢悄悄打聽打聽。城門邊有個進過山的獵戶、街上有個走村串戶的賣貨郎、縣衙前還有位當值多年的老捕快——這三位見多識廣﹐後生家分頭去 ask 他們 about 渾沌獸﹐興許各有各的說法。都問齊了﹐再回井邊來說與老漢﹐老漢必有酬謝﹗" :),
		}));
		return 1;
	}

	// 老王燒烤：給個本地指路的閒談
	if( arg == "farmer about 老王"
	||  arg == "farmer about 燒烤"
	||  arg == "farmer about 烤肉"
	||  arg == "farmer about laowang" ) {
		do_chat(({
			(: command, "say 哈哈﹐後生家也聞著那股香了﹖那是縣前街西頭老王的燒烤攤子﹐他那烤肉的手藝﹐方圓百里都掛了號的。" :),
			(: command, "say 趁熱去嚐上幾串罷﹐就著一壺村釀的濁酒﹐神仙也不換哩﹗" :),
		}));
		return 1;
	}

	return notify_fail("老農聽不大明白你問的﹐只憨憨地衝你笑。（試試 ask farmer about 兆隱）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗後生家這是做甚﹖老漢一把年紀的莊稼人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
