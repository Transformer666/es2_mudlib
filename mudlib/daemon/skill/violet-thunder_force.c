// 紫府雷經 violet-thunder force -- 天師派紫衣弟子的入門內功
//
// 天師派紫衣一脈以雷證道的根本吐納之術，幽幽紫雷盤旋、如紫府裂空而藏護體雷罡。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、並 override cultivate_msg() 提供天師派紫衣自家的打坐氣象。
// 注意 key 含空白，故檔名為 violet-thunder_force.c。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("violet-thunder force");
	setup();
}

// 天師派紫衣弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIM "$N閉目盤膝﹐緩緩運轉紫府雷經﹐周身似有一團幽幽的紫雷盤旋不散﹐"
	           "丹田之中一道雷氣冉冉升起﹐霹靂之中自有一股護體的雷罡。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
