// hunter.c -- 山戶獵人，歇腳文國西山林麓的西山老獵手（純氣氛 / lore NPC）。
//
// init() 招呼一律加 interactive(this_player()) 護衛（lesson #14），只招呼真人﹐
// 免 NPC 互觸洗版。ask hunter about <topic> 講西山的野獸風物、勸生客留神野豬灰猿。
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
	set_name("山戶獵人", ({ "hunter", "mountain hunter", "shanhu" }) );
	set("nickname", "山戶獵人");
	set_attr("con", 28);
	set_attr("str", 26);
	set_attr("dex", 26);
	set_race("human");
	set_class("fighter");
	set_level(22);

	set_skill("unarmed", 34);
	set_skill("dodge", 30);
	set_skill("parry", 28);
	set_skill("force", 22);

	set("age", 46);
	set("gender", "male");
	// 純氣氛 lore NPC，不可殺：no_fight 擋住 kill 與 fight（kill.c:38 / fight.c:25）﹔
	// civilized 使 fight 時走 accept_fight 婉拒分支（出入戲對白）。兩者皆 NPC-local﹐
	// 不動房間 no_fight﹐不影響同房其他可獵的野物。
	set("no_fight", 1);
	set("civilized", 1);
	set("long",
		"一位西山裡討生活的山戶獵人﹐生得精悍黝黑﹐裹著件鹿皮的短褂﹐\n"
		"荷著一張上了弦的硬弓﹐腰間掛著新獵的山雞野兔﹐還插著幾枝淬\n"
		"了藥的短箭。他在這西山裡行獵了二十多年﹐山裡哪處有獸、哪叢\n"
		"藏著惡物、哪條獸道好設陷﹐沒有他不熟的。他靠石歇腳﹐看著最\n"
		"是健談﹐你可以問問他﹕ask hunter about 獵場。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"山戶獵人撥弄著腰間新獵的山雞野兔﹐自顧自地清點著今日的收成﹐臉上掛著淡淡的笑。\n",
		"山戶獵人取下硬弓﹐就著石稜細細地檢視弓弦﹐又抹了抹箭鏃上的藥。\n",
		"山戶獵人側耳聽了聽林子深處傳來的獸吼﹐低聲道﹕那頭老野豬﹐又出來拱食了。\n",
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
			"say 這位客官也是進山練手的﹖西山的野豬灰猿可不好惹﹐留神著些。" :));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這山戶獵人甚麼﹖（試試 ask hunter about 獵場）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("山戶獵人正低頭檢視弓弦﹐一時沒理會你。\n");

	// 獵場 / 山狸 / 野豬 / 灰猿 / 西山 風物
	if( arg == "hunter about 獵場"
	||  arg == "hunter about 西山"
	||  arg == "hunter about 山林"
	||  arg == "hunter about 山狸"
	||  arg == "hunter about 野豬"
	||  arg == "hunter about 灰猿"
	||  arg == "hunter about hunt" ) {
		do_chat(({
			(: command, "say 城西這片西山﹐文國雖以文墨出名﹐這山林卻是莽莽蒼蒼的好獵場。林子裡那些花斑的山狸﹐攀樹竄枝快得很﹐機警靈巧﹐客官要練手﹐拿牠們開葷正合適——只是身手快﹐須得有些準頭才逮得著。" :),
			(: command, "say 再往林子深處去﹐住著膘肥力大的野豬﹐一對撩牙又長又利﹐性子暴烈﹐橫衝直撞起來連咱們也得退避三分。最裡頭那古藤岩窟﹐盤著一群灰猿﹐裡頭一頭毛色蒼白的老灰猿﹐通臂力大、機變如人﹐是群猿的老祖——生手切莫單身闖那岩窟﹐栽在猿群手裡的後生﹐我見得多了。" :),
		}));
		return 1;
	}

	// 文國縣 / 山戶獵人身世
	if( arg == "hunter about 文國"
	||  arg == "hunter about 文國縣"
	||  arg == "hunter about 獵戶"
	||  arg == "hunter about 山戶"
	||  arg == "hunter about wenguo" ) {
		do_chat((: command,
			"say 文國這小縣﹐城裡是文墨書香的斯文地﹐城西這山卻是咱們山戶討生活的去處。咱祖祖輩輩在這西山裡行獵﹐打山雞、套野兔、獵野豬﹐拿山貨換城裡的米鹽筆墨。這二十多年的山路走下來﹐這林子的脾性﹐沒有咱不熟的。客官若進山﹐有甚拿不準的﹐只管問咱便是。" :));
		return 1;
	}

	return notify_fail("山戶獵人憨憨一笑﹕客官問這個做甚﹖山裡的野物可不等人﹐閒話改日再嘮罷。\n");
}

// 純氣氛 lore NPC。配 set("civilized",1)：玩家 fight 時 fight.c 走 civilized 分支查
// accept_fight﹐回 0＝婉拒切磋並出本對白。注意這【擋不住 kill】﹐真正不可殺靠
// set("no_fight",1)（見 create()）。
int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖咱一個進山打獵的山野之人﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
