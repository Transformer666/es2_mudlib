// 大邪心經 danei-sutra -- 哭笑門「使者」進階(二轉)的內功心法
//
// 哭笑門使者(七損刀)一脈的內功(見 docs/03-門派與武功/01-武者-五大門派.md §3 哭笑門-
// 使者(七損刀))。docs 載「大邪心經 戰鬥時可使用同時補精氣」﹐定位為攻守俱補的邪派
// 內功﹐由入門大邪心法(huge force)精進而成﹐既助七損刀刀勢﹐又能於激戰中回補精氣。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔只註冊心法名、
// 登錄中文名「大邪心經」、並 override cultivate_msg() 提供哭笑門使者一脈的打坐氣象。
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄(避免與
// 入門 huge force「大邪心法」混淆﹐故另用 key "danei-sutra")。
//
// TODO(使者完整化)：docs 載大邪心經「戰鬥時同時補精氣」屬 combat/heal 系統(非 force
//   基底)﹐標記為待辦﹔本檔先把心法掛上、接通修煉與內力成長﹐與 daemon/skill/
//   tianxie-force.c、luohan_force.c 同一範圍。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("danei-sutra");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("danei-sutra", "大邪心經");
	setup();
}

// 哭笑門使者打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIK "$N盤膝閉目﹐緩緩運轉大邪心經﹐周身浮起一層陰沉森然的邪氣﹐"
	           "臉上忽哭忽笑﹐隱隱有精氣自丹田回補﹐氣勢愈發詭譎難測。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
