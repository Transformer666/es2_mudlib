// firegod.c -- 火神(鳳凰)，正史主線第六章「四神任務」天龍島四神之一。
//
// 設定（承接 docs 05 L52-54 四神任務 火/天龍/雷/風；docs 05 L133-143 火神(鳳凰)攻略
//   ——會 hide、berserk、三昧大業火、補血四次；江隕 L108 所言：火神之力與星光環四道
//   古篆同源，集四神完整封印嵌入星光環另有造化）：
//   火神是天龍島上以鳳凰之形顯化的烈焰之神，司南方離火、三昧真火。三百年前山林川
//   原四鬼既封於卯天樹下，四方元素神祇之力便分鎮天龍島上——少俠誅盡四鬼、得了那枚
//   星光環，循環上四道古篆之引、自檒城望安港渡海登天龍島，要將這鎮島的火、天龍、
//   雷、風四神一一降伏，取其完整神印嵌入星光環。火神乃這四神之中以離火搏殺的一頭，
//   通體烈焰、鳳翼蔽空。
//
// 設計（boss-tier：四神之一，lvl 50。四神以風神/雷神為最強(lvl 54/55)，火神/天龍
//      (lvl 50/52)稍遜——皆係須有備而來、武藝精純方能克的強力高階 NPC）：
//   * level 50；unarmed 195 / parry 185 / dodge 180 / force 210——以鳳凰離火之爪翼
//     搏殺、不持兵器(unarmed 主戰)。
//   * 三圍真氣 advance_stat gin/kee/sen 460/520/500——不滅烈焰之神，血(kee)、神(sen)
//     俱厚。
//   * accept_fight 回傳 1——登島挑戰、奉陪到底，然不主動撲噬(玩家自行 kill 起釁；
//     登島須持星光環、main_canon6>=1，門禁已就此把關，此即安全閥)。
//   * boss 特技(hide/berserk/三昧火/補血)逾本檔範疇——以「一頭強力高階 NPC」呈現即
//     可，不另造戰鬥 efun(鏡 chixiao/moyun 之做法)。
//
// 任務推進（die()）——四神共用之掉印機制：
//   火神伏誅時，若下手者(last_damage_giver)是身負第六章旗標(quest/main_canon6 >= 1)
//   的真實玩家(userp)：於 ::die() 之後自屍身掉落其完整神印「火神之印」(npc/obj/
//   seal_fire)。防重複掉印（確定性 guard）：唯下手者「身上尚無火神之印」且「尚未將
//   火神之印嵌入星光環」(quest/main_canon6_seal_fire != 1)者方掉——已持印或已嵌印者
//   重殺亦不再掉。無須 kill-counter：四片神印 + 星光環嵌入機制即把關進度。
//   ⚠ LPC GOTCHA：::die() 之後 Neolith 屍體方生成並登錄 temp("corpse")，故掉印須置
//     於 ::die() 之後；而 ::die() 後同函式其餘碼仍可續行(掉印置最末，本身不再有後續
//     要緊邏輯)。判旗/取屍/掉印一氣呵成，::die() 殿其前。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 掉落完整神印「火神之印」。who=下手者(真實玩家)；於 ::die() 之後呼叫，corpse 已存
// 在於 temp("corpse")。印入屍身；屍體不存則退置房間地面(防萬一)。確定性 guard 已於
// die() 內判妥（身上無印、尚未嵌印），此處僅負責掉印。
void firegod_drop_seal(object who)
{
	object corpse, loot;

	if( !who ) return;

	loot = new(__DIR__"npc/obj/seal_fire");
	if( !objectp(loot) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIR "火神那一身蔽空的烈焰倏地暴漲、又驟然斂盡——只見那鳳凰之形自尾"
		"羽處層層燃成灰燼、散入海風，自牠湮滅處那一蓬不滅的離火中，緩緩凝出"
		"一枚通體流轉著赤金火芒的神印，落入了火神的遺蛻之中。那便是了結這南"
		"方離火之神的鐵證『火神之印』了——四神之印，已得其一！\n" NOR);
}

