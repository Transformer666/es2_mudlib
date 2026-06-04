// hunter.c -- 赤魈森林的老獵人(uid: hunter)。
//
// 設定（承接 canon：docs 05 L106「獵人@赤魈森林 給 necklace」）：
//   赤魈森林深處那位披著獸皮、以打獵為生的老獵人，在這四鬼出沒的凶險山林裡討了半
//   輩子生活，是這森林裡唯一的活人。他自村中老輩處得了一串避邪的獸牙項鍊(npc/obj/
//   hunter_necklace.c)；見少俠是奔著卯天樹下四鬼封印而來，便將這串護身的項鍊相贈，
//   盼少俠多一分護持、平安了結那四鬼之患，並道出四鬼將動的警示。
//
// 用法（純氣氛/輔助 NPC，「不」作主線旗標把關）：
//   * ask 獵人 about 四鬼／森林／項鍊 —— 道四鬼將動的警示氣氛，並（一次）相贈獸牙
//     項鍊。防重複贈與：玩家身上已有項鍊(present "necklace")者，不再贈。
//   * 此項鍊乃可選的避邪/護身輔助，非開封/通行的門檻——封印之開仍須招喚環 + 第五章
//     旗標(見 d/skysnow/tree.c::do_use)。
//   同步贈與（new+move/give，非延遲 do_chat——承同步交付之教訓）。

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

// 同步贈「獸牙項鍊」。who=玩家。防重複贈與。
private void give_necklace(object who)
{
	object necklace;

	if( !who || environment(who) != environment() ) {
		command("say 咦 ... 人呢？");
		return;
	}
	if( present("necklace", who) ) return;   // 已有者不再贈（雙重保險）。
	necklace = new("/d/chimei/npc/obj/hunter_necklace");
	necklace->move(this_object());
	command("give fang necklace to " + who->query("id"));
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
	||  arg == "old hunter about 四鬼" ) {
		// 已贈過項鍊（玩家身上已有）：只道警示，不再重贈。
		if( present("necklace", me) ) {
			do_chat(({
				(: command, "say 那串獸牙項鍊，少俠既已收下，便好生戴在身上罷——這林子最深處的卯天樹下，鎮著四頭長生不滅的元神之鬼，那陰邪戾氣，可不是頑笑的。" :),
				(: command, "say 山鬼赤魈、林鬼青蛛、川鬼濁魚、原鬼旱魃，三百年的鎮鬼之封一鬆，這四鬼便要應劫而出。少俠此去兇險萬分，務必小心。" :),
			}));
			return 1;
		}
		// 一次相贈獸牙項鍊。
		do_chat(({
			(: command, "say （老獵人上下打量了少俠半晌，緩緩起身）少俠是奔著林子最深處那卯天樹下的封印去的罷？這些日子，自京畿那邊起了變故，林子深處那沉睡了三百年的東西，便一日比一日躁動了。" :),
			(: command, "say 山鬼赤魈、林鬼青蛛、川鬼濁魚、原鬼旱魃——山海經所載的山林川原四鬼，皆是長生不滅的元神之鬼，三百年來教那卯天樹下的封印鎮著。如今封印一鬆，那陰邪戾氣，連我這獵了半輩子的老骨頭都覺著心驚。" :),
			(: command, "say （老獵人自頸間解下一串獸牙項鍊，鄭重遞來）這串獸牙項鍊，是村中老輩傳下的避邪之物，以山裡最兇悍野獸的獠牙串成，戴在身上，能教那四鬼的陰邪戾氣不敢近身。少俠拿去護身罷——盼你多一分護持，平安了結那四鬼之患。" :),
			(: give_necklace, me :),
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
