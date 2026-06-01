// roaster.c -- 炒米坊焙炒米麥的炒米師傅（純氣氛閒談）；
//              兼衛國鎮非戰鬥支線「鎮關炒米茶」的和茶人。
//
// 本檔原為炒米坊焙米的氣氛 NPC（俯在鐵鐺前翻炒米麥）。為支線「鎮關炒米茶」
// 加掛和茶一段：
//   玩家自守井老叟絞得井亭瓦罐後﹐持井亭瓦罐 ask roaster about 炒米茶（或
//   give well crock to roaster）-> 炒米師傅接過井亭瓦罐﹐抓一把新焙的炒米
//   沖進甜水裡和勻、封好罐口交還玩家﹐記 quest/weiguo_tea_filled = 1。
//   交付「鎮關炒米茶」實物的同時銷除手中的「井亭瓦罐」。指引玩家持炒米茶回衛國客棧。
//   （driver give 指令不認中文「給」﹐故持井亭瓦罐 ask 即視同送件和茶：同步和茶、
//     交付炒米茶罐、記旗標、並銷除井亭瓦罐﹐與經 give 指令觸發 accept_object 等效。）
// 不動其原有的閒談 chat_msg 與 accept_fight。
//
// 炒米茶罐採直接 new + move(who) 同步交付——give／ask 皆由玩家觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記旗標
// （與 d/ziyan incenseman、d/weiguo welltender 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void mix_tea(object me);

