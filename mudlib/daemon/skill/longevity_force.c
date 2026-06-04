// 長生心法 longevity force -- 寶蓮寺「長生上人」進階(二轉)的最高階內功心法
//
// 寶蓮寺善想一脈長生上人所修的無量壽內功(設計(docs未明定):承 docs 明列之「長生
// 禪法 longevity magic / link;link2 長生」一脈﹐見 docs/03-門派與武功/03-和尚-
// 寶蓮天月白象.md §寶蓮寺)。docs 明載寶蓮主力玩法為「link/link2 長生：維持隊友
// 狀態」、長生禪法 longevity magic 為其最高絕學﹐然 docs 未明列長生上人之內功
// 心法名﹔故長生心法 longevity force 為設計值﹐定位為以無量壽願力續命延壽、培
// 元固本、滋養神識(sen)的最高階吐納之術﹐由大悲心經(almsdeed force)精進而成。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔只註冊心法
// 名、登錄中文名「長生心法」、並 override cultivate_msg() 提供寶蓮寺長生上人
// 一脈的打坐氣象。中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate()
// 自行登錄。
//
// TODO(寶蓮治療化)：docs 載長生禪法之核心為「link/link2 維持隊友狀態」之群體續命
//   機制﹐其「續命/狀態維持/法力恢復」加成屬 heal/regen/link 系統(非 force 基底)﹐
//   標記為待辦﹔本檔先把心法掛上、接通修煉與內力成長﹐與 luohan_force.c /
//   almsdeed_force.c 同一範圍。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("longevity force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("longevity force", "長生心法");
	setup();
}

// 寶蓮寺長生上人打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIW "$N結無量壽印盤膝入定﹐默運長生心法﹐周身似有一輪澄澈瑩白的壽光"
	           "緩緩流轉﹐一股清淨綿長之氣自丹田氤氳而生﹐培元固本、續命延壽。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
