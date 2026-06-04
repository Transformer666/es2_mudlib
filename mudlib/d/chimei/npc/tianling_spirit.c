// tianling_spirit.c -- 天靈，正史主線第八章「天靈任務」赤魈村許願池之終局靈。
//
// 設定（承接 canon 主線樹 docs 05 L59-60「天靈任務(赤魈村許願池) → 天命刃(dagger of
//   fate) + eye」；江隕第八章交差所伏「往赤魈村許願池解天命刃與一枚『眼』」之 lead）：
//   赤魈村後那一泓終年不涸、天地靈氣所鍾的許願池，上應天靈之所；池上盤踞著一頭司一方
//   天命的天靈，通體流轉著澄澈天光、星河微芒。少俠降盡渾沌獸、持渾沌之心與星光環而來，
//   引動池水，將這天靈招出而降之——伏誅之際，自牠那一點未散的靈光中，凝出『天靈之眼』
//   並落下天靈所掌的神兵『天命刃』。
//
// 設計（boss-tier：lvl 56。較渾沌獸(lvl57)稍遜、與其同階——以「一頭須武藝精純且有備而來
//      方克的強力高階 NPC」呈現即可，不另造戰鬥 efun，鏡 chaosbeast/firegod 之做法）：
//   * level 56；unarmed 210 / parry 200 / dodge 200 / force 235——以天靈一縷司命之力、星
//     河天光搏殺、不持兵器(unarmed 主戰)。
//   * 三圍真氣 advance_stat gin/kee/sen 590/700/650——天命之靈，神(sen)尤厚。
//   * accept_fight 回傳 1——既被許願池引動招出便奉戰到底，然不主動撲噬。
//
// 任務推進（die()）——第八章天靈掉物機制（承 chaosbeast.c 範式 + lesson #10「::die()-LAST」、
//   lesson #1「__DIR__ 已含 npc/ 尾斜線，掉物路徑為 __DIR__"obj/x" 非 "npc/obj/x"」）：
//   天靈伏誅時，若下手者(last_damage_giver)是身負第八章旗標(quest/main_canon8 >= 1、尚未
//   推進至 2)的真實玩家(userp)、且身上尚無天靈之眼(防重複)：
//     (1) 先推進 main_canon8 → 2（務必置於 ::die() 之前——承 lesson #10）。
//     (2) 恒呼 ::die()（屍體於此生成並登錄 temp("corpse")）。
//     (3) 自屍身掉『天靈之眼』(__DIR__"obj/sky_eye") + 『天命刃』(__DIR__"obj/fate_dagger")，
//         置於 ::die() 之後（屍體已生成）、函式最末。
//   防重複掉物（確定性 guard）：唯 main_canon8>=1 且 <2、身上尚無天靈之眼者方掉。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 掉落「天靈之眼」+「天命刃」入屍。who=下手者(真實玩家)；於 ::die() 之後呼叫，corpse 已
// 存在於 temp("corpse")。掉物路徑 __DIR__"obj/x"——__DIR__ 已含 npc/ 尾斜線(本檔在 npc/)，
// 故為 obj/ 非 npc/obj/(承 lesson #1)。確定性 guard 已於 die() 內判妥，此處僅負責掉物。
void tianling_drop_loot(object who)
{
	object corpse, eye, dagger;

	if( !who ) return;

	corpse = query_temp("corpse");

	eye = new(__DIR__"obj/sky_eye");
	if( objectp(eye) ) {
		if( !objectp(corpse) || !eye->move(corpse) )
			eye->move(environment());
	}

	dagger = new(__DIR__"obj/fate_dagger");
	if( objectp(dagger) ) {
		if( !objectp(corpse) || !dagger->move(corpse) )
			dagger->move(environment());
	}

	message_vision(
		HIC "天靈發出一聲清越的長吟，那一身流轉的澄澈天光倏地暴漲到極處、又驟然"
		"向內崩塌——只見那渾圓的靈軀自心口處層層潰散、化作點點星河般的微芒四下飛"
		"濺、湮入虛空，自牠湮滅處那一點未散的靈光中，緩緩凝出一枚通體流轉著澄澈天"
		"光的奇眼，連同牠所掌的那柄短刃，一同落入了天靈的遺蛻之中——那便是了結天命"
		"之靈的鐵證『天靈之眼』，與天靈所遺的神兵『天命刃』了！\n" NOR);
}

