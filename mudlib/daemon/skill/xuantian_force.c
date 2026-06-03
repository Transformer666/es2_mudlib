// 玄天心法 xuantian force -- 玄天教散人門下的入門內功
//
// 玄天教以文心參武道、觀星問道的根本吐納之術，氣息澄澈空靈、機鋒暗藏。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、登錄中文名「玄天心法」、並 override cultivate_msg() 提供
// 玄天教自家的打坐氣象。注意 key 含空白，檔名以底線代之。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("xuantian force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("xuantian force", "玄天心法");
	setup();
}

// 玄天教弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIC "$N閉目盤膝﹐緩緩運轉玄天心法﹐周身似有一股玄奧清靈之氣如星河流轉不息﹐"
	           "神思之中自有一股觀星問道的玄妙。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
