// incenseman.c -- 沉香小亭焙香的焙香師（純氣氛閒談）；
//                 兼紫煙鎮非戰鬥支線「安神香湯」的和香人。
//
// 本檔原為亭中焙香的氣氛 NPC（借溫泉湯氣焙香、自得其樂）。為支線「安神香湯」
// 加掛和香一段：
//   玩家自燒湯老叟汲得溫泉陶罐後﹐持溫泉陶罐 ask incenseman about 香湯（或
//   give spring crock to incenseman）-> 焙香師接過溫泉陶罐﹐調進新焙的沉香細末
//   和勻、封好罐口交還玩家﹐記 quest/ziyan_incense_filled = 1。
//   交付「安神香湯罐」實物的同時銷除手中的「溫泉陶罐」。指引玩家持香湯回紫煙小棧。
//   （driver give 指令不認中文「給」﹐故持溫泉陶罐 ask 即視同送件和香：同步和香、
//     交付香湯罐、記旗標、並銷除溫泉陶罐﹐與經 give 指令觸發 accept_object 等效。）
// 不動其原有的閒談 chat_msg 與 accept_fight。
//
// 香湯罐採直接 new + move(who) 同步交付——give／ask 皆由玩家觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記旗標
// （與本鎮 d/ziyan keeper、springman、d/shuiyue angler 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void mix_soup(object me);

