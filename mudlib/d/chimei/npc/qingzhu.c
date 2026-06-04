// qingzhu.c -- 青蛛(林鬼)，正史主線第五章「四鬼任務」山林川原四鬼之一。
//              卯天樹下封印之地(/d/skysnow/tree.c)開封後現身的四鬼之一。
//
// 設定（承接 docs 01-神話與創世 L44-47/L76：山海經山林川原四鬼，元神之鬼、長生
//   不滅；并接第四章守木尊者所言——京畿聖木之節既斷、鎮鬼封印一鬆，四鬼應劫而
//   出）：
//   青蛛乃山海經所載之「林鬼」，是寒於氏元神所化的元神之鬼，長生不滅，與赤魈
//   (山鬼)、濁魚(川鬼)、旱魃(原鬼)同被鎮封於卯天樹下亙古的封印之中。三百年來
//   封印鎮鬼，四鬼沉睡；及至京畿聖木之節為巨蜈蝕斷，鎮鬼的封印一鬆，少俠持四
//   鬼招喚環於卯天樹下開那封印，四鬼盡數現身——青蛛據林而生，身法詭譎輕捷，乃
//   這四鬼之中最是飄忽難纏的一頭。
//
// 設計（boss-tier：四鬼之一，lvl 47。四鬼以旱魃(原鬼)為最強(lvl50)，青蛛/赤魈/
//      濁魚 依次相當——皆係須有備而來、武藝精純方能克的強力高階 NPC）：
//   * level 47；unarmed 178 / parry 160 / dodge 172 / force 178——以元神之鬼的毒
//     爪蛛絲搏殺、不持兵器(unarmed 主戰)，dex 為尊、身法飄忽。
//   * 三圍真氣 advance_stat gin/kee/sen 380/400/400——長生不滅之鬼，血(kee)、神
//     (sen)俱厚。
//   * accept_fight 回傳 1——封印既開、奉陪到底，然不主動撲噬(玩家自行 kill 起釁；
//     卯天樹開封機制已就 quest/main_canon5 與招喚環把關，此即安全閥)。
//   * boss 特技逾本檔範疇——以「一頭強力高階 NPC」呈現即可，不另造戰鬥 efun(鏡
//     moyun/huitiangui/skeleton_king 之做法)。
//
// 任務推進（die()）——四鬼共用之 kill-counter 機制：
//   青蛛伏誅時，若下手者(last_damage_giver)是身負第五章旗標(quest/main_canon5 >= 1)
//   的真實玩家(userp)：把其四鬼計數 quest/main_canon5_ghosts +1(封頂於 4)。四鬼盡
//   誅(計數達 4)之際——把 quest/main_canon5 推進為 2，并於 ::die() 之後自屍身掉落
//   終局聖物「星光環」(npc/obj/starlight_ring)。防重複：旗標非 >=1、或計數已達 4
//   者，僅作尋常死亡、不重複推進、不重複掉環。
//   ⚠ LPC GOTCHA：計數 +1 與旗標推進(main_canon5 -> 2)務必置於 ::die() 之前——
//     ::die() 之後 Neolith 不保證其後邏輯續行(承第四章聖木節之教訓：自毀/die 後
//     續碼不執行)；星光環掉落則須置於 ::die() 之後(屆時屍體已生成、登錄 temp
//     ("corpse"))，方掉得進屍身。另設 bounty，由 ::die() 結算給下手者。

#include <npc.h>
#include <ansi.h>

inherit F_VILLAGER;

// 四鬼總數——四鬼盡誅(計數達此數)即推進 main_canon5 1->2、掉星光環。
#define GHOST_TOTAL   4

// 掉落終局聖物：星光環。who=下手者(真實玩家)；於 ::die() 之後呼叫，corpse 已存在
// 於 temp("corpse")。星光環置入屍身；屍體不存則退置房間地面(防萬一)。四鬼之中末
// 一頭被誅者方掉(計數達 GHOST_TOTAL 時)。
void qingzhu_drop_starlight(object who)
{
	object corpse, loot;

	if( !who ) return;

	loot = new(__DIR__"obj/starlight_ring");
	if( !objectp(loot) ) return;

	corpse = query_temp("corpse");
	if( !objectp(corpse) || !loot->move(corpse) )
		loot->move(environment());

	message_vision(
		HIW "山林川原四鬼盡數湮滅的剎那，卯天樹下那座鎮鬼三百年的亙古封印轟"
		"然徹底崩解！只見自那崩解封印的最深處、四鬼元神所化的一點至清之光中，"
		"緩緩誕出一枚通體流轉著星河微芒的奇環——那便是了結這四鬼之患的鐵證、亦"
		"是日後再戰侮天鬼的終局之鑰『星光環』了！\n" NOR);
}

