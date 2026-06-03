// 冰蠶奇功 polar-silkworm force -- 天師派素衣弟子的入門內功
//
// 天師派素衣一脈以冰證道的根本吐納之術，清冽寒氣氤氳、如玄冰封脈而藏護體罡正。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、並 override cultivate_msg() 提供天師派素衣自家的打坐氣象。
// 注意 key 含連字號與空白，故檔名為 polar-silkworm_force.c。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("polar-silkworm force");
	setup();
}

// 天師派素衣弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIC "$N閉目盤膝﹐緩緩運轉冰蠶奇功﹐周身似有一股清冽的寒氣氤氳不散﹐"
	           "丹田之中一輪寒月冉冉升起﹐沁寒之中自有一股護體的罡正。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
