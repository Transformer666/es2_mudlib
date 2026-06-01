// hunter.c -- 老獵戶，常年在老松林裡狩獵的山民，主線任務四「獸亂之兆」的委託人
//
// 故事背景（承接主線三「聖木探封」）：
//   京畿神社守木老者道破封印將潰之實﹐封山派陸抱朴師叔亦埋下伏筆﹕當年斷木
//   放出的悔天鬼爪牙一旦復出﹐連深山裡的走獸都要受其蠱惑而生亂。這伏筆如今
//   應驗了——老松林深處的走獸近來一反常態﹐成群結隊地朝天靈山的方向湧去﹐凶
//   戾異常﹐連這位在松林裡打了大半輩子獵的老獵戶都心驚膽寒。他親手獵殺了一
//   頭發狂的異獸﹐拔下牙來﹐卻看不出個所以然﹐遂託這位循著聖木舊案一路追來
//   的少俠﹐把那枚殘牙帶去京畿神社﹐請識得異兆的守木老者參詳。
//
// 任務流程（旗標存在玩家身上：quest/main_omen4）：
//   入門條件     : 須先完成主線三（quest/main_omen3 >= 3）﹐否則只喃喃自語﹐不開任務
//   未開始 (0)   : 玩家 ask hunter about 獸亂 -> 老獵戶交付「異獸殘牙」﹐旗標設為 1
//   進行中 (1)   : 玩家持異獸殘牙到京畿神社﹐交(give)給守木老者(/d/capital/npc/shrinekeeper)
//                  老者驗牙後收下﹐道出獸亂源自將潰的聖木封印﹐回給「識獸帖」﹐
//                  並把旗標推進為 2（推進在 shrinekeeper.c）
//   已取得 (2)   : 玩家把識獸帖帶回老松林交(give)給老獵戶 -> 領賞(give_reward)﹐旗標設為 3
//   已完成 (3)   : 不再重複給賞﹐do_ask 給出朝向動物war／悔天鬼／混沌珠一段的純劇情伏筆

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老獵戶", ({ "old hunter", "hunter" }) );
	set("nickname", "老獵戶");
	set_attr("str", 20);
	set_attr("con", 18);
	set_race("human");
	set_class("commoner");
	set_level(12);
	set_skill("unarmed", 25);
	set_skill("dodge", 25);
	set_skill("blade", 20);
	set_skill("force", 20);

	set("gender", "male");
	set("age", 54);
	set("long",
		"一位常年在老松林裡討生活的老獵戶﹐身形精瘦結實﹐一張臉教\n"
		"山風與日頭烤得黧黑﹐顴骨上一道舊疤﹐想是早年與野獸搏鬥所\n"
		"留。他身上一件磨得發亮的舊皮襖﹐肩頭斜挎著弓矢﹐腰間別一\n"
		"柄缺了口的獵刀﹐一雙眼睛在松影裡仍利得像鷹。這幾日他卻不\n"
		"似往常那般沉穩﹐每每望向林子深處﹐眉宇間都透著一股說不出\n"
		"的驚惶。你或許可以問問他﹕ask hunter about 獸亂。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老獵戶按著腰間的獵刀﹐警覺地望向松林深處﹐喉間發出一聲低咒。\n",
		"老獵戶喃喃道﹕邪門 ... 真是邪門﹐打了半輩子獵﹐沒見過走獸這般發瘋的 ...\n",
	}));
	setup();
	carry_object("/obj/area/obj/cloth")->wear();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		int q = this_player()->query("quest/main_omen4");
		if( q == 1 || q == 2 )
			do_chat((: command,
				"say 少俠﹐那枚異獸殘牙﹐京畿神社那位老者可看出名堂了麼﹖" :));
		else if( !q && this_player()->query("quest/main_omen3") >= 3 )
			do_chat((: command,
				"say 少俠瞧著面善 ... 這林子近來邪得很﹐你也是覺出不對才來的麼﹖" :));
	}
}

