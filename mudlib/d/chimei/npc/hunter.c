// hunter.c -- 赤魈森林的老獵人(uid: hunter)，docs 支線 item-giver。
//
// 設定（承接 canon：docs 05 L106「獵人@赤魈森林 給 necklace」）：
//   赤魈森林深處那位披著獸皮、以打獵為生的老獵人，在這四鬼出沒的凶險山林裡討了半
//   輩子生活，是這森林裡唯一的活人。他自村中老輩處得了一串避邪的獸牙項鍊(npc/obj/
//   hunter_necklace.c)；見少俠是奔著卯天樹下四鬼封印而來，便將這串護身的項鍊相贈，
//   盼少俠多一分護持、平安了結那四鬼之患，並道出四鬼將動的警示。
//
// 給法（同步交付，承本專案頭號 bug class「同步交付」之教訓 — 鏡 d/capital/npc/
//   atuo.c / d/capital/npc/jieyan.c 之 give_X：直接 new()+if(!move(who))move(env)，
//   並於設旗標『之前』同步呼叫；絕「不」把 give 放進延遲的 do_chat closure(玩家
//   中途離場會 soft-lock，物沒了旗標卻記完成)；do_chat 只擺氣氛對白）：
//   * 防重領：以逐玩家旗標 quest/sq_hunter 為閘（已領者只給警示氣氛、不重發），
//     give_necklace 內另以 present("necklace", who) 作第二道防重給保險。
//   * 防遺失補發：若旗標已設、然項鍊已不在身(present 查無)，則同步補贈一串——
//     便於「領了又弄丟/賣掉」的玩家(及測試)再取一次，補發路徑亦同步、不延入 closure。
//   * 閘門可測性：UNGATED single-ask——任何玩家(含 wizard)ask 一次即得項鍊，
//     無硬性前置(書換/規費皆無)，便於驗收。此項鍊乃可選的避邪/護身輔助，非開封/
//     通行的門檻——封印之開仍須招喚環 + 第五章旗標(見 d/skysnow/tree.c::do_use)。
//
// ⚠ 本 NPC 自訂 do_ask(add_action)，依 lesson『有自訂 add_action 之 NPC 斷不可
//   replace_program』— 本檔故「不」replace_program。
//   do_ask 內以 is_fighting()/is_chatting() 守衛(#11)；旗標寫在同步給物『之後』(#10)。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

int do_ask(string arg);
private void give_necklace(object who);

void create()
{
	set_name("獵人", ({ "hunter", "old hunter", "lieren" }) );
	set("nickname", "老獵人");
	set_race("human");
	set_class("commoner");
	set_level(12);

	set("age", 58);
	set("gender", "male");
	set("long",
		"一名披著獸皮、以打獵為生的老獵人。他身形精瘦結實，皮膚是\n"
		"常年風霜熬出的黧黑，臉上一道舊疤自額角斜貫到頷下——想是當年\n"
		"與山中猛獸搏命留下的。他蹲在背風岩窟前將熄的篝火旁，一桿磨得\n"
		"發亮的舊獵叉斜倚在身畔，一雙眼睛卻警覺得很，時不時警惕地往林\n"
		"子最深處望去。這老獵人在這四鬼出沒的凶險山林裡討了半輩子生\n"
		"活，是這赤魈森林裡唯一的活人，山裡的門道，再沒人比他更清楚了。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老獵人往篝火裡添了根枯枝，火光一跳，映出他滿臉風霜的皺紋。\n",
		"老獵人警惕地往林子最深處望了一眼，壓低聲音道：這些日子，林子不太平。\n",
		"老獵人摩挲著那桿磨得發亮的舊獵叉，眼神悠遠，似在掂量著甚麼凶險。\n",
	}));
	setup();
	carry_money("coin", 30);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

// 同步贈「獸牙項鍊」。who=玩家。直接 new()+move(who)；move 失敗才落地
// （鏡 atuo.c/jieyan.c——絕不靜默丟失，亦不用 `if(move)`成功時反落地）。
// 第二道防重給：玩家身上已有則不再贈。
private void give_necklace(object who)
{
	object necklace;

	if( !who || environment(who) != environment() )
		return;
	if( present("necklace", who) )
		return;   // 已有者不再贈（雙重保險）。

	necklace = new(__DIR__"obj/hunter_necklace");
	if( !necklace->move(who) )
		necklace->move(environment());

	message_vision(
		"老獵人自頸間解下一串以野獸獠牙串成的避邪項鍊，在掌心抖了抖塵土，"
		"鄭重地遞到$N手中。\n", who);

	who->gain_score("emprise", 80);
	who->gain_score("reputation", 40);
	who->gain_score("explorer fame", 30);
}

