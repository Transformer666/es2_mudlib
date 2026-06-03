// 寶蓮心法 baolian force -- 寶蓮寺善想門下的入門內功
//
// 寶蓮寺以慈悲清淨為本的根本吐納之術，清淨慈和、化解魔障。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、登錄中文名「寶蓮心法」、並 override cultivate_msg() 提供
// 寶蓮寺自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("baolian force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("baolian force", "寶蓮心法");
	setup();
}

// 寶蓮寺弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N閉目盤膝﹐緩緩運轉寶蓮心法﹐周身似有一股清淨慈和之氣氤氳流轉﹐"
	           "丹田之中一朵寶蓮悄然綻放﹐祥和之意循經滋長。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
