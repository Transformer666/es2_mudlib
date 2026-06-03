// 明鏡止水 mingjing -- 冷梅莊「劍士」進階(二轉)的內功心法
//
// 劍士由入門「寒梅心法」精進而成的高階吐納之術﹕心如明鏡、意若止水﹐
// 一動一靜皆暗藏凌厲殺機。明鏡止水加成傷害(force)﹐是劍士「攻防一體、
// 既有爆發又有防禦」的力道根本(見 docs/03-門派與武功/01-武者-五大門派.md
// §2 冷梅莊-劍士)。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹕本檔只
// 註冊心法名、登錄中文名「明鏡止水」、並 override cultivate_msg() 提供
// 劍士自家的打坐氣象。內功如何加成戰鬥力道見 adm/daemons/combatd.c::fight()
// (force_bonus = query_skill("force") * kee * (ratio + action["force"]) / 25)﹕
// 明鏡止水本身只是「更高火候的 force」﹐其加成隨技能等級與所配傲梅暗劍訣
// 招式裡的 "force" 係數一同放大。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("mingjing");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("mingjing", "明鏡止水");
	setup();
}

// 冷梅莊劍士打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N盤膝閉目﹐緩緩運轉明鏡止水﹐心如明鏡、意若止水﹐周身真氣"
	           "凝而不散﹐動靜之間自有一股清冷凌厲的劍意流轉不息。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
