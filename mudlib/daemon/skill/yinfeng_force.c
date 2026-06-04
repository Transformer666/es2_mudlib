// 隱風訣 yinfeng force -- 茅山派隱風觀(進階)的內功
//
// 茅山隱風觀以風御靈、藏形匿息的吐納之術，周身似有一層隱隱罡風盤旋﹐
// 形跡飄忽、靈台空明﹐召役獸靈時更得清靈罡風相護。修煉與 valid_enable
// 等共用機制由 FORCE(/std/force.c)基底提供；本檔只註冊心法名、並 override
// cultivate_msg() 提供茅山隱風觀自家的打坐氣象。
// 注意 key 含空白，故檔名為 yinfeng_force.c。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("yinfeng force");
	// 登錄中文名﹐使 enable / skills 等顯示「隱風訣」而非英文代號。
	CHINESE_D->add_translate("yinfeng force", "隱風訣");
	setup();
}

// 茅山隱風觀弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIC "$N閉目盤膝﹐緩緩運轉隱風訣﹐周身似有一層隱隱罡風盤旋不散﹐"
	           "形跡漸隱、靈台空明﹐飄忽之中自有一股御靈藏形的清靈之氣。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