// 把一枚異獸殘牙交到玩家手上（先複製到自己身上，再 give 出去）
private void give_fang(object who)
{
	object fang;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢﹖");
		return;
	}
	fang = new(__DIR__"obj/beast_fang");
	fang->move(this_object());
	command("give beast fang to " + who->query("id"));
}

// 領賞：給一串銅錢、一帖傷藥﹐並授俠義之舉、聲望與旅行見聞
private void give_reward(object who)
{
	object coin, berry;

	if( !who || environment(who) != environment() ) return;

	coin = new("/obj/money/coin");
	coin->set_amount(350);
	if( !coin->move(who) ) coin->move(environment());

	berry = new("/obj/medication/boar_berry");
	if( !berry->move(who) ) berry->move(environment());

	who->gain_score("survive", 350);
	who->gain_score("emprise", 120);
	who->gain_score("reputation", 60);
	who->gain_score("explorer fame", 40);

	message_vision(
		"老獵戶將那紙識獸帖湊到眼前反覆看了幾遍﹐臉色越發凝重﹐末了"
		"自皮襖裡掏出一串攢下的銅錢與幾顆隨身的山豬果﹐一併塞到$N手裡。\n",
		who);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "hunter about 獸亂"
		&&   arg != "hunter about 異獸"
		&&   arg != "hunter about 主線"
		&&   arg != "hunter about 任務"
		&&   arg != "old hunter about 獸亂"
		&&   arg != "old hunter about 異獸"
		&&   arg != "hunter about quest"
		&&   arg != "hunter about task") )
		return notify_fail("你想問這位獵戶甚麼﹖（試試 ask hunter about 獸亂）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老獵戶正警覺地盯著林子深處﹐沒空理你。\n");

	// 入門條件：須先完成主線三「聖木探封」
	if( me->query("quest/main_omen3") < 3 ) {
		do_chat(({
			(: command, "say 少俠面生﹐這林子裡的邪事﹐老朽也說不出個所以然來。" :),
			(: command, "say 你若真想弄明白﹐倒不如先去問問那些追查舊案的明白人——聽說封山派與京畿神社那邊﹐有人專管這等異兆。待你弄清了根底﹐老朽再與你細說林子裡的怪事。" :),
		}));
		return 1;
	}

	q = me->query("quest/main_omen4");

	// 主線四已全部完成：收尾、加深朝向動物war／悔天鬼／混沌珠一段的伏筆（純劇情，不開任務）
	if( q >= 3 ) {
		do_chat(({
			(: command, "say 多虧少俠走這一趟﹐老朽總算明白了——這滿山走獸發狂﹐竟是那聖木封印鬆動鬧的。難怪牠們不要命似地往天靈山那頭奔。" :),
			(: command, "say 那帖子上說﹐天靈山裡有頭叫悔天鬼的邪物﹐還連著一顆甚麼『混沌珠』﹐這些瘋獸都是教那邪念勾了魂去。如今不過是頭幾撥﹐往後只怕更兇。" :),
			(: command, "say 老朽一介山民﹐護得了這片松林﹐護不了天下。少俠是有本事的人﹐這場獸亂的根子既在天靈山﹐來日剿那禍源﹐還望少俠多擔待。老朽就在這林子裡﹐替少俠守著後路。" :),
		}));
		return 1;
	}

	// 已取得識獸帖，回來交付（理應用 give 交付，這裡只作提示）
	if( q == 2 ) {
		if( present("omen note", me) )
			do_chat((: command,
				"say 京畿神社那一趟有著落了罷﹖快把那位老者寫的識獸帖交(give)給老朽瞧瞧﹗" :));
		else
			do_chat((: command,
				"say 咦﹐那紙識獸帖呢﹖少俠莫不是弄丟了﹖快回京畿神社找那守木老者補寫一紙。" :));
		return 1;
	}

	// 任務進行中（已領殘牙，還沒回來）
	if( q == 1 ) {
		if( present("beast fang", me) )
			do_chat((: command,
				"say 那枚殘牙少俠帶在身上了。出松林往北回雪亭鎮南的草棚﹐一路往京畿去﹐"
				"到了帝都﹐自皇城廣場往北便是京畿神社﹐尋著那位守木的老者﹐把牙交(give)給他過目。" :));
		else
			// 萬一玩家把殘牙弄丟了，補一枚給他
			do_chat(({
				"老獵戶搖頭嘆了口氣﹐又自皮囊裡摸出另一枚一般無二的獸牙。\n",
				(: command, "say 怎麼那牙不見了﹖罷了﹐這等瘋獸老朽多殺了幾頭﹐牙還有的是﹐少俠這回可收好了。" :),
				(: give_fang, me :),
			}));
		return 1;
	}

	// 尚未接任務：交付異獸殘牙，旗標設為 1
	me->set("quest/main_omen4", 1);
	do_chat(({
		(: command, "say 少俠既是明白人﹐老朽便不瞞你。這老松林老朽打了快四十年獵﹐林裡的脾性沒有不曉得的﹐可這些日子﹐怪了——" :),
		(: command, "say 深山裡的走獸像是中了邪﹐白猴、野豬、乃至那些素來避人的猛獸﹐一隻隻紅了眼﹐成群結隊地往北邊天靈山那個方向奔﹐見人見獸都咬﹐凶得不像活物。" :),
		(: command, "say 前日老朽撞上一頭發狂的﹐拚著命才把牠放倒﹐拔下這枚牙來——你瞧﹐牙上這股青黑的戾氣﹐邪門得很﹐尋常山獸哪有這個。" :),
		(: command, "say 老朽看不透這異兆。聽聞京畿神社有位守木的老者﹐專識這等怪事。少俠可願把這枚牙帶去交(give)給他過目﹐問問這滿山的瘋獸﹐究竟是教甚麼東西勾了魂去﹖" :),
		(: give_fang, me :),
	}));
	return 1;
}