void create()
{
	set_name(HIG "青蛛" NOR, ({ "qingzhu", "forest ghost", "spider" }) );
	set("nickname", "林鬼");
	set_attr("str", 28);
	set_attr("dex", 34);
	set_attr("int", 28);
	set_attr("wis", 22);
	set_attr("spi", 31);
	set_attr("con", 30);
	set_attr("cor", 26);
	set_race("human");
	set_level(47);
	set_class("fighter");
	set("sect", "山林川原");
	set("rank", "林鬼");

	// boss-tier：以元神之鬼的毒爪蛛絲搏殺、不持兵器(unarmed 主戰)，身法飄忽輕捷。
	set_skill("unarmed", 178);
	set_skill("parry", 160);
	set_skill("dodge", 172);
	set_skill("force", 178);

	// 長生不滅之鬼：血(kee)、神(sen)俱厚。
	advance_stat("gin", 380);
	advance_stat("kee", 400);
	advance_stat("sen", 400);

	set("gender", "male");
	set("age", 3000);
	set("long",
		"這便是山海經所載、長生不滅的林鬼『青蛛』了。牠是一頭碩大如\n"
		"磨盤的青色巨蛛之鬼，通體覆著一層幽幽泛光的青碧硬殼，八條覆\n"
		"著細密棘刺的長足細而修長，行動間悄無聲息，倏忽便已自一處飄\n"
		"忽掠至另一處。牠那一張蛛面似人非人，數隻深陷的青芒鬼眼冷冷\n"
		"映著幽光，一對螯牙間不住滲出墨綠的劇毒涎液，滴落處草木立時\n"
		"枯焦。牠自牠那織滿青絲的林冠垂吊而下，蛛絲縱橫如網、罩定方\n"
		"圓，把這一片林子盡織成了牠的獵場。三百年前牠與赤魈、濁魚、\n"
		"旱魃同被鎮封於這卯天樹下的封印之中，沉睡至今；如今封印一\n"
		"鬆，牠這據林之鬼身法詭譎、毒爪蛛絲難防，是這四鬼裡最飄忽難\n"
		"纏的一頭。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"青蛛八足一錯，幽碧的身形倏地化作一道殘影飄忽掠至，一對淌著墨綠劇毒的螯牙當頭噬落！\n",
		"青蛛口中青絲驟噴，霎時織成漫天黏網兜頭罩落，欲把來人牢牢纏死於這蛛網之中！\n",
		"青蛛數隻青芒鬼眼一齊暴盛，棘刺密布的長足如毒鞭般連環撈刺，腥綠的毒風撲面而來。\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）。
	set("bounty", ([
		"survive"         : 720,
		"unarmed mastery" : 132,
		"martial art"     : 70,
		"martial mastery" : 55,
		"combat"          : 60,
	]));
}

// 封印既開、奉陪到底，然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 青蛛數隻青芒鬼眼倏地暴漲，據林而生的詭譎戾氣化作漫天毒絲，飄忽迎向膽敢開這封印的來人！" :));
	return 1;
}

// 死亡：四鬼計數 +1（盡誅則推進 main_canon5 1->2），末了恒呼 ::die()，再(末一頭被
// 誅時)擲星光環入屍。
void die()
{
	object killer;
	int n, completed;

	killer = last_damage_giver();
	completed = 0;   // 本次死亡是否「恰為」誅盡四鬼的末一頭——唯此情形方掉星光環。

	// 下手者須為身負第五章旗標(>=1)的真實玩家，方計數（防重複推進與重複掉環）。
	if( objectp(killer)
	&&	killer != this_object()
	&&	userp(killer)
	&&	killer->query("quest/main_canon5") >= 1 )
	{
		n = killer->query("quest/main_canon5_ghosts");
		if( n < GHOST_TOTAL ) {     // 計數封頂於 4：已達 4 者不再 +1，故末一頭唯誅一次。
			n++;
			killer->set("quest/main_canon5_ghosts", n);
			message_vision(
				HIG "青蛛發出一聲尖銳的厲嘯，那具幽碧的巨蛛之軀自蛛腹處蜷縮"
				"乾癟下去，八條棘足一根根抽搐、捲攏、僵硬，數隻青芒鬼眼終於黯"
				"然熄滅。$N誅了這據林而生的林鬼青蛛——卯天樹下的四鬼之患，又去"
				"其一了！\n" NOR, killer);

			// 四鬼盡誅（本次 +1 恰使計數達 4）：把第五章旗標推進 1->2，并記
			// completed=1 以便 ::die() 後掉星光環。旗標推進務必置於 ::die() 之前
			// ——免自毀後續碼不執行致旗標推不到 2（承第四章聖木節之教訓）。
			if( n >= GHOST_TOTAL && killer->query("quest/main_canon5") == 1 ) {
				killer->set("quest/main_canon5", 2);
				completed = 1;
			}
		}
	}

	// 屍體/bounty/善後悉依 std/char/npc.c::die()（恒呼，不可略）。
	// 須先呼 ::die()(屍體於此生成並登錄 temp("corpse"))，再擲星光環入屍。
	::die();

	// 星光環掉落：唯本次死亡恰為誅盡四鬼的末一頭(completed==1)時掉入屍身。
	// 以 completed 局部旗為憑（而非僅查計數/旗標）——確保縱有日後重刷再殺，亦
	// 斷不重複掉環。
	if( completed )
		qingzhu_drop_starlight(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
