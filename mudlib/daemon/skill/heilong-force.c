// 黑龍真氣 heilong-force -- 瑯夷派「黑龍左使」進階(二轉)的內功心法
//
// 黑龍左使一脈由入門「瑯夷派內功 longyeforce」精進而成的高階吐納之術。
// docs/03-門派與武功/05-盜賊-瑯夷隱教.md §進階分支-黑龍左使 載其內功主提高
// 「偷襲、暗算技倆 / 殺手本能 / 縱躍閃躲之法 / 攻勢等級」﹐並有「消除疲勞內功」。
// 故黑龍真氣陰沉幽冷更甚入門﹐殺機內斂如蟄龍蓄勢﹐是黑龍左使「奪命血魂匕」
// 見血追命、暗算取命之力道根本。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹕本檔只
// 註冊心法名、登錄中文名「黑龍真氣」、並 override cultivate_msg() 提供黑龍
// 左使自家的打坐氣象。內功如何加成戰鬥力道見 adm/daemons/combatd.c::fight()
// (force_bonus = query_skill("force") * kee * (ratio + action["force"]) / 25)﹕
// 黑龍真氣本身是「更高火候的 force」﹐其加成隨技能等級與所配匕招裡的 "force"
// 係數一同放大。
//
// TODO(黑龍左使完整化)：docs「消除疲勞內功(清疲勞)」、「攻擊狀態脫離有機會
//   造成一擊必殺技」屬 force special / perform 系統(非招式表)﹐標記為待辦。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("heilong-force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("heilong-force", "黑龍真氣");
	setup();
}

// 瑯夷派黑龍左使打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N閉目反手按膝﹐緩緩運轉黑龍真氣﹐周身陰沉幽冷之氣愈斂愈深﹐"
	           "殺機內藏如蟄龍蓄勢﹐幽冷無聲之中自有一股噬人奪命的勁力暗暗流轉。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
