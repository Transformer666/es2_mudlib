// beastking.c -- 隱居老獵王，獵王世家末代後人，掛單於雪亭鎮飲風客棧，
//                主線任務六「摩雲蹤跡」的委託人與領賞人
//
// 故事背景（承接主線五「群獸朝靈」）：
//   雪亭鎮飲風客棧那位雲遊道人﹐已自老松林守山人帶回的遷徙圖坐實﹕滿山走
//   獸皆聽命於一頭喚作摩雲的獸王﹐齊朝天靈山而去——這場動物war算是揭了序
//   幕。然摩雲究竟退往何處蓄勢﹐道人卻推算不真。恰有一位隱居的老獵王﹐也
//   掛單在這飲風客棧——他出身獵王世家﹐祖孫三代專追摩雲一脈﹐手裡有半卷祖
//   傳的《摩雲蹤跡圖》。老獵王年邁腿腳不便﹐又因那獸窟最深處戾氣太重不敢
//   再涉﹐遂託這位已勘明群獸朝靈、循異兆而來的少俠﹐持那卷殘圖往野獸山林
//   最深處﹐尋一位能辨獸語的異人續補蹤跡﹐探明摩雲今時退守的去向﹐好早作
//   籌謀﹐迎那將臨的決戰。
//
// 任務流程（旗標存在玩家身上：quest/main_omen6）：
//   入門條件     : 須先完成主線五（quest/main_omen5 >= 3）﹐否則只嘆息﹐不開任務
//   未開始 (0)   : 玩家 ask beastking about 摩雲 -> 老獵王交付「摩雲蹤跡圖殘卷」﹐旗標設為 1
//   進行中 (1)   : 玩家持殘卷往野獸山林林窟深處之側的密窟﹐交(give)給獸語者
//                  (/d/hudao/wild/npc/beasttalker)﹐獸語者驗卷後收下﹐續補蹤跡、
//                  道出摩雲退守天靈山麓蓄勢﹐回給「摩雲爪拓」﹐並把旗標推進為 2
//                  （推進在 beasttalker.c）
//   已取得 (2)   : 玩家把爪拓帶回飲風客棧交(give)給老獵王 -> 領賞(give_reward)﹐旗標設為 3
//   已完成 (3)   : 不再重複給賞﹐do_ask 給出朝向天靈山決戰／混沌珠一段的純劇情伏筆

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("隱居老獵王", ({ "old beast king", "beast king", "beastking" }) );
	set("nickname", "隱居老獵王");
	set_attr("str", 24);
	set_attr("con", 22);
	set_attr("dex", 23);
	set_race("human");
	set_class("fighter");
	set_level(16);
	set_skill("unarmed", 35);
	set_skill("dodge", 35);
	set_skill("blade", 40);
	set_skill("archery", 45);
	set_skill("force", 35);

	set("gender", "male");
	set("age", 66);
	set("long",
		"一位獨坐客棧角落、鬚髮皆白的老者﹐脊背雖已微僂﹐一雙手卻\n"
		"仍筋骨虯結﹐虎口處磨著厚厚的老繭——那是常年挽弓執刃才有的\n"
		"印記。他身上一件半舊的玄色獸皮短打﹐領口袖緣綴著幾枚森森\n"
		"的獸牙獸爪﹐皆是當年親手獵得的猛獸所留。聽客棧的人說﹐這\n"
		"老者出身一門專獵兇獸的獵王世家﹐祖孫三代追的﹐都是同一頭\n"
		"喚作摩雲的獸王。如今他老了﹐獵不動了﹐只揣著半卷祖傳的舊\n"
		"圖﹐日日望著北面天靈山的方向出神。\n"
		"你或許可以問問他﹕ask beastking about 摩雲。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老獵王枯瘦的手指無意識地摩挲著領口那幾枚獸爪﹐渾濁的眼裡掠過一絲精光。\n",
		"老獵王喃喃道﹕摩雲 ... 我祖孫三代追了你一世 ... 這回你又躲到哪裡去了 ...\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen6");
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 少俠﹐野獸山林最深處那一趟﹐摩雲今時的去向﹐可有了著落﹖" :));
		else if( !q && this_player()->query("quest/main_omen5") >= 3 )
			do_chat((: command,
				"say 少俠身上 ... 竟沾著摩雲那一脈的戾氣﹖看來你也是循著那獸王的蹤跡來的。" :));
	}
}

