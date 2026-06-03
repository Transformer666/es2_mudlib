// 隱教心法 yinjiao force -- 隱教聖女門下的入門內功
//
// 隱教潛行暗殺、見血封喉的根本吐納之術，陰寒幽冷、如金蛇蟄伏待噬。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、登錄中文名「隱教心法」、並 override cultivate_msg() 提供
// 隱教自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("yinjiao force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("yinjiao force", "隱教心法");
	setup();
}

// 隱教弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N閉目盤膝﹐緩緩運轉隱教心法﹐周身似有一股陰寒幽冷之氣如毒蛇潛行﹐"
	           "丹田之中一縷青黑真氣悄然滋長﹐殺機暗藏﹐如金蛇蟄伏待噬。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
