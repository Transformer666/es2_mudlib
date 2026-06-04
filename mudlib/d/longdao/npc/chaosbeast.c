// chaosbeast.c -- 渾沌獸，正史主線第七章「渾沌獸任務」的終局之獸。
//
// 設定（承接 docs 05 L54-57「5 個 broken seal + 神之心 → 渾沌印記」「渾沌獸（七彩石招
//   喚）」「必掉任一完整印記」；docs 05 L174-182 渾沌獸攻略——烙人猛砍、補血四次、會隨
//   機飛去兆隱縣/熊月村/天山等偏僻處、隨地流竄）：
//   渾沌獸是天地初開、清濁未判時所遺的一頭混沌巨獸，通體流轉著赤橙黃綠青藍紫七彩混沌
//   之力，隨地流竄、混沌未分。少俠降盡天龍島火、天龍、雷、風四神、嵌齊星光環之後，自
//   漕幫江隕處得了那方以『破碎的印記』合『神之心』熔煉的渾沌印記，持往天龍島島心神域
//   旁的七彩石、於身上『insert chaos seal』，便能將這頭封鎮石中的渾沌獸重新招出而降之。
//
// 設計（boss-tier：迄今最強之獸，lvl 57。較天龍島四神(火50/天龍52/雷55/風54)更強——以
//      七彩混沌之力搏殺、須武藝精純且有備而來方克的強力高階 NPC）：
//   * level 57；unarmed 215 / parry 205 / dodge 200 / force 240——以混沌巨獸之爪牙、七彩
//     混沌之力搏殺、不持兵器(unarmed 主戰)。
//   * 三圍真氣 advance_stat gin/kee/sen 600/720/660——混沌巨獸，血(kee)、神(sen)俱厚，較
//     四神更甚。
//   * accept_fight 回傳 1——既被自七彩石招出便奉戰到底，然不主動撲噬(招喚門禁已把關：
//     須 main_canon7==1 之玩家於七彩石招出)。
//   * boss 特技(烙人猛砍/補血四次/隨地流竄)逾本檔範疇——以「一頭迄今最強之高階 NPC」呈
//     現即可，不另造戰鬥 efun(鏡 firegod/dragongod 之做法)。
//
// 任務推進（die()）——第七章掉印機制（承 firegod.c 範式 + lesson #10「::die()-LAST」、
//   lesson #1「__DIR__ 已含 npc/ 尾斜線，掉物路徑為 __DIR__"obj/x" 非 "npc/obj/x"」）：
//   渾沌獸伏誅時，若下手者(last_damage_giver)是身負第七章旗標(quest/main_canon7==1)的
//   真實玩家(userp)：
//     (1) 先推進 main_canon7 1->2（務必置於 ::die() 之前——承 lesson #10：::die() 後同
//         函式其後碼不保證續行）。
//     (2) 恒呼 ::die()（屍體於此生成並登錄 temp("corpse")）。
//     (3) 自屍身掉一片完整印記/獎賞信物『渾沌之心』(__DIR__"obj/chaos_heart"——正確路
//         徑，無重覆 npc/)，置於 ::die() 之後（屍體已生成）、函式最末。
//   防重複掉印（確定性 guard）：唯 main_canon7==1(尚未推進)、身上尚無渾沌之心者方掉——
//   已推進(==2)或已持心者重殺亦不再掉。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 掉落第七章獎賞信物「渾沌之心」(一片完整印記)。who=下手者(真實玩家)；於 ::die() 之後
// 呼叫，corpse 已存在於 temp("corpse")。掉物路徑 __DIR__"obj/chaos_heart"——__DIR__ 已
// 含 npc/ 尾斜線(本檔在 npc/)，故為 obj/ 非 npc/obj/(承 lesson #1)。確定性 guard 已於
// die() 內判妥，此處僅負責掉印。
void chaosbeast_drop_loot(object who)
{
	object corpse, loot;

	if( !who ) return;

	loot = new(__DIR__"obj/chaos_heart");
	if( !objectp(loot) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIW "渾沌獸發出一聲撕裂天地的悲嘯，那一身流轉七彩的混沌之力倏地暴漲到"
		"極處、又驟然向內崩塌——只見那混沌的巨軀自心口處層層潰散、化作赤橙黃綠青"
		"藍紫七色的流光四下飛濺、湮入虛空，自牠湮滅處那一點未散的混沌元神中，緩"
		"緩凝出一枚通體流轉著七彩混沌之力的完整印記，落入了渾沌獸的遺蛻之中。那"
		"便是了結這頭天地初開之獸的鐵證『渾沌之心』了——一片完整印記，已得！\n"
		NOR);
}

