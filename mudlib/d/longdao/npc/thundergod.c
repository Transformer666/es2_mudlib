// thundergod.c -- 雷神(澤獸)，正史主線第六章「四神任務」天龍島四神之一。
//
// 設定（承接 docs 05 L52-54 四神任務 火/天龍/雷/風；docs 05 L154-162 雷神(澤獸)攻略
//   ——瘋狂 SR、只能打精/神、kee<50% 立刻新生、會 berserk、結印脫離補滿；江隕 L108
//   所言：雷神之力與星光環四道古篆同源，集四神完整封印嵌入星光環另有造化）：
//   雷神是天龍島上以澤獸之形顯化的疾雷之神，司北方坎水、九天玄雷。三百年前山林川
//   原四鬼既封於卯天樹下，四方元素神祇之力便分鎮天龍島上——少俠誅盡四鬼、得了那枚
//   星光環，循環上四道古篆之引、自檒城望安港渡海登天龍島，要將鎮島的火、天龍、雷、
//   風四神一一降伏，取其完整神印嵌入星光環。雷神乃這四神之中最是難纏的兩頭之一，
//   一身紫電玄雷、捉摸不定。
//
// 設計（boss-tier：四神之一，lvl 55——四神中與風神並列最強。皆係須有備而來、武藝精
//      純方能克的強力高階 NPC）：
//   * level 55；unarmed 215 / parry 205 / dodge 215 / force 235——以澤獸之爪、玄雷搏
//     殺、不持兵器(unarmed 主戰)；雷神疾如奔雷，dodge 尤高。
//   * 三圍真氣 advance_stat gin/kee/sen 540/560/620——疾雷之神，神(sen)尤厚(司雷、瘋
//     狂 SR)。
//   * accept_fight 回傳 1——登島挑戰、奉陪到底，然不主動撲噬(登島門禁已把關)。
//   * boss 特技(瘋狂 SR/kee<50% 新生/結印補滿)逾本檔範疇——以「一頭強力高階 NPC」呈
//     現即可，不另造戰鬥 efun(鏡 chixiao/moyun 之做法)。
//
// 任務推進（die()）——四神共用之掉印機制：見 firegod.c 之說明。雷神伏誅、下手者合格
//   (main_canon6>=1 之真實玩家、身上無雷神之印、尚未嵌雷神之印 main_canon6_seal_
//   thunder != 1)時，於 ::die() 之後自屍身掉「雷神之印」(npc/obj/seal_thunder)。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 掉落完整神印「雷神之印」。who=下手者(真實玩家)；於 ::die() 之後呼叫，corpse 已存
// 在於 temp("corpse")。確定性 guard 已於 die() 內判妥，此處僅負責掉印。
void thundergod_drop_seal(object who)
{
	object corpse, loot;

	if( !who ) return;

	loot = new(__DIR__"obj/seal_thunder");
	if( !objectp(loot) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIM "雷神周身那一片瘋狂炸響的紫電驟然盡數熄滅——那澤獸之形自獸目處"
		"龜裂崩散、化作漫天細碎的雷光消融——自牠湮滅處那一身不滅的雷光中，緩"
		"緩凝出一枚通體流轉著紫電雷芒的神印，落入了雷神的遺蛻之中。那便是了"
		"結這北方玄雷之神的鐵證『雷神之印』了——四神之印，又得其一！\n" NOR);
}

void create()
{
	set_name(HIM "雷神" NOR,
		({ "thundergod", "thunder", "god" }) );
	set("nickname", "澤獸");
	set_attr("str", 37);
	set_attr("dex", 36);
	set_attr("int", 30);
	set_attr("wis", 29);
	set_attr("spi", 35);
	set_attr("con", 36);
	set_attr("cor", 33);
	set_race("human");
	set_level(55);
	set_class("fighter");
	set("sect", "四神");
	set("rank", "雷神");

	// boss-tier：以澤獸之爪、玄雷搏殺、不持兵器(unarmed 主戰)；疾如奔雷，dodge 尤高。
	set_skill("unarmed", 215);
	set_skill("parry", 205);
	set_skill("dodge", 215);
	set_skill("force", 235);

	// 疾雷之神：神(sen)尤厚（司雷、瘋狂 SR）。
	advance_stat("gin", 540);
	advance_stat("kee", 560);
	advance_stat("sen", 620);

	set("gender", "male");
	set("age", 6000);
	set("long",
		"這便是天龍島上司北方坎水玄雷、以澤獸之形顯化的雷神了。牠\n"
		"形如一頭蜷伏的巨獸，通體覆著青黑泛紫的鱗甲，鱗甲之間時時迸\n"
		"竄出一道道細密的紫電，啪啪炸響，將四下的空氣都灼出一股焦糊\n"
		"的氣味。牠那一雙獸目是兩團疾閃的紫芒，眸光所及，便有一道道\n"
		"九天玄雷劈落；牠周身罡氣狂亂無常，忽而靜如淵潭、忽而暴如奔\n"
		"雷，叫人全然捉摸不定。三百年前山林川原四鬼既封於卯天樹下，\n"
		"這司雷的神祇便鎮在這天龍島上；如今少俠循星光環之引渡海而\n"
		"來，要降的，正是這頭一身紫電、捉摸不定的玄雷之神。牠每一次\n"
		"吐息，周身的紫電便瘋狂炸響一輪，那股疾雷轟頂的赫赫神威，震\n"
		"得人耳鳴目眩、心神俱亂。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"雷神周身的紫電驟然瘋狂炸響，一道粗如兒臂的九天玄雷挾著焦雷之聲當頭劈落！\n",
		"雷神那一雙疾閃的紫芒眸子驟然暴盛，蜷伏的獸軀如奔雷般彈射撲來，紫電裂空！\n",
		"雷神獸吼一聲，周身青黑鱗甲間的紫電盡數迸出，化作一片瘋狂亂竄的雷網四下罩落。\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive"         : 1500,
		"unarmed mastery" : 210,
		"martial art"     : 112,
		"martial mastery" : 90,
		"combat"          : 98,
	]));
}

// 登島挑戰、奉陪到底，然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 雷神周身的紫電驟然瘋狂炸響，九天玄雷如怒濤般迎向膽敢渡海登島的來人！" :));
	return 1;
}

// 死亡：恒呼 ::die()(屍體生成並登錄 temp("corpse"))，再(下手者合格時)擲雷神之印入
// 屍。確定性 guard 同 firegod.c：唯身負第六章旗標(>=1)、身上尚無雷神之印、且尚未嵌
// 雷神之印的真實玩家方掉。
void die()
{
	object killer;
	int drop;

	killer = last_damage_giver();
	drop = 0;

	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon6") >= 1
	&&	killer->query("quest/main_canon6_seal_thunder") != 1
	&&	!present("thunder seal", killer) )
		drop = 1;

	::die();

	if( drop )
		thundergod_drop_seal(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
