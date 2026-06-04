// hanba.c -- 旱魃(原鬼)，正史主線第五章「四鬼任務」山林川原四鬼之首惡、最強一頭。
//            卯天樹下封印之地(/d/skysnow/tree.c)開封後現身的四鬼之一。
//
// 設定（承接 docs 01-神話與創世 L44-47/L76：山海經山林川原四鬼，元神之鬼、長生
//   不滅；并接第四章守木尊者所言——京畿聖木之節既斷、鎮鬼封印一鬆，四鬼應劫而
//   出）：
//   旱魃乃山海經所載之「原鬼」，是寒於氏元神所化的元神之鬼，長生不滅，與赤魈
//   (山鬼)、青蛛(林鬼)、濁魚(川鬼)同被鎮封於卯天樹下亙古的封印之中。三百年來
//   封印鎮鬼，四鬼沉睡；及至京畿聖木之節為巨蜈蝕斷，鎮鬼的封印一鬆，少俠持四
//   鬼招喚環於卯天樹下開那封印，四鬼盡數現身——旱魃據原而生，所過赤地千里、戾氣
//   最盛，乃這四鬼之中最強的壓軸一頭。
//
// 設計（boss-tier：四鬼之首惡，lvl 50——四鬼以旱魃(原鬼)為最強，赤魈/青蛛/濁魚
//      (lvl46~47)依次稍遜；旱魃乃須有備而來、武藝精純方能克的最強高階 NPC）：
//   * level 50；unarmed 185 / parry 172 / dodge 165 / force 188——以元神之鬼的焦
//     土戾氣搏殺、不持兵器(unarmed 主戰)，str 為最、諸圍俱高。
//   * 三圍真氣 advance_stat gin/kee/sen 420/440/440——四鬼最強，較赤魈尤厚，長生
//     不滅之鬼血(kee)、神(sen)更勝一籌。
//   * accept_fight 回傳 1——封印既開、奉陪到底，然不主動撲噬(玩家自行 kill 起釁；
//     卯天樹開封機制已就 quest/main_canon5 與招喚環把關，此即安全閥)。
//   * boss 特技逾本檔範疇——以「一頭最強高階 NPC」呈現即可，不另造戰鬥 efun(鏡
//     moyun/huitiangui/skeleton_king 之做法)。
//
// 任務推進（die()）——四鬼共用之 kill-counter 機制：
//   旱魃伏誅時，若下手者(last_damage_giver)是身負第五章旗標(quest/main_canon5 >= 1)
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
void hanba_drop_starlight(object who)
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
	set_name(HIY "旱魃" NOR, ({ "hanba", "plain ghost", "drought" }) );
	set("nickname", "原鬼");
	set_attr("str", 36);
	set_attr("dex", 32);
	set_attr("int", 26);
	set_attr("wis", 24);
	set_attr("spi", 33);
	set_attr("con", 35);
	set_attr("cor", 30);
	set_race("human");
	set_level(50);
	set_class("fighter");
	set("sect", "山林川原");
	set("rank", "原鬼");

	// boss-tier：以元神之鬼的焦土戾氣搏殺、不持兵器(unarmed 主戰)，四鬼最強。
	set_skill("unarmed", 185);
	set_skill("parry", 172);
	set_skill("dodge", 165);
	set_skill("force", 188);

	// 四鬼最強之鬼：血(kee)、神(sen)較赤魈尤厚。
	advance_stat("gin", 420);
	advance_stat("kee", 440);
	advance_stat("sen", 440);

	set("gender", "female");
	set("age", 3000);
	set("long",
		"這便是山海經所載、長生不滅的原鬼『旱魃』了。牠是一頭乾枯如\n"
		"焦炭的人形旱鬼，通體覆著一層龜裂如赤地的焦褐枯皮，那皮膚乾\n"
		"皺龜裂，紋路間滲著陣陣灼人的熱浪，所立之處方圓丈許的草木盡\n"
		"皆焦黃枯萎、寸寸凋亡。牠一身瘦骨嶙峋卻力大無窮，一雙深陷的\n"
		"鬼眼燃著兩簇焦黃的死火，周身浮動著一層扭曲的熱氣，連空氣都\n"
		"被烤得隱隱蒸騰、波動變形。牠所過之處赤地千里、滴水不存，那\n"
		"是亙古不滅、最是酷烈的焦土殺戾之氣。三百年前牠與赤魈、青\n"
		"蛛、濁魚同被鎮封於這卯天樹下的封印之中，沉睡至今；如今封印\n"
		"一鬆，牠這據原之鬼戾氣最盛、氣力最沉，正是這四鬼之中最強的\n"
		"壓軸一頭。\n");
	set("chat_chance_combat", 4);
	set("chat_msg_combat", ({
		"旱魃周身焦熱的死火驟然暴漲，挾著赤地千里的酷烈熱浪當頭蒸落，所及之處草木立時焦枯！\n",
		"旱魃那雙焦黃的死火鬼眼暴盛，一雙龜裂的枯骨厲爪如灼鐵般撈來，灼人的熱氣撲面欲焚！\n",
		"旱魃乾枯的身形猛地一震，腳下的地皮霎時龜裂乾涸、騰起一片焦土熱浪，挾著殺戾轟然席捲！\n",
	}));
	setup();

	// 尋常戰鬥經驗（由 ::die() 結算給下手者）——四鬼最強，bounty 較赤魈尤厚。
	set("bounty", ([
		"survive"         : 900,
		"unarmed mastery" : 150,
		"martial art"     : 80,
		"martial mastery" : 64,
		"combat"          : 70,
	]));
}

// 封印既開、奉陪到底，然不主動撲噬。
int accept_fight(object ob)
{
	do_chat((: command, "say 旱魃那雙焦黃的死火鬼眼倏地暴漲，據原而生的酷烈殺戾化作赤地焦浪，鋪天蓋地迎向膽敢開這封印的來人！" :));
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
				HIY "旱魃發出一聲淒厲的長嘯，那具焦炭般的乾枯之軀自胸腹處龜"
				"裂崩解，焦褐的枯皮一片片寸寸碎裂、剝落，周身那層酷烈的焦土熱"
				"浪終於徹底熄滅。這旱魃乃四鬼之中戾氣最盛、最強的壓軸一頭，$N"
				"連牠也一併誅了——卯天樹下的四鬼之患，至此已盡去矣！\n" NOR,
				killer);

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
		hanba_drop_starlight(killer);
}

// vim: set ts=4 sw=4 syntax=lpc
