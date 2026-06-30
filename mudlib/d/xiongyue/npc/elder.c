// elder.c -- 熊月村中老者：一個枯坐桂樹下說古的村中老人。
//
// 定位：純氣氛/lore NPC——講熊月村的由來，並埋一段呼應渾沌獸(docs L178「渾沌獸
//   隨機飛去兆隱縣、熊月村、天山…」)的飛掠傳說伏筆。本檔【不】開啟任何任務、不
//   給獎、不動旗標——渾沌獸是正史第七章 boss(/d/longdao/npc/chaosbeast.c)，其招喚
//   /降伏自有主線把關；此處只作世界觀鋪陳與伏筆 hook，speculative 之處一律留作
//   口耳相傳的「老人傳說」，不臆造完整解謎/獎賞。
//
// 範式來源(先讀既有檔模仿，未臆造 efun)：氣氛 lore NPC 之 do_ask 對白機
//   d/wutang/npc/washerwoman.c、d/snow/npc/heiyilaoren.c(ask 純對白、init 招呼
//   加 interactive 護衛、do_ask 開頭 is_fighting/is_chatting 護衛)。
//
// 鐵則遵循：
//   #10：本檔無 ::die()/destruct()——純對白，不涉自毀。
//   #14：init() 招呼一律 `this_player() && interactive(this_player())` 護衛(只招
//        呼真人)；do_ask 開頭 is_fighting()/is_chatting() 護衛。本檔不覆寫
//        relay_say(故無 say-loop 之虞)。
//   #6：do_ask 比對的 about token 含裸拼音/英文 id(elder/laozhe)，中文亦塞入
//       set_name id 陣列以便玩家以「老者」呼喚(對白判斷則用完整 arg 字串比對)。

#include <npc.h>

inherit F_VILLAGER;

int do_ask(string arg);

void create()
{
	set_name("村中老者", ({ "elder", "laozhe", "old man", "村中老者", "老者" }) );
	set("nickname", "村中老者");
	set_attr("int", 22);
	set_attr("wis", 26);
	set_attr("con", 16);
	set_attr("spi", 18);
	set_race("human");
	set_class("commoner");
	set_level(12);
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_skill("force", 24);

	set("age", 73);
	set("gender", "male");
	set("long",
		"一個鬚髮皆白的村中老者﹐枯坐在街心桂樹下的石桌旁。他生得\n"
		"清癯﹐一張臉曬得黝黑﹐刻滿了山風霜雪般的皺紋﹐一雙渾濁的老\n"
		"眼裡卻透著歷盡世事的清明。他披一件半舊的粗布褐衣﹐就著清冷\n"
		"的山月﹐慢條斯理地搖著一柄蒲扇﹐像是要把這熊月村幾代人的舊\n"
		"事﹑連同那些山裡代代相傳的奇談﹐都一遍遍地說與肯聽的人聽。\n"
		"見你這外鄉客循山而來﹐他渾濁的老眼裡漾起一絲笑意。\n"
		"你或許可以問問他這山村的來歷：ask elder about 熊月村。\n");
	set("chat_chance", 3);
	set("chat_msg", ({
		"村中老者搖著蒲扇﹐望著當空的山月出神﹐喃喃道﹕又是這般的月色 ... 一晃﹐都這許多年了。\n",
		"村中老者呷了口粗茶﹐慢條斯理地道﹕咱這熊月村僻是僻了些﹐山月卻是天下一等一的好哪。\n",
		"村中老者捋著白鬚﹐壓低了聲音道﹕這山裡頭的怪事﹐說與你們外鄉人聽﹐怕是沒人肯信囉。\n",
	}));
	setup();
}

void init()
{
	::init();
	add_action("do_ask", "ask");
	// #14：只對真人招呼(interactive 護衛)，免 NPC 互觸成洗版。
	if( this_player() && interactive(this_player()) && !is_fighting() ) {
		do_chat((: command,
			"say 外鄉的客官循山而來﹐難得難得。你若不嫌悶﹐便坐下聽老朽說一段這山村的舊事罷。(ask elder about 熊月村)" :));
	}
}

