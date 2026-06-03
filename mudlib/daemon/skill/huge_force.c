// 大邪心法 huge force -- 哭笑門護法的入門內功
//
// 哭笑門根本的吐納之術，陰寒森然、忽哭忽笑而氣勢愈盛。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名（注冊名 huge force 與 data/chinese.o 一致）、並 override
// cultivate_msg() 提供哭笑門自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("huge force");
	setup();
}

// 哭笑門弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N盤膝閉目﹐緩緩運轉大邪心法﹐周身隱隱泛起一層暗沉的罡氣﹐"
	           "臉上忽哭忽笑﹐渾身骨節爆出一連串脆響﹐氣勢愈發森然。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
