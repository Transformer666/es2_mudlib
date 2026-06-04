// 茅山心經 mao-shan force -- 茅山遺址「茅山劍士」轉職所授的內功心法
//
// 來歷(docs/03-門派與武功/02-道士-天師與茅山.md「茅山劍士 → 茅山心經 mao-shan
// force」)：茅山心經與茅山劍法同為祖師一脈所傳﹐藏於藏書閣﹐總壇大火後殘於茅
// 山遺址。茅山心經以靈力(sen)御真氣﹐docs 載其特性──regenerate 消當前 gin 恢復
// sen、exert element 召風火水雷之力、check 查體內靈力符文﹔習得時 sen -50、
// gin/kee 各 +10﹐每級 +1~2 gin、+1~2 kee。
//
// 修煉與 valid_enable 等共用機制由 FORCE(/std/force.c)基底提供(同 daemon/skill/
// mingjing.c 冷梅劍士「明鏡止水」的建檔模型)：本檔只註冊心法名、登錄中文名
// 「茅山心經」、並 override cultivate_msg() 提供茅山劍士自家的打坐氣象。內功
// 如何加成戰鬥力道見 adm/daemons/combatd.c::fight() 之 force_bonus 公式──茅山
// 心經本身即「更高火候的 force」﹐其加成隨技能等級與所配茅山劍法招式裡的
// "force" 係數一同放大。
//
// 註(key 含空白)：技能 key「mao-shan force」含空白﹐故檔名以連字號代之
// (mao-shan-force.c)﹐register/map 用的 key 仍為含空白原名(同 mao-shan-lightning
// / mao-shan-sword 的命名先例)。
//
// TODO(docs 特性待接)：regenerate(消 gin 恢復 sen)、exert element(召風火水雷之
//   力)、check(查靈力符文)等 docs 所載的 perform/exert 特技﹐須俟咒術/特技效果
//   引擎就緒後再各自承襲(同 mao-shan-lightning 凝聚/賦予/補給之 TODO)。本檔先
//   提供可被指派、打坐修煉、戰鬥加成的內功本體。

#include <ansi.h>

inherit FORCE;

private void
create()
{
	seteuid(getuid());
	DAEMON_D->register_skill_daemon("mao-shan force");
	// 自行登錄中文名﹐字典查無此 key 時 to_chinese() 仍可工整顯示。
	CHINESE_D->add_translate("mao-shan force", "茅山心經");
	setup();
}

// 茅山劍士打坐運轉茅山心經時所現的內功氣象。
string cultivate_msg()
{
	return WHT "$N盤膝閉目﹐緩緩運轉茅山心經﹐周身靈力凝為一道道無形符文﹐"
	           "風火水雷之氣於丹田中隱隱流轉﹐劍意與道法在這一呼一吸間漸臻"
	           "圓融。\n" NOR;
}

// vim: set ts=4 sw=4 syntax=lpc
