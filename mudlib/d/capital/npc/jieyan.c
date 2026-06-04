// jieyan.c -- 戒言大師：掛單於京畿運河渡口、結庵誦經的方外高僧。
//             docs 支線「渡口贈玉」的贈物人——以一枚溫養多年的黃玉佩，相贈有心
//             向道、肯為蒼生奔走的少俠。(canon：docs 01-世界觀與劇情/05 L109
//             「戒言大師 @ 京畿渡口 → 給黃玉佩」)
//
// 故事背景：
//   京畿城內漕運渡口邊，那座飄著青布招子的板棚旁，常年結著一座不起眼的草庵。
//   庵中住著一位人稱戒言大師的老僧——早年遍歷江湖、看盡恩怨紛擾，晚來只在這
//   南來北往的渡口邊誦一段平安經，替過客了卻幾分塵心。大師隨身有一枚溫養了
//   數十載的黃玉佩，玉中蘊著他半生戒貪、戒嗔、清靜守一的定力。他不問來客
//   名姓，只看一點本心——若見有人於這滾滾紅塵中尚存一縷向道、利人之念，便
//   肯將那玉佩相贈，盼它護持那人的心神，於江湖風波裡多一分安定。
//
// 支線流程（旗標存玩家身上：quest/sq_jieyan）：
//   未領 (0)  : 玩家 ask jieyan about 玉佩（或 戒言/黃玉佩/定力 …）-> 大師略一
//               打量，見來客肯靜心聽他一段話，便取出那枚溫養多年的黃玉佩相贈，
//               同步交付、即記旗標為 1。
//   已領 (1)  : 不再重複贈玉（防重領）；ask 只給一段勸人清靜守一的純劇情對白。
//   穩健性    : 若旗標已記為 1 但玉佩不在玩家身上（中途遺失/賣掉），補贈一枚、
//               不重置進度（step-flag 在、物不在則重給）。
//
// 同步交付（本專案頭號 bug class 之防範）：贈玉一律在 do_ask handler 內直接
//   new()+move() 給玩家、且在設完成旗標之前——絕不放進延遲的 do_chat/closure
//   (玩家中途離場會「物沒了、旗標卻記完成」soft-lock)。do_chat 只擺氣氛對白。
//
// 注意：本 NPC 有 do_ask，**不** replace_program。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIY "戒言大師" NOR, ({ "jieyan dashi", "jieyan", "dashi", "monk", "戒言大師", "戒言", "大師" }) );
	set("nickname", HIY "戒言大師" NOR);
	set_attr("int", 22);
	set_attr("wis", 28);
	set_attr("con", 20);
	set_race("human");
	set_class("commoner");
	set_level(15);
	set_skill("unarmed", 28);
	set_skill("dodge", 28);
	set_skill("force", 34);
	set_skill("literate", 34);

	set("gender", "male");
	set("age", 68);
	set("long",
		"一位結庵於漕運渡口邊的方外高僧，人稱戒言大師。大師生得清\n"
		"癯矍鑠，眉目慈和，一部花白的長鬚垂至胸前，一襲洗得發灰的\n"
		"舊僧袍，腰間懸著一串溫潤的菩提念珠。他不似那些奔忙的船工\n"
		"與往來的客商，只揀了板棚旁一方蒲團趺坐著，望著渡口邊終年\n"
		"不歇的河水，時而闔目誦持，時而拈鬚微笑。聽渡口的老船工\n"
		"說，這位大師早年遍歷江湖、看盡恩怨紛擾，晚來只在這南來北\n"
		"往的渡口邊誦一段平安經，替過客了卻幾分塵心。他周身透著一\n"
		"股說不出的安定氣息，教人一近前，那滿腔的躁念也莫名地靜了\n"
		"下來。\n"
		"你或許可以問問他：ask jieyan about 玉佩。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"戒言大師捻動著手中念珠，闔目低誦了一段平安經，渡口的喧囂彷彿都遠了。\n",
		"戒言大師望著渡口邊那一河濁黃的流水，悠悠道：水過不留痕，人過不留執，便是清靜。\n",
		"戒言大師拈鬚微笑，向過往的客商頷首：施主一路風塵，且在這渡口邊歇歇心罷。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	if( this_player() && interactive(this_player()) ) {
		if( !this_player()->query("quest/sq_jieyan") )
			do_chat((: command,
				"say 施主面帶風塵、眉宇間一團躁氣 ... 可是讓這江湖的恩怨纏得緊了？不妨與老衲說說話。(ask jieyan about 玉佩)" :));
	}
}

