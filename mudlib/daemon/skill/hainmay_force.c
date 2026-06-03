// 寒梅心法 hainmay force -- 冷梅莊弟子的入門內功
//
// 冷梅莊的根本吐納之術，清冷如寒梅破雪、疏影暗香而藏勃發生機。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、並 override cultivate_msg() 提供冷梅莊自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("hainmay force");
	setup();
}

// 冷梅莊弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N閉目盤膝﹐緩緩運轉寒梅心法﹐周身似有一股清冷之氣流轉不息﹐"
	           "一縷暖意如寒梅破雪﹐冷冽中自有一股勃發的生機。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
