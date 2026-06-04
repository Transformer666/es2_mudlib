// 山人心法 shanren_force -- 封山派「山人」進階(二轉)的內功心法
//
// 山人一脈捨劍習拳(ES2 唯二使用拳法的武者門派之一﹐見 docs/03-門派與武功/
// 01-武者-五大門派.md §1 封山派-山人)﹐其內功亦由入門「封山派內功
// fonxanforce」轉化而成﹕不走奔雷破陣的剛猛路子﹐反取山嶽吐納、綿長深厚的
// 守拙之道﹐以契合「定人、打擊精/氣、穿移動力裝、極靈活」的拳法身法。
// 山人心法加成傷害(force)﹐是封山伏虎拳力道的根本。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供﹕本檔只
// 註冊心法名、登錄中文名「山人心法」、並 override cultivate_msg() 提供
// 山人自家的打坐氣象。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("shanren_force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("shanren_force", "山人心法");
	setup();
}

// 封山派山人打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N盤膝閉目﹐緩緩運轉山人心法﹐真氣綿長深厚一如群山吐納﹐"
	           "不見鋒芒外露﹐唯覺周身輕靈圓融﹐進退之間自有一股渾然天成的"
	           "拙樸勁力流轉不息。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
