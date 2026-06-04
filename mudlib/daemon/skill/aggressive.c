// 怒氣訣 aggressive -- 振武軍營「怒濤先鋒」進階(二轉)所授的內功(基底 FORCE)
//
// docs 載振武軍營統領一脈有「怒氣 aggressive(殺業 1000、berserk 70)：每次消 1 殺業
// 暫提膽臂攻」(見 docs/03-門派與武功/06-軍人-振武大內.md §進階-軍隊統領)。本檔將其
// 實作為一門內功心法(force)﹐使弟子戰鬥時力道能隨內功成長﹐並借 FORCE(/std/force.c)
// 提供的打坐修煉 + valid_enable 共用機制﹔本檔只註冊心法名、登錄中文名、並 override
// cultivate_msg() 提供怒濤先鋒自家的打坐氣象。
//
// 設計(docs未明定其為內功)：docs 將 aggressive 列為「怒氣」狀態(消殺業暫提膽臂攻)﹐
//   屬殺業/業力計分驅動的主動 buff﹔其「消 1 殺業換取暫時膽臂攻加成」屬業力系統 +
//   combat/perform(狀態增益)工作﹐標記為待辦 TODO(同冷梅虎督「拜入天邪」、虎刀鬼才
//   「5000 殺業」之故事/業力門檻)。本檔先把它做成隨修為成長的振武內功﹐供 force 槽
//   吐納運功與戰鬥 force_bonus 取用﹔殺業驅動的暴怒 buff 待業力系統就緒後再掛上。
//
// 字典 data/chinese.o 查無 "aggressive" key﹐以 CHINESE_D->add_translate() 自行登錄
// 中文名「怒氣訣」。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("aggressive");
	// 自行登錄中文名﹐字典查無此 key﹐使 enable / skills 等顯示「怒氣訣」而非英文代號。
	CHINESE_D->add_translate("aggressive", "怒氣訣");
	setup();
}

// 怒濤先鋒打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIR "$N咬牙瞋目﹐緩緩運轉怒氣訣﹐周身似有一股暴烈的殺氣自丹田奔湧而上﹐"
	           "如怒濤拍岸、如烈火焚膛﹐膽氣與臂力俱隨之鼓盪不息。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
