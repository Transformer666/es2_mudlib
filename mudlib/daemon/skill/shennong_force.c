// 神農真經 shennong force -- 武陀灸堂「神農上人」進階(二轉)的內功心法
//
// 武陀灸堂針法、灸術之大成所修的上乘吐納(見 docs/03-門派與武功/07-方士-龍圖武陀.md
// §武陀灸堂﹔docs 載武陀堂「可修習神農之術」、針灸出神入化)。神農真經由入門武陀
// 心法(wuto force)精進而成﹐溫醇渾厚如百草歸元、艾火溫煦﹐養氣活人之餘亦能臨陣護身、
// 隨內功放大針勢力道。與龍圖丹派最高階內功「龍圖真經 longtu force」對位。
//
// 內功(force)是被動的「力道乘數」：戰鬥時 COMBAT_D->fight() 讀 query_skill("force")
// 與 skill_mapped("force")﹐藉氣(kee)與功力百分比放大攻擊力道﹐故內功 daemon 不需
// 攻擊招式表。玩家以 `enable force with shennong force` 掛上本心法後﹐再用
// `exert shennong force` 盤膝打坐修煉(見 /std/force.c 與 cmds/std/exert.c)。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔只註冊心法名、
// 登錄中文名「神農真經」、並 override cultivate_msg() 提供武陀神農一脈的打坐氣象。
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("shennong force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("shennong force", "神農真經");
	setup();
}

// 武陀灸堂神農上人打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIY "$N閉目盤膝﹐緩緩運轉神農真經﹐周身似有一股醇厚平和之氣循經流轉﹐"
	           "真氣如百草歸元、艾火溫煦﹐渾厚之中自有一股活人濟世的勃勃生機。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
