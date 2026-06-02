// jiangyun.c -- 漕幫禮堂的耆宿「江隕」(uid: jiangyun)。純氣氛閒談 NPC：
//               不接任務、不交物、不動旗標。
//
// 【設定 / canon】依 ES2 設定﹐江隕是漕幫在京畿的老前輩、漕幫「四鬼問環」支線的關鍵人﹕
//   他授予玩家「四鬼」的指環﹐玩家持環往訪赤魈／青蛛／濁魚／旱魃 四鬼。本幫亦以江隕
//   為名義上的創幫者——漕幫禮堂（/d/caobang/hall）於 create() 內即以 uid "jiangyun"
//   向 CLAN_D 登錄漕幫(register_clan)。
//
// 【A-gated TODO】「四鬼問環」（江隕授環 → 赤魈/青蛛/濁魚/旱魃）繫於另一樁尚未拍板的
//   主線抉擇(決策 A)﹐故本檔【不】實作任何授環 / 問環任務﹕江隕只是位話裡藏著舊事、
//   點到「四鬼」為止的氣氛耆宿。
//   == 待決策 A 拍板後再補（此處一律不做、不設旗標）==
//     - 江隕授玩家「四鬼之環」(指環實物)
//     - 持環問訪 赤魈 / 青蛛 / 濁魚 / 旱魃 的四鬼支線
//   本檔絕不讀寫任何 四鬼 / 旋芒 / main_omen / 主線 旗標﹔對白裡的「四鬼」純為 canon 氣氛。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("江隕", ({ "jiangyun", "elder jiangyun", "jiang yun" }) );
	set("nickname", "江隕");
	set_race("human");
	set_class("commoner");
	set_level(20);

	set("age", 71);
	set("gender", "male");
	set("long",
		"這位是漕幫在京畿輩分最高的老前輩﹐江隕。他生得清癯﹐一\n"
		"頭花白的長髮在腦後束成一個髻﹐穿一件洗得發舊的玄青長袍﹐袍\n"
		"角還沾著經年的河水氣。他不像個跑船的﹐倒像個飽歷風霜的隱\n"
		"者——一雙眼睛深得很﹐望著「漕」字大旗出神時﹐眉宇間似壓著\n"
		"一樁說不出口的舊事。漕幫上下﹐連分舵主見了他都要執晚輩禮。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"江隕負手立在「漕」字大旗下﹐仰望著歷代總舵主的牌位﹐久久不語。\n",
		"江隕枯瘦的手指輕輕撫過供案上那具鏽蝕的鐵錨﹐眼神悠遠﹐似在追憶甚麼。\n",
		"江隕端起一盞涼透了的茶﹐卻並不喝﹐只望著窗外東去的河水﹐輕輕嘆了口氣。\n",
		"江隕低聲自語﹕四鬼散於四方 ... 這一樁因果﹐到底何時方了 ...\n",
	}));
	setup();
	carry_money("silver", 5);
}

void init()
{
	::init();
	add_action("do_ask", "ask");
}

int do_ask(string arg)
{
	if( !arg )
		return notify_fail("你想向這位老前輩請教甚麼﹖（試試 ask jiangyun about 漕幫）\n");

	// 漕幫：江隕道出漕幫的源流與不結仇的幫風
	if( arg == "jiangyun about 漕幫"
	||  arg == "jiangyun about 禮堂"
	||  arg == "jiangyun about 漕運"
	||  arg == "jiangyun about caobang"
	||  arg == "elder jiangyun about 漕幫" ) {
		do_chat(({
			(: command, "say 客官遠來。這裡是漕幫的禮堂﹐老朽江隕﹐在這幫裡叨陪末座﹐忝為幾分薄面。漕幫執掌天下漕運﹐自前朝開鑿這條大運河、設下漕運糧道時便已立幫﹐傳到如今﹐也有百十年的光景了。" :),
			(: command, "say 咱漕幫幫眾數十萬﹐沿運河南北分舵林立﹐看著聲勢浩大﹔可這幫子自立幫起﹐便守著一條不成文的規矩——不與江湖中人結仇怨。跑船的人﹐求的是四海通達、與人方便﹐結那些刀頭舔血的梁子﹐做甚﹖" :),
			(: command, "say 客官若有心入夥﹐這禮堂的分舵主宋安江﹐人最爽利﹐入幫的章程﹐尋他問便是。老朽老了﹐如今只在這禮堂裡看看舊旗、守守舊事罷了。" :),
		}));
		return 1;
	}

	// 四鬼：canon 核心引子——只給氣氛舊事﹐絕不授環、不接任務、不設旗標
	if( arg == "jiangyun about 四鬼"
	||  arg == "jiangyun about 環"
	||  arg == "jiangyun about 指環"
	||  arg == "jiangyun about 舊事"
	||  arg == "jiangyun about 赤魈"
	||  arg == "jiangyun about 青蛛"
	||  arg == "jiangyun about 濁魚"
	||  arg == "jiangyun about 旱魃" ) {
		do_chat(({
			(: command, "say （江隕的神色倏地凝重起來﹐枯瘦的手在那具鐵錨上停了一停）客官 ... 也聽說了『四鬼』麼﹖" :),
			(: command, "say 唉。那是一樁壓在老朽心頭數十年的舊因果了。當年有四個人﹐喚作赤魈、青蛛、濁魚、旱魃﹐因著一段恩怨﹐散落於天下四方 ... 老朽手裡﹐還留著一枚當年的舊環﹐本該交付一個有緣、有膽識的後生﹐持環去尋這四鬼﹐了結這段因果。" :),
			(: command, "say 只是 ... （江隕搖了搖頭﹐長嘆一聲）這環何時能交、該交與何人﹐眼下還有一樁更大的關節未曾分曉﹐時機未到。客官且記下這四個名字﹐來日因緣際會﹐自有分曉。今日﹐老朽只能說到這裡了。" :),
		}));
		// TODO(decision-A)：「四鬼問環」(授環→赤魈/青蛛/濁魚/旱魃)整條支線繫於主線抉擇 A。
		//   抉擇拍板前﹐本處【不】new 任何指環、【不】接任務、【不】設 四鬼/旋芒/主線 旗標﹔
		//   僅以上列對白作 canon 氣氛鋪墊。待 A 拍板後﹐再於此實作授環與問環流程。
		return 1;
	}

	return notify_fail("江隕望著東去的河水﹐淡淡道﹕有些事﹐時候未到﹐多問無益。客官且自便罷。（試試 ask jiangyun about 漕幫）\n");
}

int accept_fight(object ob)
{
	do_chat((: command, "say （江隕並不動怒﹐只淡淡看你一眼）客官﹐這是漕幫議事的清淨禮堂﹐動手的事﹐犯不著。老朽一把年紀﹐也奉陪不起。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