// 把一卷摩雲蹤跡圖殘卷交到玩家手上（先複製到自己身上，再 give 出去）
private void give_scroll(object who)
{
	object scroll;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	scroll = new("/d/snow/npc/obj/trace_scroll");
	scroll->move(this_object());
	command("give trace scroll to " + who->query("id"));
}

// 領賞：給一串銅錢、一帖傷藥﹐並授存活、俠義之舉、聲望與旅行見聞
private void give_reward(object who)
{
	object coin, pill;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(450);
	if( !coin->move(who) ) coin->move(environment());

	pill = new("/obj/medication/alchemist/aquapill");
	if( !pill->move(who) ) pill->move(environment());

	who->gain_score("survive", 450);
	who->gain_score("emprise", 160);
	who->gain_score("reputation", 90);
	who->gain_score("explorer fame", 60);

	message_vision(
		"老獵王將那幅爪拓在燈下反覆端詳﹐枯瘦的手指撫過拓上那道青黑爪痕﹐"
		"久久不語﹐末了自懷裡摸出一串攢下的銅錢與一帖金液丹﹐鄭重地交到$N手裡。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "beast king about 摩雲"
		&&   arg != "beast king about 主線"
		&&   arg != "beast king about 任務"
		&&   arg != "beast king about 獸王"
		&&   arg != "beastking about 摩雲"
		&&   arg != "beastking about 主線"
		&&   arg != "beastking about 任務"
		&&   arg != "old beast king about 摩雲"
		&&   arg != "old beast king about 獸王"
		&&   arg != "beast king about quest"
		&&   arg != "beast king about task") )
		return notify_fail("你想問這位老獵王甚麼﹖（試試 ask beastking about 摩雲）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老獵王正出神地望著北面天靈山的方向﹐沒空理你。\n");

	// 入門條件：須先完成主線五「群獸朝靈」
	if( me->query("quest/main_omen5") < 3 ) {
		do_chat(({
			(: command, "say 少俠面生 ... 老朽追了一世的摩雲﹐這滿山走獸的禍事﹐豈是三言兩語能與生人說清的。" :),
			(: command, "say 少俠若真要究這獸王的根底﹐倒不如先去尋那位掛單在本店的雲遊道長﹐隨他把這群獸朝靈的去向勘個明白。待你曉得了摩雲是何方神聖﹐再來尋老朽不遲。" :),
		}));
		return 1;
	}

	q = me->query("quest/main_omen6");

	// 主線六已全部完成：收尾、加深朝向天靈山決戰／混沌珠一段的伏筆（純劇情，不開任務）
	if( q >= 3 ) {
		do_chat(({
			(: command, "say 多虧少俠走這一趟﹐那幅爪拓老朽已參詳明白——摩雲果然退往天靈山麓去了﹐蟄伏蓄勢﹐怕是要養足了氣力﹐再興一場更大的獸亂。" :),
			(: command, "say 老朽獵王世家三代追摩雲﹐到頭來才看清﹕摩雲不過是頭被驅策的猛獸﹐真正勾動牠的﹐是天靈山深處那頭悔天鬼﹐還有那顆喚作『混沌珠』的至邪之物。摩雲一脈之後﹐尚有骨屍妖王、鬼王噬魂之輩﹐層層守著那珠的下落。" :),
			(: command, "say 老朽腿腳不中用了﹐這條追兇之路﹐往後得靠少俠去走。摩雲既退守天靈山麓﹐少俠須先尋一位能破那山中邪障的同道﹐再求一件能制混沌珠的聖物﹐方好上那天靈山與摩雲決一死戰。少俠是有大氣運的人﹐老朽這把老骨頭﹐就在這客棧裡替你守著消息。" :),
		}));
		return 1;
	}

	// 已取得爪拓，回來交付（理應用 give 交付，這裡只作提示）
	if( q == 2 ) {
		if( present("claw rubbing", me) )
			do_chat((: command,
				"say 野獸山林那一趟有著落了罷﹖快把那幅摩雲爪拓交(give)給老朽瞧瞧﹗" :));
		else
			do_chat((: command,
				"say 咦﹐那幅爪拓呢﹖少俠莫不是弄丟了﹖快回野獸山林最深處﹐尋那獸語者補拓一幅。" :));
		return 1;
	}

	// 任務進行中（已領殘卷，還沒回來）
	if( q == 1 ) {
		if( present("trace scroll", me) )
			do_chat((: command,
				"say 那卷蹤跡圖少俠帶在身上了。出客棧往廣場去﹐自廣場南行出草棚﹐"
				"入老松林再往東便是深處﹐自深處循新踏的獸徑往北﹐穿過山坡獸窟﹐"
				"直入林窟深處﹐窟東石壁另有一道隙縫﹐裡頭密窟裡棲著位獸語者——"
				"把殘卷交(give)給他﹐自能續補出摩雲的去向。" :));
		else
			// 萬一玩家把殘卷弄丟了，補一卷給他
			do_chat(({
				"老獵王搖頭一嘆﹐又自懷裡取出另一卷一般無二的舊圖摹本。\n",
				(: command, "say 怎麼那卷圖不見了﹖罷了﹐這摩雲蹤跡圖老朽心裡記著大半﹐再與少俠摹一卷便是﹐這回可收好了。" :),
				(: give_scroll, me :),
			}));
		return 1;
	}

	// 尚未接任務：交付摩雲蹤跡圖殘卷，旗標設為 1
	me->set("quest/main_omen6", 1);
	do_chat(({
		(: command, "say 少俠既已隨那雲遊道長勘明了群獸朝靈的去向﹐想必也曉得那獸王摩雲了。老朽便不瞞你——老朽這一門﹐是世代追獵摩雲的獵王世家。" :),
		(: command, "say 老朽的祖父、父親﹐連同老朽自個兒﹐祖孫三代追了摩雲一世。這頭獸王生具懾服百獸之能﹐極是狡黠﹐每隔數十年便要興一場獸亂﹐亂後又遁入深山蟄伏。老朽這裡有半卷祖傳的《摩雲蹤跡圖》﹐記著歷年勘下的舊蹤——可惜殘缺過半﹐又教天靈山這縷新漫的邪念攪亂了脈絡﹐再認不出摩雲今時退往何處。" :),
		(: command, "say 老朽老了﹐獵不動了﹐那獸窟最深處戾氣又重﹐委實不敢再涉。少俠可願持這卷殘圖﹐往野獸山林最深處走一遭﹖那林窟深處之側﹐另有一道隙縫﹐裡頭密窟裡棲著一位能辨獸語、識獸蹤的異人——把殘卷交(give)給他續補﹐自能探明摩雲今時退守的去向。" :),
		(: command, "say 摩雲既受悔天鬼驅策而動﹐這場動物war﹐怕是要愈演愈烈。少俠探明牠的去向﹐老朽好早作籌謀﹐迎那將臨的決戰。此事干係天下安危﹐萬望少俠謹慎﹗" :),
		(: give_scroll, me :),
	}));
	return 1;
}

