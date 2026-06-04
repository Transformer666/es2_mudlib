// 紫薇心經 chivi sutra -- 振武軍營「軍師」進階(二轉)所授的內功(基底 FORCE)
//
// docs 載振武軍營軍師一脈「天風道長任務可學紫薇心經與法術」(見 docs/03-門派與武功/
// 06-軍人-振武大內.md §進階-軍師)。本檔將紫薇心經實作為一門內功心法(force)﹐使軍師
// 施法/施術時力道與法力能隨內功成長﹐並借 FORCE(/std/force.c)提供的打坐修煉 +
// valid_enable 共用機制﹔本檔只註冊心法名、登錄中文名、並 override cultivate_msg()
// 提供軍師自家的打坐氣象。
//
// 中文名「紫薇心經」於 data/chinese.o 已有對應 key "chivi sutra":"紫薇心經"﹐故本檔
// 沿用該 romanization "chivi sutra"(含空白﹐故檔名以連字號代之 chivi-sutra.c﹐
// register/translate 用的 key 仍為含空白原名)﹐add_translate 僅作備援(字典已有則覆寫
// 同值﹐無害)。
//
// 設計(docs 原值)：docs 軍師習紫薇心經之條件為「天風道長任務」﹐屬尚未接的任務門檻﹔
//   為與本批進階一致(只 gate level/skill/attr)﹐其達標查驗由 master.c::do_advance 以
//   入門火候 + 屬性門檻替代﹐天風道長任務標記為待接的故事門檻 TODO。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("chivi sutra");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示(字典已有則覆寫同值)。
	CHINESE_D->add_translate("chivi sutra", "紫薇心經");
	setup();
}

// 振武軍師打坐運功時所現的內功氣象。
string cultivate_msg()
{
	return HIM "$N斂神靜坐﹐緩緩運轉紫薇心經﹐周身似有一股紫氣自百會垂落、繞身周流﹐"
	           "如帝星臨頂、星河環身﹐心神為之清明﹐法力亦隨之溫養綿長。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
