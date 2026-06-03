// 丹陽神功 sun force -- 天師派朱衣弟子的入門內功
//
// 天師派以火證道的根本吐納之術，溫煦火氣蒸騰、如烈焰焚天而藏護體罡正。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、並 override cultivate_msg() 提供天師派朱衣自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("sun force");
	setup();
}

// 天師派朱衣弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIR "$N閉目盤膝﹐緩緩運轉丹陽神功﹐周身似有一股溫煦的火氣蒸騰不息﹐"
	           "丹田之中一輪赤日冉冉升起﹐熾熱之中自有一股護體的罡正。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
