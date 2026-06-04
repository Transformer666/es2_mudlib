// 幻霧訣 huanwu force -- 茅山派幻霧觀(進階)的內功
//
// 茅山幻霧觀以陰御鬼、養魂凝煞的吐納之術，周身似有一團幽幽陰霧繚繞﹐
// 神識沉入幽冥、與鬼神相通﹐運使陰火奇術時更得幽冥煞氣相滋。修煉與
// valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只註冊心法
// 名、並 override cultivate_msg() 提供茅山幻霧觀自家的打坐氣象。
// 注意 key 含空白，故檔名為 huanwu_force.c。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("huanwu force");
	// 登錄中文名﹐使 enable / skills 等顯示「幻霧訣」而非英文代號。
	CHINESE_D->add_translate("huanwu force", "幻霧訣");
	setup();
}

// 茅山幻霧觀弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return GRN "$N閉目盤膝﹐緩緩運轉幻霧訣﹐周身似有一團幽幽的陰霧繚繞不散﹐"
	           "神識沉入幽冥﹐昏昧之中自有一股御鬼養魂的幽冥煞氣。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
