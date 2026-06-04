// 太陰真經 taiyin force -- 天月庵進階(二轉)的太陰內功心法
//
// 天月庵以太陰(月)之力濟世度人(見 docs/03-門派與武功/03-和尚-寶蓮天月白象.md
// §天月庵)。docs 天月庵核心技能列有太陰秘法 moon magic、太陰七損鞭 moon whip
// 等月法﹐入門時師父暫沿用和尚共用內功蓮華心法(lotus force)並標 TODO 待換
// (見 d/tianyue/npc/master.c 檔頭)。本檔即該 TODO 所指的天月庵專屬上乘內功﹐
// 由進階分支(雨花仙子/太陰尊者)精進而成﹐清冷如月、綿長不息﹐以太陰真氣
// 滋養月法與療傷之力。
//
// 設計(docs未明定):docs 只列天月庵以太陰之力為本﹐未明列其進階內功名﹔
//   「太陰真經」為承太陰一脈之意的專屬內功﹐與白象寺進階內功 luohan force
//   (羅漢降魔功)、天師進階內功 violet-thunder force(紫府雷經)同階對位。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔只
// 註冊心法名、登錄中文名「太陰真經」、並 override cultivate_msg() 提供
// 天月庵自家的打坐氣象。字典(data/chinese.o)查無此 key﹐以
// CHINESE_D->add_translate() 自行登錄。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("taiyin force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("taiyin force", "太陰真經");
	setup();
}

// 天月庵弟子打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIW "$N合什趺坐﹐默運太陰真經﹐周身似有清冷如月的太陰真氣緩緩流轉﹐"
	           "丹田之中一輪皎月隱隱生輝﹐照得周身一片澄澈祥和。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
