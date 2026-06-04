// 羅漢降魔功 luohan force -- 白象寺「羅漢」進階(二轉)的內功心法
//
// 白象寺羅漢一脈攻擊型內功(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md
// §白象寺-羅漢核心技能﹕「羅漢降魔功 luohan force」)。docs 載羅漢降魔功
// 「傷害與恢復提高﹐受 almsdeed(善想禪要) 50% 影響」(9/2 平衡)﹐故定位為剛猛
// 兼帶恢復的金剛內功﹐由入門蓮華心法(lotus force)精進而成。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔只
// 註冊心法名、登錄中文名「羅漢降魔功」、並 override cultivate_msg() 提供
// 白象寺羅漢一脈的打坐氣象。中文字典(data/chinese.o)查無此 key﹐以
// CHINESE_D->add_translate() 自行登錄。
//
// TODO(羅漢完整化)：docs 載羅漢降魔功之「傷害/恢復加成」與「受 almsdeed 50%
//   影響」屬 combat/heal 系統(非 force 基底)﹐標記為待辦﹔本檔先把心法掛上、
//   接通修煉與內力成長﹐與 daemon/skill/tianxie-force.c 同一範圍。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("luohan force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("luohan force", "羅漢降魔功");
	setup();
}

// 白象寺羅漢打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIY "$N結金剛跏趺坐﹐默運羅漢降魔功﹐周身似有十八尊羅漢虛影環立﹐"
	           "一股雄渾如山的金剛之氣自丹田勃然而起﹐降龍伏虎﹐凜然辟邪。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