void create()
{
	set_name("焙香師", ({ "incenseman", "incense maker", "beixiangshi" }) );
	set("nickname", "焙香師");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 52);
	set("gender", "male");
	set("long",
		"一位在沉香小亭焙香的師傅﹐生得清雅文靜﹐一雙手卻被香\n"
		"料染得微微發黃﹐成日凝神守著爐上的香材﹐借坡上引來的溫泉\n"
		"湯氣回潮養香。他焙的沉香是紫煙鎮一絕﹐安神助眠﹐鎮外的客\n"
		"商都愛來討買。這和香、焙香的門道﹐他最是精熟。得閒也可問\n"
		"問他﹕ask incenseman about 香湯。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"焙香師拈起一撮切碎的香材﹐輕輕撒在爐上的竹篩裡﹐凝神看著那縷青煙裊裊升起。\n",
		"焙香師悠悠地道﹕焙香最忌火燥﹐借這溫泉湯氣回潮慢養﹐香味纔焙得綿長醇厚哩。\n",
		"焙香師閉目深深吸了口亭裡的香氣﹐神色一片寧定﹐似已物我兩忘。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 和香：焙香師拿溫泉水調進新焙的沉香細末和成香湯﹐交付安神香湯罐、記旗標﹐
// 同時銷除玩家手中的溫泉陶罐。直接 new + move(me) 同步交付（玩家此刻必在場）﹐
// 先交香湯罐、銷溫泉罐、後記旗標。
private void mix_soup(object me)
{
	object empty = present("spring crock", me);
	object full = new(__DIR__"obj/incense_crock");
	if( !full->move(me) ) full->move(environment());
	if( empty ) destruct(empty);
	me->set("quest/ziyan_incense_filled", 1);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這焙香師甚麼﹖（試試 ask incenseman about 香湯）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("焙香師正凝神守著爐上的香材﹐一時沒理會你。\n");

	// 香湯 / 沉香：支線「安神香湯」——持溫泉陶罐來和香
	if( arg == "incenseman about 香湯"
	||  arg == "incenseman about 沉香"
	||  arg == "incenseman about 香"
	||  arg == "incenseman about 溫泉"
	||  arg == "incenseman about 陶罐"
	||  arg == "incenseman about incense"
	||  arg == "incenseman about soup" ) {
		object me = this_player();
		int q = me->query("quest/ziyan_incense");

		// 已完成或已和好香湯：純氣氛收尾
		if( q >= 2 || me->query("quest/ziyan_incense_filled") ) {
			do_chat((: command,
				"say 那罐香湯﹐老夫已替客官和好了。客官快持回紫煙小棧交與掌櫃罷﹐莫教那罐好香湯擱涼了走了味。" :));
			return 1;
		}

		// 進行中、持溫泉陶罐：ask 即當作和香處理——和香、交香湯罐、銷溫泉罐、記旗標
		// （此路不經 give 指令﹐故由 mix_soup 自行銷除玩家手裡的溫泉陶罐﹐
		//   與 accept_object 經 give 指令回 1 後自動銷除溫泉陶罐等效﹐免玩家
		//   留著溫泉罐重複觸發。）
		if( q == 1 && present("spring crock", me) ) {
			message_vision(
				"焙香師接過$N手裡的溫泉陶罐﹐自爐上撮起一撮新焙的沉香細末\n"
				"調進罐裡﹐拿竹箸緩緩攪勻﹐又取一片荷葉嚴嚴地封了罐口。\n", me);
			// 先同步和香、交付香湯罐、銷溫泉罐、記旗標﹐再以 do_chat 收尾（香湯罐已先到玩家手裡）。
			mix_soup(me);
			do_chat(({
				(: command, "say 客官是紫煙小棧掌櫃打發來和安神香湯的罷﹖燒湯的老倌兒汲的這罐溫泉水﹐果然鮮活﹐礦氣足——拿來和香最好不過。" :),
				(: command, "say 老夫這就拿新焙的沉香細末調進去﹐和勻封好。喏﹐這沉香是借溫泉湯氣回潮慢養焙的﹐火氣不燥、香味綿長﹐和進這溫泉水裡﹐溫飲泡浴皆宜﹐安神得很。" :),
				(: command, "say 喏﹐這罐安神香湯﹐方纔已奉到客官手裡了﹐快持回紫煙小棧交與掌櫃（ask keeper about 香湯﹐或 give incense crock to keeper）﹐也好教他拿去款待那位貴客﹐了卻一樁心事。" :),
			}));
			return 1;
		}

		// 進行中、未持溫泉陶罐：提示先去溫泉向燒湯老叟汲水
		if( q == 1 ) {
			do_chat((: command,
				"say 客官要和香湯﹖總得有罐和香的溫泉水罷。客官且去鎮南的紫煙溫泉﹐尋那位司爐的燒湯老叟汲一罐溫泉水來（ask springman about 香湯）﹐老夫纔好替客官和香。" :));
			return 1;
		}

		// 未接任務：純風味帶過
		do_chat((: command,
			"say 香湯﹖客官說的是拿溫泉水和沉香末和的安神香湯罷。那是咱鎮上待客的好東西﹐客官若為這香湯的事﹐還是先去紫煙小棧問問掌櫃罷。" :));
		return 1;
	}

	// 純氣氛閒談：焙香／沉香小亭
	if( arg == "incenseman about 亭"
	||  arg == "incenseman about 沉香小亭"
	||  arg == "incenseman about 焙香"
	||  arg == "incenseman about censer" ) {
		do_chat(({
			(: command, "say 這沉香小亭啊﹐三面通風﹐一面倚著坡上引來的溫泉湯氣﹐老夫就靠這湯氣回潮養香﹐焙出的沉香火氣不燥、香味綿長﹐是別處乾焙比不得的。" :),
			(: command, "say 老夫焙了半輩子的香﹐圖的是這份心定神閒。客官若心煩﹐也來亭裡坐坐﹐聞聞這沉香﹐保管把煩心事都忘了。" :),
		}));
		return 1;
	}

	return notify_fail("焙香師拈著香材淡淡一笑﹕客官問這個做甚﹖坐下來﹐聞聞這沉香罷。\n");
}

// 收下信物：
//   溫泉陶罐(spring crock) -- 支線「安神香湯」和香﹐持溫泉罐且任務進行中時
//   收下、和香、交付安神香湯罐、記旗標 ziyan_incense_filled。
// 不在此 move／destruct 溫泉陶罐——give 指令於本函回 1 後會自行 destruct 有值的
// 溫泉陶罐（與本鎮其餘送件 NPC、d/shuiyue angler 一致）﹔非送件玩家／時機不符
// 則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("spring crock") ) {
		int q = who->query("quest/ziyan_incense");

		// 未接任務／已完成：婉拒，不收下（避免吞掉溫泉陶罐）
		if( q != 1 ) {
			do_chat((: command,
				"say 這罐溫泉水 ... 客官還是自個兒收著罷，老夫一時也用不上。" :));
			return 0;
		}

		// 已和過香（香湯罐已交）：婉拒，提示徑去回報客棧
		if( who->query("quest/ziyan_incense_filled") ) {
			do_chat((: command,
				"say 客官的香湯方纔已和好了﹐這空罐就煩客官留著罷。快持那罐安神香湯回紫煙小棧交與掌櫃便是（ask keeper about 香湯﹐或 give incense crock to keeper）。" :));
			return 0;
		}

		// 進行中、持溫泉陶罐和香：和香、交付香湯罐、記旗標（溫泉陶罐由 give 指令於回 1 後自行銷除）
		message_vision(
			"焙香師接過$N遞來的溫泉陶罐﹐自爐上撮起一撮新焙的沉香細末\n"
			"調進罐裡﹐拿竹箸緩緩攪勻﹐又取一片荷葉嚴嚴地封了罐口。\n", who);
		// give 指令會於本函回 1 後自行 destruct 溫泉陶罐﹐故此處 mix_soup 只交香湯罐、記旗標﹔
		// 為穩妥﹐mix_soup 內仍會嘗試銷除手中溫泉罐（present 取到的即將被 give 銷除的同一個）。
		mix_soup(who);
		do_chat(({
			(: command, "say 客官是紫煙小棧掌櫃打發來和安神香湯的罷﹖燒湯的老倌兒汲的這罐溫泉水﹐果然鮮活——拿來和香最好不過。" :),
			(: command, "say 老夫拿新焙的沉香細末調進去和勻封好了。喏﹐這罐安神香湯﹐方纔已奉到客官手裡了﹐快持回紫煙小棧交與掌櫃（ask keeper about 香湯﹐或 give incense crock to keeper）。" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老夫用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗客官好沒道理﹗欺負我一個焙香的手藝人做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
