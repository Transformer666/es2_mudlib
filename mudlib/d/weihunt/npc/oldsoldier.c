// oldsoldier.c -- 老戍卒，盤桓衛國邊塞荒坡、不肯隨軍撤走的屯軍老人（純氣氛 / lore NPC）。
//
// init() 招呼一律加 interactive(this_player()) 護衛（lesson #14），只招呼真人﹐
// 免 NPC 互觸洗版。ask soldier about <topic> 講邊塞的野狼沙狐、屯軍舊事，勸生客
// 留神成群的塞狼。無任務、無給物。
// （與 /d/weiguo/npc/oldsoldier 同名不同路徑、不同 id﹐互不衝突。）
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
	set_name("老戍卒", ({ "soldier", "old soldier", "border guard", "laoshuzu" }) );
	set("nickname", "老戍卒");
	set_attr("con", 30);
	set_attr("str", 28);
	set_race("human");
	set_class("fighter");
	set_level(26);

	set_skill("unarmed", 36);
	set_skill("dodge", 30);
	set_skill("parry", 32);
	set_skill("force", 24);

	set("age", 64);
	set("gender", "male");
	// 純氣氛 lore NPC，不可殺：no_fight 擋住 kill 與 fight（kill.c:38 / fight.c:25）﹔
	// civilized 使 fight 時走 accept_fight 婉拒分支（出入戲對白）。兩者皆 NPC-local﹐
	// 不動房間 no_fight﹐不影響同房其他可獵的野物。
	set("no_fight", 1);
	set("civilized", 1);
	set("long",
		"一位披著褪色舊號褂的老戍卒﹐花白的鬍子被塞風吹得亂顫﹐一張\n"
		"飽經風霜的臉膛黑裡透紅﹐眼角刻滿了刀劈似的皺紋。他是早年屯\n"
		"軍裡留下的老人﹐撤軍時不肯走﹐成日拄著長矛守在這荒坡上瞭望\n"
		"塞外﹐念著當年戍邊的舊事。塞外的風物、荒坡的野物﹐沒有他不\n"
		"熟的﹐你可以問問他﹕ask soldier about 獵場。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"老戍卒拄著長矛遠眺塞外﹐花白的鬍子被風吹得亂顫﹐喃喃道﹕又起風了﹐塞外的天﹐說變就變哪。\n",
		"老戍卒摩挲著矛桿上一道深深的舊痕﹐眼神悠遠﹐似又回到了當年戍邊的烽火裡。\n",
		"老戍卒側耳聽了聽西邊崖下傳來的狼嗥﹐沉聲道﹕那群塞狼﹐又在叫了。\n",
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
			"say 這位後生也是來這荒坡練手的﹖塞外的野狼可不是耍的﹐留神些。" :));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這老戍卒甚麼﹖（試試 ask soldier about 獵場）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("老戍卒拄著長矛遠眺塞外﹐一時沒理會你。\n");

	// 獵場 / 野狼 / 沙狐 / 邊塞 風物
	if( arg == "soldier about 獵場"
	||  arg == "soldier about 荒坡"
	||  arg == "soldier about 邊塞"
	||  arg == "soldier about 野狼"
	||  arg == "soldier about 塞狼"
	||  arg == "soldier about 沙狐"
	||  arg == "soldier about hunt" ) {
		do_chat(({
			(: command, "say 西邊這片荒坡﹐原是當年屯軍牧馬操演的草場﹐撤了軍便荒了。如今盡是塞外來的野物——亂石坡上那些火紅的沙狐﹐機警得很﹐叼了獵物便鑽石縫﹐快得叫人抓不著。後生若要練手﹐拿牠們開葷正合適。" :),
			(: command, "say 再往西去那片亂石坡、崖根的狼窩﹐住著成群的灰背塞狼﹐個個比尋常的狼壯實﹐塞外苦寒磨出來的硬骨頭﹐連失蹄的牛馬也敢撲。崖窩最深處還盤著一頭巨碩的頭狼﹐是群狼之王﹐凶得很——生手切莫單身去招惹﹐栽在那裡的後生﹐老朽見得多了。" :),
		}));
		return 1;
	}

	// 衛國鎮 / 屯軍舊事 / 老戍卒身世
	if( arg == "soldier about 衛國"
	||  arg == "soldier about 衛國鎮"
	||  arg == "soldier about 屯軍"
	||  arg == "soldier about 戍卒"
	||  arg == "soldier about weiguo" ) {
		do_chat((: command,
			"say 衛國鎮啊﹐早年是戍邊的軍屯關隘﹐這荒坡上的烽燧馬廄﹐都是當年屯軍的營盤。後來刀兵入庫、撤了軍﹐弟兄們有的回鄉、有的入了土﹐就剩老朽這把老骨頭﹐捨不得這守了半輩子的關﹐便留下來了。守著守著﹐關沒了﹐倒守起這荒坡上的野狼來嘍——也好﹐替過往的後生瞭個風﹐免得教塞狼撈了去。" :));
		return 1;
	}

	return notify_fail("老戍卒呵呵一笑﹕後生問這個做甚﹖塞外的風緊﹐閒話改日再嘮罷。\n");
}

// 純氣氛 lore NPC。配 set("civilized",1)：玩家 fight 時 fight.c 走 civilized 分支查
// accept_fight﹐回 0＝婉拒切磋並出本對白。注意這【擋不住 kill】﹐真正不可殺靠
// set("no_fight",1)（見 create()）。
int accept_fight(object ob)
{
	do_chat((: command, "say 哎﹗後生這是做甚﹖老朽一個守關的殘卒﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
