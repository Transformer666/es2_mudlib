// 古文造詣 archaic attainment -- 振武軍營「軍師」進階(二轉)所授的文書技能(基礎技能 literate)
//
// docs 載振武軍營軍師「獲得 古文、咒術、幻劍術」(見 docs/03-門派與武功/06-軍人-振武
// 大內.md §進階-軍師)﹐古文造詣亦見於大內巡院核心技能表「古文造詣 archaic attainment」。
// 本檔將其實作為一門文書/學識技能(literate 系)﹐軍師為 ES2 戰場後勤核心﹐其「文官能力」
// (讀書/古文)與戰術補給(strategy)掛鉤(見 docs §戰術兵法/軍師加強 strategy)。
//
// 中文名「古文造詣」於 data/chinese.o 已有對應 key "archaic attainment":"古文造詣"﹐故
// 本檔沿用該 romanization "archaic attainment"(含空白﹐故檔名以連字號代之
// archaic-attainment.c﹐register/translate 用的 key 仍為含空白原名)﹐add_translate 僅作
// 備援(字典已有則覆寫同值﹐無害)。master.c::do_advance 以 map_skill("literate",
// "archaic attainment") 將文書/讀書(literate)對應到本技能。
//
// 古文造詣為被動的文書學識(非攻擊招式)﹐故不提供 attack_using﹐valid_enable 回 0﹕
// 其作為「軍師文官能力」放大 strategy/tactic 補給效果與軍師法術之耦合﹐屬戰術兵法
// strategy 系統工作(同 illusion-sword「軍師 strategy 受法術強度額外影響」之 TODO)﹐
// 標記為待辦。本檔先把技能本身做實、可被指派與習練。

inherit SKILL;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("archaic attainment");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示(字典已有則覆寫同值)。
	CHINESE_D->add_translate("archaic attainment", "古文造詣");
	setup();
}

int
valid_enable (string usage)
{
	// 文書學識為被動技能﹐不佔 enable 槽(不可主動 enable 為某攻防動作)。
	return 0;
}

// vim: set ts=4 sw=4 syntax=lpc
