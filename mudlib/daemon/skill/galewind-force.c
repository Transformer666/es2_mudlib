// 玄風訣 galewind force -- 天師派玄衣弟子的入門內功
//
// 天師派玄衣一脈以風證道的根本吐納之術，清靈罡風盤旋、如玄風裂脈而藏護體罡正。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、並 override cultivate_msg() 提供天師派玄衣自家的打坐氣象。
// 注意 key 含空白，故檔名為 galewind-force.c。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("galewind force");
	setup();
}

// 天師派玄衣弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIC "$N閉目盤膝﹐緩緩運轉玄風訣﹐周身似有一股清靈的罡風盤旋不散﹐"
	           "丹田之中一團罡氣冉冉升起﹐飄逸之中自有一股護體的罡正。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
