// songanjiang.c -- 漕幫禮堂的分舵主「宋安江」。
//
// 【設定 / canon】依 ES2 設定（docs 01-世界觀與劇情/05-主線任務與NPC.md L113
//   「宋安江 @ 吏部尚書府漕幫禮堂分舵主 → 給旋芒」）：宋安江是漕幫禮堂的分舵
//   主﹐掌京畿一處幫務﹐爽利仗義。canon 中他會將漕幫壓箱底那柄信物兵刃「旋芒」
//   (d/caobang/npc/obj/xuanmang_sword)相贈有緣的少俠。
//
// 【贈物支線（item-giver，鏡 d/capital/npc/jieyan.c）】（旗標存玩家身上：
//   quest/sq_songanjiang）：
//   未領 (0)  : 玩家 ask songanjiang about 旋芒（或 武學/信物/兵刃 …）-> 宋安江爽利
//               一笑﹐取出那柄旋芒相贈﹐同步交付、即記旗標為 1。ungated——不設任何
//               前置門檻。
//   已領 (1)  : 不再重複贈劍（防重領）；ask 只給一段漕幫家風的純劇情對白。
//   穩健性    : 若旗標已記為 1 但旋芒不在玩家身上（中途遺失/賣掉），補贈一柄、
//               不重置進度（step-flag 在、物不在則重給）。
//
// 同步交付（本專案頭號 bug class 之防範，承 jieyan.c 教訓）：贈劍一律在 do_ask
//   handler 內直接 new()+move() 給玩家、且在設完成旗標之前——絕不放進延遲的
//   do_chat/closure（玩家中途離場會「物沒了、旗標卻記完成」soft-lock）。do_chat
//   只擺氣氛對白。
//
// 注意：本 NPC 有 do_ask，**不** replace_program（#11）；die()/destruct 不在此檔。

#include <npc.h>
#include <ansi.h>

int do_ask(string arg);
private void give_xuanmang(object who);

void create()
{
	set_name("宋安江", ({ "songanjiang", "deputy songanjiang", "song anjiang" }) );
	set("nickname", "宋安江");
	set_race("human");
	set_class("commoner");
	set_level(18);

	set("age", 41);
	set("gender", "male");
	set("long",
		"這位是漕幫禮堂的分舵主宋安江﹐掌著京畿這一處的幫務。他\n"
		"生得方面闊口﹐三綹墨髯﹐穿一身利落的玄色勁裝﹐腰束革帶﹐行\n"
		"止間自有一股當家理事的精悍幹練。漕幫號稱數十萬眾﹐能在天子\n"
		"腳下替漕幫坐鎮一方分舵的﹐自非泛泛之輩。他待人爽利仗義﹐一\n"
		"雙眼睛卻精光內斂﹐顯是個外圓內方、心裡極有成算的人物。\n"
		"你或許可以問問他：ask songanjiang about 旋芒。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"宋安江立在烏木長案後﹐執筆在一函漕運帳冊上勾畫﹐神色專注。\n",
		"宋安江抱拳和進出禮堂的幫眾一一招呼﹐三言兩語便把幾樁幫務分派停當。\n",
		"宋安江抬眼瞧了瞧「漕」字大旗﹐又朝江隕那頭恭敬地一拱手﹐方低頭理事。\n",
	}));
	setup();
	carry_money("silver", 8);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 同步贈劍：直接 new()+move() 給玩家。先試 move 到玩家身上，
