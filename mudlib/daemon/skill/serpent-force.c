// 金蛇罡氣 serpent-force -- 瑯夷派「金蛇門人」進階(二轉)的內功心法
//
// 金蛇門人俗稱「戰鬥賊」(見 docs/03-門派與武功/05-盜賊-瑯夷隱教.md §進階分支-
// 金蛇門人﹕「右手持劍、左手搭配槍法」、「戰鬥中靠快速背刺有驚人破壞力」、
// 「蛇感﹕大幅提升警覺」)。金蛇罡氣捨瑯夷暗算之陰柔、轉走剛猛搶攻一路﹐真氣
// 如金蛇盤纏、伺機暴起﹐是金蛇門人持劍快攻、背刺暴擊之力道根本。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹕本檔只
// 註冊心法名、登錄中文名「金蛇罡氣」、並 override cultivate_msg() 提供金蛇
// 門人自家的打坐氣象。
//
// TODO(金蛇門人完整化)：docs「蛇感大幅提升警覺」、「快速背刺暴擊」屬警覺/
//   backstab/perform 系統(非力道係數)﹐標記為待辦。本檔先把金蛇剛猛內功的
//   吐納與力道加成做實。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("serpent-force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("serpent-force", "金蛇罡氣");
	setup();
}

// 瑯夷派金蛇門人打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N盤膝挺身﹐緩緩運轉金蛇罡氣﹐一身真氣如金蛇盤纏蓄勢﹐剛猛中暗"
	           "藏靈動﹐周身殺氣鋒銳如劍﹐只待一個破綻便要暴起噬人。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
