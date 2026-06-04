// 靈甲術 lingjia force -- 龍圖丹派「劍甲門傳人」進階(二轉)的內功心法
//
// 龍圖/武陀兩派方士共通進階「劍甲門」的護體內功(見 docs/03-門派與武功/07-方士-龍圖
// 武陀.md §劍甲門﹔典型玩家 Kankichi 載「靈甲術 200」)。靈甲術運氣護體、生甲禦敵﹐
// 使一身以煉丹針法為本的方士得護身與臨陣之力﹐由入門龍圖心經(dragon force)旁參而成。
//
// 內功(force)是被動的「力道乘數」：戰鬥時 COMBAT_D->fight() 讀 query_skill("force")
// 與 skill_mapped("force")﹐藉氣(kee)與功力百分比放大攻擊力道﹐故內功 daemon 不需
// 攻擊招式表。玩家以 `enable force with lingjia force` 掛上本心法後﹐再用
// `exert lingjia force` 盤膝打坐修煉(見 /std/force.c 與 cmds/std/exert.c)。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔只註冊心法名、
// 登錄中文名「靈甲術」、並 override cultivate_msg() 提供劍甲門一脈的打坐氣象。中文
// 字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("lingjia force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("lingjia force", "靈甲術");
	setup();
}

// 劍甲門傳人打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIC "$N閉目凝神﹐默運靈甲術﹐周身似有一層淡淡寶光流轉如甲﹐"
	           "內息護體﹐刀劍難侵。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
