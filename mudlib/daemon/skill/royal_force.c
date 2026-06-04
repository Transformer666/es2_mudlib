// 大內心法 royal force -- 大內巡院「大內供奉/大內都統」進階(二轉)所授的上乘內功
//
// 大內心法為 docs 明列的大內巡院核心技能(見 docs/03-門派與武功/06-軍人-振武大內.md
// §2 大內巡院 soldier.royal-核心技能「大內心法 royal force」﹐並載其 lv10 起有
// refresh(消氣回精)/recover(消神回精氣)/royal(神威狀態提升護甲傷害)三式)。入門大內
// 巡院授的是大內罡氣(danei force)﹐進階「大內供奉」「大內都統」二脈方兼修這套更上乘
// 的大內心法。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔只註冊心法名、
// 登錄中文名「大內心法」、並 override cultivate_msg() 提供大內供奉一脈的打坐氣象。
// 字典 data/chinese.o 查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。
//
// TODO(大內心法完整化)：docs 載大內心法 lv10 起有 refresh / recover / royal 三式﹐其
//   消氣回精、消神回精氣、神威狀態(提升護甲傷害)屬主動技能/狀態(perform/combat 系統)﹐
//   標記為待辦。本檔先把內功吐納(掛 force 槽、exert 打坐成長、戰鬥力道加成)做實﹐與
//   入門大內罡氣 danei force 同一機制。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("royal force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("royal force", "大內心法");
	setup();
}

// 大內供奉/都統打坐運轉大內心法時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N閉目盤膝﹐緩緩運轉大內心法﹐周身似有一層神威護體真氣流轉﹐"
	           "森嚴肅穆之中暗蘊宿衛禁中、護駕克敵的凜然煞氣。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
