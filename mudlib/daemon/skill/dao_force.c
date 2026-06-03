// 明道心法 dao force -- 茅山派弟子的入門內功
//
// 茅山道士存神養氣、以通鬼神的根本吐納之術，神台澄澈、五氣朝元。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、並 override cultivate_msg() 提供茅山派自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("dao force");
	setup();
}

// 茅山弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N閉目盤膝﹐緩緩運轉明道心法﹐周身真氣流轉﹐心神漸入空明之境﹐"
	           "神台澄澈如鏡﹐隱隱與天地鬼神之氣相通。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
