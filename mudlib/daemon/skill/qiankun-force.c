// 乾坤三轉心法 qiankun-force -- 步玄派「居士進階」乾坤三轉的內功心法
//
// 步玄派書生一脈以文心參武道﹐入門「步玄心法 myst-force」精進而成的高階
// 吐納之術﹕在步玄心法玄奧清靈的真氣之上﹐另蘊一股周天循環、生生不息的
// 乾坤三轉勁勢(見 docs/03-門派與武功/04-書生-步玄玄天.md §步玄派-居士進階
// 「乾坤三轉」﹕步玄心法增加 rotate 功能、消耗 100 神恢復 50% 精氣、同時
// 下次攻擊觸發奇門劍訣)。乾坤三轉心法加成傷害(force)﹐是奇門劍訣與步玄
// 雙龍劍氣威力的力道根本。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹕本檔只
// 註冊心法名、登錄中文名「乾坤三轉心法」、並 override cultivate_msg()
// 提供乾坤三轉自家的打坐氣象。內功如何加成戰鬥力道見 adm/daemons/combatd.c
// ::fight() 之 force_bonus 公式(force_bonus = query_skill("force") * kee *
// (ratio + action["force"]) / 25)﹕乾坤三轉心法本身只是「更高火候的 force」﹐
// 其加成隨技能等級與所配奇門劍訣/虛空斬招式裡的 "force" 係數一同放大。
//
// TODO(乾坤三轉完整化)：docs 載乾坤三轉「rotate 消耗 100 神恢復 50% 精氣、
//   下次攻擊觸發奇門劍訣」屬 perform/精氣循環系統(非 force 修煉介面)﹐標記
//   為待辦。本檔先接通內功修煉與力道加成。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("qiankun-force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("qiankun-force", "乾坤三轉心法");
	setup();
}

// 步玄派居士打坐運轉乾坤三轉時所現的內功氣象。
string cultivate_msg()
{
	return HIC "$N閉目盤膝﹐緩緩運轉乾坤三轉心法﹐周身玄奧清靈之氣如周天運行﹐"
	           "一轉一收、生生不息﹐精氣神隨那無形乾坤循環往復﹐妙用無窮。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
