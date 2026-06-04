// diling_spirit.c -- 地靈，正史主線第八章「地靈任務」地氣塔頂之終局靈。
//
// 設定（承接 canon 主線樹 docs 05 L62-64「地靈任務 → 悍地斧(twohanded axe) + heart」；江
//   隕第八章交差所伏「登地氣塔頂解悍地斧與一枚『心』」之 lead；docs 列的火雷風雨四神武器
//   /聖木殘根→炎日箭→太陽槍 物鏈乃敘事鋪陳，已抽象入江隕對白，本檔不另造）：
//   京畿地脈所鍾、地氣磅礡之處，矗著一座上古的地氣塔；塔頂之上盤踞著一頭司一方地氣的地
//   靈，通體流轉著沉雄土光。少俠降盡渾沌獸、持渾沌之心與星光環而來，引動地氣，將這地靈
//   招出而降之——伏誅之際，自牠那一點未散的地氣中，凝出『地靈之心』並落下地靈所掌的神兵
//   『悍地斧』。
//
// 設計（boss-tier：lvl 57。與渾沌獸同階、為天靈/地靈二靈中之較強者——以「一頭須武藝精純
//      且有備而來方克的強力高階 NPC」呈現即可，不另造戰鬥 efun，鏡 chaosbeast/firegod）：
//   * level 57；unarmed 215 / parry 205 / dodge 200 / force 240——以地靈一縷厚土之力、沉雄
//     地氣搏殺、不持兵器(unarmed 主戰)。
//   * 三圍真氣 advance_stat gin/kee/sen 600/730/660——厚土之靈，血(kee)尤厚。
//   * accept_fight 回傳 1——既被地氣引動招出便奉戰到底，然不主動撲噬。
//
// 任務推進（die()）——第八章地靈掉物機制（承 chaosbeast.c/tianling_spirit.c 範式 + lesson
//   #10「::die()-LAST」、lesson #1「__DIR__ 已含 npc/ 尾斜線，掉物路徑為 __DIR__"obj/x"」）：
//   地靈伏誅時，若下手者(last_damage_giver)是身負第八章旗標(quest/main_canon8 == 2、天靈已
//   斃)的真實玩家(userp)、且身上尚無地靈之心(防重複)：
//     (1) 先推進 main_canon8 2 → 3（務必置於 ::die() 之前——承 lesson #10）。
//     (2) 恒呼 ::die()（屍體於此生成並登錄 temp("corpse")）。
//     (3) 自屍身掉『地靈之心』(__DIR__"obj/earth_heart") + 『悍地斧』(__DIR__"obj/quake_axe")，
//         置於 ::die() 之後（屍體已生成）、函式最末。
//   防重複掉物（確定性 guard）：唯 main_canon8==2、身上尚無地靈之心者方掉。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 掉落「地靈之心」+「悍地斧」入屍。who=下手者(真實玩家)；於 ::die() 之後呼叫，corpse 已
// 存在於 temp("corpse")。掉物路徑 __DIR__"obj/x"——__DIR__ 已含 npc/ 尾斜線(本檔在 npc/)，
// 故為 obj/ 非 npc/obj/(承 lesson #1)。確定性 guard 已於 die() 內判妥，此處僅負責掉物。
void diling_drop_loot(object who)
{
	object corpse, heart, axe;

	if( !who ) return;

	corpse = query_temp("corpse");

	heart = new(__DIR__"obj/earth_heart");
	if( objectp(heart) ) {
		if( !objectp(corpse) || !heart->move(corpse) )
			heart->move(environment());
	}

	axe = new(__DIR__"obj/quake_axe");
	if( objectp(axe) ) {
		if( !objectp(corpse) || !axe->move(corpse) )
			axe->move(environment());
	}

	message_vision(
		HIY "地靈發出一聲沉雄的悶吼，那一身流轉的沉雄土光倏地暴漲到極處、又驟然向"
		"內崩塌——只見那渾厚的靈軀自心口處層層潰散、化作漫天黃濛的土光四下飛濺、湮"
		"入虛空，自牠湮滅處那一點未散的地氣中，緩緩凝出一枚通體流轉著沉雄土光的奇"
		"心，連同牠所掌的那柄巨斧，一同落入了地靈的遺蛻之中——那便是了結厚土之靈的"
		"鐵證『地靈之心』，與地靈所遺的神兵『悍地斧』了！\n" NOR);
}

