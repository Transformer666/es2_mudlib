// yaoshi_book.c -- 藥石脈錄：秋一谷守谷者靈樞藥叟畢生參詳藥石針理而成的頂級書。
//
// 來歷（承接 canon）：
//   docs 02-遊戲系統與機制/05-裝備與強化.md L233：藥石脈錄→水嵐東方森林秋一谷。
//   docs 02-遊戲系統與機制/06-煉丹與書本系統.md L160：藥石脈錄→水嵐東方森林秋一谷。
//   這卷『藥石脈錄』是秋一谷世代守藥的谷主靈樞藥叟(d/qiuyi/npc/yaoshou.c)守谷一甲
//   子、畢生參詳藥石經脈與針砭之道而成的醫藥奇書。譜中所載，上自藥石之中暗藏的人
//   身經脈藥理，下至運氣施針、以針引氣的針砭之法，皆是天底下最精微的醫藥針石之學。
//   欲得此譜，須先在秋一谷底堂堂正正將藥叟擊敗(見 yaoshou.c::die())。
//
// 用法：可用 study 研讀的醫藥針石秘本(ITEM + F_STUDY，鏡 d/mengjia/npc/obj/sixyin_manual.c、
//   d/heifeng/npc/obj/qiyong_book.c 之頂級書範式)。譜中所載既深，須有相當的文識
//   (literate)方能讀通其上以經脈藥理立論的精微圖訣；讀通之後，於針法(needle，藥石針
//   砭之道)與內功(force，藥石經脈、調氣養生)之道俱有所進益——以「運針施治、以針引氣」
//   對應 needle 為主、佐以「調氣養生、藥石煉藥」之 force。
//
// 平衡（content 值 = study 可習得的技能上限，見 feature/study.c::study_content：僅當
//   query_skill(t) < content[t] 時才 improve）：比照既有頂級書的尺度封頂，不臆造破壞
//   平衡——現存頂級書以 wuming_manual(force45/parry35)、sixyin_manual(unarmed45/dodge40)
//   為高標。藥石脈錄定位為 lv50 boss 靈樞藥叟的鎮谷頂級書(docs 列「頂級書」一系)，故
//   取與之同列的上緣：
//     needle(藥石針砭)   45   —— 對齊 sixyin/unarmed45、wuming/force45 的頂級主修高標。
//     force (調氣養生)   35   —— 略低於主修(佐修)，守於 wuming/parry35 一線(佐修上緣)。
//   literate 門檻 30(同 sixyin_manual)，契合「頂級書、譜訣艱深」的定位。
//   設 no_sell：藥叟畢生心血、堂堂正正奪來的鎮谷奇書，玩家自當珍習，不宜變賣。

#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name(HIY "藥石脈錄" NOR,
		({ "yaoshi", "yaoshi book", "yaoshi manual", "pharmacopoeia", "manual", "book",
		   "藥石脈錄", "脈錄" }) );
	set_weight(900);

	if( !clonep() ) {
		set("unit", "卷");
		set("value", 1);
		set("no_sell", 1);
		set("long",
			"一卷以陳年絹帛裝裱、邊角磨得起了毛的舊譜﹐封皮上『藥石\n"
			"脈錄』四個蒼勁的篆字依稀可辨﹐隱隱透著一股久浸藥石靈氣的\n"
			"清苦藥香。翻開來﹐內裡以經脈藥理立論﹐圖文並茂地繪註著一\n"
			"門精微深奧的醫藥針石之學——上自秋一谷藥石之中暗藏的人身\n"
			"經脈藥理﹐下至運氣施針、以針引氣的針砭之法﹐其間夾著一幅\n"
			"幅周身穴位、經脈走向與運針施治的人形圖訣﹐藥力的吞吐、針\n"
			"鋒的進退、氣血的盈虛﹐無不勾畫得纖毫畢現。這便是那守谷藥\n"
			"叟靈樞先生守谷一甲子、畢生參詳藥石針理而成的鎮谷奇書了。\n"
			"只是這脈錄以經脈藥理立論﹐精微艱深﹐非有相當的文識﹐怕是\n"
			"連讀都讀不通。\n"
			"可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 30,
		]));
		set("content", ([
			"needle" : 45,    // 藥石針砭之道(針法)，對齊 sixyin/wuming 頂級主修高標。
			"force"  : 35,    // 調氣養生、藥石煉藥(內功)，佐修。
		]));
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
