// 大悲心經 almsdeed force -- 寶蓮寺「大悲行者」進階(二轉)的內功心法
//
// 寶蓮寺善想一脈大悲行者所修的願力內功(設計(docs未明定):承 docs 明列之「大悲咒
// almsdeed magic / 善想禪要 almsdeed」一脈﹐見 docs/03-門派與武功/03-和尚-寶蓮
// 天月白象.md §寶蓮寺)。docs 明載寶蓮為「治療輔助」之寺院、大悲咒(almsdeed)為
// 其看家禪要﹐然 docs 未明列大悲行者之內功心法名﹔故大悲心經 almsdeed force 為
// 設計值﹐定位為承載大悲願力、滋養神識(sen)以續法力的願力吐納之術﹐由入門寶蓮
// 心法(baolian force)精進而成。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔只註冊心法
// 名、登錄中文名「大悲心經」、並 override cultivate_msg() 提供寶蓮寺大悲行者
// 一脈的打坐氣象。中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate()
// 自行登錄。
//
// TODO(寶蓮治療化)：docs 載寶蓮主力為 link/link2 群補、almsdeed 增益等治療輔助
//   機制﹐其「滋養神識/法力恢復」加成屬 heal/regen 系統(非 force 基底)﹐標記為
//   待辦﹔本檔先把心法掛上、接通修煉與內力成長﹐與 luohan_force.c 同一範圍。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("almsdeed force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("almsdeed force", "大悲心經");
	setup();
}

// 寶蓮寺大悲行者打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIR "$N結大悲手印盤膝而坐﹐默運大悲心經﹐周身似有萬千金紅願力梵光氤氳"
	           "環繞﹐一股莊嚴慈悲之氣自丹田緩緩升騰﹐滋養神識、護法度世。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
