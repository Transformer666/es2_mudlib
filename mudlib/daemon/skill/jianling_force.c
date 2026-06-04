// 劍靈心法 jianling_force -- 封山派「劍靈」進階(二轉)的內功心法
//
// 劍靈一脈由入門「封山派內功 fonxanforce」精進而成的高階吐納之術﹕封山
// 守正的沉凝勁勢中﹐另蘊一股凌厲奔放的劍靈罡氣﹐故劍靈能「以劍招提升
// 攻勢、守勢、護甲」(見 docs/03-門派與武功/01-武者-五大門派.md §1 封山派-
// 劍靈)。劍靈心法加成傷害(force)﹐是劍靈「無視防禦三連擊」威力的力道根本。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹕本檔只
// 註冊心法名、登錄中文名「劍靈心法」、並 override cultivate_msg() 提供
// 劍靈自家的打坐氣象。內功如何加成戰鬥力道見 adm/daemons/combatd.c::fight()
// (force_bonus = query_skill("force") * kee * (ratio + action["force"]) / 25)﹕
// 劍靈心法本身只是「更高火候的 force」﹐其加成隨技能等級與所配凰翔三疊劍
// 招式裡的 "force" 係數一同放大。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("jianling_force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("jianling_force", "劍靈心法");
	setup();
}

// 封山派劍靈打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N盤膝閉目﹐緩緩運轉劍靈心法﹐沉凝如山的真氣中暗蘊一縷凌厲"
	           "奔放的劍靈罡氣﹐周身似有無形劍鳴隱隱迴盪﹐守正之中自有一股"
	           "破陣奔雷的勁勢。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
