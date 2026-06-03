// 虎刀心法 hudao force -- 虎刀門護衛的入門內功
//
// 虎刀門賴以煉氣養刀的根本吐納之術，剽悍燥烈、催刀奪命。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、登錄中文名「虎刀心法」、並 override cultivate_msg() 提供
// 虎刀門自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("hudao force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("hudao force", "虎刀心法");
	setup();
}

// 虎刀門弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIY "$N盤膝閉目﹐緩緩運轉虎刀心法﹐周身似有一股剽悍燥烈的真氣如猛虎在籠般奔突鼓盪﹐"
	           "隱隱有虎嘯之聲在胸臆間迴盪。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
