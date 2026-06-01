// cook.c -- 井臺灶上掌灶蒸飯的灶上嬸子（純氣氛閒談）；
//           兼康平村非戰鬥支線「康平新米飯糰」的蒸飯人。
//
// 本檔原為井臺灶上掌灶蒸飯的氣氛 NPC（守著灶火添柴看籠）。為支線「新米飯糰」
// 加掛蒸飯一段：
//   玩家自田裡老農碾得新米陶缽後﹐持新米陶缽 ask cook about 新米（或
//   give rice bowl to cook）-> 灶上嬸子接過新米陶缽﹐把新米上籠蒸熟、
//   捏成一個熱乎乎的飯糰、拿荷葉包好交還玩家﹐記 quest/kangping_rice_dough = 1。
//   交付「新米飯糰」實物的同時銷除手中的「新米陶缽」。指引玩家持飯糰回康平小店。
//   （driver give 指令不認中文「給」﹐故持新米陶缽 ask 即視同送件蒸飯：同步蒸飯、
//     交付飯糰、記旗標、並銷除新米陶缽﹐與經 give 指令觸發 accept_object 等效。）
// 不動其原有的閒談 chat_msg 與 accept_fight。
//
// 新米飯糰採直接 new + move(who) 同步交付——give／ask 皆由玩家觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記旗標
// （與 d/weiguo roaster、d/ziyan incenseman 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void steam_rice(object me);

