// 瘋虎功 tiger force -- 振武軍營軍隊統領門下的入門內功
//
// 振武軍營沙場廝殺的根本吐納之術，剛猛霸烈、如猛虎下山而藏嗜血兇悍。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、並 override cultivate_msg() 提供振武軍營自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("tiger force");
	setup();
}

// 振武軍營弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIY "$N閉目盤膝﹐緩緩運轉瘋虎功﹐周身似有一股剛猛霸烈之氣奔騰不息﹐"
	           "一股獷悍之力如猛虎下山﹐剛猛之中自有一股嗜血的兇悍。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
