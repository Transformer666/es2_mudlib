// 天邪神功 tianxie-force -- 雪吟莊浪人的入門內功
//
// 源自外邦「天邪國」、雪吟莊一脈根本的吐納之術，陰冷詭譎、雄渾而暗藏煞氣。
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供；本檔只
// 註冊心法名、登錄中文名「天邪神功」、並 override cultivate_msg() 提供
// 雪吟莊自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("tianxie-force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("tianxie-force", "天邪神功");
	setup();
}

// 雪吟莊浪人打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N盤膝閉目﹐緩緩運轉天邪神功﹐周身似有一股陰冷詭譎的真氣流轉不息﹐"
	           "渾厚難測﹐如天邪國萬里風雪﹐凜然不可逼視。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