void create()
{
	set_name(HIR "火神" NOR,
		({ "firegod", "fire god", "phoenix", "god" }) );
	set("nickname", "鳳凰");
	set_attr("str", 35);
	set_attr("dex", 33);
	set_attr("int", 28);
	set_attr("wis", 26);
	set_attr("spi", 33);
	set_attr("con", 35);
	set_attr("cor", 30);
	set_race("human");
	set_level(50);
	set_class("fighter");
	set("sect", "四神");
	set("rank", "火神");

	// boss-tier：以鳳凰離火之爪翼搏殺、不持兵器(unarmed 主戰)。
	set_skill("unarmed", 195);
	set_skill("parry", 185);
	set_skill("dodge", 180);
	set_skill("force", 210);

	// 不滅烈焰之神：血(kee)、神(sen)俱厚。
	advance_stat("gin", 460);
	advance_stat("kee", 520);
	advance_stat("sen", 500);

	set("gender", "male");
	set("age", 5000);
	set("long",
		"這便是天龍島上司南方離火、以鳳凰之形顯化的火神了。牠周身\n"
		"裹著一蓬蓬蔽空的赤金烈焰，雙翼一振，便有漫天的三昧真火如赤\n"
		"雨般灑落；那一條長長的尾羽燃作九道火舌，在身後獵獵翻捲，所\n"
		"過之處，海風都被燒得扭曲變形。牠那一張人面隱在熊熊火光之\n"
		"後，一雙眸子是兩簇幽深的離火，睥睨眾生，亙古不滅。三百年\n"
		"前山林川原四鬼既封於卯天樹下，這司火的神祇便鎮在這天龍島\n"
		"上；如今少俠循星光環之引渡海而來，要降的，正是這頭通體烈\n"
		"焰、鳳翼蔽空的離火之神。牠周身的高溫遠遠便逼得人汗如雨\n"
		"下、口乾舌燥，那股焚天煮海的赫赫神威，教人望之心驚。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"火神鳳翼倏地一振，漫天的三昧真火如赤雨般當頭潑落，連海水都被燒得騰起白煙！\n",
		"火神那簇幽深的離火眸子驟然暴盛，一雙燃著赤金烈焰的鳳爪裂空撈來，腥熱的火浪撲面！\n",
		"火神周身烈焰猛地一縮、復又轟然炸開，化作一蓬焚天煮海的業火，四下激射而出。\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive"         : 1100,
		"unarmed mastery" : 180,
		"martial art"     : 95,
		"martial mastery" : 76,
		"combat"          : 84,
	]));
}

// 登島挑戰、奉陪到底，然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 火神那簇幽深的離火眸子驟然暴漲，蔽空的烈焰如怒濤般迎向膽敢渡海登島的來人！" :));
	return 1;
}

// 死亡：恒呼 ::die()(屍體於此生成並登錄 temp("corpse"))，再(下手者合格時)擲火神之
// 印入屍。確定性 guard：唯身負第六章旗標(>=1)、身上尚無火神之印、且尚未嵌火神之印
// 的真實玩家方掉(防重複掉印)。
void die()
{
	object killer;
	int drop;

	killer = last_damage_giver();
	drop = 0;   // 本次死亡是否該掉火神之印。

	// 確定性掉印 guard：下手者須為身負第六章旗標(>=1)的真實玩家，且身上尚無火神之
	// 印、尚未將火神之印嵌入星光環(quest/main_canon6_seal_fire != 1)——已持印或已嵌
	// 印者重殺不再掉。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon6") >= 1
	&&	killer->query("quest/main_canon6_seal_fire") != 1
	&&	!present("fire seal", killer) )
		drop = 1;

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼，不可略）。
	// 須先呼 ::die()(屍體於此生成並登錄 temp("corpse"))，再擲火神之印入屍。
	::die();

	// 掉火神之印：唯本次死亡合格(drop==1)時掉入屍身。置於函式最末（::die() 殿其
	// 前；掉印本身不再有後續要緊邏輯）。
	if( drop )
		firegod_drop_seal(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
