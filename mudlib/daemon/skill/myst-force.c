// 步玄心法 myst-force -- 步玄派居士門下的入門內功
//
// 步玄派以文心參武道的根本吐納之術，玄奧清靈、如行雲流水而妙用無窮。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、並 override cultivate_msg() 提供步玄派自家的打坐氣象。
// 注意 myst-force 之 key 本身不含空白，檔名直接同 key（連字號保留）。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("myst-force");
	setup();
}

// 步玄派弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIC "$N閉目盤膝﹐緩緩運轉步玄心法﹐周身似有一股玄奧清靈之氣流轉不息﹐"
	           "氣息如行雲流水﹐澄澈之中自有一股無窮的妙用。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