// 收下信物：
//   摩雲爪拓(claw rubbing) -- 主線六「摩雲蹤跡」交還﹐旗標 main_omen6 2 -> 3﹐領賞(give_reward)
// 收下後不自行 destruct﹐由 give 指令將信物移入本 NPC（與 hunter／diviner 一致）﹐
// 並於最終旗標處作防重複領獎。
int accept_object(object who, object ob)
{
	// 主線六：交還摩雲爪拓
	if( ob->id("claw rubbing") ) {
		// 已領過賞（旗標已 >=3）：道謝收下﹐不重複給賞
		if( who->query("quest/main_omen6") >= 3 ) {
			do_chat((: command, "say 那幅爪拓老朽早已收訖﹐正日夜參詳著﹐多謝少俠跑這一趟了﹗" :));
			return 1;
		}
		// 尚未進行到交付這一步（旗標不為 2）：仍收下避免卡物﹐但不推進、不給賞
		if( who->query("quest/main_omen6") != 2 ) {
			do_chat((: command, "say 多謝少俠﹗" :));
			return 1;
		}

		who->set("quest/main_omen6", 3);
		do_chat(({
			(: command, "say 這便是摩雲今時的爪痕麼 ... 嘶﹗少俠瞧這爪距、這崩石的紋路——不錯﹐正是摩雲那一脈的爪法﹐老朽祖父留下的圖譜上記著呢。這青黑戾氣 ... 牠果真退往天靈山麓蓄勢去了。" :),
			(: give_reward, who :),
			(: command, "say 這點銅錢與丹藥﹐少俠收著防身。少俠肯為這天下蒼生涉那獸窟之險﹐老朽承你的情了——往後上天靈山尋摩雲決戰﹐還要靠少俠這身本事啊﹗" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒﹐不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 老朽一個行將就木的獵戶﹐了無長物﹐這個受不起﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠息怒﹗老朽一個獵不動兇獸的老朽夫﹐與少俠無冤無仇哪。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