void create()
{
	set_name(HIW "渾沌獸" NOR,
		({ "chaosbeast", "chaos beast", "beast" }) );
	set("nickname", "混沌巨獸");
	set_attr("str", 38);
	set_attr("dex", 36);
	set_attr("int", 30);
	set_attr("wis", 28);
	set_attr("spi", 36);
	set_attr("con", 38);
	set_attr("cor", 32);
	set_race("human");
	set_level(57);
	set_class("fighter");
	set("sect", "渾沌");
	set("rank", "混沌巨獸");

	// boss-tier：以混沌巨獸之爪牙、七彩混沌之力搏殺、不持兵器(unarmed 主戰)。較四神更強。
	set_skill("unarmed", 215);
	set_skill("parry", 205);
	set_skill("dodge", 200);
	set_skill("force", 240);

	// 混沌巨獸：血(kee)、神(sen)俱厚，較四神更甚。
	advance_stat("gin", 600);
	advance_stat("kee", 720);
	advance_stat("sen", 660);

	set("gender", "male");
	set("age", 99999);
	set("long",
		"這便是天地初開、清濁未判時所遺的那頭渾沌獸了。牠那一團龐\n"
		"然的混沌巨軀並無定形，似獸而非獸，通體流轉著赤、橙、黃、綠、\n"
		"青、藍、紫七色的混沌之力，明滅迴盪，將凝未凝、將散未散，彷彿\n"
		"一整方鴻濛初判的天地都絞縮進了牠這一具身軀之中。牠周身那七彩\n"
		"的混沌之氣無風自捲，所過之處，連空間都被攪得扭曲變形、虛實莫\n"
		"辨；牠那一張混沌的面孔上隱隱睜著一雙深不見底的眸子，睥睨之\n"
		"間，自有一股吞天噬地、混沌未分的太古凶威。傳聞牠隨地流竄、無\n"
		"有定所，須以上古印記方能封鎮——如今少俠以渾沌印記將牠自七彩石\n"
		"中重新招出，要降的，正是這頭天地初開、七彩混沌的太古之獸。牠\n"
		"未動分毫，那股混沌磅礡的太古神威，已教人周身百骸俱為之一寒。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"渾沌獸混沌的巨軀倏地暴漲，七彩的混沌之力如怒濤般絞捲而出，連空間都被攪得扭曲變形！\n",
		"渾沌獸那雙深不見底的眸子驟然爆出七彩混沌之光，一爪烙空撈來，所過之處虛實莫辨、焦痕宛然！\n",
		"渾沌獸周身的七彩混沌之氣猛地一縮、復又轟然炸開，化作一片吞天噬地的混沌風暴，四下激射而出！\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者；迄今最高）。
	set("bounty", ([
		"survive"         : 1800,
		"unarmed mastery" : 220,
		"martial art"     : 120,
		"martial mastery" : 96,
		"combat"          : 105,
	]));
}

// 既被自七彩石招出便奉戰到底，然不主動撲噬（招喚門禁已把關）。
int accept_fight(object ob)
{
	do_chat((: command, "say 渾沌獸那雙深不見底的眸子驟然爆出七彩混沌之光，混沌的巨軀如怒濤般迎向膽敢將牠自七彩石招出的來人！" :));
	return 1;
}

// 死亡：第七章掉印機制。確定性 guard：唯身負第七章旗標(main_canon7==1、尚未推進)、身上
// 尚無渾沌之心的真實玩家方推進+掉印（防重複）。
//   (1) 先推進 main_canon7 1->2（務必置於 ::die() 之前——承 lesson #10）。
//   (2) 恒呼 ::die()（屍體生成、登錄 temp("corpse")）。
//   (3) 掉渾沌之心入屍（置於 ::die() 之後、函式最末）。
void die()
{
	object killer;
	int drop;

	killer = last_damage_giver();
	drop = 0;   // 本次死亡是否該推進+掉渾沌之心。

	// 確定性 guard：下手者須為身負第七章旗標(==1、尚未推進)的真實玩家，且身上尚無渾沌
	// 之心——已推進(main_canon7>=2)或已持心者重殺不再掉。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon7") == 1
	&&	!present("chaos heart", killer) )
		drop = 1;

	// (1) 推進 main_canon7 1->2（務必置於 ::die() 之前——承 lesson #10：::die() 後同函
	//     式其後碼不保證續行；推進旗標是「要緊事」，須在 ::die() 之前做完）。
	if( drop )
		killer->set("quest/main_canon7", 2);

	// (2) 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼，不可略；屍體於此生成並登錄
	//     temp("corpse")）。
	::die();

	// (3) 掉渾沌之心：唯本次死亡合格(drop==1)時掉入屍身。置於函式最末（::die() 殿其前；
	//     掉物本身不再有後續要緊邏輯——::die()-LAST 範式，承 lesson #10）。
	if( drop )
		chaosbeast_drop_loot(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
