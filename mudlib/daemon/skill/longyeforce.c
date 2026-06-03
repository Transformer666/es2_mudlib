// 瑯夷派內功 longyeforce -- 瑯夷派黑龍左使門下的入門內功
//
// 瑯夷派暗算取命的根本吐納之術，陰沉幽冷、如毒蛇潛行而殺機暗藏。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、並 override cultivate_msg() 提供瑯夷派自家的打坐氣象。
// 注意 longyeforce 之 key 本身不含空白，檔名直接同 key。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("longyeforce");
	setup();
}

// 瑯夷派弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N閉目盤膝﹐緩緩運轉瑯夷派內功﹐周身似有一股陰沉幽冷之氣如毒蛇潛行﹐"
	           "幽冷之中自有一股噬人的勁力。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
