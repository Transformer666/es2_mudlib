// inkmaker.c -- 松煙墨坊裡燒煙搗墨的墨工（純氣氛閒談）；
//               兼文國縣非戰鬥支線「天風筆會」的配墨人。
//
// 本檔為松煙墨坊製墨的氣氛 NPC。為支線「天風筆會」加掛配墨一段：
//   玩家自老筆匠討得安了新筆的「筆匣」後﹐持筆匣 ask inkmaker about 文房（或
//   give brush case to inkmaker）-> 墨工揀一錠坊裡最得意的松煙好墨﹐配進匣中﹐
//   湊成筆墨相稱的一副文房﹐封好匣蓋交還玩家﹐記 quest/wenguo_brush_filled = 1。
//   交付「文房筆匣」實物的同時銷除手中的「天風筆匣」。指引玩家持配齊的文房回天風客棧。
//   （driver give 指令不認中文「給」﹐故持筆匣 ask 即視同送件配墨：同步配墨、
//     交付滿匣、記旗標、並銷除空匣﹐與經 give 指令觸發 accept_object 等效。）
//
// 滿匣採直接 new + move(who) 同步交付——give／ask 皆由玩家觸發﹐玩家此刻必在場﹔
// move 回 1 為成功（落在玩家身上）﹐回 0（失敗）才退而落到地上。先交物、後記旗標
// （與本縣 d/wenguo keeper、brushmaker、d/louxian welltender 一致）。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void fill_case(object me);

