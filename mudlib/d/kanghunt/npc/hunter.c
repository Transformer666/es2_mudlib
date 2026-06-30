// hunter.c -- 老獵戶，盤桓康平塘畔豁口的逮鼠攆狗老把式（純氣氛 / lore NPC）。
//
// init() 招呼一律加 interactive(this_player()) 護衛（lesson #14），只招呼真人﹐
// 免 NPC 互觸洗版。ask hunter about <topic> 講塘畔的鳥獸風物、勸生客留神田鼠野狗。
// 無任務、無給物。
//
// 不可殺：純氣氛 lore NPC。真正擋住攻擊的是 set("no_fight",1)——cmds/std/kill.c:38
// 與 cmds/std/fight.c:25 都先查 obj->query("no_fight")﹐為真即回「不行。」。
// 切記 accept_fight() 回 0 【擋不住 kill】：kill.c 全程不查 accept_fight﹔fight.c
// 也只在 NPC 帶 civilized 旗標時才查 accept_fight﹐無旗標的 fight 直接真打。故另設
// civilized 旗標﹐使 fight 時走 accept_fight 婉拒分支（出本 NPC 的入戲對白）作配套。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("老獵戶", ({ "hunter", "old hunter", "laoliehu" }) );
	set("nickname", "老獵戶");
	set_attr("con", 24);
	set_attr("str", 22);
	set_race("human");
	set_class("commoner");
	set_level(14);

	set_skill("unarmed", 26);
	set_skill("dodge", 22);
	set_skill("parry", 20);

	set("age", 58);
	set("gender", "male");
	// 純氣氛 lore NPC，不可殺：no_fight 擋住 kill 與 fight（kill.c:38 / fight.c:25）﹔
	// civilized 使 fight 時走 accept_fight 婉拒分支（出入戲對白）。兩者皆 NPC-local﹐
	// 不動房間 no_fight﹐不影響同房其他可獵的野物。
	set("no_fight", 1);
	set("civilized", 1);
	set("long",
		"一位上了年紀的老獵戶﹐生得精瘦結實﹐裹著件硝得發硬的舊皮褂﹐\n"
		"背後斜插著一柄磨得發亮的獵叉﹐腰間掛著幾張新剝的鼠皮。他在這\n"
		"塘畔逮鼠攆狗了大半輩子﹐塘窪裡哪處有鼠洞、哪叢葦子裡藏著惡狗﹐\n"
		"沒有他不熟的。他眯眼望著荒塘﹐看著最是和氣健談﹐你可以問問他﹕\n"
		"ask hunter about 獵場。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老獵戶把獵叉往地上一頓﹐眯眼望著塘窪﹐喃喃道﹕這荒塘的田鼠﹐今年又見多了。\n",
		"老獵戶撥弄著腰間幾張新剝的鼠皮﹐自顧自地數著﹐臉上掛著淡淡的笑。\n",
		"老獵戶側耳聽了聽葦叢裡的窸窣聲﹐低聲道﹕又是那群野狗﹐留神著些。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	// 招呼只對真人﹐加 interactive 護衛免 NPC 互觸洗版（lesson #14）。
	if( this_player() && interactive(this_player()) && !is_fighting() )
		do_chat((: command,
			"say 客官也是來這荒塘練手的﹖留神塘邊的田鼠野狗﹐莫教牠們圍上了。" :));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這老獵戶甚麼﹖（試試 ask hunter about 獵場）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老獵戶正盯著葦叢裡的動靜﹐一時沒理會你。\n");

	// 獵場 / 田鼠 / 野狗 / 塘窪 風物
	if( arg == "hunter about 獵場"
	||  arg == "hunter about 荒塘"
	||  arg == "hunter about 塘窪"
	||  arg == "hunter about 田鼠"
	||  arg == "hunter about 野狗"
	||  arg == "hunter about hunt" ) {
		do_chat(({
			(: command, "say 南面這片荒塘窪地﹐原是早年蓄水灌田的舊塘﹐渠塞塘淤後便撂荒了。如今成了野物的天下——草根底下盡是田鼠的洞﹐成群結隊地糟蹋村裡的穀子﹐是莊稼人恨極了的害物。客官若肯替咱們逮上幾隻﹐也算積德。" :),
			(: command, "say 田鼠雖小﹐逼急了也會回身咬人﹔再往裡去那片亂葦深處﹐藏著三五條結伙的野狗﹐裡頭有一條瘸腿的老野狗﹐體格壯、心眼狠﹐是這塘窪的霸主﹐生手莫要單身去招惹。練手嘛﹐先在外頭窪地拿田鼠、野狗開開葷﹐穩當些。" :),
		}));
		return 1;
	}

	// 康平村 / 老獵戶身世
	if( arg == "hunter about 康平村"
	||  arg == "hunter about 康平"
	||  arg == "hunter about 獵戶"
	||  arg == "hunter about kangping" ) {
		do_chat((: command,
			"say 老朽在這塘畔逮鼠攆狗大半輩子嘍。康平村是個巴掌大的莊稼村子﹐合村靠著村外那片好田過活﹐這荒塘的田鼠野狗一多﹐便要鬧到田裡去﹐糟蹋莊稼。村裡便派老朽常來下塘清剿﹐如今也老了﹐逮得動的有限﹐倒指望客官這樣的後生來搭把手哩。" :));
		return 1;
	}

	return notify_fail("老獵戶呵呵一笑﹕客官問這個做甚﹖塘邊的野物可不等人﹐閒話改日再嘮罷。\n");
}

// 純氣氛 lore NPC。配 set("civilized",1)：玩家 fight 時 fight.c 走 civilized 分支查
// accept_fight﹐回 0＝婉拒切磋並出本對白。注意這【擋不住 kill】﹐真正不可殺靠
// set("no_fight",1)（見 create()）。
int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖老朽一個逮鼠攆狗的山野獵戶﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
