// 大內罡氣 danei force -- 大內巡院統領門下的入門內功
//
// 大內巡院宿衛禁中、護駕緝兇的根本吐納之術，剛正森嚴、凜然不可犯。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、登錄中文名「大內罡氣」、並 override cultivate_msg() 提供
// 大內巡院自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("danei force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("danei force", "大內罡氣");
	setup();
}

// 大內巡院弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N閉目盤膝﹐緩緩運轉大內罡氣﹐周身似有一層森嚴肅穆的護體真氣流轉﹐"
	           "剛正之中自有一股宿衛禁中的肅殺之意。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