void create()
{
	set_name(HIY "地靈" NOR,
		({ "diling", "earth spirit", "spirit" }) );
	set("nickname", "厚土之靈");
	set_attr("str", 38);
	set_attr("dex", 36);
	set_attr("int", 30);
	set_attr("wis", 30);
	set_attr("spi", 37);
	set_attr("con", 38);
	set_attr("cor", 33);
	set_race("human");
	set_level(57);
	set_class("fighter");
	set("sect", "地靈");
	set("rank", "厚土之靈");

	// boss-tier：以地靈一縷厚土之力、沉雄地氣搏殺、不持兵器(unarmed 主戰)。與渾沌獸同階。
	set_skill("unarmed", 215);
	set_skill("parry", 205);
	set_skill("dodge", 200);
	set_skill("force", 240);

	// 厚土之靈：血(kee)尤厚。
	advance_stat("gin", 600);
	advance_stat("kee", 730);
	advance_stat("sen", 660);

	set("gender", "male");
	set("age", 99999);
	set("long",
		"這便是地氣塔頂那司一方地氣的地靈了。牠那一團渾厚的靈軀並\n"
		"無定形，通體流轉著一層沉雄的土光，黃濛起伏，將凝未凝、將散\n"
		"未散，彷彿一整方厚重的大地都絞縮進了牠這一具身軀之中。牠周\n"
		"身那沉雄的地氣無風自湧，所立之處連塔石都隱隱震顫、塵土簌簌\n"
		"而落；牠那一張渾厚的面孔上隱隱睜著一雙深沉如淵的眸子，睥睨\n"
		"之間，自有一股鎮壓四方、沉雄磅礡的厚土神威。傳聞牠盤踞地氣\n"
		"塔頂、上應地脈之所，須以磅礡地氣方能引動——如今少俠以渾沌之\n"
		"心、星光環引動了地氣，要降的，正是這頭司一方地氣的地靈。牠\n"
		"未動分毫，那股沉雄磅礡的厚土神威，已教人周身百骸俱為之一沉。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"地靈渾厚的靈軀倏地暴漲，沉雄的地氣如怒濤般絞捲而出，連塔石都被震得簌簌崩落！\n",
		"地靈那雙深沉如淵的眸子驟然爆出黃濛土光，一掌沉沉拍落，所過之處地動山搖、裂土崩石！\n",
		"地靈周身的沉雄地氣猛地一縮、復又轟然炸開，化作一片鎮壓四方的地氣風暴，四下激射而出！\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者；與渾沌獸同階）。
	set("bounty", ([
		"survive"         : 1800,
		"unarmed mastery" : 220,
		"martial art"     : 120,
		"martial mastery" : 96,
		"combat"          : 105,
	]));
}

// 既被地氣引動招出便奉戰到底，然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 地靈那雙深沉如淵的眸子驟然爆出黃濛土光，渾厚的靈軀如怒濤般迎向膽敢引動地氣、將牠自地氣塔頂招出的來人！" :));
	return 1;
}

// 死亡：第八章地靈掉物機制。確定性 guard：唯下手者為身負第八章旗標(main_canon8==2、天靈
// 已斃)、身上尚無地靈之心的真實玩家方推進+掉物（防重複）。
//   (1) 先推進 main_canon8 2 → 3（務必置於 ::die() 之前——承 lesson #10）。
//   (2) 恒呼 ::die()（屍體生成、登錄 temp("corpse")）。
//   (3) 掉地靈之心+悍地斧入屍（置於 ::die() 之後、函式最末）。
void die()
{
	object killer;
	int drop;

	killer = last_damage_giver();
	drop = 0;   // 本次死亡是否該推進+掉物。

	// 確定性 guard：下手者須為身負第八章旗標(==2、天靈已斃、尚未推進)的真實玩家，且身上
	// 尚無地靈之心——尚未斃天靈(main_canon8<2)、已推進(==3)或已持心者重殺不再掉。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon8") == 2
	&&	!present("earth heart", killer) )
		drop = 1;

	// (1) 推進 main_canon8 2 → 3（務必置於 ::die() 之前——承 lesson #10：::die() 後同函式
	//     其後碼不保證續行；推進旗標是「要緊事」，須在 ::die() 之前做完）。
	if( drop )
		killer->set("quest/main_canon8", 3);

	// (2) 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼，不可略；屍體於此生成並登錄
	//     temp("corpse")）。
	::die();

	// (3) 掉地靈之心+悍地斧：唯本次死亡合格(drop==1)時掉入屍身。置於函式最末（::die()
	//     殿其前——::die()-LAST 範式，承 lesson #10）。
	if( drop )
		diling_drop_loot(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