// 同步贈玉：直接 new()+move() 給玩家。先試 move 到玩家身上，
// 不成（負重等）則落在環境地上——絕不靜默丟失。
private void give_pei(object who)
{
	object pei;

	if( !who || environment(who) != environment() ) return;

	pei = new("/d/capital/npc/obj/huang_jade_pei");
	if( !pei->move(who) ) pei->move(environment());

	message_vision(
		"戒言大師自懷中取出一枚溫養多年的黃玉佩，那玉色作熟栗般的暖黃，"
		"在渡口的天光下瑩潤生溫。大師將玉佩鄭重地交到$N手中，合十唱了一聲佛號。\n",
		who);

	who->gain_score("emprise", 120);
	who->gain_score("reputation", 60);
	who->gain_score("explorer fame", 40);
}

int do_ask(string arg)
{
	object me = this_player();
	int q;

	if( !arg || (arg != "jieyan about 玉佩"
		&&   arg != "jieyan about 黃玉佩"
		&&   arg != "jieyan about 戒言"
		&&   arg != "jieyan about 定力"
		&&   arg != "jieyan about 清靜"
		&&   arg != "jieyan dashi about 玉佩"
		&&   arg != "dashi about 玉佩"
		&&   arg != "jieyan about pei"
		&&   arg != "jieyan about jade") )
		return notify_fail("你想問這位大師甚麼？（試試 ask jieyan about 玉佩）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("戒言大師正闔目捻珠誦持著甚麼，沒空理你。\n");

	q = me->query("quest/sq_jieyan");

	// 已領過玉佩：純劇情對白，不重發（防重領）。
	if( q >= 1 ) {
		// 穩健性：旗標在、玉佩卻不在身上（遺失/賣掉）-> 補贈一枚，不重置進度。
		if( !present("huang jade pei", me) ) {
			// 同步補贈：give_pei 直接 new+move（玩家此刻必在場）；do_chat 只留氣氛對白。
			// 不可把 give_pei 塞進 do_chat 陣列——那會延後數心跳異步執行，違同步交付契約。
			give_pei(me);
			do_chat((: command, "say 施主那枚玉佩怎不見了？罷了，老衲這裡尚有一枚，再贈與你便是——這回可要收好，玉護的是心，丟不得。" :));
			return 1;
		}
		do_chat(({
			(: command, "say 施主那枚黃玉佩可還佩在身上？好。玉性溫潤而恆久，最似這守一不移的本心——佩之日久，自能消磨那一身的躁氣。" :),
			(: command, "say 老衲一生只得這『戒言』二字：戒口中之言，更戒心中之念。施主行走江湖，刀光劍影之外，但能守住這一點清靜，便是莫大的造化了。去罷，老衲在這渡口邊，替施主誦一段平安經。" :),
		}));
		return 1;
	}

	// 首次：同步贈玉、即記旗標（give_pei 為直接 new+move，玩家此刻必在場）。
	// 先給物、後記旗標——免於回呼前離場致玉沒領、旗標卻記完成而卡關。
	give_pei(me);
	me->set("quest/sq_jieyan", 1);
	do_chat(({
		(: command, "say 施主肯駐足聽老衲一句閒話，便是與這渡口、與老衲有緣。老衲早年也曾在這江湖裡爭過、嗔過、放不下過，到頭來不過是一場空執。" :),
		(: command, "say 老衲隨身有一枚黃玉佩，是老衲結庵這渡口、誦經守一數十載，以一身戒貪戒嗔的定力日日溫養而成。玉性溫潤，能定人心神。" :),
		(: command, "say 看施主眉宇間雖纏著躁氣，卻尚存一縷向道、利人之念——這玉佩，老衲便贈與施主了。佩之在身，但教那滿腔的躁念靜上幾分；行走江湖，心定則身固，莫教這風波撼動了施主的本心。去罷，珍重。" :),
	}));
	return 1;
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品（尤不收回黃玉佩）。
int accept_object(object who, object ob)
{
	if( ob->id("huang jade pei") ) {
		do_chat((: command,
			"say 施主快收回——這玉佩既已贈出，便是施主的了，老衲怎能再收？佩在身上護心便是。" :));
		return 0;
	}
	do_chat((: command,
		"say 老衲出家人，了無長物，這個受不起，施主還是自個兒留著罷。" :));
	return 0;
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 施主息怒——老衲一個誦經的出家人，與施主無冤無仇，何苦動這刀兵之念。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
