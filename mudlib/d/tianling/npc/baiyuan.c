// baiyuan.c -- 千年白猿：盤桓於天靈山、通體雪白而通靈的千年老猿。
//             docs 支線「白猿贈書」的贈物人——將其亙古守護的一卷失傳奇書（無名古籍）
//             奉與登山而來、心志清正的少俠。
//             (canon：docs 01-世界觀與劇情/05 L123「千年白猿 @ 天靈山 → 無名古籍」)
//
// 故事背景：
//   天靈山麓那道虯松亂石的坡道間，盤桓著一頭通體雪白、目透精光的千年白猿。這白猿
//   守山日久，已通了幾分靈性；它得了山中一卷不知何人所遺、亦無書名的奇書，便將之
//   亙古守護，不教湮沒於荒山。白猿不通人言，卻識得人心——它見少俠登山而來、心志清
//   正，便將這卷『無名古籍』奉與少俠，盼這失傳的武學得以傳續。
//
// 支線流程（旗標存玩家身上：quest/sq_baiyuan）：
//   未領 (0)  : 玩家 ask baiyuan about 書（或 古籍/無名古籍/秘笈/baiyuan about book …）
//               -> 白猿一句 ask 即將「無名古籍」同步交付、即記旗標為 1
//               （UNGATED 單問即贈：任何 docs 條件只作對白風味，wizard 一步可測）。
//   已領 (1)  : 不再重複贈書（防重領）；ask 只給一段純風味互動。
//   穩健性    : 若旗標已記為 1 但古籍不在玩家身上（中途遺失/賣掉），同步補贈一卷、
//               不重置進度（step-flag 在、物不在則重給）。
//
// 同步交付（本專案頭號 bug class 之防範）：贈書一律在 do_ask handler 內直接 new()+move()
//   給玩家、且在設完成旗標之前——絕不放進延遲的 do_chat/closure（玩家中途離場會「物沒了、
//   旗標卻記完成」soft-lock）。do_chat 只擺氣氛對白。
//
// 注意：本 NPC 有 do_ask，**不** replace_program。is_chatting/is_fighting guard 於 do_ask。
// 白猿不通人言，「say」對白以動作神態（拊掌、長嘯、以爪畫地）代之，仍走 do_chat 擺氣氛。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIW "千年白猿" NOR,
		({ "baiyuan", "white ape", "ape", "千年白猿", "白猿" }) );
	set("nickname", HIW "千年白猿" NOR);
	set_attr("int", 24);
	set_attr("wis", 26);
	set_attr("dex", 30);
	set_attr("con", 24);
	// 慣例：本 mudlib 之走獸(wildape/windlion/madwolf …)一律 set_race("human")
	//   set_class("commoner")——daemon/race 未註冊 "animal" 一族，沿用之免載入失敗。
	set_race("human");
	set_class("commoner");
	set_level(22);
	set_skill("unarmed", 45);
	set_skill("dodge", 45);
	set_skill("force", 40);
	set_skill("literate", 30);

	set("gender", "male");
	set("age", 1000);
	set("long",
		"一頭通體雪白、軀幹卻甚是雄健的千年老猿，蹲踞在這天靈山麓的\n"
		"虯松亂石之間。牠周身的長毛雪也似的白，根根透著一層柔和的銀\n"
		"光，一雙眼眸卻黑得發亮、精光內蘊，望之竟不似尋常山猿那般野\n"
		"性，反倒有幾分人立的靈慧與沉靜。聽天靈山的老輩說，這白猿守\n"
		"山已逾千年，早已通了靈性，識得人心善惡；牠不傷登山的善類，\n"
		"反似在這荒山間守護著甚麼。牠靜靜地蹲在那裡，黑亮的眼眸打量\n"
		"著你，懷中似護著一卷甚麼焦黃殘破的書冊。\n"
		"你或許可以問問牠：ask baiyuan about 書。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"千年白猿蹲踞松間，黑亮的眼眸靜靜望著你，似在掂量你的來意。\n",
		"千年白猿仰首向著雲遮霧繞的天靈山巔，發出一聲悠長清越的長嘯，山谷迴盪。\n",
		"千年白猿以爪在地上輕輕劃出幾道古拙的紋路，又抬眼看你，似有所示。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !this_player()->query("quest/sq_baiyuan") )
			do_chat((: command,
				"say 千年白猿黑亮的眼眸在你身上打量了半晌，竟拍了拍懷中那卷焦黃的書冊，似在向你示意甚麼。(ask baiyuan about 書)" :));
	}
}

