// 武陀心法 wuto force -- 武陀灸堂香主弟子的入門內功
//
// 武陀灸堂行針施灸、養氣活人的根本吐納之術，溫醇平和、如艾火溫煦而藏活人生機。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、登錄中文名「武陀心法」、並 override cultivate_msg() 提供
// 武陀灸堂自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("wuto force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("wuto force", "武陀心法");
	setup();
}

// 武陀灸堂弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIY "$N閉目盤膝﹐緩緩運轉武陀心法﹐周身似有一股溫醇平和之氣循經流轉﹐"
	           "真氣如艾火溫煦﹐平和之中自有一股活人濟世的生機。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
