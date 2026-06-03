// 封山派內功 fonxanforce -- 封山派劍客的入門內功
//
// 封山派根本的吐納之術，沉凝如山、靜水深流而奔雷待發。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名（注冊名 fonxanforce 與 data/chinese.o 一致）、並 override
// cultivate_msg() 提供封山派自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("fonxanforce");
	setup();
}

// 封山派弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N盤膝閉目﹐緩緩運轉封山派內功﹐周身似有一股沉凝如山的真氣流轉不息﹐"
	           "穩固之中自有一股奔雷待發的勁勢。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
