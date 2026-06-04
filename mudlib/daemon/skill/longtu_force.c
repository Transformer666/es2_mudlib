// 龍圖真經 longtu force -- 龍圖丹派「龍圖丹師」進階(二轉)的內功心法
//
// 龍圖丹派內功之大成(見 docs/03-門派與武功/07-方士-龍圖武陀.md §龍圖丹派﹔docs 載
// 入門「龍圖心經 lv30/悟性30/內功90」)。龍圖真經乃由入門龍圖心經(dragon force)登峰
// 造極而成﹐內息醇厚溫養、與丹道針法相濟﹐是龍圖丹師一脈濟世活人的內功根本。
//
// 內功(force)是被動的「力道乘數」：戰鬥時 COMBAT_D->fight() 讀 query_skill("force")
// 與 skill_mapped("force")﹐藉氣(kee)與功力百分比放大攻擊力道﹐故內功 daemon 不需
// 攻擊招式表。玩家以 `enable force with longtu force` 掛上本心法後﹐再用
// `exert longtu force` 盤膝打坐修煉(見 /std/force.c 與 cmds/std/exert.c)。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔只註冊心法名、
// 登錄中文名「龍圖真經」、並 override cultivate_msg() 提供龍圖丹師一脈的打坐氣象。
// 中文字典(data/chinese.o)查無此 key﹐以 CHINESE_D->add_translate() 自行登錄。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("longtu force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("longtu force", "龍圖真經");
	setup();
}

// 龍圖丹師打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIW "$N閉目盤膝﹐緩緩運轉龍圖真經﹐周身似有一縷龍形真氣循經流轉﹐"
	           "溫醇醇厚﹐溫養經脈、滋潤丹田。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
