// fisher.c -- 漁戶，補網於婁縣澤畔水濱的水澤老漁人（純氣氛 / lore NPC）。
//
// init() 招呼一律加 interactive(this_player()) 護衛（lesson #14），只招呼真人﹐
// 免 NPC 互觸洗版。ask fisher about <topic> 講水澤的禽獸風物、勸生客留神蘆雁水獺、
// 莫驚了潭裡的老澤蛇。無任務、無給物。
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
	set_name("漁戶", ({ "fisher", "fisherman", "yuhu" }) );
	set("nickname", "漁戶");
	set_attr("con", 26);
	set_attr("str", 24);
	set_attr("dex", 24);
	set_race("human");
	set_class("commoner");
	set_level(18);

	set_skill("unarmed", 28);
	set_skill("dodge", 26);
	set_skill("parry", 22);

	set("age", 52);
	set("gender", "male");
	// 純氣氛 lore NPC，不可殺：no_fight 擋住 kill 與 fight（kill.c:38 / fight.c:25）﹔
	// civilized 使 fight 時走 accept_fight 婉拒分支（出入戲對白）。兩者皆 NPC-local﹐
	// 不動房間 no_fight﹐不影響同房其他可獵的野物。
	set("no_fight", 1);
	set("civilized", 1);
	set("long",
		"一位水澤裡討生活的漁戶﹐生得乾瘦黝黑﹐挽著褲腿﹐小腿上沾著\n"
		"澤裡洗不淨的青泥﹐一雙手在漁網間穿梭得飛快。他在這片甘泉下\n"
		"游的水澤裡撈了半輩子魚﹐澤裡哪處水深、哪叢葦子裡藏著惡物、\n"
		"哪片潭水撐不得船﹐沒有他不熟的。他盤腿補網﹐看著最是健談﹐\n"
		"你可以問問他﹕ask fisher about 獵場。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"漁戶低頭在漁網間穿梭著梭子﹐手底飛快﹐口中哼著綿軟的水鄉小調。\n",
		"漁戶直起腰捶了捶後背﹐望著浩淼的水澤﹐喃喃道﹕今年澤裡的魚﹐倒比往年肥。\n",
		"漁戶側耳聽了聽蘆蕩深處的雁鳴﹐自語道﹕那群蘆雁﹐又在護窩了。\n",
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
			"say 這位客官也是下澤練手的﹖蘆蕩裡水道繞﹐潭裡的老澤蛇毒﹐留神著些。" :));
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想問這漁戶甚麼﹖（試試 ask fisher about 獵場）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("漁戶正低頭補著漁網﹐一時沒理會你。\n");

	// 獵場 / 蘆雁 / 水獺 / 澤蛇 / 水澤 風物
	if( arg == "fisher about 獵場"
	||  arg == "fisher about 水澤"
	||  arg == "fisher about 蘆蕩"
	||  arg == "fisher about 蘆雁"
	||  arg == "fisher about 水獺"
	||  arg == "fisher about 澤蛇"
	||  arg == "fisher about hunt" ) {
		do_chat(({
			(: command, "say 城西這片水澤﹐是咱甘泉的水匯下來瀦成的﹐蘆葦連天﹐養活了滿澤的魚蝦水禽。客官要練手﹐淺水裡那些蘆雁正好——這野雁看著溫馴﹐護起窩來可凶哩﹐撲翅啄人不留情﹐拿牠們開開葷穩當。" :),
			(: command, "say 再往蘆蕩深處去﹐泥岸窩穴裡住著溜滑的水獺﹐游水捕魚快如游龍﹐護食時一口利齒咬住便不鬆口。最裡頭那一泓蛇潭﹐潭底盤著一條碗口粗的老澤蛇﹐丈把長﹐身懷劇毒﹐纏絞起來力大無窮——咱漁戶撐船都不敢到那潭心去。生手切莫單身闖蛇潭﹐被那老蛇纏上﹐神仙也難救。" :),
		}));
		return 1;
	}

	// 婁縣 / 甘泉 / 漁戶身世
	if( arg == "fisher about 婁縣"
	||  arg == "fisher about 甘泉"
	||  arg == "fisher about 漁戶"
	||  arg == "fisher about louxian" ) {
		do_chat((: command,
			"say 婁縣是個僻處山坳的小縣﹐就憑那一脈甘泉出名。那泉水匯了縣外的溪流﹐到城西低窪處便瀦成了這一片大水澤﹐咱們漁戶世世代代靠著它撈魚過活。城裡的甘泉客棧、甘泉茶館用的是井裡的好水﹐咱們吃的卻是這澤裡的魚蝦——一方水土養一方人哪。客官下澤﹐有甚拿不準的﹐只管問咱便是。" :));
		return 1;
	}

	return notify_fail("漁戶憨憨一笑﹕客官問這個做甚﹖網還沒補完哩﹐閒話改日再嘮罷。\n");
}

// 純氣氛 lore NPC。配 set("civilized",1)：玩家 fight 時 fight.c 走 civilized 分支查
// accept_fight﹐回 0＝婉拒切磋並出本對白。注意這【擋不住 kill】﹐真正不可殺靠
// set("no_fight",1)（見 create()）。
int accept_fight(object ob)
{
	do_chat((: command, "say 哎喲﹗客官這是做甚﹖咱一個下澤撈魚的漁家﹐與你無冤無仇哪﹗" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