// 收下信物：
//   識獸帖(omen note) -- 主線四「獸亂之兆」交還﹐旗標 main_omen4 2 -> 3﹐領賞(give_reward)
// 收下後不自行 destruct﹐由 give 指令將信物移入本 NPC（與 archivist／shrinekeeper 一致）﹐
// 並於最終旗標處作防重複領獎。
int accept_object(object who, object ob)
{
	// 主線四：交還識獸帖
	if( ob->id("omen note") ) {
		// 已領過賞（旗標已 >=3）：道謝收下﹐不重複給賞
		if( who->query("quest/main_omen4") >= 3 ) {
			do_chat((: command, "say 那紙帖子老朽早已收訖﹐多謝少俠跑這一趟了﹗" :));
			return 1;
		}
		// 尚未進行到交付這一步（旗標不為 2）：仍收下避免卡物﹐但不推進、不給賞
		if( who->query("quest/main_omen4") != 2 ) {
			do_chat((: command, "say 多謝少俠﹗" :));
			return 1;
		}

		// 同步給賞、即記旗標（give_reward 為直接 new+move﹐玩家此刻必在場）。
		// 不把給賞放進延遲的 do_chat——免玩家於回呼前離場致賞沒領、旗標卻記完成而卡關。
		give_reward(who);
		who->set("quest/main_omen4", 3);
		do_chat(({
			(: command, "say 守木老者的識獸帖 ... 老朽識字不多﹐可這上頭的話﹐看得老朽脊梁骨發涼。" :),
			(: command, "say 這點銅錢與山豬果﹐少俠帶在身上﹐防身充飢。少俠肯為這滿山的生靈奔走﹐老朽這把老骨頭﹐承你的情了﹗" :),
		}));
		return 1;
	}

	// 其餘物事：婉拒﹐不收下（避免吞掉玩家的尋常物品）
	do_chat((: command, "say 這個老朽用不上﹐少俠還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say 少俠這是做甚﹖老朽一個打獵的山民﹐與你無冤無仇哪。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