void create()
{
	set_name("灶上嬸子", ({ "cook", "steamer", "zaoshangshenzi" }) );
	set("nickname", "灶上嬸子");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 44);
	set("gender", "female");
	set("long",
		"一個守著井臺公灶蒸飯的爽利嬸子﹐生得豐潤利落﹐挽著袖\n"
		"子﹐圍著件沾了米湯的藍布圍裙﹐成日守在灶前﹐添柴、看火、揭\n"
		"籠、捏飯。她一手蒸飯的好手藝在康平村是出了名的﹐村裡蒸喜\n"
		"飯、做年食﹐都少不得請她掌灶﹐那蒸飯的火候分寸﹐她最是精\n"
		"熟。得閒也可問問她﹕ask cook about 新米。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"灶上嬸子掀開籠蓋﹐一團白汽騰地冒出來﹐她伸手探了探飯的軟硬﹐又嚴嚴地蓋回籠去。\n",
		"灶上嬸子往灶膛裡添了一把乾柴﹐火舌舔著鍋底﹐她瞇眼瞧著火色﹐緩緩道﹕蒸飯最忌火急﹐文火慢蒸﹐纔蒸得粒粒晶瑩、軟而不爛哩。\n",
		"灶上嬸子挽著袖子﹐在水臺邊把一籮新米淘得雪白﹐瀝乾了水﹐預備上籠﹐口中哼著支不成調的鄉間小曲。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 蒸飯：灶上嬸子把新米上籠蒸熟、捏成飯糰﹐交付新米飯糰、記旗標﹐
// 同時銷除玩家手中的新米陶缽。直接 new + move(me) 同步交付（玩家此刻必在場）﹐
// 先交飯糰、銷陶缽、後記旗標。
private void steam_rice(object me)
{
	object empty = present("rice bowl", me);
	object full = new(__DIR__"obj/rice_dough");
	if( !full->move(me) ) full->move(environment());
	if( empty ) destruct(empty);
	me->set("quest/kangping_rice_dough", 1);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這灶上嬸子甚麼﹖（試試 ask cook about 新米）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("灶上嬸子正守著灶火蒸飯﹐一時沒理會你。\n");

	// 新米 / 飯糰 / 蒸飯：支線「新米飯糰」——持新米陶缽來蒸飯
	if( arg == "cook about 新米"
	||  arg == "cook about 飯糰"
	||  arg == "cook about 飯"
	||  arg == "cook about 米"
	||  arg == "cook about 蒸飯"
	||  arg == "cook about 陶缽"
	||  arg == "cook about rice"
	||  arg == "cook about dough" ) {
		object me = this_player();
		int q = me->query("quest/kangping_rice");

		// 已完成或已蒸好飯糰：純氣氛收尾
		if( q >= 2 || me->query("quest/kangping_rice_dough") ) {
			do_chat((: command,
				"say 那個新米飯糰﹐我已替客官蒸好了。客官快持回康平小店交與店家罷﹐莫教那個好飯糰擱涼了走了味。" :));
			return 1;
		}

		// 進行中、持新米陶缽：ask 即當作蒸飯處理——蒸飯、交飯糰、銷陶缽、記旗標
		// （此路不經 give 指令﹐故由 steam_rice 自行銷除玩家手裡的新米陶缽﹐
		//   與 accept_object 經 give 指令回 1 後自動銷除新米陶缽等效﹐免玩家
		//   留著新米陶缽重複觸發。）
		if( q == 1 && present("rice bowl", me) ) {
			message_vision(
				"灶上嬸子接過$N手裡的新米陶缽﹐把新米淘了一遍﹐瀝乾上籠﹐\n"
				"文火慢蒸了一陣﹐揭籠捏成一個結實的飯糰﹐拿一片乾荷葉嚴嚴地包了。\n", me);
			// 先同步蒸飯、交付飯糰、銷陶缽、記旗標﹐再以 do_chat 收尾（飯糰已先到玩家手裡）。
			steam_rice(me);
			do_chat(({
				(: command, "say 客官是康平小店店家打發來備新米飯糰的罷﹖田裡老倌兒碾的這缽新米﹐果然雪白晶瑩——拿來蒸飯最好不過。" :),
				(: command, "say 我這就把米淘了上籠﹐文火慢蒸﹐蒸熟了捏成糰子﹐拿荷葉包好。喏﹐這新米是今年現收現碾的﹐蒸出來香軟頂飢﹐是咱康平謝場待客的喜飯。" :),
				(: command, "say 喏﹐這個新米飯糰﹐方纔已奉到客官手裡了﹐快持回康平小店交與店家（ask keeper about 新米﹐或 give rice dough to keeper）﹐也好教他拿這籠喜飯去張羅秋收謝場﹐了卻一樁心事。" :),
			}));
			return 1;
		}

		// 進行中、未持新米陶缽：提示先去田壟向田裡老農碾米
		if( q == 1 ) {
			do_chat((: command,
				"say 客官要蒸飯糰﹖總得有缽蒸飯的新米罷。客官且去村心南面的村外田壟﹐尋那位田裡老農碾一缽新收的新米來（ask farmer about 新米）﹐我纔好替客官蒸飯。" :));
			return 1;
		}

		// 未接任務：純風味帶過
		do_chat((: command,
			"say 新米飯糰﹖客官說的是拿田裡新收的米蒸的飯糰罷。那是咱村裡謝場待客的好東西﹐客官若為這飯糰的事﹐還是先去康平小店問問店家罷。" :));
		return 1;
	}

	// 純氣氛閒談：井臺／灶／蒸飯手藝
	if( arg == "cook about 井臺"
	||  arg == "cook about 井"
	||  arg == "cook about 灶"
	||  arg == "cook about 手藝"
	||  arg == "cook about well" ) {
		do_chat(({
			(: command, "say 這蒸飯的工夫啊﹐看著簡單﹐做著精細。米要淘得淨、水要瀝得乾、火要文得勻﹐火急一分則夾生﹐火過一分則爛糊﹐全憑一雙手摸著籠裡的軟硬。我掌了半輩子灶﹐方敢說摸著了門道。" :),
			(: command, "say 咱這井臺的灶是合村公用的﹐誰家有了紅白喜事、要蒸一籠像樣的飯食﹐都來這兒張羅。井裡的水甜﹐淘出來的米也清爽﹐拿這井水蒸的新米飯﹐格外香軟哩。" :),
		}));
		return 1;
	}

	return notify_fail("灶上嬸子抹了把汗爽利一笑﹕客官問這個做甚﹖坐下歇歇﹐聞聞這蒸籠裡新米飯的香罷。\n");
}

// 收下信物：
//   新米陶缽(rice bowl) -- 支線「新米飯糰」蒸飯﹐持新米陶缽且任務進行中時
//   收下、蒸飯、交付新米飯糰、記旗標 kangping_rice_dough。
// 不在此 move／destruct 新米陶缽——give 指令於本函回 1 後會自行 destruct 有值的
// 新米陶缽（與 d/weiguo roaster、d/ziyan incenseman 一致）﹔非送件玩家／時機不符
// 則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("rice bowl") ) {
		int q = who->query("quest/kangping_rice");

		// 未接任務／已完成：婉拒，不收下（避免吞掉新米陶缽）
		if( q != 1 ) {
			do_chat((: command,
				"say 這缽新米 ... 客官還是自個兒收著罷，我一時也用不上。" :));
			return 0;
		}

		// 已蒸過飯（飯糰已交）：婉拒，提示徑去回報小店
		if( who->query("quest/kangping_rice_dough") ) {
			do_chat((: command,
				"say 客官的飯糰方纔已蒸好了﹐這空缽就煩客官留著罷。快持那個新米飯糰回康平小店交與店家便是（ask keeper about 新米﹐或 give rice dough to keeper）。" :));
			return 0;
		}

		// 進行中、持新米陶缽蒸飯：蒸飯、交付飯糰、記旗標（新米陶缽由 give 指令於回 1 後自行銷除）
		message_vision(
			"灶上嬸子接過$N遞來的新米陶缽﹐把新米淘了一遍﹐瀝乾上籠﹐\n"
			"文火慢蒸了一陣﹐揭籠捏成一個結實的飯糰﹐拿一片乾荷葉嚴嚴地包了。\n", who);
		// give 指令會於本函回 1 後自行 destruct 新米陶缽﹐故此處 steam_rice 只交飯糰、記旗標﹔
		// 為穩妥﹐steam_rice 內仍會嘗試銷除手中新米陶缽（present 取到的即將被 give 銷除的同一個）。
		steam_rice(who);
		do_chat(({
			(: command, "say 客官是康平小店店家打發來備新米飯糰的罷﹖田裡老倌兒碾的這缽新米﹐果然雪白晶瑩——拿來蒸飯最好不過。" :),
			(: command, "say 我把米淘了上籠蒸熟﹐捏成糰子拿荷葉包好了。喏﹐這個新米飯糰﹐方纔已奉到客官手裡了﹐快持回康平小店交與店家（ask keeper about 新米﹐或 give rice dough to keeper）。" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個我用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗客官好沒道理﹗欺負我一個掌灶蒸飯的婦道人家做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