// 不成（負重等）則落在環境地上——絕不靜默丟失。鏡 jieyan.c::give_pei。
private void give_xuanmang(object who)
{
	object sword;

	if( !who || environment(who) != environment() ) return;

	sword = new("/d/caobang/npc/obj/xuanmang_sword");
	if( !objectp(sword) ) return;
	if( !sword->move(who) ) sword->move(environment());

	message_vision(
		HIC "宋安江爽利地一笑﹐自案後抽出一柄水波似的青芒長劍﹐雙手橫遞﹐"
		"鄭重地交到$N手中——這柄旋芒﹐是漕幫壓箱底那門水上工夫的信物。\n" NOR,
		who);

	who->gain_score("emprise", 120);
	who->gain_score("reputation", 60);
	who->gain_score("martial fame", 80);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg )
		return notify_fail("你想向這位分舵主打聽甚麼﹖（試試 ask songanjiang about 漕幫／旋芒）\n");

	// 漕幫 / 入幫：宋安江介紹漕幫幫風、引玩家去尋江隕（純氣氛，無旗標）
	if( arg == "songanjiang about 漕幫"
	||  arg == "songanjiang about 禮堂"
	||  arg == "songanjiang about 入幫"
	||  arg == "songanjiang about 加入"
	||  arg == "songanjiang about caobang"
	||  arg == "deputy songanjiang about 漕幫" ) {
		if( is_fighting() || is_chatting() )
			return notify_fail("宋安江正分派著幫務﹐一時無暇答話。\n");
		do_chat(({
			(: command, "say 客官光臨敝幫禮堂﹐失敬。在下宋安江﹐忝為這禮堂的分舵主﹐京畿一處的幫務﹐都歸在下打理。客官面生﹐想必是頭一回到咱漕幫罷？" :),
			(: command, "say 咱漕幫執掌天下漕運﹐幫眾數十萬﹐沿大運河南北分舵林立﹐勢力不可謂不大。可咱這幫子有條老規矩﹕從不與江湖中人結仇怨。跑船的求的是四海通達、和氣生財﹐這份『不結仇』的家風﹐百十年來未曾變過。" :),
			(: command, "say 客官若是有心在漕幫討個出身﹐這是好事﹐在下歡迎得很。禮堂裡那位老前輩江隕江爺﹐輩分最高﹐客官得空﹐不妨去拜會江爺（ask jiangyun about 漕幫），聽聽他老人家的意思。" :),
		}));
		return 1;
	}

	// 旋芒：item-giver——同步贈劍、防重領、遺失補贈（ungated，鏡 jieyan.c）
	if( arg == "songanjiang about 旋芒"
	||  arg == "songanjiang about 武學"
	||  arg == "songanjiang about 武功"
	||  arg == "songanjiang about 絕學"
	||  arg == "songanjiang about 信物"
	||  arg == "songanjiang about 兵刃"
	||  arg == "songanjiang about 劍"
	||  arg == "songanjiang about xuanmang"
	||  arg == "deputy songanjiang about 旋芒" ) {

		if( is_fighting() || is_chatting() )
			return notify_fail("宋安江正分派著幫務﹐一時無暇答話。\n");

		q = me->query("quest/sq_songanjiang");

		// 已領過旋芒：純劇情對白，不重發（防重領）。
		if( q >= 1 ) {
			// 穩健性：旗標在、旋芒卻不在身上（遺失/賣掉）-> 補贈一柄，不重置進度。
			// 同步補贈：give_xuanmang 直接 new+move（玩家此刻必在場）；do_chat 只留氣氛。
			if( !present("xuanmang", me) ) {
				give_xuanmang(me);
				do_chat((: command, "say 客官那柄旋芒怎不見了？跑船人最忌的便是『失了趁手的傢伙』。罷了﹐在下這裡尚有一柄﹐再贈與客官便是——這回可要收好。" :));
				return 1;
			}
			do_chat(({
				(: command, "say 客官那柄旋芒可還趁手？這劍勢脫胎自咱跑船人撐篙、收纜、破浪的勁路﹐使熟了﹐腕底自有一片旋光護身﹐最是綿密難當。" :),
				(: command, "say 客官帶著這柄旋芒﹐便算是和咱漕幫結了一分善緣。記著咱漕幫那條老規矩——不與江湖中人結仇怨。客官行走江湖﹐多結善緣、少惹是非﹐方是長久之道。去罷。" :),
			}));
			return 1;
		}

		// 首次：同步贈劍、即記旗標（give_xuanmang 為直接 new+move，玩家此刻必在場）。
		// 先給物、後記旗標——免於回呼前離場致劍沒領、旗標卻記完成而卡關。
		give_xuanmang(me);
		me->set("quest/sq_songanjiang", 1);
		do_chat(({
			(: command, "say 客官也聽過咱漕幫的『旋芒』？（宋安江眼中精光一閃﹐隨即爽利地笑了笑）那是咱漕幫壓箱底的一門功夫﹐脫胎自跑船的撐篙、收纜、破浪的勁路﹐使將開來如水上旋芒﹐端的不凡。" :),
			(: command, "say 在下看客官面生﹐卻是個有膽識、有來歷的人物﹐與咱漕幫也算投緣。這門功夫所附的信物兵刃﹐在下這裡正有一柄——既是緣分﹐便贈與客官了。" :),
			(: command, "say 客官好生使著。這劍勢綿密如水上旋光﹐護身最是穩當。只記著咱漕幫那條老規矩——不與江湖中人結仇怨﹔客官持咱漕幫的信物﹐行事也多留三分餘地﹐和氣生財﹐方不墮了這旋芒的名頭。去罷。" :),
		}));
		return 1;
	}

	return notify_fail("宋安江拱手一笑﹕客官若是來見識見識咱漕幫的氣派﹐只管隨意﹔旁的﹐恕在下一時也說不周全。（試試 ask songanjiang about 漕幫／旋芒）\n");
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品（尤不收回旋芒）。
int accept_object(object who, object ob)
{
	if( ob->id("xuanmang") ) {
		do_chat((: command,
			"say 客官快收回——這旋芒既已贈出﹐便是客官的了﹐在下怎能再收？帶在身上趁手便是。" :));
		return 0;
	}
	do_chat((: command,
		"say 在下一個分舵主﹐受不起客官的東西﹐客官還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command, "say （宋安江不慌不忙地一拱手）客官說笑了。這是漕幫議事的禮堂﹐又有江爺在座﹐動手是萬萬使不得的。客官有甚麼話﹐好好說便是。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