void create()
{
	set_name("炒米師傅", ({ "roaster", "rice roaster", "chaomishifu" }) );
	set("nickname", "炒米師傅");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 46);
	set("gender", "male");
	set("long",
		"一個守著炒米坊焙炒米麥的敦實漢子﹐一身的焦香﹐臉膛教\n"
		"灶火烤得紅亮﹐裹著件沾了米屑的短褐﹐成日俯在鐵鐺前﹐拿長\n"
		"柄木鏟把鐺裡的米麥翻得颯颯作響。他焙的炒米是鎮上一絕﹐沖\n"
		"水即食﹐耐放頂飢﹐那「鎮關炒米茶」和茶的火候分寸﹐他最是\n"
		"精熟。得閒也可問問他﹕ask roaster about 炒米茶。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"炒米師傅拿長柄木鏟把鐺裡的米麥翻得颯颯作響﹐焦香撲鼻﹐惹得人腹中咕咕直叫。\n",
		"炒米師傅瞇眼瞧著鐺裡漸漸轉黃的米粒﹐緩緩道﹕炒米最忌火燥﹐文火慢焙﹐纔焙得粒粒金黃、香而不苦哩。\n",
		"炒米師傅抓起一把焙好的炒米﹐就著鼻子聞了聞那焦香﹐滿意地點點頭﹐倒進一旁的陶甕收著。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 和茶：炒米師傅拿井水沖進新焙的炒米和成炒米茶﹐交付鎮關炒米茶、記旗標﹐
// 同時銷除玩家手中的井亭瓦罐。直接 new + move(me) 同步交付（玩家此刻必在場）﹐
// 先交炒米茶罐、銷井亭瓦罐、後記旗標。
private void mix_tea(object me)
{
	object empty = present("well crock", me);
	object full = new(__DIR__"obj/tea_crock");
	if( !full->move(me) ) full->move(environment());
	if( empty ) destruct(empty);
	me->set("quest/weiguo_tea_filled", 1);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這炒米師傅甚麼﹖（試試 ask roaster about 炒米茶）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("炒米師傅正俯在鐺前翻炒米麥﹐一時沒理會你。\n");

	// 炒米茶 / 炒米：支線「鎮關炒米茶」——持井亭瓦罐來和茶
	if( arg == "roaster about 炒米茶"
	||  arg == "roaster about 炒米"
	||  arg == "roaster about 茶"
	||  arg == "roaster about 井水"
	||  arg == "roaster about 瓦罐"
	||  arg == "roaster about tea"
	||  arg == "roaster about rice" ) {
		object me = this_player();
		int q = me->query("quest/weiguo_tea");

		// 已完成或已和好炒米茶：純氣氛收尾
		if( q >= 2 || me->query("quest/weiguo_tea_filled") ) {
			do_chat((: command,
				"say 那罐炒米茶﹐老夫已替客官和好了。客官快持回衛國客棧交與掌櫃罷﹐莫教那罐好茶擱涼了走了味。" :));
			return 1;
		}

		// 進行中、持井亭瓦罐：ask 即當作和茶處理——和茶、交炒米茶罐、銷井亭瓦罐、記旗標
		// （此路不經 give 指令﹐故由 mix_tea 自行銷除玩家手裡的井亭瓦罐﹐
		//   與 accept_object 經 give 指令回 1 後自動銷除井亭瓦罐等效﹐免玩家
		//   留著井亭瓦罐重複觸發。）
		if( q == 1 && present("well crock", me) ) {
			message_vision(
				"炒米師傅接過$N手裡的井亭瓦罐﹐自陶甕裡抓一把新焙的炒米\n"
				"撒進罐裡的甜水﹐拿長箸緩緩攪勻﹐又取一片箬葉嚴嚴地封了罐口。\n", me);
			// 先同步和茶、交付炒米茶罐、銷井亭瓦罐、記旗標﹐再以 do_chat 收尾（炒米茶罐已先到玩家手裡）。
			mix_tea(me);
			do_chat(({
				(: command, "say 客官是衛國客棧掌櫃打發來和鎮關炒米茶的罷﹖守井的老倌兒絞的這罐古井水﹐果然甜冽——拿來沖炒米最好不過。" :),
				(: command, "say 老夫這就抓一把新焙的炒米沖進去﹐攪勻封好。喏﹐這炒米是文火慢焙的﹐粒粒金黃﹐沖進這井水裡﹐焦香頂飢、回甘解乏﹐當年屯軍出關喝的就是這一口。" :),
				(: command, "say 喏﹐這罐鎮關炒米茶﹐方纔已奉到客官手裡了﹐快持回衛國客棧交與掌櫃（ask keeper about 炒米茶﹐或 give tea crock to keeper）﹐也好教他拿這碗鄉味替那位舊識餞行﹐了卻一樁心事。" :),
			}));
			return 1;
		}

		// 進行中、未持井亭瓦罐：提示先去古井亭向守井老叟絞水
		if( q == 1 ) {
			do_chat((: command,
				"say 客官要和炒米茶﹖總得有罐沖茶的井水罷。客官且去場南石徑盡頭的古井亭﹐尋那位守井的老叟絞一罐古井甜水來（ask welltender about 炒米茶）﹐老夫纔好替客官和茶。" :));
			return 1;
		}

		// 未接任務：純風味帶過
		do_chat((: command,
			"say 炒米茶﹖客官說的是拿井水沖炒米和的鎮關炒米茶罷。那是咱鎮上送遠待客的好東西﹐客官若為這炒米茶的事﹐還是先去衛國客棧問問掌櫃罷。" :));
		return 1;
	}

	// 純氣氛閒談：炒米／炒米坊
	if( arg == "roaster about 坊"
	||  arg == "roaster about 炒米坊"
	||  arg == "roaster about 焙米"
	||  arg == "roaster about studio" ) {
		do_chat(({
			(: command, "say 這炒米的工夫啊﹐看著粗﹐做著細。火大一分則焦苦﹐火小一分則不香﹐全憑一雙眼看著鐺裡的米色﹐一鏟也馬虎不得。老夫焙了半輩子﹐方敢說摸著了門道。" :),
			(: command, "say 衛國地處邊縣﹐出鎮便是長路。早年屯軍出關﹐隨身帶的便是這般炒得乾透的米麥﹐沖水即食﹐耐放頂飢。後來鎮民循著這法子焙出鎮關炒米茶﹐如今成了衛國送遠待客的鄉味嘍。" :),
		}));
		return 1;
	}

	return notify_fail("炒米師傅抹了把汗憨憨一笑﹕客官問這個做甚﹖坐下歇歇﹐聞聞這炒米的焦香罷。\n");
}

// 收下信物：
//   井亭瓦罐(well crock) -- 支線「鎮關炒米茶」和茶﹐持井亭瓦罐且任務進行中時
//   收下、和茶、交付鎮關炒米茶、記旗標 weiguo_tea_filled。
// 不在此 move／destruct 井亭瓦罐——give 指令於本函回 1 後會自行 destruct 有值的
// 井亭瓦罐（與 d/ziyan incenseman、d/shuiyue angler 一致）﹔非送件玩家／時機不符
// 則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("well crock") ) {
		int q = who->query("quest/weiguo_tea");

		// 未接任務／已完成：婉拒，不收下（避免吞掉井亭瓦罐）
		if( q != 1 ) {
			do_chat((: command,
				"say 這罐井水 ... 客官還是自個兒收著罷，老夫一時也用不上。" :));
			return 0;
		}

		// 已和過茶（炒米茶罐已交）：婉拒，提示徑去回報客棧
		if( who->query("quest/weiguo_tea_filled") ) {
			do_chat((: command,
				"say 客官的炒米茶方纔已和好了﹐這空罐就煩客官留著罷。快持那罐鎮關炒米茶回衛國客棧交與掌櫃便是（ask keeper about 炒米茶﹐或 give tea crock to keeper）。" :));
			return 0;
		}

		// 進行中、持井亭瓦罐和茶：和茶、交付炒米茶罐、記旗標（井亭瓦罐由 give 指令於回 1 後自行銷除）
		message_vision(
			"炒米師傅接過$N遞來的井亭瓦罐﹐自陶甕裡抓一把新焙的炒米\n"
			"撒進罐裡的甜水﹐拿長箸緩緩攪勻﹐又取一片箬葉嚴嚴地封了罐口。\n", who);
		// give 指令會於本函回 1 後自行 destruct 井亭瓦罐﹐故此處 mix_tea 只交炒米茶罐、記旗標﹔
		// 為穩妥﹐mix_tea 內仍會嘗試銷除手中井亭瓦罐（present 取到的即將被 give 銷除的同一個）。
		mix_tea(who);
		do_chat(({
			(: command, "say 客官是衛國客棧掌櫃打發來和鎮關炒米茶的罷﹖守井的老倌兒絞的這罐古井水﹐果然甜冽——拿來沖炒米最好不過。" :),
			(: command, "say 老夫抓一把新焙的炒米沖進去攪勻封好了。喏﹐這罐鎮關炒米茶﹐方纔已奉到客官手裡了﹐快持回衛國客棧交與掌櫃（ask keeper about 炒米茶﹐或 give tea crock to keeper）。" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老夫用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗客官好沒道理﹗欺負我一個焙米的手藝人做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