void create()
{
	set_name(HIC "天靈" NOR,
		({ "tianling", "sky spirit", "spirit" }) );
	set("nickname", "天命之靈");
	set_attr("str", 37);
	set_attr("dex", 37);
	set_attr("int", 32);
	set_attr("wis", 32);
	set_attr("spi", 38);
	set_attr("con", 37);
	set_attr("cor", 33);
	set_race("human");
	set_level(56);
	set_class("fighter");
	set("sect", "天靈");
	set("rank", "天命之靈");

	// boss-tier：以天靈一縷司命之力、星河天光搏殺、不持兵器(unarmed 主戰)。較渾沌獸稍遜、同階。
	set_skill("unarmed", 210);
	set_skill("parry", 200);
	set_skill("dodge", 200);
	set_skill("force", 235);

	// 天命之靈：神(sen)尤厚。
	advance_stat("gin", 590);
	advance_stat("kee", 700);
	advance_stat("sen", 650);

	set("gender", "male");
	set("age", 99999);
	set("long",
		"這便是赤魈村許願池上那司一方天命的天靈了。牠那一團渾圓的\n"
		"靈軀並無定形，通體流轉著一層澄澈的天光，明滅迴盪，將凝未凝、\n"
		"將散未散，彷彿一汪天地初判時的清靈之氣盡凝於這一具身軀之中。\n"
		"牠周身那澄澈的天光無風自漾，眼瞳深處有星河般的微芒明滅流轉，\n"
		"睥睨之間，自有一股司掌天命、高遠莫測的清越神威。傳聞牠盤踞許\n"
		"願池上、上應天靈之所，須以天地靈氣方能引動——如今少俠以渾沌之\n"
		"心、星光環引動了池水，要降的，正是這頭司一方天命的天靈。牠未\n"
		"動分毫，那股高遠清越的神威，已教人周身百骸俱為之一肅。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"天靈渾圓的靈軀倏地暴漲，澄澈的天光如星河般絞捲而出，所過之處清越刺骨！\n",
		"天靈眼瞳深處的星河微芒驟然爆亮，一縷司命之力凌空斫來，宛若天命已定、無可閃避！\n",
		"天靈周身的澄澈天光猛地一縮、復又轟然炸開，化作一片星河傾瀉的天光風暴，四下激射而出！\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive"         : 1700,
		"unarmed mastery" : 215,
		"martial art"     : 116,
		"martial mastery" : 92,
		"combat"          : 100,
	]));
}

// 既被許願池引動招出便奉戰到底，然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 天靈眼瞳深處的星河微芒驟然爆亮，渾圓的靈軀如星河傾瀉般迎向膽敢引動池水、將牠自許願池招出的來人！" :));
	return 1;
}

// 死亡：第八章天靈掉物機制。確定性 guard：唯下手者為身負第八章旗標(main_canon8>=1 且 <2、
// 尚未推進)、身上尚無天靈之眼的真實玩家方推進+掉物（防重複）。
//   (1) 先推進 main_canon8 → 2（務必置於 ::die() 之前——承 lesson #10）。
//   (2) 恒呼 ::die()（屍體生成、登錄 temp("corpse")）。
//   (3) 掉天靈之眼+天命刃入屍（置於 ::die() 之後、函式最末）。
void die()
{
	object killer;
	int drop;

	killer = last_damage_giver();
	drop = 0;   // 本次死亡是否該推進+掉物。

	// 確定性 guard：下手者須為身負第八章旗標(>=1 且 <2、尚未推進)的真實玩家，且身上尚無
	// 天靈之眼——已推進(main_canon8>=2)或已持眼者重殺不再掉。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon8") >= 1
	&&	killer->query("quest/main_canon8") < 2
	&&	!present("sky eye", killer) )
		drop = 1;

	// (1) 推進 main_canon8 → 2（務必置於 ::die() 之前——承 lesson #10：::die() 後同函式
	//     其後碼不保證續行；推進旗標是「要緊事」，須在 ::die() 之前做完）。
	if( drop )
		killer->set("quest/main_canon8", 2);

	// (2) 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼，不可略；屍體於此生成並登錄
	//     temp("corpse")）。
	::die();

	// (3) 掉天靈之眼+天命刃：唯本次死亡合格(drop==1)時掉入屍身。置於函式最末（::die()
	//     殿其前——::die()-LAST 範式，承 lesson #10）。
	if( drop )
		tianling_drop_loot(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
