// 龍涎毒功 venom-force -- 瑯夷派「黑龍右使」進階(二轉)的內功心法
//
// 黑龍右使一脈由入門「瑯夷派內功 longyeforce」另闢蹊徑、轉修用毒的內功
// (見 docs/03-門派與武功/05-盜賊-瑯夷隱教.md §進階分支-黑龍右使﹕「將身上的毒
// 傳遞給敵人(不會進入戰鬥狀態)」、「適合暗殺掌門級 NPC」、「渾沌獸的無風險
// 打法﹕黑龍右使毒死他」)。龍涎毒功以內息煉毒、以毒養功﹐周身真氣陰寒帶毒﹐
// 是黑龍右使隔空遞毒、不戰而殺之力道根本。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹕本檔只
// 註冊心法名、登錄中文名「龍涎毒功」、並 override cultivate_msg() 提供黑龍
// 右使自家的打坐氣象。
//
// TODO(黑龍右使完整化)：docs「隔空遞毒、不進戰鬥即毒殺」屬 perform/poison 系統
//   (非招式表/非力道係數)﹐標記為待辦。本檔先把帶毒內功的吐納與力道加成做實。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("venom-force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("venom-force", "龍涎毒功");
	setup();
}

// 瑯夷派黑龍右使打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N盤膝閉目﹐緩緩運轉龍涎毒功﹐以內息煉毒、以毒養功﹐周身真氣陰寒"
	           "帶毒﹐指尖隱隱泛起一層幽碧的毒華﹐殺人於無形的毒勁悄然滋長。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
