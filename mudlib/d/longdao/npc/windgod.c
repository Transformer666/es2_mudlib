// windgod.c -- 風神(大鵬)，正史主線第六章「四神任務」天龍島四神之一。
//
// 設定（承接 docs 05 L52-54 四神任務 火/天龍/雷/風；docs 05 L164-172 風神(大鵬)攻略
//   ——會 berserk、招大鵬、需 charge、補血四次、可隨地招喚；江隕 L108 所言：風神之力
//   與星光環四道古篆同源，集四神完整封印嵌入星光環另有造化）：
//   風神是天龍島上以大鵬之形顯化的罡風之神，司西方兌金、九萬里扶搖罡風。三百年前
//   山林川原四鬼既封於卯天樹下，四方元素神祇之力便分鎮天龍島上——少俠誅盡四鬼、得
//   了那枚星光環，循環上四道古篆之引、自檒城望安港渡海登天龍島，要將鎮島的火、天
//   龍、雷、風四神一一降伏，取其完整神印嵌入星光環。風神乃這四神之中最是難纏的兩
//   頭之一，扶搖萬里、來去如風。
//
// 設計（boss-tier：四神之一，lvl 54——四神中與雷神並列最強。皆係須有備而來、武藝精
//      純方能克的強力高階 NPC）：
//   * level 54；unarmed 210 / parry 200 / dodge 220 / force 230——以大鵬之翼爪、罡風
//     搏殺、不持兵器(unarmed 主戰)；風神來去如風，dodge 尤高。
//   * 三圍真氣 advance_stat gin/kee/sen 530/580/580——罡風之神，氣血神俱厚。
//   * accept_fight 回傳 1——登島挑戰、奉陪到底，然不主動撲噬(登島門禁已把關)。
//   * boss 特技(berserk/招大鵬/charge/補血)逾本檔範疇——以「一頭強力高階 NPC」呈現即
//     可，不另造戰鬥 efun(鏡 chixiao/moyun 之做法)。
//
// 任務推進（die()）——四神共用之掉印機制：見 firegod.c 之說明。風神伏誅、下手者合格
//   (main_canon6>=1 之真實玩家、身上無風神之印、尚未嵌風神之印 main_canon6_seal_
//   wind != 1)時，於 ::die() 之後自屍身掉「風神之印」(npc/obj/seal_wind)。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 掉落完整神印「風神之印」。who=下手者(真實玩家)；於 ::die() 之後呼叫，corpse 已存
// 在於 temp("corpse")。確定性 guard 已於 die() 內判妥，此處僅負責掉印。
void windgod_drop_seal(object who)
{
	object corpse, loot;

	if( !who ) return;

	loot = new(__DIR__"npc/obj/seal_wind");
	if( !objectp(loot) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIW "風神那一雙摶起萬里罡風的大鵬之翼倏地頹然垂落——那大鵬之形自翼"
		"尖處層層化作青白的罡風消散、捲入海天——自牠湮滅處那一身不滅的罡風"
		"中，緩緩凝出一枚通體流轉著青白風芒的神印，落入了風神的遺蛻之中。那"
		"便是了結這西方罡風之神的鐵證『風神之印』了——四神之印，至此盡集！"
		"\n" NOR);
}

void create()
{
	set_name(HIW "風神" NOR,
		({ "windgod", "wind", "roc", "god" }) );
	set("nickname", "大鵬");
	set_attr("str", 37);
	set_attr("dex", 36);
	set_attr("int", 29);
	set_attr("wis", 28);
	set_attr("spi", 35);
	set_attr("con", 36);
	set_attr("cor", 32);
	set_race("human");
	set_level(54);
	set_class("fighter");
	set("sect", "四神");
	set("rank", "風神");

	// boss-tier：以大鵬之翼爪、罡風搏殺、不持兵器(unarmed 主戰)；來去如風，dodge 尤高。
	set_skill("unarmed", 210);
	set_skill("parry", 200);
	set_skill("dodge", 220);
	set_skill("force", 230);

	// 罡風之神：氣血神俱厚。
	advance_stat("gin", 530);
	advance_stat("kee", 580);
	advance_stat("sen", 580);

	set("gender", "male");
	set("age", 7000);
	set("long",
		"這便是天龍島上司西方兌金罡風、以大鵬之形顯化的風神了。牠\n"
		"那一雙巨翼一展，便遮蔽了半邊天空，翼上覆著青白相間的雪羽，\n"
		"羽尖風渦旋轉不休，每一次振翅，便摶起九萬里扶搖直上的滔天罡\n"
		"風，捲得滿島的草木盡數匍匐、海面掀起千層巨浪。牠那一張隱在\n"
		"罡風之後的面容冷峻孤高，一雙鵬目銳利如刀，俯瞰眾生，自有一\n"
		"股摶風九萬里、來去無蹤的逍遙神威。三百年前山林川原四鬼既封\n"
		"於卯天樹下，這司風的神祇便鎮在這天龍島上；如今少俠循星光環\n"
		"之引渡海而來，要降的，正是這頭扶搖萬里、來去如風的罡風之\n"
		"神。牠雙翼未振，那股壓下來的浩浩罡風，已教人立足不穩、衣袂\n"
		"翻飛欲裂。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"風神巨翼倏地一振，九萬里扶搖罡風挾著漫天雪羽當頭捲落，海面掀起千層巨浪！\n",
		"風神那一雙銳利如刀的鵬目驟然暴盛，一雙摶風的巨爪裂空撈來，罡風刮得人面如刀割！\n",
		"風神摶風而起、瞬息已至背後，雙翼一合，化作一道無可閃避的罡風利刃當頭斬落。\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive"         : 1450,
		"unarmed mastery" : 205,
		"martial art"     : 110,
		"martial mastery" : 88,
		"combat"          : 96,
	]));
}

// 登島挑戰、奉陪到底，然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 風神那一雙銳利如刀的鵬目驟然暴漲，九萬里扶搖罡風如怒濤般迎向膽敢渡海登島的來人！" :));
	return 1;
}

// 死亡：恒呼 ::die()(屍體生成並登錄 temp("corpse"))，再(下手者合格時)擲風神之印入
// 屍。確定性 guard 同 firegod.c：唯身負第六章旗標(>=1)、身上尚無風神之印、且尚未嵌
// 風神之印的真實玩家方掉。
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
	&&	killer->query("quest/main_canon6_seal_wind") != 1
	&&	!present("wind seal", killer) )
		drop = 1;

	::die();

	if( drop )
		windgod_drop_seal(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
