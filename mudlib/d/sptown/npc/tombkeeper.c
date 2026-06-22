// tombkeeper.c -- 守墓老人：常年掃劍守碑於祭劍臺的一位白髮老者。
//
// 【定位】純氣氛 NPC：不接任務、不發物、不設任何旗標。唯一作用是 ask 講述
//   「祭劍臺 / 劍冢 / 棄劍石」的由來，呼應「江湖前輩埋劍歸隱」之武俠 lore
//   （docs 01-世界觀與劇情/04-地圖與場景.md L116/L140）。為 lv45 傳送落點的
//   氣氛點綴，給駕雲飛升至此的玩家一段身世來歷可問。
//
// 【runtime 鐵則】本 NPC 有 do_ask / init，**不** replace_program（#11）。
//   do_ask 入口以 is_fighting()/is_chatting() 守衛；本檔不給物、不設旗標，
//   無 #10「自毀後碼不跑」之虞。init() 招呼一律加 interactive(this_player())
//   護衛（#14：只招呼真人，免 NPC 互觸成洗版）。所在房 altar 設 no_fight，
//   且 accept_fight 婉拒，動不得干戈。

#include <ansi.h>
#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name(HIW "守墓老人" NOR, ({ "tombkeeper", "tomb keeper", "keeper", "old man", "守墓老人", "老人", "老者" }) );
	set("nickname", HIW "守墓老人" NOR);
	set_race("human");
	set_class("commoner");
	set_level(20);
	set_attr("con", 22);
	set_attr("str", 18);

	set("age", 71);
	set("gender", "male");
	set("long",
		"一個白髮蕭疏的乾瘦老者﹐佝僂著背﹐手裡拄著一柄禿了頭的舊\n"
		"竹帚。他一身洗得發白的青布衣裳﹐袖口磨出了毛邊﹐面上溝壑縱\n"
		"橫﹐唯有一雙眼睛在皺紋深處透著幾分歷盡滄桑的清明。也不知他在\n"
		"這祭劍臺守了多少年了﹐日日掃著劍林間的落葉斷枝﹐拂去石碑上的\n"
		"塵土﹐替那一柄柄無人問津的斷劍﹐守著最後一點香火。他見了你也\n"
		"不驚詫﹐只默默拄帚而立﹐彷彿這滿臺斷劍的來歷﹐他都記在心裡。\n"
		"你或許可以問問他：ask keeper about 祭劍臺。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"守墓老人佝僂著腰﹐拄著禿帚﹐一下一下地掃著劍林間飄落的桃花與枯葉。\n",
		"守墓老人停下帚來﹐伸出枯瘦的手﹐輕輕拂去石碑上一層薄塵﹐喃喃地不知念著哪一個名字。\n",
		"守墓老人抬眼望了望臺東那片如霞的桃花﹐又低頭看看滿地斷劍﹐長長地嘆了一口氣。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");

	// 只招呼真人（#14：interactive 護衛，免 NPC 漫遊互觸洗版）。
	if( this_player() && interactive(this_player()) && !is_fighting() ) {
		do_chat((: command,
			"say 客官也是駕雲來的麼？這祭劍臺上葬的﹐都是當年響噹噹的人物哪……要問來歷﹐只管問老朽。(ask keeper about 祭劍臺)" :));
	}
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想跟這守墓的老人打聽甚麼？（試試 ask keeper about 祭劍臺）\n");

	if( is_fighting() || is_chatting() )
		return notify_fail("守墓老人正拄著禿帚低頭掃著落花﹐一時沒理會你。\n");

	// 祭劍臺 / 劍冢的由來。
	if( arg == "keeper about 祭劍臺"
	||  arg == "keeper about 劍冢"
	||  arg == "keeper about 斷劍"
	||  arg == "keeper about 鐵林"
	||  arg == "keeper about 石碑"
	||  arg == "keeper about altar"
	||  arg == "tombkeeper about 祭劍臺"
	||  arg == "old man about 祭劍臺" ) {
		do_chat(({
			(: command, "say 客官有所不知。這祭劍臺﹐江湖上又喚作『劍冢』。但凡成了名的劍客﹐或是看破紅塵、折節歸隱﹐或是仇殺場中、敗亡身死﹐他那柄佩了一生的劍﹐便都要送到這臺上來﹐插進土裡。" :),
			(: command, "say 你瞧這滿臺斷劍——一柄劍﹐便是一條人命﹐一段恩怨。年深日久﹐劍積得多了﹐遠望竟成了一片鐵林。風一吹﹐錚錚作響﹐老朽聽了幾十年﹐只當是那些故人在說話。" :),
			(: command, "say 臺心那座石碑上﹐刻的都是他們的名姓。如今字跡都磨花了﹐認得出的沒幾個﹐認得他們的人﹐也都不在嘍。老朽守在這兒﹐替他們掃掃落葉﹐拂拂塵﹐也算……有個人記著。" :),
		}));
		return 1;
	}

	// 棄劍石 / 桃花林 / 那位歸隱前輩的公案。
	if( arg == "keeper about 棄劍石"
	||  arg == "keeper about 桃花林"
	||  arg == "keeper about 桃花"
	||  arg == "keeper about 前輩"
	||  arg == "keeper about swordstone"
	||  arg == "tombkeeper about 棄劍石"
	||  arg == "old man about 棄劍石" ) {
		do_chat(({
			(: command, "say 臺東那片桃花林﹐林心有一方青石﹐喚作『棄劍石』。客官若得閒﹐不妨往東去瞧瞧。" :),
			(: command, "say 那是好些年前的事了。有一位劍道前輩﹐劍法通神﹐一生快意恩仇﹐到頭來卻看破了這刀光劍影裡的冤冤相報。他便在那桃花林中對石立誓﹐一劍劈石為記﹐自此罷劍歸隱——那劍﹐就埋在這祭劍臺上。" :),
			(: command, "say 旁人都道他是急流勇退、得了善終。可老朽瞧著﹐能在頑石上留下那道劍痕的人﹐要放下手裡的劍﹐怕比拿起來還要難上百倍哪。罷了罷了﹐都過去嘍。" :),
		}));
		return 1;
	}

	// 老人自身 / 守墓的緣由。
	if( arg == "keeper about 守墓"
	||  arg == "keeper about 老人"
	||  arg == "keeper about 你"
	||  arg == "keeper about keeper"
	||  arg == "tombkeeper about 守墓"
	||  arg == "old man about 你" ) {
		do_chat(({
			(: command, "say 老朽?一個埋了名姓的糟老頭子罷了﹐有甚麼好問的。年輕時也曾在這江湖上闖蕩過﹐後來看膩了刀頭舔血的日子﹐便來這劍冢守著。" :),
			(: command, "say 一柄禿帚、一座孤碑﹐掃掃落花﹐守守斷劍﹐這日子比甚麼都清靜。客官﹐莫看這些劍客生前何等風光﹐到頭來不過化作這土裡一截殘鋒——你若也是練劍的人﹐倒不妨在這臺上多站一站﹐想想清楚。" :),
		}));
		return 1;
	}

	return notify_fail("守墓老人拄著禿帚搖了搖頭：客官問這做甚?要問這臺上的事﹐老朽倒還說得上幾句。（試試 ask keeper about 祭劍臺）\n");
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品。
int accept_object(object who, object ob)
{
	do_chat((: command,
		"say 使不得使不得﹐老朽守著這劍冢﹐甚麼也不缺﹐客官的東西自個兒留著罷。" :));
	return 0;
}

// 此臺肅穆禁鬥（房間亦設 no_fight），婉拒任何挑釁。
int accept_fight(object ob)
{
	do_chat((: command,
		"say 哎﹗客官萬萬使不得﹗這祭劍臺是葬劍安魂的清淨地﹐豈容在這兒動刀動劍、驚擾了亡者？" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