// 同步贈書：直接 new()+move() 給玩家。先試 move 到玩家身上，
// 不成（負重等）則落在環境地上——絕不靜默丟失。
private void give_manual(object who)
{
	object ob;

	if( !who || environment(who) != environment() ) return;

	ob = new("/d/tianling/npc/obj/wuming_manual");
	if( !ob->move(who) ) ob->move(environment());

	message_vision(
		HIW "千年白猿自懷中捧出一卷焦黃殘破的奇書，黑亮的眼眸中精光一閃，"
		"竟極珍重地將那卷書奉到$N手中，而後退開一步，深深俯下身去。\n" NOR,
		who);

	who->gain_score("emprise", 160);
	who->gain_score("reputation", 80);
	who->gain_score("explorer fame", 60);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "baiyuan about 書"
		&&   arg != "baiyuan about 書冊"
		&&   arg != "baiyuan about 古籍"
		&&   arg != "baiyuan about 無名古籍"
		&&   arg != "baiyuan about 秘笈"
		&&   arg != "white ape about 書"
		&&   arg != "ape about 書"
		&&   arg != "baiyuan about book"
		&&   arg != "baiyuan about manual"
		&&   arg != "white ape about book") )
		return notify_fail("你想問這頭白猿甚麼？（試試 ask baiyuan about 書）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("千年白猿正仰首向著山巔長嘯，恍若未聞，沒空理你。\n");

	q = me->query("quest/sq_baiyuan");

	// 已領過古籍：純風味互動，不重發（防重領）。
	if( q >= 1 ) {
		// 穩健性：旗標在、古籍卻不在身上（遺失/賣掉）-> 補贈一卷，不重置進度。
		if( !present("wuming manual", me) ) {
			// 同步補贈：give_manual 直接 new+move（玩家此刻必在場）；do_chat 只留氣氛對白。
			// 不可把 give_manual 塞進 do_chat 陣列——那會延後數心跳異步執行，違同步交付契約。
			give_manual(me);
			do_chat((: command, "say 千年白猿歪了歪頭，似覺你那卷書怎不見了，便又自懷中取出一卷，重新奉與你，黑眸中隱隱有些催促之意——這回可要收好。" :));
			return 1;
		}
		do_chat(({
			(: command, "say 千年白猿瞧了瞧你身上那卷焦黃的古籍，黑亮的眼眸中掠過一絲安慰之色，拍了拍胸口，似在叮囑你好生研讀。" :),
			(: command, "say 千年白猿仰首向著天靈山巔發出一聲悠長的清嘯，而後蹲回松間，靜靜目送著你——那守護千年的奇書，總算是託付了出去。" :),
		}));
		return 1;
	}

	// 首次：同步贈書、即記旗標（give_manual 為直接 new+move，玩家此刻必在場）。
	// 先給物、後記旗標——免於回呼前離場致書沒領、旗標卻記完成而卡關。
	give_manual(me);
	me->set("quest/sq_baiyuan", 1);
	do_chat(({
		(: command, "say 千年白猿黑亮的眼眸定定地望了你良久，似已認定你是個心志清正、堪託此書的善類。" :),
		(: command, "say 千年白猿自懷中極珍重地捧出那卷焦黃殘破的奇書——這是牠在這荒山間亙古守護、不知何人所遺的失傳武學。牠以爪輕輕拂過書頁，又看了看你，似在叮囑這書中的學問艱深、莫要荒廢。" :),
		(: command, "say 千年白猿將那卷無名古籍奉到你手中，退開一步深深俯身，而後仰首長嘯一聲——這守護千年的奇書，總算尋得了傳人。你可用 study 研讀其上失傳的武學。" :),
	}));
	return 1;
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品（尤不收回無名古籍）。
int accept_object(object who, object ob)
{
	if( ob->id("wuming manual") ) {
		do_chat((: command,
			"say 千年白猿擺了擺爪，將你遞來的古籍輕輕推回——這書既已奉你，便是你的了，牠斷不肯再收。" :));
		return 0;
	}
	do_chat((: command,
		"say 千年白猿歪頭瞧了瞧你遞來的物事，卻不肯接，只搖了搖頭。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 千年白猿往後退了一步，黑亮的眼眸中閃過一絲詫異與不解——牠並無傷你之意，何苦動手？" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