int do_ask(string arg)
{
	object me = this_player();

	if( !me ) return 0;

	if( !arg )
		return notify_fail(
			"你想問這位老獵人甚麼？（試試 ask 獵人 about 四鬼／森林／項鍊）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老獵人正自警惕地望著林深處，無暇理你。\n");

	// 四鬼／森林／項鍊 —— 道警示氣氛，並（一次）相贈獸牙項鍊。
	if( arg == "hunter about 四鬼"
	||  arg == "獵人 about 四鬼"
	||  arg == "hunter about 森林"
	||  arg == "獵人 about 森林"
	||  arg == "hunter about 項鍊"
	||  arg == "獵人 about 項鍊"
	||  arg == "hunter about 卯天樹"
	||  arg == "獵人 about 卯天樹"
	||  arg == "hunter about necklace"
	||  arg == "hunter about forest"
	||  arg == "old hunter about 四鬼"
	||  arg == "lieren about 四鬼" ) {

		// 已領過（旗標已設）：若項鍊已不在身(弄丟/賣掉)，同步補贈一串；
		// 否則只道警示氣氛、不重發（防重領）。
		if( me->query("quest/sq_hunter") >= 1 ) {
			if( !present("necklace", me) ) {
				give_necklace(me);
				do_chat(({
					(: command, "say 咦？前番贈你的那串獸牙項鍊，怎不見了？這四鬼出沒之地，避邪的物事可丟不得。" :),
					(: command, "say 罷了，老朽頸上還有一串，再與你一串便是——這回可要好生戴牢嘍。" :),
				}));
				return 1;
			}
			do_chat(({
				(: command, "say 那串獸牙項鍊，少俠既已收下，便好生戴在身上罷——這林子最深處的卯天樹下，鎮著四頭長生不滅的元神之鬼，那陰邪戾氣，可不是頑笑的。" :),
				(: command, "say 山鬼赤魈、林鬼青蛛、川鬼濁魚、原鬼旱魃，三百年的鎮鬼之封一鬆，這四鬼便要應劫而出。少俠此去兇險萬分，務必小心。" :),
			}));
			return 1;
		}

		// 首次：先同步贈項鍊（give_necklace 為直接 new+move，玩家此刻必在場），
		// 後設旗標——免於回呼前離場致物沒領、旗標卻記完成而卡關(#10)。
		give_necklace(me);
		me->set("quest/sq_hunter", 1);
		do_chat(({
			(: command, "say （老獵人上下打量了少俠半晌，緩緩起身）少俠是奔著林子最深處那卯天樹下的封印去的罷？這些日子，自京畿那邊起了變故，林子深處那沉睡了三百年的東西，便一日比一日躁動了。" :),
			(: command, "say 山鬼赤魈、林鬼青蛛、川鬼濁魚、原鬼旱魃——山海經所載的山林川原四鬼，皆是長生不滅的元神之鬼，三百年來教那卯天樹下的封印鎮著。如今封印一鬆，那陰邪戾氣，連我這獵了半輩子的老骨頭都覺著心驚。" :),
			(: command, "say 那串獸牙項鍊，是村中老輩傳下的避邪之物，以山裡最兇悍野獸的獠牙串成，戴在身上，能教那四鬼的陰邪戾氣不敢近身。少俠拿去護身罷——盼你多一分護持，平安了結那四鬼之患。" :),
		}));
		return 1;
	}

	return notify_fail("老獵人摩挲著那桿舊獵叉，並不答你這一句。\n");
}

// 純氣氛/輔助 NPC：自衛反擊（老獵人在山林裡討生活，亦非全無自保之力）。
int accept_fight(object ob)
{
	do_chat((: command, "say （老獵人霍地抄起身畔那桿舊獵叉，警惕地後退半步）少俠這是作甚？這山裡的凶險還不夠，何苦自家人動起手來！" :));
	return 1;
}

// vim: set ts=4 sw=4 syntax=lpc
