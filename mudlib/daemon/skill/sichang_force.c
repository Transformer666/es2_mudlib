// 四廠心法 sichang force -- 玄天教四廠都督(二轉)的上乘內功
//
// 玄天教書生投靠朝廷諜報機構「四廠」後可得的進階內功(見 docs/03-門派與武功/
// 04-書生-步玄玄天.md §玄天教-搭配四廠﹕「玄天劍訣傷害提高 25%、困天 delay
// 提昇為 3」﹐及 §兩派書生都可投靠四廠「獲得更強攻擊力」)。四廠心法以諜報心術
// 淬鍊內息﹐氣機縝密如算無遺策、運籌千里﹐佐困天劍訣施展。
//
// 由藏雲/玄天一脈內功更進一階﹐修煉與 valid_enable 等共用機制由 FORCE
// (/std/force.c)基底提供﹔本檔只註冊心法名、登錄中文名「四廠心法」、並 override
// cultivate_msg() 提供四廠都督自家的打坐氣象。注意 key 含空白﹐檔名以底線代之。
//
// 設計(docs未明定):docs 言四廠「獲得更強攻擊力」屬投靠後的攻擊加成(perform/
//   身分系統)﹐標記為待辦。本檔先以 FORCE 基底接通內功修煉與力道成長。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("sichang force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("sichang force", "四廠心法");
	setup();
}

// 玄天教四廠都督打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIC "$N閉目盤膝﹐緩緩運轉四廠心法﹐周身氣機縝密如算無遺策、運籌千里﹐"
	           "神思之中自有一股諜影潛行的肅殺。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
