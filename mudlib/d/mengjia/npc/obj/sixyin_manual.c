// sixyin_manual.c -- 六陰八卦譜：孟家後院武師田由(boss)畢生鑽研的鎮身武學秘笈。
//
// 來歷（承接 canon）：
//   docs 01-世界觀與劇情/04-地圖與場景.md L118：孟家莊→孟家後院(六陰八卦譜：先打田由)。
//   docs 02-遊戲系統與機制/05-裝備與強化.md L232：六陰八卦譜→風城北方孟家後院(先打田由)。
//   這卷『六陰八卦譜』是孟家後院那位武師田由(d/mengjia/npc/tianyou.c)畢生鑽研、視若
//   性命的武學秘本。譜中以陰陽八卦立論，圖文並茂地繪註著一路陰柔詭譎的「六陰八卦掌」
//   ——掌走兩儀、步循八卦，掌隨步轉、身似游龍。田由便是憑這一身六陰八卦之學，闖出
//   「六陰掌」的名號。欲得此譜，須先在孟家後院堂堂正正將他擊敗(見 tianyou.c::die())。
//
// 用法：可用 study 研讀的武功秘笈(ITEM + F_STUDY，鏡 d/tianling/npc/obj/wuming_manual.c、
//   d/qiaoyin/obj/fist_manual.c 之 manual 做法)。譜中所載既深，須有相當的文識(literate)
//   方能讀通其上以八卦立論的精微圖訣；讀通之後，於掌法(unarmed，六陰八卦掌)與身法
//   (dodge，八卦步法)之道俱有所進益——以「掌走兩儀」對應 unarmed 為主、佐以八卦步法的
//   dodge。
//
// 平衡（content 值 = study 可習得的技能上限，見 feature/study.c::study_content：僅當
//   query_skill(t) < content[t] 時才 improve）：比照既有秘笈的尺度封頂，不臆造破壞平衡——
//   現存秘本以 wuming_manual(千年白猿失傳奇書) force45/parry35 為高標。六陰八卦譜定位為
//   lv50 boss 田由的鎮身頂級書(docs L232 列「頂級書」一系)，故取與之同列的上緣：
//     unarmed(六陰八卦掌)   45   —— 對齊 wuming 的 force45 高標(主修)。
//     dodge  (八卦步法)     40   —— 略低於主修(佐修)，仍守於 wuming/parry 一線之上半階。
//   literate 門檻 30(略高於 wuming 的 25)，契合「頂級書、譜訣艱深」的定位。
//   設 no_sell：田由視若性命、堂堂正正奪來的鎮身武學，玩家自當珍習，不宜變賣。

#include <ansi.h>

inherit ITEM;
inherit F_STUDY;

void create()
{
	set_name(HIW "六陰八卦譜" NOR,
		({ "sixyin manual", "bagua manual", "manual", "book",
		   "六陰八卦譜", "八卦譜" }) );
	set_weight(800);

	if( !clonep() ) {
		set("unit", "卷");
		set("value", 1);
		set("no_sell", 1);
		set("long",
			"一卷以陳年絹帛裝裱、邊角磨得起了毛的舊譜﹐封皮上『六陰\n"
			"八卦譜』五個古樸的篆字依稀可辨。翻開來﹐內裡以陰陽八卦立\n"
			"論﹐圖文並茂地繪註著一路陰柔詭譎的掌法——掌走兩儀、步循八\n"
			"卦﹐掌隨步轉、身似游龍﹐其間夾著一幅幅運掌、走步、拆招的\n"
			"人形圖訣﹐掌力的吞吐開闔、步法的方位轉換﹐無不勾畫得纖毫\n"
			"畢現。這便是那「六陰掌」田由畢生鑽研、視若性命的鎮身武學\n"
			"了。只是這譜訣以八卦立論﹐精微艱深﹐非有相當的文識﹐怕是\n"
			"連讀都讀不通。\n"
			"可用 study 研讀。\n");
		set("required/skill", ([
			"literate" : 30,
		]));
		set("content", ([
			"unarmed" : 45,    // 六陰八卦掌(掌法)，對齊 wuming force45 高標。
			"dodge"   : 40,    // 八卦步法(身法)，佐修。
		]));
	}

	setup();
}

// vim: set ts=4 sw=4 syntax=lpc
