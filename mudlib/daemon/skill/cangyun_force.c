// 藏雲心法 cangyun force -- 玄天教藏雲客(二轉)的進階內功
//
// 玄天教藏雲客一脈以藏雲訣佐身法游走、脫戰避實(見 docs/03-門派與武功/04-書生-
// 步玄玄天.md §玄天教-核心技能「藏雲訣」與散人進階「脫戰入潛行」)。藏雲心法
// 由入門玄天心法(xuantian force)更進一階﹐氣息斂藏如雲卷雲舒、來去無蹤﹐隨身法
// 流轉而生生不息。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹔本檔只註冊心法
// 名、登錄中文名「藏雲心法」、並 override cultivate_msg() 提供藏雲客自家的打坐
// 氣象。注意 key 含空白﹐檔名以底線代之。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("cangyun force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("cangyun force", "藏雲心法");
	setup();
}

// 玄天教藏雲客打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIC "$N閉目盤膝﹐緩緩運轉藏雲心法﹐周身氣息斂藏如雲卷雲舒、來去無蹤﹐"
	           "神思之中自有一股藏形匿跡的玄妙。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