void create()
{
	set_name("墨工", ({ "inkmaker", "ink maker", "mogong" }) );
	set("nickname", "墨工");
	set_race("human");
	set_class("commoner");
	set_level(6);

	set("age", 57);
	set("gender", "male");
	set("long",
		"一位松煙墨坊的墨工﹐生得精瘦﹐臉上手上沾著洗不淨的墨\n"
		"色﹐圍著條黑黢黢的布裙﹐俯在案前拿小錘細細地修著墨錠的稜\n"
		"角。他在這墨坊裡燒了大半輩子的煙、搗了大半輩子的墨﹐那松\n"
		"煙的肥瘦、和膠的火候﹐沒有他不熟的。得閒也可問問他﹕ask inkmaker about 文房。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"墨工俯在案前﹐拿一柄小錘與一把細銼﹐一點一點地修著墨錠的稜角。\n",
		"墨工就著矮窯的火光看了看碗底的松煙﹐自語道﹕火候到了﹐這一窯的煙﹐肥瘦正好。\n",
		"墨工拈起一錠晾乾的新墨﹐就著鼻子聞了聞﹐又對著光看那描金的紋樣﹐滿意地點點頭。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 配墨：墨工揀一錠坊裡最得意的松煙好墨配進匣中﹐交付配齊的文房筆匣、記旗標﹐
// 同時銷除玩家手中的天風筆匣（空匣）。直接 new + move(me) 同步交付（玩家此刻必在場）﹐
// 先交滿匣、銷空匣、後記旗標。
private void fill_case(object me)
{
	object empty = present("brush case", me);
	object full = new(__DIR__"obj/writing_case");
	if( !full->move(me) ) full->move(environment());
	if( empty ) destruct(empty);
	me->set("quest/wenguo_brush_filled", 1);
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這墨工甚麼﹖（試試 ask inkmaker about 文房）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("墨工正俯在案前修著墨錠﹐一時沒理會你。\n");

	// 文房 / 墨 / 松煙：支線「天風筆會」——持筆匣來配墨
	if( arg == "inkmaker about 文房"
	||  arg == "inkmaker about 筆"
	||  arg == "inkmaker about 墨"
	||  arg == "inkmaker about 松煙"
	||  arg == "inkmaker about 筆匣"
	||  arg == "inkmaker about brush"
	||  arg == "inkmaker about ink" ) {
		object me = this_player();
		int q = me->query("quest/wenguo_brush");

		// 已完成或已配齊文房：純氣氛收尾
		if( q >= 2 || me->query("quest/wenguo_brush_filled") ) {
			do_chat((: command,
				"say 那副文房﹐墨工已替客官配齊了。客官快持回天風客棧交與掌櫃罷﹐莫教那舊識的文會誤了日子。" :));
			return 1;
		}

		// 進行中、持筆匣：ask 即當作配墨處理——配墨、交滿匣、銷空匣、記旗標
		// （此路不經 give 指令﹐故由 fill_case 自行銷除玩家手裡的天風筆匣﹐
		//   與 accept_object 經 give 指令回 1 後自動銷除空匣等效﹐免玩家
		//   留著空匣重複觸發。）
		if( q == 1 && present("brush case", me) ) {
			message_vision(
				"墨工接過$N手裡的筆匣﹐揭蓋瞧了瞧那管新筆﹐又自木格上揀下\n"
				"一錠描金的松煙好墨﹐就著匣中的襯綢安頓妥當﹐封好了匣蓋。\n", me);
			// 先同步配墨、交付滿匣、銷空匣、記旗標﹐再以 do_chat 收尾（滿匣已先到玩家手裡）。
			fill_case(me);
			do_chat(({
				(: command, "say 客官是天風客棧掌櫃打發來配墨的罷﹖老筆匠安的這管天風狼毫﹐果然是好筆——配墨﹐自當配咱坊裡最得意的松煙好墨﹐方不辱沒了這副文房。" :),
				(: command, "say 墨工與客官揀的這一錠﹐是頭窯的肥煙、上好的魚膠和的﹐又添了幾分龍麝﹐磨開來烏亮生光、清香撲鼻﹐落紙不滯不洇。喏﹐就安在匣裡了。" :),
				(: command, "say 喏﹐這隻筆墨俱備的文房筆匣﹐方纔已奉到客官手裡了﹐快持回天風客棧交與掌櫃（ask keeper about 文房﹐或 give writing case to keeper）﹐也好教他驗驗這副雅禮﹐了卻一樁心事。" :),
			}));
			return 1;
		}

		// 進行中、未持筆匣：提示先去制筆作坊向老筆匠討筆匣
		if( q == 1 ) {
			do_chat((: command,
				"say 客官要配墨﹖總得先有管好筆、有隻安筆的匣子罷。客官且去大街西北的制筆作坊﹐尋那位老筆匠討一管天風狼毫、安進筆匣（ask brushmaker about 文房）﹐墨工纔好替客官配墨。" :));
			return 1;
		}

		// 未接任務：純風味帶過
		do_chat((: command,
			"say 文房﹖客官說的是配咱坊裡這松煙好墨罷。這墨是好墨﹐客官若為備文房雅禮的事﹐還是先去天風客棧問問掌櫃罷。" :));
		return 1;
	}

	// 純氣氛閒談：松煙墨坊／製墨
	if( arg == "inkmaker about 墨坊"
	||  arg == "inkmaker about 製墨"
	||  arg == "inkmaker about 窯"
	||  arg == "inkmaker about inkstudio" ) {
		do_chat(({
			(: command, "say 這製墨的工夫啊﹐講究『輕膠十萬杵』——煙要細、膠要輕、杵要狠、晾要久﹐一錠好墨擱上十年八年﹐磨開來反倒更見光彩﹐這才叫『藏墨』。" :),
			(: command, "say 咱文國這『翰墨之鄉』的名號﹐筆佔一半﹐墨佔一半。後生家莫嫌這坊裡煙嗆﹐沒這一窯一窯的松煙﹐縣裡的文士拿甚麼揮毫﹖" :),
		}));
		return 1;
	}

	return notify_fail("墨工抬眼一笑﹕客官問這個做甚﹖這坊裡煙嗆得很﹐仔細燻了客官的衣裳。\n");
}

// 收下信物：
//   天風筆匣(brush case) -- 支線「天風筆會」配墨﹐持空匣（內安新筆）且任務進行中時
//   收下、配墨、交付文房筆匣、記旗標 wenguo_brush_filled。
// 不在此 move／destruct 天風筆匣——give 指令於本函回 1 後會自行 destruct 有值的
// 天風筆匣（與本縣其餘送件 NPC、d/louxian welltender 一致）﹔非送件玩家／時機不符
// 則回 0 婉拒，不吞物。
int accept_object(object who, object ob)
{
	if( ob->id("brush case") ) {
		int q = who->query("quest/wenguo_brush");

		// 未接任務／已完成：婉拒，不收下（避免吞掉天風筆匣）
		if( q != 1 ) {
			do_chat((: command,
				"say 這筆匣 ... 客官還是自個兒收著罷，墨工一時也用不上。" :));
			return 0;
		}

		// 已配過墨（滿匣已交）：婉拒，提示徑去回報客棧
		if( who->query("quest/wenguo_brush_filled") ) {
			do_chat((: command,
				"say 客官的文房方纔已配齊了﹐這匣子就煩客官好生收著罷。快持那副文房回天風客棧交與掌櫃便是（ask keeper about 文房﹐或 give writing case to keeper）。" :));
			return 0;
		}

		// 進行中、持筆匣配墨：配墨、交付滿匣、記旗標（天風筆匣由 give 指令於回 1 後自行銷除）
		message_vision(
			"墨工接過$N遞來的筆匣﹐揭蓋瞧了瞧那管新筆﹐又自木格上揀下\n"
			"一錠描金的松煙好墨﹐就著匣中的襯綢安頓妥當﹐封好了匣蓋。\n", who);
		// give 指令會於本函回 1 後自行 destruct 天風筆匣﹐故此處 fill_case 只交滿匣、記旗標﹔
		// 為穩妥﹐fill_case 內仍會嘗試銷除手中空匣（present 取到的即將被 give 銷除的同一個）。
		fill_case(who);
		do_chat(({
			(: command, "say 客官是天風客棧掌櫃打發來配墨的罷﹖老筆匠安的這管天風狼毫﹐果然是好筆——配墨﹐自當配咱坊裡最得意的松煙好墨﹐方不辱沒了這副文房。" :),
			(: command, "say 墨工與客官揀的這一錠﹐烏亮生光、清香撲鼻。喏﹐這隻筆墨俱備的文房筆匣﹐方纔已奉到客官手裡了﹐快持回天風客棧交與掌櫃（ask keeper about 文房﹐或 give writing case to keeper）。" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒，不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個墨工用不上﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 哎呀﹗客官好沒道理﹗欺負我一個搗墨的匠人做甚﹖" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