int do_ask(string arg)
{
	if( is_fighting() || is_chatting() )
		return notify_fail("村中老者正搖著蒲扇出神﹐沒空理你。\n");

	if( !arg )
		return notify_fail("你想問這位老者甚麼﹖（試試 ask elder about 熊月村）\n");

	// 熊月村的由來
	if( arg == "elder about 熊月村"
	||  arg == "elder about 熊月"
	||  arg == "elder about 村子"
	||  arg == "laozhe about 熊月村"
	||  arg == "elder about xiongyue"
	||  arg == "elder about village" ) {
		do_chat(({
			(: command, "say 客官問起這熊月村的來歷麼﹖呵﹐說來話長囉。咱這村子三面環山﹐一道清溪繞腳而過﹐世代以打獵採藥為生﹐打老輩傳下來﹐便喚作熊月村了。" :),
			(: command, "say 這「熊」字﹐是說咱這後山熊羆出沒﹐村口那幾株老樹上的熊爪痕﹐客官路過時想必也瞧見了﹔這「月」字麼 ... 客官且看這當空的山月﹐照了咱這孤村千百年﹐再不曾改過。山熊與孤月﹐這便是熊月村了。" :),
			(: command, "say 村小人稀﹐外鄉人一年也來不了幾個。客官若要進那後山獵獸練本事﹐村街南頭那條草徑便是了——只是那林子兇險﹐熊羆山魈都有﹐務必小心。" :),
		}));
		return 1;
	}

	// 渾沌獸飛掠的傳說伏筆（呼應 chaosbeast；純口耳相傳，不開任務、不給解謎答案）
	if( arg == "elder about 怪物"
	||  arg == "elder about 怪夜"
	||  arg == "elder about 七彩"
	||  arg == "elder about 七彩光華"
	||  arg == "elder about 焦痕"
	||  arg == "elder about 渾沌獸"
	||  arg == "elder about 渾沌"
	||  arg == "laozhe about 怪物"
	||  arg == "elder about beast"
	||  arg == "elder about monster" ) {
		do_chat(({
			(: command, "say 客官 ... 也聽說了那樁怪事﹖唉﹐村裡的後生都當老朽是說瘋話﹐可那一夜﹐老朽是親眼見著的﹐這雙老眼﹐還沒昏花到那個地步。" :),
			(: command, "say 那是好些年前的一個怪夜。三更天上﹐村裡的雞犬忽地齊聲狂叫﹐老朽推門出去﹐只見天邊一團龐然的怪物自雲裡飛來——那物事說它像獸罷又不像獸﹐通身流轉著赤橙黃綠青藍紫七彩的光華﹐明滅迴盪﹐將天都映得五色斑斕。" :),
			(: command, "say 它自咱村頂險險擦過﹐所過之處連風都是燙的﹐那打麥場上的青石﹐便是教它擦出的一塊焦痕﹐至今洗刷不去。眨眼工夫﹐它便朝著後山那雪峰、天山的方向飛去了﹐再不見蹤影。" :),
			(: command, "say 老朽後來聽走方的郎中說﹐那物事似是甚麼天地初開時遺下的太古凶獸﹐隨地流竄﹑無有定所﹐兆隱、天山、龍安那些偏僻去處﹐都有人見它掠空飛過。它究竟是甚麼來歷、又該如何降伏 ... 老朽一個山村野老﹐如何曉得﹖客官若是江湖中有本事的人物﹐他日若真撞上了它﹐可千萬 ... 千萬當心哪。" :),
		}));
		return 1;
	}

	// 後山獵場的指點（純提示，無任務）
	if( arg == "elder about 後山"
	||  arg == "elder about 林子"
	||  arg == "elder about 獵獸"
	||  arg == "laozhe about 後山"
	||  arg == "elder about hunting" ) {
		do_chat(({
			(: command, "say 客官要進後山麼﹖村街南頭那條草徑鑽進去便是了。林徑那一帶常有黑熊出沒﹐那畜生力大皮厚﹐尋常後生近不得身。" :),
			(: command, "say 再往深裡去﹐那月影深林的巨岩陰處﹐還盤踞著山魈——那是山裡的精怪﹐攀岩縱躍﹑刁鑽得很﹐比黑熊還難纏幾分。客官本事若足﹐倒是練功的好去處﹔本事若不濟﹐可萬莫逞強深入。" :),
			(: command, "say 進山前﹐街北山月小鋪買些乾糧傷藥傍身﹐總是不錯的。" :),
		}));
		return 1;
	}

	return notify_fail("村中老者搖搖頭﹕這個老朽就不曉得了。客官不妨問問熊月村、後山、或是那樁怪夜的事。（試試 ask elder about 熊月村）\n");
}

int accept_fight(object ob)
{
	do_chat((: command,
		"say 客官這是做甚麼﹖老朽一個年逾古稀的山村野老﹐手無縛雞之力﹐你 ... 你莫要為難老朽哪。" :));
	return 0;
}

// 收物防呆：婉拒玩家遞來的物事，不吞玩家物品。
int accept_object(object who, object ob)
{
	do_chat((: command,
		"say 老朽一個山村野老﹐了無長物﹐這個 ... 老朽受不起﹐你還是自個兒留著罷。" :));
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
