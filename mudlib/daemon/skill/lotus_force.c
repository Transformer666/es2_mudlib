// 蓮華心法 lotus force -- 白象寺羅漢門下的入門內功
//
// 白象寺以慈悲降魔的根本吐納之術，寶相莊嚴、祥和而藏金剛之力。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、並 override cultivate_msg() 提供白象寺自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("lotus force");
	setup();
}

// 白象寺弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIY "$N閉目盤膝﹐緩緩運轉蓮華心法﹐周身似有一股清淨祥和之氣流轉不息﹐"
	           "丹田之中一朵金蓮悄然綻放﹐隱有降魔的金剛之力。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
