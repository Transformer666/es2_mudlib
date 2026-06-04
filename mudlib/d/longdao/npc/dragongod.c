// dragongod.c -- 天龍，正史主線第六章「四神任務」天龍島四神之一（島主）。
//
// 設定（承接 docs 05 L52-54 四神任務 火/天龍/雷/風；docs 05 L145-152 天龍攻略——會招
//   guardian 八次、berserk、吸精吸神、持久戰；江隕 L108 所言：天龍之力與星光環四道
//   古篆同源，集四神完整封印嵌入星光環另有造化）：
//   天龍是天龍島之主、司東方青木震雷的真龍之神，翻江倒海、吞雲吐霧。三百年前山林
//   川原四鬼既封於卯天樹下，四方元素神祇之力便分鎮天龍島上——少俠誅盡四鬼、得了那
//   枚星光環，循環上四道古篆之引、自檒城望安港渡海登天龍島，要將鎮島的火、天龍、
//   雷、風四神一一降伏，取其完整神印嵌入星光環。天龍乃這四神之主，盤踞天龍島最深
//   的龍淵，一身龍息磅礡如海。
//
// 設計（boss-tier：四神之主，lvl 52。四神以風神/雷神為最強(lvl 54/55)，火神/天龍
//      (lvl 50/52)稍遜——皆係須有備而來、武藝精純方能克的強力高階 NPC）：
//   * level 52；unarmed 200 / parry 195 / dodge 185 / force 220——以真龍之爪牙、龍息
//     搏殺、不持兵器(unarmed 主戰)。
//   * 三圍真氣 advance_stat gin/kee/sen 500/600/540——真龍之神，血(kee)、神(sen)俱厚。
//   * accept_fight 回傳 1——登島挑戰、奉陪到底，然不主動撲噬(登島門禁已把關)。
//   * boss 特技(招 guardian/berserk/吸精吸神/持久戰)逾本檔範疇——以「一頭強力高階
//     NPC」呈現即可，不另造戰鬥 efun(鏡 chixiao/moyun 之做法)。
//
// 任務推進（die()）——四神共用之掉印機制：見 firegod.c 之說明。天龍伏誅、下手者合格
//   (main_canon6>=1 之真實玩家、身上無天龍之印、尚未嵌天龍之印 main_canon6_seal_
//   dragon != 1)時，於 ::die() 之後自屍身掉「天龍之印」(npc/obj/seal_dragon)。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 掉落完整神印「天龍之印」。who=下手者(真實玩家)；於 ::die() 之後呼叫，corpse 已存
// 在於 temp("corpse")。確定性 guard 已於 die() 內判妥，此處僅負責掉印。
void dragongod_drop_seal(object who)
{
	object corpse, loot;

	if( !who ) return;

	loot = new(__DIR__"obj/seal_dragon");
	if( !objectp(loot) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIC "天龍發出一聲撼天動地的悲鳴，那盤踞龍淵的萬丈龍軀自龍睛處迸裂"
		"開來、層層化作青碧的水霧消散——自牠湮滅處那一身不滅的龍息中，緩緩凝"
		"出一枚通體流轉著青碧龍芒的神印，落入了天龍的遺蛻之中。那便是了結這"
		"東方震雷之主的鐵證『天龍之印』了——四神之印，又得其一！\n" NOR);
}

void create()
{
	set_name(HIC "天龍" NOR,
		({ "dragongod", "dragon", "god" }) );
	set("nickname", "島主");
	set_attr("str", 36);
	set_attr("dex", 34);
	set_attr("int", 30);
	set_attr("wis", 28);
	set_attr("spi", 34);
	set_attr("con", 36);
	set_attr("cor", 31);
	set_race("human");
	set_level(52);
	set_class("fighter");
	set("sect", "四神");
	set("rank", "天龍");

	// boss-tier：以真龍之爪牙、龍息搏殺、不持兵器(unarmed 主戰)。
	set_skill("unarmed", 200);
	set_skill("parry", 195);
	set_skill("dodge", 185);
	set_skill("force", 220);

	// 真龍之神：血(kee)、神(sen)俱厚。
	advance_stat("gin", 500);
	advance_stat("kee", 600);
	advance_stat("sen", 540);

	set("gender", "male");
	set("age", 8000);
	set("long",
		"這便是天龍島之主、司東方青木震雷的天龍了。牠那一條萬丈龍\n"
		"軀盤踞在島心最深的龍淵之上，通體覆著青碧如玉的龍鱗，鱗光流\n"
		"轉，明滅如海面的粼粼波光；龍首高昂，雙角崢嶸，一蓬蓬墨綠的\n"
		"龍鬚在身畔的水霧裡無風自動。牠每一次吞吐，便有翻江倒海的龍\n"
		"息自鼻間噴湧而出，捲起滿島的雲霧；那一雙龍睛深邃如淵，睥睨\n"
		"之間，自有一股吞雲吐霧、號令四方的真龍之威。三百年前山林川\n"
		"原四鬼既封於卯天樹下，這司震雷的島主便鎮在這天龍島最深的龍\n"
		"淵；如今少俠循星光環之引渡海而來，要降的，正是這頭翻雲覆\n"
		"雨、磅礡如海的真龍之神。牠盤龍未動，那股壓下來的萬鈞龍威，\n"
		"已教人喘息為之一窒。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"天龍龍首一昂，翻江倒海的龍息自鼻間轟然噴湧，挾著漫天水霧當頭撲落！\n",
		"天龍那一雙深邃如淵的龍睛驟然爆出青芒，萬丈龍軀如怒濤般絞來，鱗甲森然蔽空！\n",
		"天龍尾掃千鈞，龍淵的水被牠攪得騰空而起，化作一道排山倒海的青碧水龍激射而出。\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive"         : 1300,
		"unarmed mastery" : 195,
		"martial art"     : 105,
		"martial mastery" : 84,
		"combat"          : 92,
	]));
}

// 登島挑戰、奉陪到底，然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 天龍那一雙深邃如淵的龍睛驟然爆出青芒，翻江倒海的龍息如怒濤般迎向膽敢渡海登島的來人！" :));
	return 1;
}

// 死亡：恒呼 ::die()(屍體生成並登錄 temp("corpse"))，再(下手者合格時)擲天龍之印入
// 屍。確定性 guard 同 firegod.c：唯身負第六章旗標(>=1)、身上尚無天龍之印、且尚未嵌
// 天龍之印的真實玩家方掉。
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
	&&	killer->query("quest/main_canon6_seal_dragon") != 1
	&&	!present("dragon seal", killer) )
		drop = 1;

	::die();

	if( drop )
		dragongod_drop_seal(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
